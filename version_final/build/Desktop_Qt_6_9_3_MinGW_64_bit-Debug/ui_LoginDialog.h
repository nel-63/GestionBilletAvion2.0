/********************************************************************************
** Form generated from reading UI file 'LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *lineUsername;
    QLineEdit *linePassword;
    QHBoxLayout *buttonLayout;
    QPushButton *btnCancel;
    QPushButton *btnLogin;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(193, 126);
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(LoginDialog);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        lineUsername = new QLineEdit(LoginDialog);
        lineUsername->setObjectName("lineUsername");

        verticalLayout->addWidget(lineUsername);

        linePassword = new QLineEdit(LoginDialog);
        linePassword->setObjectName("linePassword");
        linePassword->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(linePassword);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        btnCancel = new QPushButton(LoginDialog);
        btnCancel->setObjectName("btnCancel");

        buttonLayout->addWidget(btnCancel);

        btnLogin = new QPushButton(LoginDialog);
        btnLogin->setObjectName("btnLogin");

        buttonLayout->addWidget(btnLogin);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(LoginDialog);

        btnLogin->setDefault(true);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Authentification", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginDialog", "Bienvenue - Gestion R\303\251servations", nullptr));
        lineUsername->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Nom d'utilisateur", nullptr));
        linePassword->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Mot de passe", nullptr));
        btnCancel->setText(QCoreApplication::translate("LoginDialog", "Annuler", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "Se connecter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
