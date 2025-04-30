#include "managedoctorswindow.h"
#include "ui_managedoctorswindow.h"

#include "PostgresQSqlRepositories/doctorqsqlrepository.h"
#include "stringutils.h" // TODO - Refactor Utilize ui adaptor to convert DTO to UI Q objects.
#include <QDebug>

ManageDoctorsWindow::ManageDoctorsWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ManageDoctorsWindow)
{
    ui->setupUi(this);
    ui->doctorComboBox->setEditable(true);

    const char* database = std::getenv("database");
    const char* username = std::getenv("username");
    const char* password = std::getenv("password");

    doctorRepository = std::make_shared<DoctorQSqlRepository>(database, username, password);
    doctorService = new DoctorService(doctorRepository);

    loadDoctorsIntoComboBox();
}

ManageDoctorsWindow::~ManageDoctorsWindow()
{
    delete doctorService;
    delete ui;
}

void ManageDoctorsWindow::on_backButton_clicked()
{
    emit backClicked();
}

void ManageDoctorsWindow::loadDoctorsIntoComboBox()
{
    ui->doctorComboBox->clear();
    std::vector<DoctorDTO> doctors = doctorService->getDoctorList();

    ui->doctorComboBox->addItem("", -1); // Blank option

    for (const DoctorDTO& doctor : doctors) {
        ui->doctorComboBox->addItem(StringUtils::toQString(doctor.name), doctor.id);
    }
}
// TODO Move conversion logic (ui adaptor).
void ManageDoctorsWindow::on_addDoctorButton_clicked()
{
    QString doctorName = ui->doctorNameLineEdit->text();

    if (!doctorName.isEmpty()) {
        DoctorDTO doctor;
        doctor.name = StringUtils::toStdString(doctorName);

        if (doctorService->addDoctor(doctor)) {
            qDebug() << "Doctor added successfully!";
            loadDoctorsIntoComboBox();
            ui->doctorNameLineEdit->clear();
        } else {
            qDebug() << "Failed to add doctor.";
        }
    }
}
// TODO Move conversion and assignment logic. (ui adaptor)
void ManageDoctorsWindow::on_editDoctorButton_clicked()
{
    int doctorId = ui->doctorComboBox->currentData().toInt();
    QString oldDoctorName = ui->doctorComboBox->currentText();

    if (doctorId <= 0)
        return;

    DoctorEditDialog editDialog(oldDoctorName, this);

    connect(&editDialog, &DoctorEditDialog::saveClicked, this, [this, &editDialog]() {
        QString newDoctorName = editDialog.getNewDoctorName();
        int doctorId = ui->doctorComboBox->currentData().toInt();

        if (!newDoctorName.isEmpty()) {
            DoctorDTO doctor;
            doctor.id = doctorId;
            doctor.name = StringUtils::toStdString(newDoctorName);

            if (doctorService->updateDoctor(doctor)) {
                qDebug() << "Doctor updated successfully!";
                loadDoctorsIntoComboBox();
                editDialog.accept();
            } else {
                qDebug() << "Failed to update doctor.";
            }
        }
    });

    connect(&editDialog, &DoctorEditDialog::cancelClicked, &editDialog, &QDialog::reject);

    connect(&editDialog, &DoctorEditDialog::deleteClicked, this, [this, &editDialog]() {
        int doctorId = ui->doctorComboBox->currentData().toInt();

        DoctorDTO doctor;
        doctor.id = doctorId;

        if (doctorService->deleteDoctor(doctor)) {
            qDebug() << "Doctor deleted successfully!";
            loadDoctorsIntoComboBox();
            editDialog.accept();
        } else {
            qDebug() << "Failed to delete doctor.";
        }
    });

    editDialog.exec();
}
