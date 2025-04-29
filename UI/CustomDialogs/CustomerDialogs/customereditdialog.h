#ifndef CUSTOMEREDITDIALOG_H
#define CUSTOMEREDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CustomerEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerEditDialog(const QString& customerName, QWidget* parent = nullptr);

    QString getNewCustomerName() const;

signals:
    void saveClicked();
    void cancelClicked();
    void deleteClicked();

private:
    QLineEdit* customerNameLineEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* deleteButton;
};

#endif // CUSTOMEREDITDIALOG_H
