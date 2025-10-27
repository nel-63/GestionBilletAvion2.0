#ifndef RESERVATIONDIALOG_H
#define RESERVATIONDIALOG_H

#include <QDialog>

namespace Ui { class ReservationDialog; }

class ReservationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReservationDialog(QWidget *parent = nullptr, int reservationId = -1);
    ~ReservationDialog() override;

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::ReservationDialog *ui;
    int m_reservationId = -1;
    void loadReservation();
    void populateCombos();
};

#endif // RESERVATIONDIALOG_H