#ifndef MANAGEDOCTORSWINDOW_H
#define MANAGEDOCTORSWINDOW_H

#include <QWidget>
#include <memory>
#include "doctorservice.h"
#include "doctoreditdialog.h"

namespace Ui {
class ManageDoctorsWindow;
}

/**
 * @brief The ManageDoctorsWindow class provides a GUI interface for managing doctors.
 * It allows adding, editing, and deleting doctors using a combo box and dialog windows.
 */
class ManageDoctorsWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for ManageDoctorsWindow.
     * @param parent Optional QWidget parent.
     */
    explicit ManageDoctorsWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for ManageDoctorsWindow.
     */
    ~ManageDoctorsWindow();

private slots:
    /**
     * @brief Slot triggered when the back button is clicked.
     */
    void on_backButton_clicked();

    /**
     * @brief Slot triggered when the "Add Doctor" button is clicked.
     */
    void on_addDoctorButton_clicked();

    /**
     * @brief Slot triggered when the "Edit Doctor" button is clicked.
     */
    void on_editDoctorButton_clicked();

    /**
     * @brief Loads the doctor list into the combo box.
     */
    void loadDoctorsIntoComboBox();

signals:
    /**
     * @brief Emitted when the user clicks the back button.
     */
    void backClicked();

private:
    Ui::ManageDoctorsWindow *ui;
    DoctorService *doctorService;
    std::shared_ptr<IDoctorRepository> doctorRepository;
};

#endif // MANAGEDOCTORSWINDOW_H
