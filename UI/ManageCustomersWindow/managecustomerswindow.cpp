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
    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    customerRepository = std::make_shared<CustomerQSqlRepository>(database, username, password);

    customerService = new CustomerService(customerRepository);
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
    // ui->customerComboBox->clear();

    // // Add the default placeholder value to the combo box
    // ui->customerComboBox->addItem("           --Select Customer--", -1);  // -1 or any value that doesn't tie to an actual customer ID

    // std::vector<CustomerDTO> customers = customerService->getCustomerList();

    // // Add customers to the combo box
    // for (const CustomerDTO& customer : customers) {
    //     ui->customerComboBox->addItem(StringUtils::toQString(customer.name), customer.id);
    // }
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

