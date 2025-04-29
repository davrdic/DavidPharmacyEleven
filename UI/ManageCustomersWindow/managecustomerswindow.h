#ifndef MANAGECUSTOMERSWINDOW_H
#define MANAGECUSTOMERSWINDOW_H

#include <QWidget>

namespace Ui {
class ManageCustomersWindow;
}

class ManageCustomersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageCustomersWindow(QWidget *parent = nullptr);
    ~ManageCustomersWindow();

private:
    Ui::ManageCustomersWindow *ui;
};

#endif // MANAGECUSTOMERSWINDOW_H
