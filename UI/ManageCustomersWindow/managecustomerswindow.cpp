#include <QDebug>

#include "managecustomerswindow.h"
#include "ui_managecustomerswindow.h"
#include "PostgresQSqlRepositories/customerqsqlrepository.h"
#include "stringutils.h"

ManageCustomersWindow::ManageCustomersWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManageCustomersWindow)
{
    ui->setupUi(this);
    ui->customerComboBox->setEditable(true);
    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    customerRepository = std::make_shared<CustomerQSqlRepository>(database, username, password);

    customerService = new CustomerService(customerRepository);

    loadCustomersIntoComboBox();
}

ManageCustomersWindow::~ManageCustomersWindow()
{
    delete ui;
    delete customerService;
}

void ManageCustomersWindow::on_backButton_clicked()
{
    emit backClicked();
}


void ManageCustomersWindow::loadCustomersIntoComboBox()
{
    ui->customerComboBox->clear();
    std::vector<CustomerDTO> customers = customerService->getCustomerList();
    ui->customerComboBox->addItem("", -1);
    for (const CustomerDTO& customer : customers) {
        QVariantMap customerData;
        customerData["id"] = customer.id;
        customerData["name"] = StringUtils::toQString(customer.name);
        customerData["doctor_id"] = customer.doctor_id;

        qDebug() << "doctor_id:" << customerData["doctor_id"];

        // Add name as display text, and store the map explicitly at Qt::UserRole
        ui->customerComboBox->addItem(customerData["name"].toString());
        int index = ui->customerComboBox->count() - 1;
        ui->customerComboBox->setItemData(index, customerData, Qt::UserRole);
    }
}

void ManageCustomersWindow::on_addCustomerButton_clicked()
{
    QString customerName = ui->customerNameLineEdit->text();
    CustomerDTO customer;
    customer.name = StringUtils::toStdString(customerName);
    if (customerService->addCustomer(customer)) {
        qDebug() << "Customer added successfully!";
        loadCustomersIntoComboBox(); // Refresh the list
        ui->customerNameLineEdit->clear();
    } else {
        qDebug() << "Failed to add customer.";
    }
}


void ManageCustomersWindow::on_editCustomerButton_clicked()
{
    // Get the customer data stored at Qt::UserRole
    QVariantMap customerData = ui->customerComboBox->currentData(Qt::UserRole).toMap();

    // Extract the customer ID and doctor ID from the customer data map
    int customerId = customerData["id"].toInt();
    int oldDoctorId = customerData["doctor_id"].toInt();

    qDebug() << "oldDoctorId:" << oldDoctorId;

    // Proceed if the customer ID is valid
    if (customerId > 0) {
        // Create and open the edit dialog, passing the customer data
        CustomerEditDialog editDialog(customerData, this);

        // Connect the save button to the saving logic
        connect(&editDialog, &CustomerEditDialog::saveClicked, this, [this, &editDialog]() {
            QString newCustomerName = editDialog.getNewCustomerName();
            int newDoctorId = editDialog.getNewDoctorId();
            int customerId = ui->customerComboBox->currentData(Qt::UserRole).toMap()["id"].toInt();

            if (!newCustomerName.isEmpty()) {
                CustomerDTO customer;
                customer.name = StringUtils::toStdString(newCustomerName);
                customer.id = customerId;
                customer.doctor_id = newDoctorId;

                if (customerService->updateCustomer(customer)) {
                    qDebug() << "Customer updated successfully!";
                    loadCustomersIntoComboBox(); // Refresh the combo box
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
            customer.id = ui->customerComboBox->currentData(Qt::UserRole).toMap()["id"].toInt();

            if (customerService->deleteCustomer(customer)) {
                qDebug() << "Customer deleted successfully!";
                loadCustomersIntoComboBox(); // Refresh the combo box
                editDialog.accept();  // Close the dialog on successful delete
            } else {
                qDebug() << "Failed to delete customer.";
            }
        });

        // Execute the dialog
        editDialog.exec();
    }
}

