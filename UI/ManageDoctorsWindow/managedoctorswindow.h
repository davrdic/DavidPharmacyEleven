#ifndef MANAGEDOCTORSWINDOW_H
#define MANAGEDOCTORSWINDOW_H

#include <QWidget>
#include "doctorservice.h"
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
    DoctorService *doctorService;
    DoctorEditDialog *doctorEditDialog;
    QStringList doctorList;
    std::shared_ptr<IDoctorRepository> doctorRepository;

signals:
    void backClicked();
};

#endif // MANAGEDOCTORSWINDOW_H
