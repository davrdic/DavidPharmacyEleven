#include <QDebug>

#include "managedoctorswindow.h"
#include "ui_managedoctorswindow.h"
#include "PostgresQSqlRepositories/doctorqsqlrepository.h"
#include "stringutils.h"

ManageDoctorsWindow::ManageDoctorsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManageDoctorsWindow)
{
    ui->setupUi(this);
    ui->doctorComboBox->setEditable(true);
    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    doctorRepository = std::make_shared<DoctorQSqlRepository>(database, username, password);

    doctorService = new DoctorService(doctorRepository);

    loadDoctorsIntoComboBox();
}

ManageDoctorsWindow::~ManageDoctorsWindow()
{
    delete ui;
    delete doctorService;
}

void ManageDoctorsWindow::on_backButton_clicked()
{
    emit backClicked();
}

void ManageDoctorsWindow::loadDoctorsIntoComboBox()
{
    ui->doctorComboBox->clear();
    std::vector<DoctorDTO> doctors = doctorService->getDoctorList();
    ui->doctorComboBox->addItem("", -1);
    // Add doctors to the combo box
    for (const DoctorDTO& doctor : doctors) {
        ui->doctorComboBox->addItem(StringUtils::toQString(doctor.name), doctor.id);
    }
}

void ManageDoctorsWindow::on_addDoctorButton_clicked()
{
    QString doctorName = ui->doctorNameLineEdit->text();
    DoctorDTO doctor;
    doctor.name = StringUtils::toStdString(doctorName);
    if (doctorService->addDoctor(doctor)) {
        qDebug() << "Doctor added successfully!";
        loadDoctorsIntoComboBox(); // Refresh the list
        ui->doctorNameLineEdit->clear();
    } else {
        qDebug() << "Failed to add doctor.";
    }
}

void ManageDoctorsWindow::on_editDoctorButton_clicked()
{
    // Get the currently selected doctor name from the combo box
    QString oldDoctorName = ui->doctorComboBox->currentText();
    int doctorId = ui->doctorComboBox->currentData().toInt();

    if (doctorId > 0 ) {
        DoctorEditDialog editDialog(oldDoctorName, this);

        // Show the dialog and check if the user clicked save, cancel, or delete
        connect(&editDialog, &DoctorEditDialog::saveClicked, this, [this, &editDialog]() {
            QString newDoctorName = editDialog.getNewDoctorName();
            int doctorId = ui->doctorComboBox->currentData().toInt();

            if (!newDoctorName.isEmpty()) {
                DoctorDTO doctor;
                doctor.name = StringUtils::toStdString(newDoctorName);
                doctor.id = doctorId;

                if (doctorService->updateDoctor(doctor)) {
                    qDebug() << "Doctor updated successfully!";
                    loadDoctorsIntoComboBox(); // Refresh the combo box
                    editDialog.accept();  // Close the dialog on successful save
                } else {
                    qDebug() << "Failed to update doctor.";
                }
            }
        });

        connect(&editDialog, &DoctorEditDialog::cancelClicked, &editDialog, &QDialog::reject);

        connect(&editDialog, &DoctorEditDialog::deleteClicked, this, [this, &editDialog]() {
            DoctorDTO doctor;
            doctor.id = ui->doctorComboBox->currentData().toInt();

            if (doctorService->deleteDoctor(doctor)) {
                qDebug() << "Doctor deleted successfully!";
                loadDoctorsIntoComboBox(); // Refresh the combo box
                editDialog.accept();  // Close the dialog on successful save
            } else {
                qDebug() << "Failed to delete doctor.";
            }
        });

        // Execute the dialog
        editDialog.exec();
    }
}

