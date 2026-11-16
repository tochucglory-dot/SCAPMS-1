#include "PatientPanel.h"

#include "../controller/ClinicManager.h"
#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>

#include <memory>

namespace SCAPMS {

PatientPanel::PatientPanel(ClinicManager* clinicManager, QWidget* parent)
    : QWidget(parent), manager(clinicManager)
{
    setupUI();
    refreshPatientTable();
}

void PatientPanel::setupUI()
{
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter patient name");

    contactInput = new QLineEdit(this);
    contactInput->setPlaceholderText("Enter phone number");

    ageInput = new QSpinBox(this);
    ageInput->setRange(0, 120);

    categoryInput = new QComboBox(this);
    categoryInput->addItems({"General", "Emergency", "Follow-Up"});

    patientTable = new QTableWidget(this);
    patientTable->setColumnCount(5);
    patientTable->setHorizontalHeaderLabels(
        {"Patient ID", "Name", "Age", "Contact", "Category"});

    patientTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    registerButton = new QPushButton("Register Patient", this);
    editButton = new QPushButton("Edit Patient", this);
    undoButton = new QPushButton("Undo Last Operation", this);
    deleteButton = new QPushButton("Delete Patient", this);
    refreshButton = new QPushButton("Refresh List", this);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Patient Name:", nameInput);
    formLayout->addRow("Contact:", contactInput);
    formLayout->addRow("Age:", ageInput);
    formLayout->addRow("Category:", categoryInput);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(refreshButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(patientTable);

    connect(registerButton, &QPushButton::clicked,
            this, [this]() { registerPatient(); });

    connect(editButton, &QPushButton::clicked,
            this, [this]() { editPatient(); });

    connect(undoButton, &QPushButton::clicked,
            this, [this]()
            {
                if (manager->getDatabase().undoLastOperation())
                {
                    QMessageBox::information(
                        this, "Undo Successful",
                        "The last registration has been undone.");

                    refreshPatientTable();
                }
                else
                {
                    QMessageBox::warning(
                        this, "Undo Failed",
                        "No supported operation is available to undo.");
                }
            });

    connect(deleteButton, &QPushButton::clicked,
            this, [this]() { deletePatient(); });

    connect(refreshButton, &QPushButton::clicked,
            this, [this]() { refreshPatientTable(); });
}

void PatientPanel::registerPatient()
{
    try
    {
        std::string name = nameInput->text().trimmed().toStdString();
        std::string contact = contactInput->text().trimmed().toStdString();
        int age = ageInput->value();

        if (name.empty() || contact.empty())
        {
            QMessageBox::warning(this, "Invalid Input",
                                 "Please enter the patient's name and contact.");
            return;
        }

        std::string id = "PAT" +
            std::to_string(manager->getDatabase().getPatients().size() + 1);

        std::unique_ptr<PatientRecord> patient;

        QString category = categoryInput->currentText();

        if (category == "General")
        {
            patient = std::make_unique<GeneralPatient>(
                id, name, age, contact);
        }
        else if (category == "Emergency")
        {
            patient = std::make_unique<EmergencyPatient>(
                id, name, age, contact);
        }
        else
        {
            patient = std::make_unique<FollowUpPatient>(
                id, name, age, contact);
        }

        manager->registerPatient(std::move(patient));

        QMessageBox::information(this, "Success",
                                 "Patient registered successfully.");

        nameInput->clear();
        contactInput->clear();
        ageInput->setValue(0);

        refreshPatientTable();
    }
    catch (const std::exception& error)
    {
        QMessageBox::critical(this, "Registration Error", error.what());
    }
}
void PatientPanel::editPatient()
{
    int row = patientTable->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this, "Selection Required",
                             "Please select a patient to edit.");
        return;
    }

    QString id = patientTable->item(row, 0)->text();

    PatientRecord* patient =
        manager->getDatabase().findPatientByID(id.toStdString());

    if (patient == nullptr)
    {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    QString name = nameInput->text().trimmed();
    QString contact = contactInput->text().trimmed();
    int age = ageInput->value();

    if (name.isEmpty() || contact.isEmpty())
    {
        QMessageBox::warning(this, "Invalid Input",
                             "Enter the patient's name and contact.");
        return;
    }

    if (age <= 0)
    {
        QMessageBox::warning(this, "Invalid Age",
                             "Patient age must be greater than zero.");
        return;
    }
manager->getDatabase().recordPatientEdit(*patient);

    patient->setName(name.toStdString());
    patient->setAge(age);
    patient->setContact(contact.toStdString());

    QMessageBox::information(this, "Success",
                             "Patient details updated successfully.");

    nameInput->clear();
    contactInput->clear();
    ageInput->setValue(0);

    refreshPatientTable();
}
void PatientPanel::deletePatient()
{
    int row = patientTable->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this, "Selection Required",
                             "Please select a patient to delete.");
        return;
    }

    QString id = patientTable->item(row, 0)->text();

    if (manager->deletePatient(id.toStdString()))
    {
        QMessageBox::information(this, "Success",
                                 "Patient deleted successfully.");
        refreshPatientTable();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Patient not found.");
    }
}

void PatientPanel::refreshPatientTable()
{
    patientTable->setRowCount(0);

    const auto& patients = manager->getDatabase().getPatients();

    for (const auto& patient : patients)
    {
        int row = patientTable->rowCount();
        patientTable->insertRow(row);

        patientTable->setItem(row, 0,
            new QTableWidgetItem(
                QString::fromStdString(patient->getPatientID())));

        patientTable->setItem(row, 1,
            new QTableWidgetItem(
                QString::fromStdString(patient->getName())));

        patientTable->setItem(row, 2,
            new QTableWidgetItem(QString::number(patient->getAge())));

        patientTable->setItem(row, 3,
            new QTableWidgetItem(
                QString::fromStdString(patient->getContact())));

        patientTable->setItem(row, 4,
            new QTableWidgetItem(
                QString::fromStdString(patient->getCategory())));
    }
}

}