#include "doctoreditdialog.h"
#include <QLabel>

DoctorEditDialog::DoctorEditDialog(const QString& doctorName, QWidget* parent)
    : QDialog(parent)
{
    doctorNameLineEdit = new QLineEdit(doctorName, this);

    saveButton = new QPushButton(tr("Save"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);
    deleteButton = new QPushButton(tr("Delete"), this);

    connect(saveButton, &QPushButton::clicked, this, &DoctorEditDialog::saveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &DoctorEditDialog::cancelClicked);
    connect(deleteButton, &QPushButton::clicked, this, &DoctorEditDialog::deleteClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("Enter the new doctor's name:")));
    mainLayout->addWidget(doctorNameLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Edit Doctor"));
}

QString DoctorEditDialog::getNewDoctorName() const {
    return doctorNameLineEdit->text();
}
