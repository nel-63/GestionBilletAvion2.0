#include <QApplication>
#include "src/database/DatabaseManager.h"
#include "src/ui/LoginDialog.h"
#include "src/ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Gestion Réservations - Compagnie Aérienne");
    a.setStyleSheet(R"(
        /* Simple modern blue/steel style */
        QMainWindow { background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #e8f2ff, stop:1 #f7fbff); }
        QWidget { font-family: "Segoe UI", "Helvetica Neue", Arial; color: #0b2e4f; }
        QPushButton { background-color: #1e73be; color: white; border-radius: 8px; padding: 6px 12px; }
        QPushButton:hover { background-color: #165c9a; }
        QLineEdit, QComboBox, QDateEdit, QTimeEdit { background: white; border: 1px solid #cfdff0; border-radius: 6px; padding: 4px; }
        QTableWidget { background: #ffffff; border: 1px solid #dbeaf7; }
        QLabel.title { font-size: 18px; font-weight: bold; color: #083058; }
    )");

    if (!DatabaseManager::instance().openDatabase()) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ouvrir la base de données.");
        return 1;
    }

    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}