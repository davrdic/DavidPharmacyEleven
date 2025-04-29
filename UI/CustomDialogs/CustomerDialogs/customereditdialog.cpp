#include "customereditdialog.h"
#include <QLabel>

CustomerEditDialog::CustomerEditDialog(const QString& customerName, QWidget* parent)
    : QDialog(parent)
{
    customerNameLineEdit = new QLineEdit(customerName, this);

    saveButton = new QPushButton(tr("Save"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);
    deleteButton = new QPushButton(tr("Delete"), this);

    connect(saveButton, &QPushButton::clicked, this, &CustomerEditDialog::saveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CustomerEditDialog::cancelClicked);
    connect(deleteButton, &QPushButton::clicked, this, &CustomerEditDialog::deleteClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Enter the new customer's name:")));
    mainLayout->addWidget(customerNameLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Edit Customer"));
}

CustomerEditDialog::~CustomerEditDialog() {}

QString CustomerEditDialog::getNewCustomerName() const {
    return customerNameLineEdit->text();
}
