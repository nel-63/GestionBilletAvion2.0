#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>      // <-- ajout nécessaire
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

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

    // Exemples de slots pour actions (adaptez selon votre .cpp)
    void on_btnClientAdd_clicked();
    void on_btnClientEdit_clicked();
    void on_btnClientDelete_clicked();
    void on_lineClientSearch_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    QLineEdit *m_search;       // maintenant reconnu
    QTableWidget *m_table;     // exemples de membres UI si vous en avez besoin
    QPushButton *m_btnAdd;
    QLabel *m_statusLabel;
    QStackedWidget *m_stack;
};

#endif // MAINWINDOW_H