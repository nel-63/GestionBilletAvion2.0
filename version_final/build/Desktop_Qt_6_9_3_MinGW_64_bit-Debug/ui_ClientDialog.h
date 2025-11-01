/********************************************************************************
** Form generated from reading UI file 'ClientDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTDIALOG_H
#define UI_CLIENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ClientDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineNom;
    QLineEdit *linePrenom;
    QLineEdit *lineEmail;
    QLineEdit *lineTelephone;
    QHBoxLayout *buttonBox;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    void setupUi(QDialog *ClientDialog)
    {
        if (ClientDialog->objectName().isEmpty())
            ClientDialog->setObjectName("ClientDialog");
        ClientDialog->resize(186, 164);
        verticalLayout = new QVBoxLayout(ClientDialog);
        verticalLayout->setObjectName("verticalLayout");
        lineNom = new QLineEdit(ClientDialog);
        lineNom->setObjectName("lineNom");

        verticalLayout->addWidget(lineNom);

        linePrenom = new QLineEdit(ClientDialog);
        linePrenom->setObjectName("linePrenom");

        verticalLayout->addWidget(linePrenom);

        lineEmail = new QLineEdit(ClientDialog);
        lineEmail->setObjectName("lineEmail");

        verticalLayout->addWidget(lineEmail);

        lineTelephone = new QLineEdit(ClientDialog);
        lineTelephone->setObjectName("lineTelephone");

        verticalLayout->addWidget(lineTelephone);

        buttonBox = new QHBoxLayout();
        buttonBox->setObjectName("buttonBox");
        btnCancel = new QPushButton(ClientDialog);
        btnCancel->setObjectName("btnCancel");

        buttonBox->addWidget(btnCancel);

        btnSave = new QPushButton(ClientDialog);
        btnSave->setObjectName("btnSave");

        buttonBox->addWidget(btnSave);


        verticalLayout->addLayout(buttonBox);


        retranslateUi(ClientDialog);

        btnSave->setDefault(true);


        QMetaObject::connectSlotsByName(ClientDialog);
    } // setupUi

    void retranslateUi(QDialog *ClientDialog)
    {
        ClientDialog->setWindowTitle(QCoreApplication::translate("ClientDialog", "Client", nullptr));
        lineNom->setPlaceholderText(QCoreApplication::translate("ClientDialog", "Nom", nullptr));
        linePrenom->setPlaceholderText(QCoreApplication::translate("ClientDialog", "Pr\303\251nom", nullptr));
        lineEmail->setPlaceholderText(QCoreApplication::translate("ClientDialog", "Email", nullptr));
        lineTelephone->setPlaceholderText(QCoreApplication::translate("ClientDialog", "T\303\251l\303\251phone", nullptr));
        btnCancel->setText(QCoreApplication::translate("ClientDialog", "Annuler", nullptr));
        btnSave->setText(QCoreApplication::translate("ClientDialog", "Enregistrer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientDialog: public Ui_ClientDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTDIALOG_H
