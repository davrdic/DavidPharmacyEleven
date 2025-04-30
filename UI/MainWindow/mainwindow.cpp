#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Dave's Pharmacy Management System");

    // Initialize and add sub-windows to the stacked widget
    manageDoctorsWindow = new ManageDoctorsWindow(this);
    ui->stackedWidget->addWidget(manageDoctorsWindow);

    manageCustomersWindow = new ManageCustomersWindow(this);
    ui->stackedWidget->addWidget(manageCustomersWindow);

    // Connect main buttons to their handlers
    connect(ui->manageDoctorsButton, &QPushButton::clicked, this, &MainWindow::on_manageDoctorsButton_clicked);
    connect(ui->manageCustomersButton, &QPushButton::clicked, this, &MainWindow::on_manageCustomersButton_clicked);

    // Connect back signals from sub-windows to return to main view
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

void MainWindow::on_manageCustomersButton_clicked()
{
    setWindowTitle("Manage Customers");
    ui->stackedWidget->setCurrentWidget(manageCustomersWindow);
}

void MainWindow::on_BackToMainClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("Dave's Pharmacy Management System");
}

void MainWindow::on_doctorsBackButton_clicked()
{
    // Appears redundant; included in case it's connected elsewhere.
    ui->stackedWidget->setCurrentIndex(0);
}
