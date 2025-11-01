#include "ReservationDialog.h"
#include "ui_ReservationDialog.h"
#include "../dao/ClientFonction.h"
#include "../dao/VolFonction.h"
#include "../dao/ReservationFonction.h"
#include <QMessageBox>

ReservationDialog::ReservationDialog(QWidget *parent, int reservationId)
    : QDialog(parent), ui(new Ui::ReservationDialog), m_reservationId(reservationId)
{
    ui->setupUi(this);
    ui->dateReservation->setCalendarPopup(true);
    ui->dateReservation->setDate(QDate::currentDate());
    // connect(ui->btnCancel, &QPushButton::clicked, this, &ReservationDialog::on_btnCancel_clicked);
    // connect(ui->btnSave, &QPushButton::clicked, this, &ReservationDialog::on_btnSave_clicked);
    populateCombos();
    if (m_reservationId != -1) loadReservation();
}

ReservationDialog::~ReservationDialog() { delete ui; }

void ReservationDialog::populateCombos()
{
    ui->comboClient->clear();
    auto clients = ClientFonction::all();
    for (const auto &c : clients) ui->comboClient->addItem(QString("%1 %2").arg(c.nom).arg(c.prenom), c.id);

    ui->comboVol->clear();
    auto vols = VolFonction::all();
    for (const auto &v : vols) ui->comboVol->addItem(QString("%1 - %2").arg(v.code).arg(v.destination), v.id);

    ui->comboStatut->clear();
    ui->comboStatut->addItems({"Confirmée", "En Attente", "Annulée"});
}

void ReservationDialog::loadReservation()
{
    auto r = ReservationFonction::byId(m_reservationId);
    int idxClient = ui->comboClient->findData(r.clientId);
    if (idxClient != -1) ui->comboClient->setCurrentIndex(idxClient);
    int idxVol = ui->comboVol->findData(r.volId);
    if (idxVol != -1) ui->comboVol->setCurrentIndex(idxVol);
    ui->dateReservation->setDate(r.dateReservation);
    int idxStat = ui->comboStatut->findText(r.statut);
    if (idxStat != -1) ui->comboStatut->setCurrentIndex(idxStat);
}

void ReservationDialog::on_btnSave_clicked()
{
    Reservation r;
    r.clientId = ui->comboClient->currentData().toInt();
    r.volId = ui->comboVol->currentData().toInt();
    r.dateReservation = ui->dateReservation->date();
    r.statut = ui->comboStatut->currentText();

    if (m_reservationId == -1) {
        if (!ReservationFonction::add(r)) QMessageBox::critical(this, "Erreur", "Impossible d'ajouter la réservation.");
    } else {
        r.id = m_reservationId;
        if (!ReservationFonction::update(r)) QMessageBox::critical(this, "Erreur", "Impossible de mettre à jour la réservation.");
    }
    accept();
}

void ReservationDialog::on_btnCancel_clicked() { reject(); }
