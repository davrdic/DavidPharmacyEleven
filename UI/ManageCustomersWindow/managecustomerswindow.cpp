#include <QDebug>
#include <QStandardItem>
#include "managecustomerswindow.h"
#include "ui_managecustomerswindow.h"
#include "PostgresQSqlRepositories/customerqsqlrepository.h"
#include "stringutils.h"
#include "customeruiadapter.h"

ManageCustomersWindow::ManageCustomersWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManageCustomersWindow)
{
    ui->setupUi(this);
    ui->customerTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customerTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->customerTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->customerTableWidget->setAlternatingRowColors(true);
    ui->customerTableWidget->verticalHeader()->setVisible(false);

    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    customerRepository = std::make_shared<CustomerQSqlRepository>(database, username, password);
    customerService = new CustomerService(customerRepository);

    doctorRepository = std::make_shared<DoctorQSqlRepository>(database, username, password);
    doctorService = new DoctorService(doctorRepository);

    loadCustomersIntoTableWidget();
}

ManageCustomersWindow::~ManageCustomersWindow()
{
    delete ui;
    delete customerService;
    delete doctorService;
}

void ManageCustomersWindow::on_backButton_clicked()
{
    emit backClicked();
}

void ManageCustomersWindow::loadCustomersIntoTableWidget()
{
    std::vector<CustomerDTO> customers = customerService->getCustomerList();
    doctorList = doctorService->getDoctorList();

    std::unordered_map<int, QString> doctorIdToName;
    for (const DoctorDTO& doctor : doctorList) {
        doctorIdToName[doctor.id] = QString::fromStdString(doctor.name);
    }

    ui->customerTableWidget->setRowCount(customers.size());
    ui->customerTableWidget->setColumnCount(2);
    ui->customerTableWidget->setHorizontalHeaderLabels({"Customer", "Doctor"});

    for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(customers[i].name));
        QTableWidgetItem* doctorItem = new QTableWidgetItem();

        QString doctorName = "Unknown";
        auto it = doctorIdToName.find(customers[i].doctor_id);
        if (it != doctorIdToName.end()) {
            doctorName = it->second;
        }
        doctorItem->setText(doctorName);

        QVariantMap customerData;
        customerData["id"] = customers[i].id;
        customerData["name"] = QString::fromStdString(customers[i].name);
        customerData["doctor_id"] = customers[i].doctor_id;
        nameItem->setData(Qt::UserRole, customerData);

        ui->customerTableWidget->setItem(i, 0, nameItem);
        ui->customerTableWidget->setItem(i, 1, doctorItem);
    }
}

void ManageCustomersWindow::on_addCustomerButton_clicked()
{
    CustomerEditDialog editDialog(this);

    connect(&editDialog, &CustomerEditDialog::saveClicked, this, [this, &editDialog]() {
        QString newCustomerName = editDialog.getNewCustomerName();
        int newDoctorId = editDialog.getNewDoctorId();

        if (!newCustomerName.isEmpty() && newDoctorId > 0) {
            CustomerDTO customer = CustomerUIAdapter::fromVariantMap({}, newCustomerName, newDoctorId);

            if (customerService->addCustomer(customer)) {
                qDebug() << "Customer added successfully!";
                loadCustomersIntoTableWidget();
                editDialog.accept();
            } else {
                qDebug() << "Failed to add customer.";
            }
        }
    });

    connect(&editDialog, &CustomerEditDialog::cancelClicked, &editDialog, &QDialog::reject);
    editDialog.findChild<QPushButton*>("deleteButton")->hide();

    editDialog.exec();
}

void ManageCustomersWindow::on_editCustomerButton_clicked()
{
    int selectedRow = ui->customerTableWidget->currentRow();
    if (selectedRow < 0) {
        qDebug() << "No customer selected.";
        return;
    }

    QTableWidgetItem* nameItem = ui->customerTableWidget->item(selectedRow, 0);
    QVariantMap customerData = nameItem->data(Qt::UserRole).toMap();
    int customerId = customerData["id"].toInt();

    if (customerId > 0) {
        CustomerEditDialog editDialog(customerData, this);

        connect(&editDialog, &CustomerEditDialog::saveClicked, this, [this, &editDialog]() {
            QString newCustomerName = editDialog.getNewCustomerName();
            int newDoctorId = editDialog.getNewDoctorId();

            int selectedRow = ui->customerTableWidget->currentRow();
            QTableWidgetItem* nameItem = ui->customerTableWidget->item(selectedRow, 0);
            QVariantMap customerData = nameItem->data(Qt::UserRole).toMap();
            int customerId = customerData["id"].toInt();

            if (!newCustomerName.isEmpty()) {
                CustomerDTO customer = CustomerUIAdapter::fromVariantMap(customerData, newCustomerName, newDoctorId);

                if (customerService->updateCustomer(customer)) {
                    qDebug() << "Customer updated successfully!";
                    loadCustomersIntoTableWidget();
                    editDialog.accept();
                } else {
                    qDebug() << "Failed to update customer.";
                }
            }
        });

        connect(&editDialog, &CustomerEditDialog::cancelClicked, &editDialog, &QDialog::reject);

        connect(&editDialog, &CustomerEditDialog::deleteClicked, this, [this, &editDialog]() {
            int selectedRow = ui->customerTableWidget->currentRow();
            QTableWidgetItem* nameItem = ui->customerTableWidget->item(selectedRow, 0);
            QVariantMap customerData = nameItem->data(Qt::UserRole).toMap();
            CustomerDTO customer = CustomerUIAdapter::fromVariantMap(customerData);

            if (customerService->deleteCustomer(customer)) {
                qDebug() << "Customer deleted successfully!";
                loadCustomersIntoTableWidget();
                editDialog.accept();
            } else {
                qDebug() << "Failed to delete customer.";
            }
        });

        editDialog.exec();
    }
}
