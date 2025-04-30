#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "managedoctorswindow.h"
#include "managecustomerswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class represents the main navigation window of the application.
 * It contains navigation to manage doctors and customers.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow.
     * @param parent Optional QWidget parent.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot triggered when the "Manage Doctors" button is clicked.
     * Switches to the ManageDoctorsWindow.
     */
    void on_manageDoctorsButton_clicked();

    /**
     * @brief Slot triggered when the "Back" button is clicked in any sub-window.
     * Returns to the main screen.
     */
    void on_BackToMainClicked();

    /**
     * @brief (Legacy/unused?) Slot for returning from doctors page to main. Kept for compatibility.
     */
    void on_doctorsBackButton_clicked();

    /**
     * @brief Slot triggered when the "Manage Customers" button is clicked.
     * Switches to the ManageCustomersWindow.
     */
    void on_manageCustomersButton_clicked();

private:
    Ui::MainWindow *ui;
    ManageDoctorsWindow *manageDoctorsWindow;
    ManageCustomersWindow *manageCustomersWindow;
};

#endif // MAINWINDOW_H
