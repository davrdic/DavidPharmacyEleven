#ifndef MANAGECUSTOMERSWINDOW_H
#define MANAGECUSTOMERSWINDOW_H

#include <QWidget>
#include "customerservice.h"
#include "customereditdialog.h"

namespace Ui {
class ManageCustomersWindow;
}

class ManageCustomersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageCustomersWindow(QWidget *parent = nullptr);
    ~ManageCustomersWindow();

private slots:
    void on_backButton_clicked();

    void on_addCustomerButton_clicked();

private:
    Ui::ManageCustomersWindow *ui;
    CustomerService *customerService;
    std::shared_ptr<ICustomerRepository> customerRepository;

    void loadCustomersIntoComboBox();

signals:
    void backClicked();
};

#endif // MANAGECUSTOMERSWINDOW_H
