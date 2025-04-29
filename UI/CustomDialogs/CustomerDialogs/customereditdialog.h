#ifndef CUSTOMEREDITDIALOG_H
#define CUSTOMEREDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

#include "doctorservice.h"
#include "PostgresQSqlRepositories/doctorqsqlrepository.h"
#include "doctordto.h"
#include "customerdto.h"

class CustomerEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerEditDialog(const QVariantMap& customer, QWidget* parent = nullptr);
    ~CustomerEditDialog();

    QString getNewCustomerName() const;
    int getNewDoctorId() const;

signals:
    void saveClicked();
    void cancelClicked();
    void deleteClicked();

private:
    QLineEdit* customerNameLineEdit;
    QComboBox* doctorComboBox;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* deleteButton;
    DoctorService *doctorService;
    std::vector<DoctorDTO> doctorList;
    std::shared_ptr<IDoctorRepository> doctorRepository;
};

#endif // CUSTOMEREDITDIALOG_H
