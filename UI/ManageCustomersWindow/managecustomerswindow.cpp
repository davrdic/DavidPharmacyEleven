#include <QDebug>
#include <QStandardItem>

#include "managecustomerswindow.h"
#include "ui_managecustomerswindow.h"
#include "PostgresQSqlRepositories/customerqsqlrepository.h"
#include "stringutils.h"

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

    ui->customerTableWidget->setRowCount(customers.size()); // set row count appropriately
    ui->customerTableWidget->setColumnCount(2); // make sure the table has enough columns
    QStringList headers = {"Name", "Doctor"};
    ui->customerTableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(customers[i].name));
        QTableWidgetItem* doctorItem = new QTableWidgetItem();

        QString doctorName = "Unknown";
        auto it = doctorIdToName.find(customers[i].doctor_id);
        if (it != doctorIdToName.end()) {
            doctorName = it->second;
        }
        doctorItem->setText(doctorName);

        // Store the full CustomerDTO in the name column item using QVariantMap
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
    // QString customerName = ui->customerNameLineEdit->text();
    // CustomerDTO customer;
    // customer.name = StringUtils::toStdString(customerName);
    // if (customerService->addCustomer(customer)) {
    //     qDebug() << "Customer added successfully!";
    //     loadCustomersIntoTableWidget(); // Refresh the list
    //     ui->customerNameLineEdit->clear();
    // } else {
    //     qDebug() << "Failed to add customer.";
    // }

    // QTableWidgetItem* nameItem = ui->customerTableWidget->item(selectedRow, 0);
    // QVariantMap customerData = nameItem->data(Qt::UserRole).toMap();

    CustomerEditDialog editDialog(this);  // No customer data passed, it's a new customer

    // Connect save button for adding new customer
    connect(&editDialog, &CustomerEditDialog::saveClicked, this, [this, &editDialog]() {
        QString newCustomerName = editDialog.getNewCustomerName();
        int newDoctorId = editDialog.getNewDoctorId();

        if (!newCustomerName.isEmpty() && newDoctorId > 0) {
            CustomerDTO customer;
            customer.name = StringUtils::toStdString(newCustomerName);
            customer.doctor_id = newDoctorId;

            if (customerService->addCustomer(customer)) {
                qDebug() << "Customer added successfully!";
                loadCustomersIntoTableWidget();
                editDialog.accept();  // Close dialog
            } else {
                qDebug() << "Failed to add customer.";
            }
        }
    });

    // Cancel just closes the dialog
    connect(&editDialog, &CustomerEditDialog::cancelClicked, &editDialog, &QDialog::reject);

    // For Add mode, you can hide or disable the delete button if it's visible
    editDialog.findChild<QPushButton*>("deleteButton")->hide();  // Optional

    editDialog.exec();  // Show the dialog modally
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

    // Proceed if the customer ID is valid
    if (customerId > 0) {
        // Create and open the edit dialog, passing the customer data
        CustomerEditDialog editDialog(customerData, this);

        // Connect the save button to the saving logic
        connect(&editDialog, &CustomerEditDialog::saveClicked, this, [this, &editDialog]() {
            QString newCustomerName = editDialog.getNewCustomerName();
            int newDoctorId = editDialog.getNewDoctorId();

            int selectedRow = ui->customerTableWidget->currentRow();
            QTableWidgetItem* nameItem = ui->customerTableWidget->item(selectedRow, 0);
            QVariantMap customerData = nameItem->data(Qt::UserRole).toMap();
            int customerId = customerData["id"].toInt();

            if (!newCustomerName.isEmpty()) {
                CustomerDTO customer;
                customer.name = StringUtils::toStdString(newCustomerName);
                customer.id = customerId;
                customer.doctor_id = newDoctorId;

                if (customerService->updateCustomer(customer)) {
                    qDebug() << "Customer updated successfully!";
                    loadCustomersIntoTableWidget(); // Refresh the table too
                    editDialog.accept();  // Close the dialog on successful save
                } else {
                    qDebug() << "Failed to update customer.";
                }
            }
        });

        // Connect the cancel button to reject the dialog
        connect(&editDialog, &CustomerEditDialog::cancelClicked, &editDialog, &QDialog::reject);

        // Connect the delete button to delete the customer
        connect(&editDialog, &CustomerEditDialog::deleteClicked, this, [this, &editDialog]() {
            CustomerDTO customer;
            //customer.id = ui->customerComboBox->currentData(Qt::UserRole).toMap()["id"].toInt();

            if (customerService->deleteCustomer(customer)) {
                qDebug() << "Customer deleted successfully!";
                loadCustomersIntoTableWidget(); // Refresh the combo box
                editDialog.accept();  // Close the dialog on successful delete
            } else {
                qDebug() << "Failed to delete customer.";
            }
        });

        // Execute the dialog
        editDialog.exec();
    }
}

