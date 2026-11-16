#ifndef PATIENTPANEL_H
#define PATIENTPANEL_H

#include <QWidget>

class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;
class QTableWidget;

namespace SCAPMS {

class ClinicManager;

class PatientPanel : public QWidget
{
    Q_OBJECT

private:
    ClinicManager* manager;

    QLineEdit* nameInput;
    QLineEdit* contactInput;
    QSpinBox* ageInput;
    QComboBox* categoryInput;
    QTableWidget* patientTable;

    QPushButton* registerButton;
    QPushButton* editButton;
    QPushButton* undoButton;
    QPushButton* deleteButton;
    QPushButton* refreshButton;

public:
    explicit PatientPanel(ClinicManager* clinicManager,
                          QWidget* parent = nullptr);

private:
    void setupUI();
    void registerPatient();
    void editPatient();
    void deletePatient();
    void refreshPatientTable();

};


}

#endif
