
#include "SearchSortPanel.h"

#include "../controller/ClinicManager.h"
#include "../model/PatientRecord.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

#include <string>

namespace SCAPMS {

SearchSortPanel::SearchSortPanel(ClinicManager* clinicManager,
                                 QWidget* parent)
    : QWidget(parent), manager(clinicManager)
{
    setupUI();
    refreshTable();
}

void SearchSortPanel::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Patient Search and Sorting");
    title->setStyleSheet("font-size: 20px; font-weight: bold;");

    searchInput = new QLineEdit;
    searchInput->setPlaceholderText("Enter patient ID or name");

    searchType = new QComboBox;
    searchType->addItem("Linear Search by ID");
    searchType->addItem("Binary Search by ID");
    searchType->addItem("Recursive Search by Name");

    searchButton = new QPushButton("Search");

    sortType = new QComboBox;
    sortType->addItem("Sort by Name");
    sortType->addItem("Sort by ID");
    sortType->addItem("Sort by Age");

    sortButton = new QPushButton("Sort");

    resultsTable = new QTableWidget;
    resultsTable->setColumnCount(4);

    resultsTable->setHorizontalHeaderLabels(
        {"Patient ID", "Name", "Age", "Category"}
        );

    resultsTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
        );

    statusLabel = new QLabel("Ready");

    QHBoxLayout* searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchType);
    searchLayout->addWidget(searchButton);

    QHBoxLayout* sortLayout = new QHBoxLayout;
    sortLayout->addWidget(sortType);
    sortLayout->addWidget(sortButton);

    mainLayout->addWidget(title);
    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(sortLayout);
    mainLayout->addWidget(resultsTable);
    mainLayout->addWidget(statusLabel);

    connect(searchButton, &QPushButton::clicked,
            this, &SearchSortPanel::searchPatients);

    connect(sortButton, &QPushButton::clicked,
            this, &SearchSortPanel::sortPatients);
}

void SearchSortPanel::searchPatients()
{
    QString searchText = searchInput->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::warning(
            this, "Search Error", "Please enter a search value."
            );
        return;
    }

    PatientRecord* patient = nullptr;

    if (searchType->currentIndex() == 0) {
        patient = manager->searchPatientByID(
            searchText.toStdString()
            );
    }
    else if (searchType->currentIndex() == 1) {
        patient = manager->binarySearchPatientByID(
            searchText.toStdString()
            );
    }
    else {
        patient = manager->searchPatientByName(
            searchText.toStdString()
            );
    }

    resultsTable->setRowCount(0);

    if (patient == nullptr) {
        statusLabel->setText("No matching patient found.");
        return;
    }

    resultsTable->insertRow(0);

    resultsTable->setItem(
        0, 0,
        new QTableWidgetItem(
            QString::fromStdString(patient->getPatientID())
            )
        );

    resultsTable->setItem(
        0, 1,
        new QTableWidgetItem(
            QString::fromStdString(patient->getName())
            )
        );

    resultsTable->setItem(
        0, 2,
        new QTableWidgetItem(
            QString::number(patient->getAge())
            )
        );

    resultsTable->setItem(
        0, 3,
        new QTableWidgetItem(
            QString::fromStdString(patient->getCategory())
            )
        );

    statusLabel->setText("Patient found.");
}

void SearchSortPanel::sortPatients()
{
    switch (sortType->currentIndex()) {

    case 0:
        manager->sortPatientsByName();
        break;

    case 1:
        manager->sortPatientsByID();
        break;

    case 2:
        manager->sortPatientsByAge();
        break;

    default:
        return;
    }

    refreshTable();

    statusLabel->setText("Patients sorted successfully.");
}

void SearchSortPanel::refreshTable()
{
    resultsTable->setRowCount(0);

    const auto& patients = manager->getDatabase().getPatients();

    for (const auto& patient : patients) {

        int row = resultsTable->rowCount();
        resultsTable->insertRow(row);

        resultsTable->setItem(
            row, 0,
            new QTableWidgetItem(
                QString::fromStdString(patient->getPatientID())
                )
            );

        resultsTable->setItem(
            row, 1,
            new QTableWidgetItem(
                QString::fromStdString(patient->getName())
                )
            );

        resultsTable->setItem(
            row, 2,
            new QTableWidgetItem(
                QString::number(patient->getAge())
                )
            );

        resultsTable->setItem(
            row, 3,
            new QTableWidgetItem(
                QString::fromStdString(patient->getCategory())
                )
            );
    }
}

}
