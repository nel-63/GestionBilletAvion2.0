#ifndef VOLDIALOG_H
#define VOLDIALOG_H

#include <QDialog>

namespace Ui { class VolDialog; }

class VolDialog : public QDialog
{
    Q_OBJECT
public:
    explicit VolDialog(QWidget *parent = nullptr, int volId = -1);
    ~VolDialog() override;

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::VolDialog *ui;
    int m_volId = -1;
    void loadVol();
};

#endif // VOLDIALOG_H