#ifndef MANAGECUSTOMERSWINDOW_H
#define MANAGECUSTOMERSWINDOW_H

#include <QWidget>
#include "customerservice.h"
#include "customereditdialog.h"
#include "doctorservice.h"

namespace Ui {
class ManageCustomersWindow;
}

/**
 * @brief The ManageCustomersWindow class handles the UI and logic for managing customers.
 */
class ManageCustomersWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the ManageCustomersWindow.
     * @param parent The parent widget.
     */
    explicit ManageCustomersWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor. Cleans up allocated resources.
     */
    ~ManageCustomersWindow();

private slots:
    /**
     * @brief Slot triggered when the back button is clicked.
     * Emits the backClicked() signal.
     */
    void on_backButton_clicked();

    /**
     * @brief Slot triggered when the add customer button is clicked.
     * Opens a dialog to input a new customer and adds them if valid.
     */
    void on_addCustomerButton_clicked();

    /**
     * @brief Slot triggered when the edit customer button is clicked.
     * Opens a dialog to edit or delete the selected customer.
     */
    void on_editCustomerButton_clicked();

private:
    Ui::ManageCustomersWindow *ui;
    CustomerService *customerService;
    std::shared_ptr<ICustomerRepository> customerRepository;
    std::vector<CustomerDTO> customerList;

    /**
     * @brief Loads customers data into the table widget.
     */
    void loadCustomersIntoTableWidget();

signals:
    /**
     * @brief Emitted when the back button is clicked.
     */
    void backClicked();
};

#endif // MANAGECUSTOMERSWINDOW_H
