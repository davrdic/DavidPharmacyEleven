#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

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
}


void MainWindow::on_doctorsBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_addDoctorButton_clicked()
{
    QString doctorName = ui->doctorNameLineEdit->text();
    if (doctorService->addDoctor(doctorName)) {
        qDebug() << "Doctor added successfully!";
        populateDoctorsList(); // Refresh the list
    }
}

void MainWindow::populateDoctorsList() {
    // QList<QString> doctors = doctorService->getDoctorsList();
    // ui->doctorsListWidget->clear();
    // for (const QString& doctor : doctors) {
    //     ui->doctorsListWidget->addItem(doctor);
    // }
}

void MainWindow::on_editDoctorButton_clicked()
{

}

