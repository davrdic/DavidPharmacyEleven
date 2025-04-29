#include "managecustomerswindow.h"
#include "ui_managecustomerswindow.h"

ManageCustomersWindow::ManageCustomersWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManageCustomersWindow)
{
    ui->setupUi(this);
}

ManageCustomersWindow::~ManageCustomersWindow()
{
    delete ui;
}
