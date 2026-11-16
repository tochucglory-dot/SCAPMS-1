
#include "ReportsPanel.h"

#include "../controller/ClinicManager.h"
#include "../controller/ClinicDatabase.h"
#include "../model/PatientRecord.h"
#include "../model/Appointment.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDateEdit>
#include <QHeaderView>

#include <map>
#include <set>
#include <string>

namespace SCAPMS {

ReportsPanel::ReportsPanel(ClinicManager* clinicManager,
                           QWidget* parent)
    : QWidget(parent), manager(clinicManager)
{
    setupUI();
}

void ReportsPanel::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Clinic Reports");
    title->setStyleSheet(
        "font-size: 20px; font-weight: bold;"
        );

    reportType = new QComboBox;
    reportType->addItem("Patient Category Distribution");
    reportType->addItem("Pending Appointments");
    reportType->addItem("Daily Appointment Report");

    reportDate = new QDateEdit;
    reportDate->setCalendarPopup(true);
    reportDate->setDate(QDate::currentDate());
    reportDate->setDisplayFormat("yyyy-MM-dd");

    generateButton = new QPushButton("Generate Report");

    reportTable = new QTableWidget;
    reportTable->setColumnCount(3);
    reportTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
        );

    summaryLabel = new QLabel("Select a report to begin.");

    QHBoxLayout* controls = new QHBoxLayout;
    controls->addWidget(reportType);
    controls->addWidget(reportDate);
    controls->addWidget(generateButton);

    mainLayout->addWidget(title);
    mainLayout->addLayout(controls);
    mainLayout->addWidget(reportTable);
    mainLayout->addWidget(summaryLabel);

    connect(generateButton, &QPushButton::clicked,
            this, &ReportsPanel::generateReport);
}

void ReportsPanel::generateReport()
{
    reportTable->setRowCount(0);

    switch (reportType->currentIndex()) {
    case 0:
        generateCategoryReport();
        break;

    case 1:
        generatePendingAppointmentsReport();
        break;

    case 2:
        generateDailyReport();
        break;
    }
}

void ReportsPanel::generateCategoryReport()
{
    reportTable->setColumnCount(2);
    reportTable->setHorizontalHeaderLabels(
        {"Patient Category", "Number of Patients"}
        );

    std::map<std::string, int> categories;

    const auto& patients = manager->getDatabase().getPatients();

    for (const auto& patient : patients) {
        categories[patient->getCategory()]++;
    }

    int total = 0;

    for (const auto& category : categories) {
        int row = reportTable->rowCount();
        reportTable->insertRow(row);

        reportTable->setItem(
            row, 0,
            new QTableWidgetItem(
                QString::fromStdString(category.first)
                )
            );

        reportTable->setItem(
            row, 1,
            new QTableWidgetItem(
                QString::number(category.second)
                )
            );

        total += category.second;
    }

    summaryLabel->setText(
        "Total registered patients: " + QString::number(total)
        );
}

void ReportsPanel::generatePendingAppointmentsReport()
{
    reportTable->setColumnCount(4);
    reportTable->setHorizontalHeaderLabels(
        {"Appointment ID", "Patient ID", "Date", "Time"}
        );

    const auto& appointments =
        manager->getDatabase().getAppointments();

    int count = 0;

    for (const auto& appointment : appointments) {

        if (appointment.getStatus() != "Pending")
            continue;

        int row = reportTable->rowCount();
        reportTable->insertRow(row);

        reportTable->setItem(
            row, 0,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getAppointmentID()
                    )
                )
            );

        reportTable->setItem(
            row, 1,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getPatientID()
                    )
                )
            );

        reportTable->setItem(
            row, 2,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getAppointmentDate()
                    )
                )
            );

        reportTable->setItem(
            row, 3,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getAppointmentTime()
                    )
                )
            );

        count++;
    }

    summaryLabel->setText(
        "Pending appointments: " + QString::number(count)
        );
}

void ReportsPanel::generateDailyReport()
{
    reportTable->setColumnCount(4);
    reportTable->setHorizontalHeaderLabels(
        {"Appointment ID", "Patient ID", "Time", "Status"}
        );

    std::string selectedDate =
        reportDate->date().toString("yyyy-MM-dd").toStdString();

    const auto& appointments =
        manager->getDatabase().getAppointments();

    int count = 0;

    for (const auto& appointment : appointments) {

        if (appointment.getAppointmentDate() != selectedDate)
            continue;

        int row = reportTable->rowCount();
        reportTable->insertRow(row);

        reportTable->setItem(
            row, 0,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getAppointmentID()
                    )
                )
            );

        reportTable->setItem(
            row, 1,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getPatientID()
                    )
                )
            );

        reportTable->setItem(
            row, 2,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getAppointmentTime()
                    )
                )
            );

        reportTable->setItem(
            row, 3,
            new QTableWidgetItem(
                QString::fromStdString(
                    appointment.getStatus()
                    )
                )
            );

        count++;
    }

    summaryLabel->setText(
        "Appointments on " +
        QString::fromStdString(selectedDate) +
        ": " + QString::number(count)
        );
}

}
