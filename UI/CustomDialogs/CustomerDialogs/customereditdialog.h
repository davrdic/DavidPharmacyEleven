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

/**
 * @brief The CustomerEditDialog class provides a dialog for editing or adding a customer.
 * It allows the user to set a customer's name and associated doctor.
 */
class CustomerEditDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new CustomerEditDialog for creating a new customer.
     * @param parent The parent QWidget.
     */
    explicit CustomerEditDialog(QWidget* parent = nullptr);

    /**
     * @brief Constructs a new CustomerEditDialog for editing an existing customer.
     * @param customer A QVariantMap containing customer data (name, doctor_id).
     * @param parent The parent QWidget.
     */
    explicit CustomerEditDialog(const QVariantMap& customer, QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~CustomerEditDialog();

    /**
     * @brief Gets the new or updated customer name from the dialog.
     * @return The customer's name as a QString.
     */
    QString getNewCustomerName() const;

    /**
     * @brief Gets the selected doctor ID from the dialog.
     * @return The doctor's ID as an integer.
     */
    int getNewDoctorId() const;

signals:
    /**
     * @brief Emitted when the user clicks the "Save" button.
     */
    void saveClicked();

    /**
     * @brief Emitted when the user clicks the "Cancel" button.
     */
    void cancelClicked();

    /**
     * @brief Emitted when the user clicks the "Delete" button (edit mode only).
     */
    void deleteClicked();

private:
    QLineEdit* customerNameLineEdit;
    QComboBox* doctorComboBox;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* deleteButton;

    DoctorService* doctorService;
    std::shared_ptr<IDoctorRepository> doctorRepository;
    std::vector<DoctorDTO> doctorList;

    bool isEditMode = false;
};

#endif // CUSTOMEREDITDIALOG_H
