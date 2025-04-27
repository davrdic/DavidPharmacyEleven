#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    // Display a success message
    QMessageBox::information(this, "Success", "Doctor added successfully!");

    // Log the message
    qDebug() << "Doctor added successfully!";
}


void MainWindow::on_editDoctorButton_clicked()
{

}

