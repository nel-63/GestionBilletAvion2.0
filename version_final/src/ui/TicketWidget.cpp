#include "TicketWidget.h"
#include "ui_TicketWidget.h"
#include "../dao/ReservationFonction.h"
#include "../dao/ClientFonction.h"
#include "../dao/VolFonction.h"
#include <QPrinter>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QDir>

TicketWidget::TicketWidget(QWidget *parent, int reservationId)
    : QDialog(parent), ui(new Ui::TicketWidget), m_reservationId(reservationId)
{
    ui->setupUi(this);
    connect(ui->btnClose, &QPushButton::clicked, this, &TicketWidget::on_btnClose_clicked);
    connect(ui->btnPrint, &QPushButton::clicked, this, &TicketWidget::on_btnPrint_clicked);
    buildTicket();
}

TicketWidget::~TicketWidget() { delete ui; }

void TicketWidget::buildTicket()
{
    if (m_reservationId == -1) { ui->textTicket->setPlainText("Réservation non trouvée."); return; }
    auto r = ReservationFonction::byId(m_reservationId);
    if (r.id == -1) { ui->textTicket->setPlainText("Réservation non trouvée."); return; }

    auto c = ClientFonction::byId(r.clientId);
    auto v = VolFonction::byId(r.volId);

    QString html;
    html += "<h2>Billet électronique - Compagnie Aérienne</h2>";
    html += QString("<b>Passager:</b> %1 %2<br>").arg(c.nom).arg(c.prenom);
    html += QString("<b>Email:</b> %1<br>").arg(c.email);
    html += "<hr>";
    html += QString("<b>Vol:</b> %1 (%2)<br>").arg(v.code).arg(v.destination);
    html += QString("<b>Compagnie:</b> %1<br>").arg(v.compagnie);
    html += QString("<b>Date / Heure:</b> %1 %2<br>").arg(v.date.toString("yyyy-MM-dd")).arg(v.heure.toString("HH:mm"));
    html += QString("<b>Prix:</b> %1 €<br>").arg(QString::number(v.prix,'f',2));
    html += "<hr>";
    html += QString("<b>Date réservation:</b> %1<br>").arg(r.dateReservation.toString("yyyy-MM-dd"));
    html += QString("<b>Statut:</b> %1<br>").arg(r.statut);
    ui->textTicket->setHtml(html);
}

void TicketWidget::on_btnClose_clicked()
{
    accept();
}

void TicketWidget::on_btnPrint_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer PDF", QDir::homePath() + "/ticket.pdf", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);


    QTextDocument doc;
    doc.setHtml(ui->textTicket->toHtml());
    doc.print(&printer);

    QMessageBox::information(this, "Exporté", "Ticket exporté en PDF.");
}
