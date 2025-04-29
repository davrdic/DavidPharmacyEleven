#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Dave's Pharmacy Management System");

    // Create Windows
    manageDoctorsWindow = new ManageDoctorsWindow(this);
    ui->stackedWidget->addWidget(manageDoctorsWindow);

    manageCustomersWindow = new ManageCustomersWindow(this);
    ui->stackedWidget->addWidget(manageCustomersWindow);

    // Create connections between windows
    connect(ui->manageDoctorsButton, &QPushButton::clicked, this, &MainWindow::on_manageDoctorsButton_clicked);
    connect(manageDoctorsWindow, &ManageDoctorsWindow::backClicked, this, &MainWindow::on_BackToMainClicked);

    connect(manageCustomersWindow, &ManageCustomersWindow::backClicked, this, &MainWindow::on_BackToMainClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_manageDoctorsButton_clicked()
{
    setWindowTitle("Manage Doctors");
    ui->stackedWidget->setCurrentWidget(manageDoctorsWindow);
}

void MainWindow::on_BackToMainClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("Dave's Pharmacy Management System");
}

void MainWindow::on_doctorsBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_manageCustomersButton_clicked()
{
    setWindowTitle("Manage Customers");
    ui->stackedWidget->setCurrentWidget(manageCustomersWindow);
}

