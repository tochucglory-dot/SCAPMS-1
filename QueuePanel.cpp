
#include "QueuePanel.h"

#include "../controller/ClinicManager.h"
#include "../controller/ClinicDatabase.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>

#include <string>
#include <vector>

namespace SCAPMS {

QueuePanel::QueuePanel(ClinicManager* clinicManager, QWidget* parent)
    : QWidget(parent), manager(clinicManager)
{
    setupUI();
    refreshQueue();
}

void QueuePanel::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Waiting Queue");
    title->setStyleSheet(
        "font-size: 20px; font-weight: bold;"
    );

    patientIDInput = new QLineEdit;
    patientIDInput->setPlaceholderText("Enter Patient ID");

    addButton = new QPushButton("Add to Queue");
    nextButton = new QPushButton("Call Next Patient");

    waitingList = new QListWidget;
    countLabel = new QLabel("Patients waiting: 0");

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(nextButton);

    mainLayout->addWidget(title);
    mainLayout->addWidget(patientIDInput);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(countLabel);
    mainLayout->addWidget(waitingList);

    connect(addButton, &QPushButton::clicked,
            this, &QueuePanel::addPatientToQueue);

    connect(nextButton, &QPushButton::clicked,
            this, &QueuePanel::callNextPatient);
}

void QueuePanel::addPatientToQueue()
{
    QString patientID = patientIDInput->text().trimmed();

    if (patientID.isEmpty()) {
        QMessageBox::warning(this, "Input Error",
                             "Please enter a Patient ID.");
        return;
    }

    try {
        manager->addPatientToQueue(patientID.toStdString());

        QMessageBox::information(this, "Success",
                                 "Patient added to the waiting queue.");

        patientIDInput->clear();
        refreshQueue();

    } catch (const std::exception& error) {
        QMessageBox::warning(this, "Queue Error",
                             error.what());
    }
}

void QueuePanel::callNextPatient()
{
    std::string patientID =
        manager->getDatabase().getNextWaitingPatient();

    if (patientID.empty()) {
        QMessageBox::information(this, "Waiting Queue",
                                 "There are no patients waiting.");
        return;
    }

    QMessageBox::information(
        this,
        "Next Patient",
        "Call patient: " + QString::fromStdString(patientID)
    );

    refreshQueue();
}

void QueuePanel::refreshQueue()
{
    waitingList->clear();

    std::vector<std::string> patients =
        manager->getDatabase().getWaitingPatients();

    for (const std::string& patientID : patients) {
        waitingList->addItem(
            QString::fromStdString(patientID)
            );
    }

    countLabel->setText(
        "Patients waiting: " + QString::number(patients.size())
        );
}

}
