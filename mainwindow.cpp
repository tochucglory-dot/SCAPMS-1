
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTabWidget>

#include "controller/ClinicManager.h"
#include "gui/PatientPanel.h"
#include "gui/AppointmentPanel.h"
#include "gui/QueuePanel.h"
#include "gui/SearchSortPanel.h"
#include "gui/ReportsPanel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    manager(new SCAPMS::ClinicManager()),
    tabWidget(new QTabWidget(this))
{
    ui->setupUi(this);

    setupPanels();

    setCentralWidget(tabWidget);
    setWindowTitle("Smart Clinic Appointment & Patient Management System");
    resize(1000, 700);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::setupPanels()
{
    tabWidget->addTab(new SCAPMS::PatientPanel(manager), "Patients");
    tabWidget->addTab(new SCAPMS::AppointmentPanel(manager), "Appointments");
    tabWidget->addTab(new SCAPMS::QueuePanel(manager), "Waiting Queue");
    tabWidget->addTab(new SCAPMS::SearchSortPanel(manager), "Search & Sort");
    tabWidget->addTab(new SCAPMS::ReportsPanel(manager), "Reports");
}
