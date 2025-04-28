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

void MainWindow::on_addDoctorButton_clicked()
{
    DoctorDTO newDoctor;
    newDoctor.name = ui->doctorNameLineEdit->text();

    if (doctorService->addDoctor(newDoctor)) {
        qDebug() << "Doctor added successfully!";
        loadDoctorsIntoComboBox();
    }
}

void MainWindow::on_editDoctorButton_clicked()
{
    DoctorDTO doctor;
    doctor.name = ui->doctorComboBox->currentText();
    doctor.id = ui->doctorComboBox->currentData().toInt(); // 👈 Get the hidden ID!

    bool ok;
    QString newDoctorName = QInputDialog::getText(this, tr("Edit Doctor"),
                                                  tr("New doctor name:"), QLineEdit::Normal,
                                                  doctor.name, &ok);
    if (ok && !newDoctorName.isEmpty()) {
        doctor.name = newDoctorName;

        if (doctorService->editDoctor(doctor)) {
            qDebug() << "Doctor updated successfully!";
            loadDoctorsIntoComboBox();
        } else {
            qDebug() << "Failed to update doctor.";
        }
    }
}

void MainWindow::loadDoctorsIntoComboBox()
{
    ui->doctorComboBox->clear();
    QList<DoctorDTO> doctors = doctorService->getDoctorsList();

    for (const DoctorDTO& doctor : doctors) {
        ui->doctorComboBox->addItem(doctor.name, doctor.id);
    }
}

