
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void showDashboard();
    void showClients();
    void showVols();
    void showReservations();
    void logout();

    // Clients
    void loadClientsTable();
    void on_btnClientAdd_clicked();
    void on_btnClientEdit_clicked();
    void on_btnClientDelete_clicked();
    void on_lineClientSearch_textChanged(const QString &text); // ✅ ajouté ici

    // Vols
    void loadVolsTable();
    void on_btnVolAdd_clicked();
    void on_btnVolEdit_clicked();
    void on_btnVolDelete_clicked();
    void on_lineVolSearch_textChanged(const QString &text);

    // Reservations
    void loadReservationsTable();
    void on_btnResAdd_clicked();
    void on_btnResEdit_clicked();
    void on_btnResDelete_clicked();
    void on_btnPrintTicket_clicked();
    void on_lineResSearch_textChanged(const QString &term);

private:
    Ui::MainWindow *ui;
    void updateDashboard();

protected:
    void mousePressEvent(QMouseEvent *event) override;

};


#endif // MAINWINDOW_H
