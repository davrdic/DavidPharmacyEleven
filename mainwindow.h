#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "doctorbusinesslayer.h"
#include "doctoreditdialog.h"
#include "managedoctorswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_manageDoctorsButton_clicked();

    void on_doctorsBackButton_clicked();

    void on_addDoctorButton_clicked();

    void on_editDoctorButton_clicked();

    void loadDoctorsIntoComboBox();

    void on_manageDoctorsBackClicked();

private:
    Ui::MainWindow *ui;
    DoctorService* doctorService;
    DoctorBusinessLayer* doctorBusinessLayer;
    DoctorEditDialog* doctorEditDialog;
    QStringList doctorList;
    ManageDoctorsWindow* manageDoctorsWindow;
};
#endif // MAINWINDOW_H
