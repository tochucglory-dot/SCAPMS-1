#ifndef QUEUEPANEL_H
#define QUEUEPANEL_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QListWidget;
class QLabel;

namespace SCAPMS {

class ClinicManager;

class QueuePanel : public QWidget
{
    Q_OBJECT

private:
    ClinicManager* manager;

    QLineEdit* patientIDInput;
    QPushButton* addButton;
    QPushButton* nextButton;
    QListWidget* waitingList;
    QLabel* countLabel;

public:
    explicit QueuePanel(ClinicManager* clinicManager,
                        QWidget* parent = nullptr);

private:
    void setupUI();
    void addPatientToQueue();
    void callNextPatient();
    void refreshQueue();
};

}

#endif
