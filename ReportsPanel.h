
#ifndef REPORTSPANEL_H
#define REPORTSPANEL_H

#include <QWidget>

class QComboBox;
class QPushButton;
class QTableWidget;
class QLabel;
class QDateEdit;

namespace SCAPMS {

class ClinicManager;

class ReportsPanel : public QWidget
{
    Q_OBJECT

private:
    ClinicManager* manager;

    QComboBox* reportType;
    QDateEdit* reportDate;
    QPushButton* generateButton;
    QTableWidget* reportTable;
    QLabel* summaryLabel;

public:
    explicit ReportsPanel(ClinicManager* clinicManager,
                          QWidget* parent = nullptr);

private:
    void setupUI();
    void generateReport();
    void generateCategoryReport();
    void generatePendingAppointmentsReport();
    void generateDailyReport();
};

}

#endif
