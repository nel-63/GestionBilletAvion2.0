#include "ClientDialog.h"
#include "ui_ClientDialog.h"
#include "../dao/ClientFonction.h"
#include <QMessageBox>

ClientDialog::ClientDialog(QWidget *parent, int clientId)
    : QDialog(parent), ui(new Ui::ClientDialog), m_clientId(clientId)
{
    ui->setupUi(this);
    //connect(ui->btnCancel, &QPushButton::clicked, this, &ClientDialog::on_btnCancel_clicked);
    //connect(ui->btnSave, &QPushButton::clicked, this, &ClientDialog::on_btnSave_clicked);
    if (m_clientId != -1) loadClient();
}

ClientDialog::~ClientDialog() { delete ui; }

void ClientDialog::loadClient()
{
    auto c = ClientFonction::byId(m_clientId);
    ui->lineNom->setText(c.nom);
    ui->linePrenom->setText(c.prenom);
    ui->lineEmail->setText(c.email);
    ui->lineTelephone->setText(c.telephone);
}

void ClientDialog::on_btnSave_clicked()
{
    Client c;
    c.nom = ui->lineNom->text().trimmed();
    c.prenom = ui->linePrenom->text().trimmed();
    c.email = ui->lineEmail->text().trimmed();
    c.telephone = ui->lineTelephone->text().trimmed();

    if (c.nom.isEmpty() || c.prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs requis", "Le nom et le prénom sont requis.");
        return;
    }

    if (m_clientId == -1) {
        if (!ClientFonction::add(c)) QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le client.");
    } else {
        c.id = m_clientId;
        if (!ClientFonction::update(c)) QMessageBox::critical(this, "Erreur", "Impossible de mettre à jour le client.");
    }
    accept();
}

void ClientDialog::on_btnCancel_clicked() { reject(); }
