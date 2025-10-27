#include <QApplication>
#include <QMessageBox>
#include "ui/LoginDialog.h"
#include "ui/MainWindow.h"
#include "database/DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Gestion Réservations");


    a.setStyleSheet(R"(
    QMainWindow { background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #eaf6ff, stop:1 #ffffff); }
    QWidget { font-family: "Segoe UI", "Helvetica Neue", Arial; color:white;background: black; }
    QPushButton { background-color: #1e73be; color: white; border-radius: 8px; padding: 6px 12px; }
    QPushButton:hover { background-color: #165c9a; }
    QLineEdit, QComboBox, QDateEdit, QTimeEdit { background: white; border: 1px solid #cfdff0; border-radius: 6px; padding: 4px;color:black; }
    QTableWidget { background: #ffffff; border: 1px solid #dbeaf7;color:black }
    QTableWidget::item:selected { background-color: #d3d3d3; color: black; }
    QLabel.title { font-size: 18px; font-weight: bold; color:white; }
    )");



    if (!DatabaseManager::instance().openConnection()) {
        QMessageBox::critical(nullptr, "Erreur Connexion BDD",
                              "Impossible de se connecter au serveur MySQL. Veuillez vérifier que XAMPP (ou MariaDB) est en cours d'exécution.");
        return -1;
    }


    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
