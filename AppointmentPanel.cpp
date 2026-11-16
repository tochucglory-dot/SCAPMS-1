#include "AppointmentPanel.h"

#include "../controller/ClinicManager.h"
#include "../model/Appointment.h"
#include "../utils/IDGenerator.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>

#include <exception>

namespace SCAPMS {

AppointmentPanel::AppointmentPanel(
    ClinicManager* clinicManager, QWidget* parent)
    : QWidget(parent), manager(clinicManager)
{
    setupUI();
    refreshAppointmentTable();
}

void AppointmentPanel::setupUI()
{
    patientIDInput = new QLineEdit(this);
    patientIDInput->setPlaceholderText("Enter patient ID");

    reasonInput = new QLineEdit(this);
    reasonInput->setPlaceholderText("Enter appointment reason");

    dateInput = new QDateEdit(QDate::currentDate(), this);
    dateInput->setCalendarPopup(true);
    dateInput->setMinimumDate(QDate::currentDate());

    timeInput = new QTimeEdit(QTime::currentTime(), this);
    timeInput->setDisplayFormat("HH:mm");

    appointmentTable = new QTableWidget(this);
    appointmentTable->setColumnCount(6);
    appointmentTable->setHorizontalHeaderLabels(
        {"Appointment ID", "Patient ID", "Date",
         "Time", "Reason", "Status"});

    appointmentTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    scheduleButton = new QPushButton("Schedule Appointment", this);
    cancelButton = new QPushButton("Cancel Appointment", this);
    refreshButton = new QPushButton("Refresh List", this);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Patient ID:", patientIDInput);
    formLayout->addRow("Reason:", reasonInput);
    formLayout->addRow("Appointment Date:", dateInput);
    formLayout->addRow("Appointment Time:", timeInput);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(scheduleButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(refreshButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(appointmentTable);

    connect(scheduleButton, &QPushButton::clicked,
            this, [this]() { scheduleAppointment(); });

    connect(cancelButton, &QPushButton::clicked,
            this, [this]() { cancelAppointment(); });

    connect(refreshButton, &QPushButton::clicked,
            this, [this]() { refreshAppointmentTable(); });
}

void AppointmentPanel::scheduleAppointment()
{
    try
    {
        std::string patientID =
            patientIDInput->text().trimmed().toStdString();

        std::string reason =
            reasonInput->text().trimmed().toStdString();

        if (patientID.empty() || reason.empty())
        {
            QMessageBox::warning(
                this, "Missing Information",
                "Enter the patient ID and appointment reason.");
            return;
        }

        if (!manager->searchPatientByID(patientID))
        {
            QMessageBox::warning(
                this, "Patient Not Found",
                "Register the patient before scheduling an appointment.");
            return;
        }

        std::string appointmentID =
            IDGenerator::generateAppointmentID();

        Appointment appointment(
            appointmentID,
            patientID,
            dateInput->date().toString("yyyy-MM-dd").toStdString(),
            timeInput->time().toString("HH:mm").toStdString(),
            reason);

        manager->scheduleAppointment(appointment);

        QMessageBox::information(
            this, "Success", "Appointment scheduled successfully.");

        patientIDInput->clear();
        reasonInput->clear();

        refreshAppointmentTable();
    }
    catch (const std::exception& error)
    {
        QMessageBox::critical(
            this, "Appointment Error", error.what());
    }
}

void AppointmentPanel::cancelAppointment()
{
    int row = appointmentTable->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(
            this, "Selection Required",
            "Select an appointment to cancel.");
        return;
    }

    QString appointmentID =
        appointmentTable->item(row, 0)->text();

    if (manager->cancelAppointment(appointmentID.toStdString()))
    {
        QMessageBox::information(
            this, "Success", "Appointment cancelled.");

        refreshAppointmentTable();
    }
    else
    {
        QMessageBox::warning(
            this, "Error", "Appointment not found.");
    }
}

void AppointmentPanel::refreshAppointmentTable()
{
    appointmentTable->setRowCount(0);

    const auto& appointments =
        manager->getDatabase().getAppointments();

    for (const auto& appointment : appointments)
    {
        int row = appointmentTable->rowCount();
        appointmentTable->insertRow(row);

        appointmentTable->setItem(row, 0,
                                  new QTableWidgetItem(
                                      QString::fromStdString(
                                          appointment.getAppointmentID())));

        appointmentTable->setItem(row, 1,
                                  new QTableWidgetItem(
                                      QString::fromStdString(
                                          appointment.getPatientID())));

        appointmentTable->setItem(row, 2,
                                  new QTableWidgetItem(
                                      QString::fromStdString(
                                          appointment.getAppointmentDate())));

        appointmentTable->setItem(row, 3,
                                  new QTableWidgetItem(
                                      QString::fromStdString(
                                          appointment.getAppointmentTime())));

        appointmentTable->setItem(row, 4,
                                  new QTableWidgetItem(
                                      QString::fromStdString(
                                          appointment.getReason())));

        appointmentTable->setItem(row, 5,
                                  new QTableWidgetItem(
                                      QString::fromStdString(
                                          appointment.getStatus())));
    }
}

}