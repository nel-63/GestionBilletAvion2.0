#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "../database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    //connect(ui->btnCancel, &QPushButton::clicked, this, &LoginDialog::on_btnCancel_clicked);
    //connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::on_btnLogin_clicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::authenticate(const QString &user, const QString &pass)
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());

    q.prepare("SELECT role FROM users WHERE username=:u AND password=:p");
    q.bindValue(":u", user);
    q.bindValue(":p", pass);

    if (!q.exec()) {
        QMessageBox::critical(nullptr, "Erreur BDD", "Erreur lors de l'authentification: " + q.lastError().text());
        return false;
    }

    if (q.next()) {

        return true;
    }


    return false;
}

void LoginDialog::on_btnLogin_clicked()
{
    QString user = ui->lineUsername->text().trimmed();
    QString pass = ui->linePassword->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez fournir un nom d'utilisateur et un mot de passe.");
        return;
    }

    if (authenticate(user, pass)) {
        accept();
    } else {

        QMessageBox::critical(this, "Échec", "Nom d'utilisateur ou mot de passe incorrect.");
    }
}

void LoginDialog::on_btnCancel_clicked()
{
    reject();
}
