#ifndef TICKETWIDGET_H
#define TICKETWIDGET_H

#include <QDialog>

namespace Ui { class TicketWidget; }

class TicketWidget : public QDialog
{
    Q_OBJECT
public:
    explicit TicketWidget(QWidget *parent = nullptr, int reservationId = -1);
    ~TicketWidget() override;

private slots:
    void on_btnClose_clicked();
    void on_btnPrint_clicked();

private:
    Ui::TicketWidget *ui;
    int m_reservationId = -1;
    void buildTicket();
};

#endif // TICKETWIDGET_H