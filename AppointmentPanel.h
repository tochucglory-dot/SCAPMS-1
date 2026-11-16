#ifndef APPOINTMENTPANEL_H
#define APPOINTMENTPANEL_H

#include <QWidget>

class QLineEdit;
class QDateEdit;
class QTimeEdit;
class QComboBox;
class QPushButton;
class QTableWidget;

namespace SCAPMS {

class ClinicManager;

class AppointmentPanel : public QWidget
{
    Q_OBJECT

private:
    ClinicManager* manager;

    QLineEdit* patientIDInput;
    QLineEdit* reasonInput;
    QDateEdit* dateInput;
    QTimeEdit* timeInput;
    QTableWidget* appointmentTable;

    QPushButton* scheduleButton;
    QPushButton* cancelButton;
    QPushButton* refreshButton;

public:
    explicit AppointmentPanel(ClinicManager* clinicManager,
                              QWidget* parent = nullptr);

private:
    void setupUI();
    void scheduleAppointment();
    void cancelAppointment();
    void refreshAppointmentTable();
};

}

#endif
