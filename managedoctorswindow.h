#ifndef MANAGEDOCTORSWINDOW_H
#define MANAGEDOCTORSWINDOW_H

#include <QWidget>
#include "doctorbusinesslayer.h"
#include "doctoreditdialog.h"

namespace Ui {
class ManageDoctorsWindow;
}

class ManageDoctorsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageDoctorsWindow(QWidget *parent = nullptr);
    ~ManageDoctorsWindow();

private slots:
    void on_backButton_clicked();

    void on_addDoctorButton_clicked();

    void on_editDoctorButton_clicked();

    void loadDoctorsIntoComboBox();

private:
    Ui::ManageDoctorsWindow *ui;
    DoctorService* doctorService;
    DoctorBusinessLayer* doctorBusinessLayer;
    DoctorEditDialog* doctorEditDialog;
    QStringList doctorList;

signals:
    void backClicked();
};

#endif // MANAGEDOCTORSWINDOW_H
