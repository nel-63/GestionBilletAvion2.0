#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ClientDialog.h"
#include "VolDialog.h"
#include "ReservationDialog.h"
#include "TicketWidget.h"
#include "../dao/ClientFonction.h"
#include "../dao/VolFonction.h"
#include "../dao/ReservationFonction.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QDebug>
#include <QColor>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::showDashboard);
    connect(ui->btnClients, &QPushButton::clicked, this, &MainWindow::showClients);
    connect(ui->btnVols, &QPushButton::clicked, this, &MainWindow::showVols);
    connect(ui->btnReservations, &QPushButton::clicked, this, &MainWindow::showReservations);
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::logout);

    ui->tableClients->setColumnCount(5);
    ui->tableClients->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Email", "Téléphone"});
    ui->tableClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableVols->setColumnCount(9);
    ui->tableVols->setHorizontalHeaderLabels({"ID", "Code", "Destination", "Date", "Heure", "Compagnie", "Prix_economique_prenium","Prix_premiere","Prix_economique"});
    ui->tableVols->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableReservations->setColumnCount(5);
    ui->tableReservations->setHorizontalHeaderLabels({"ID", "Client", "Vol", "Date réservation", "Statut"});
    ui->tableReservations->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QTableWidget* tables[] = { ui->tableClients, ui->tableVols, ui->tableReservations };

    for (QTableWidget* table : tables) {
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
    }


    showDashboard();
    loadClientsTable();
    loadVolsTable();
    loadReservationsTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showDashboard() { ui->stackedWidget->setCurrentWidget(ui->pageDashboard); updateDashboard(); }
void MainWindow::showClients() { ui->stackedWidget->setCurrentWidget(ui->pageClients); loadClientsTable(); }
void MainWindow::showVols() { ui->stackedWidget->setCurrentWidget(ui->pageVols); loadVolsTable(); }
void MainWindow::showReservations() { ui->stackedWidget->setCurrentWidget(ui->pageReservations); loadReservationsTable(); }

void MainWindow::logout()
{
    close();
}

void MainWindow::updateDashboard()
{
    int totalVols = VolFonction::count();
    int totalClients = ClientFonction::all().size();
    int totalReservations = ReservationFonction::count();

    ui->lblTotalVols->setText(QString("Vols: %1").arg(totalVols));
    ui->lblTotalClients->setText(QString("Clients: %1").arg(totalClients));
    ui->lblTotalReservations->setText(QString("Réservations: %1").arg(totalReservations));
}

void MainWindow::loadClientsTable()
{
    ui->tableClients->setRowCount(0);
    auto clients = ClientFonction::all();


    ui->tableClients->setRowCount(clients.size());
    for (int i=0;i<clients.size();++i) {
        const Client &c = clients.at(i);
        ui->tableClients->setItem(i,0,new QTableWidgetItem(QString::number(c.id)));
        ui->tableClients->setItem(i,1,new QTableWidgetItem(c.nom));
        ui->tableClients->setItem(i,2,new QTableWidgetItem(c.prenom));
        ui->tableClients->setItem(i,3,new QTableWidgetItem(c.email));
        ui->tableClients->setItem(i,4,new QTableWidgetItem(c.telephone));
    }
}

void MainWindow::on_btnClientAdd_clicked()
{
    ClientDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        loadClientsTable();
        updateDashboard();
    }
}

void MainWindow::on_btnClientEdit_clicked()
{
    auto sel = ui->tableClients->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner un client."); return; }
    int row = sel.first()->row();
    int id = ui->tableClients->item(row,0)->text().toInt();
    ClientDialog dlg(this, id);
    if (dlg.exec() == QDialog::Accepted) loadClientsTable();
}

void MainWindow::on_btnClientDelete_clicked()
{
    auto sel = ui->tableClients->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner un client."); return; }
    int row = sel.first()->row();
    int id = ui->tableClients->item(row,0)->text().toInt();
    if (QMessageBox::question(this, "Supprimer", "Confirmer la suppression du client ?") == QMessageBox::Yes) {
        if (ClientFonction::remove(id)) loadClientsTable();
    }
}


void MainWindow::loadVolsTable()
{
    ui->tableVols->setRowCount(0);
    auto vols = VolFonction::all();


    ui->tableVols->setRowCount(vols.size());
    for (int i=0;i<vols.size();++i) {
        const Vol &v = vols.at(i);
        ui->tableVols->setItem(i,0,new QTableWidgetItem(QString::number(v.id)));
        ui->tableVols->setItem(i,1,new QTableWidgetItem(v.code));
        ui->tableVols->setItem(i,2,new QTableWidgetItem(v.destination));
        ui->tableVols->setItem(i,3,new QTableWidgetItem(v.date.toString("yyyy-MM-dd")));
        ui->tableVols->setItem(i,4,new QTableWidgetItem(v.heure.toString("HH:mm")));
        ui->tableVols->setItem(i,5,new QTableWidgetItem(v.compagnie));
        ui->tableVols->setItem(i,6,new QTableWidgetItem(QString::number(v.prix, 'f', 2)));
        ui->tableVols->setItem(i,7,new QTableWidgetItem(QString::number(v.prix_premiere_class, 'f', 2)));
        ui->tableVols->setItem(i,8,new QTableWidgetItem(QString::number(v.prix_class_economique, 'f', 2)));
    }
}

void MainWindow::on_btnVolAdd_clicked()
{
    VolDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        loadVolsTable();
        updateDashboard();
    }
}

void MainWindow::on_btnVolEdit_clicked()
{
    auto sel = ui->tableVols->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner un vol."); return; }
    int row = sel.first()->row();
    int id = ui->tableVols->item(row,0)->text().toInt();
    VolDialog dlg(this, id);
    if (dlg.exec() == QDialog::Accepted) loadVolsTable();
}

void MainWindow::on_btnVolDelete_clicked()
{
    auto sel = ui->tableVols->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner un vol."); return; }
    int row = sel.first()->row();
    int id = ui->tableVols->item(row,0)->text().toInt();
    if (QMessageBox::question(this, "Supprimer", "Confirmer la suppression du vol ?") == QMessageBox::Yes) {
        if (VolFonction::remove(id)) loadVolsTable();
    }
}

void MainWindow::loadReservationsTable()
{
    ui->tableReservations->setRowCount(0);
    auto list = ReservationFonction::all();


    ui->tableReservations->setRowCount(list.size());
    for (int i=0;i<list.size();++i) {
        const Reservation &r = list.at(i);
        auto c = ClientFonction::byId(r.clientId);
        auto v = VolFonction::byId(r.volId);
        ui->tableReservations->setItem(i,0,new QTableWidgetItem(QString::number(r.id)));
        ui->tableReservations->setItem(i,1,new QTableWidgetItem(QString("%1 %2").arg(c.nom).arg(c.prenom)));
        ui->tableReservations->setItem(i,2,new QTableWidgetItem(QString("%1 - %2").arg(v.code).arg(v.destination)));
        ui->tableReservations->setItem(i,3,new QTableWidgetItem(r.dateReservation.toString("yyyy-MM-dd")));
        ui->tableReservations->setItem(i,4,new QTableWidgetItem(r.statut));
    }
}

void MainWindow::on_btnResAdd_clicked()
{
    ReservationDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        loadReservationsTable();
        updateDashboard();
    }
}

void MainWindow::on_btnResEdit_clicked()
{
    auto sel = ui->tableReservations->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner une réservation."); return; }
    int row = sel.first()->row();
    int id = ui->tableReservations->item(row,0)->text().toInt();
    ReservationDialog dlg(this, id);
    if (dlg.exec() == QDialog::Accepted) loadReservationsTable();
}

void MainWindow::on_btnResDelete_clicked()
{
    auto sel = ui->tableReservations->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner une réservation."); return; }
    int row = sel.first()->row();
    int id = ui->tableReservations->item(row,0)->text().toInt();
    if (QMessageBox::question(this, "Supprimer", "Confirmer la suppression de la réservation ?") == QMessageBox::Yes) {
        if (ReservationFonction::remove(id)) loadReservationsTable();
    }
}

void MainWindow::on_btnPrintTicket_clicked()
{
    auto sel = ui->tableReservations->selectedItems();
    if (sel.isEmpty()) { QMessageBox::information(this, "Sélection", "Veuillez sélectionner une réservation."); return; }
    int row = sel.first()->row();
    int id = ui->tableReservations->item(row,0)->text().toInt();
    QString statut = ui->tableReservations->item(row, 4)->text();
    if (statut.toLower() != "confirmée") {
        QMessageBox::warning(this, "Action impossible",
                             "Veulliez confirmé la réservation.");
        return;
    }

    TicketWidget ticket(this, id);
    ticket.exec();
}

void MainWindow::on_lineClientSearch_textChanged(const QString &term)
{
    ui->tableClients->setRowCount(0);
    auto clients = ClientFonction::search(term);
    ui->tableClients->setRowCount(clients.size());
    for (int i=0;i<clients.size();++i) {
        const Client &c = clients.at(i);
        ui->tableClients->setItem(i,0,new QTableWidgetItem(QString::number(c.id)));
        ui->tableClients->setItem(i,1,new QTableWidgetItem(c.nom));
        ui->tableClients->setItem(i,2,new QTableWidgetItem(c.prenom));
        ui->tableClients->setItem(i,3,new QTableWidgetItem(c.email));
        ui->tableClients->setItem(i,4,new QTableWidgetItem(c.telephone));
    }
}

void MainWindow::on_lineVolSearch_textChanged(const QString &term)
{
    ui->tableVols->setRowCount(0);
    auto vols = VolFonction::search(term);
    ui->tableVols->setRowCount(vols.size());
    for (int i=0;i<vols.size();++i) {
        const Vol &v = vols.at(i);
        ui->tableVols->setItem(i,0,new QTableWidgetItem(QString::number(v.id)));
        ui->tableVols->setItem(i,1,new QTableWidgetItem(v.code));
        ui->tableVols->setItem(i,2,new QTableWidgetItem(v.destination));
        ui->tableVols->setItem(i,3,new QTableWidgetItem(v.date.toString("yyyy-MM-dd")));
        ui->tableVols->setItem(i,4,new QTableWidgetItem(v.heure.toString("HH:mm")));
        ui->tableVols->setItem(i,5,new QTableWidgetItem(v.compagnie));
        ui->tableVols->setItem(i,6,new QTableWidgetItem(QString::number(v.prix, 'f', 2)));
        ui->tableVols->setItem(i,7,new QTableWidgetItem(QString::number(v.prix_premiere_class, 'f', 2)));
        ui->tableVols->setItem(i,8,new QTableWidgetItem(QString::number(v.prix_class_economique, 'f', 2)));
    }
}

void MainWindow::on_lineResSearch_textChanged(const QString &term)
{
    ui->tableReservations->setRowCount(0);
    auto list = ReservationFonction::search(term);
    ui->tableReservations->setRowCount(list.size());

    for (int i = 0; i < list.size(); ++i) {
        const Reservation &r = list.at(i);
        auto c = ClientFonction::byId(r.clientId);
        auto v = VolFonction::byId(r.volId);

        ui->tableReservations->setItem(i, 0, new QTableWidgetItem(QString::number(r.id)));
        ui->tableReservations->setItem(i, 1, new QTableWidgetItem(QString("%1 %2").arg(c.nom).arg(c.prenom)));
        ui->tableReservations->setItem(i, 2, new QTableWidgetItem(QString("%1 - %2").arg(v.code).arg(v.destination)));
        ui->tableReservations->setItem(i, 3, new QTableWidgetItem(r.dateReservation.toString("yyyy-MM-dd")));
        ui->tableReservations->setItem(i, 4, new QTableWidgetItem(r.statut));
    }
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget *clicked = childAt(event->pos());

    if (!qobject_cast<QTableWidget*>(clicked) && !qobject_cast<QPushButton*>(clicked)) {
        ui->tableClients->clearSelection();
        ui->tableVols->clearSelection();
        ui->tableReservations->clearSelection();
    }

    QMainWindow::mousePressEvent(event);
}
