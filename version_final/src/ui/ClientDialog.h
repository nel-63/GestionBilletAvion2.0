#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>

namespace Ui { class ClientDialog; }

class ClientDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ClientDialog(QWidget *parent = nullptr, int clientId = -1);
    ~ClientDialog() override;

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::ClientDialog *ui;
    int m_clientId = -1;
    void loadClient();
};

#endif // CLIENTDIALOG_H