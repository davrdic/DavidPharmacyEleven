#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "doctor.h"
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    doctorService = new DoctorService(database, username, password);
    doctorBusinessLayer = new DoctorBusinessLayer(doctorService);
    connect(ui->manageDoctorsButton, &QPushButton::clicked, this, &MainWindow::on_manageDoctorsButton_clicked);
    connect(ui->doctorsBackButton, &QPushButton::clicked, this, &MainWindow::on_doctorsBackButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_manageDoctorsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    loadDoctorsIntoComboBox();
}

void MainWindow::on_doctorsBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_addDoctorButton_clicked() {
    QString doctorName = ui->doctorNameLineEdit->text();
    DoctorDTO doctor;
    doctor.name = doctorName;
    if (doctorBusinessLayer->addDoctor(doctor)) {
        qDebug() << "Doctor added successfully!";
        loadDoctorsIntoComboBox(); // Refresh the list
    } else {
        qDebug() << "Failed to add doctor.";
    }
}

void MainWindow::on_editDoctorButton_clicked() {
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
                doctor.name = newDoctorName;
                doctor.id = doctorId;

                if (doctorBusinessLayer->editDoctor(doctor)) {
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

            if (doctorBusinessLayer->deleteDoctor(doctor)) {
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

void MainWindow::loadDoctorsIntoComboBox()
{
    ui->doctorComboBox->clear();

    // Add the default placeholder value to the combo box
    ui->doctorComboBox->addItem("Select Doctor", -1);  // -1 or any value that doesn't tie to an actual doctor ID

    QList<DoctorDTO> doctors = doctorBusinessLayer->getDoctorList();

    // Add doctors to the combo box
    for (const DoctorDTO& doctor : doctors) {
        ui->doctorComboBox->addItem(doctor.name, doctor.id);
    }
}
