
#ifndef SEARCHSORTPANEL_H
#define SEARCHSORTPANEL_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QComboBox;
class QTableWidget;
class QLabel;

namespace SCAPMS {

class ClinicManager;

class SearchSortPanel : public QWidget
{
    Q_OBJECT

private:
    ClinicManager* manager;

    QLineEdit* searchInput;
    QComboBox* searchType;
    QComboBox* sortType;
    QPushButton* searchButton;
    QPushButton* sortButton;
    QTableWidget* resultsTable;
    QLabel* statusLabel;

public:
    explicit SearchSortPanel(ClinicManager* clinicManager,
                             QWidget* parent = nullptr);

private:
    void setupUI();
    void searchPatients();
    void sortPatients();
    void refreshTable();
};

}

#endif
