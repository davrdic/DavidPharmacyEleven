#ifndef DOCTOREDITDIALOG_H
#define DOCTOREDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DoctorEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorEditDialog(const QString& doctorName, QWidget* parent = nullptr);
    ~DoctorEditDialog();

    QString getNewDoctorName() const;

signals:
    void saveClicked();
    void cancelClicked();
    void deleteClicked();

private:
    QLineEdit* doctorNameLineEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* deleteButton;
};

#endif // DOCTOREDITDIALOG_H
