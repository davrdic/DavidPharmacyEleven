#include "customereditdialog.h"
#include <QLabel>
#include <QDebug>
#include "stringutils.h"

// Constructor for editing an existing customer
CustomerEditDialog::CustomerEditDialog(const QVariantMap& customer, QWidget* parent)
    : QDialog(parent), isEditMode(true)
{
    customerNameLineEdit = new QLineEdit(customer["name"].toString(), this);

    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    doctorRepository = std::make_shared<DoctorQSqlRepository>(database, username, password);
    doctorService = new DoctorService(doctorRepository);
    doctorComboBox = new QComboBox(this);

    doctorList = doctorService->getDoctorList();
    for (const DoctorDTO& doctor : doctorList) {
        doctorComboBox->addItem(StringUtils::toQString(doctor.name), doctor.id);
    }

    int oldDoctorId = customer["doctor_id"].toInt();
    int index = doctorComboBox->findData(oldDoctorId);
    if (index != -1) {
        doctorComboBox->setCurrentIndex(index);
    }

    saveButton = new QPushButton(tr("Save"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);
    deleteButton = new QPushButton(tr("Delete"), this);

    connect(saveButton, &QPushButton::clicked, this, &CustomerEditDialog::saveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CustomerEditDialog::cancelClicked);
    connect(deleteButton, &QPushButton::clicked, this, &CustomerEditDialog::deleteClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Enter the new customer's name:")));
    mainLayout->addWidget(customerNameLineEdit);
    mainLayout->addWidget(new QLabel(tr("Select Doctor:")));
    mainLayout->addWidget(doctorComboBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Edit Customer"));
}

// Constructor for adding a new customer
CustomerEditDialog::CustomerEditDialog(QWidget* parent)
    : QDialog(parent), isEditMode(false)
{
    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    doctorRepository = std::make_shared<DoctorQSqlRepository>(database, username, password);
    doctorService = new DoctorService(doctorRepository);
    doctorList = doctorService->getDoctorList();

    customerNameLineEdit = new QLineEdit(this);
    doctorComboBox = new QComboBox(this);
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);
    deleteButton = new QPushButton("Delete", this);
    deleteButton->setObjectName("deleteButton");

    for (const DoctorDTO& doctor : doctorList) {
        doctorComboBox->addItem(QString::fromStdString(doctor.name), doctor.id);
    }

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel(tr("Enter the new customer's name:")));
    mainLayout->addWidget(customerNameLineEdit);
    mainLayout->addWidget(doctorComboBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);
    mainLayout->addLayout(buttonLayout);
    setWindowTitle(tr("Add Customer"));

    // Hide the delete button in add mode
    deleteButton->hide();

    connect(saveButton, &QPushButton::clicked, this, &CustomerEditDialog::saveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CustomerEditDialog::cancelClicked);
}

CustomerEditDialog::~CustomerEditDialog() {}

QString CustomerEditDialog::getNewCustomerName() const {
    return customerNameLineEdit->text();
}

int CustomerEditDialog::getNewDoctorId() const {
    return doctorComboBox->currentData().toInt();
}
