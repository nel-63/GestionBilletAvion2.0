/********************************************************************************
** Form generated from reading UI file 'ReservationDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESERVATIONDIALOG_H
#define UI_RESERVATIONDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReservationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboClient;
    QComboBox *comboVol;
    QDateEdit *dateReservation;
    QComboBox *comboStatut;
    QHBoxLayout *buttonBox;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    void setupUi(QDialog *ReservationDialog)
    {
        if (ReservationDialog->objectName().isEmpty())
            ReservationDialog->setObjectName("ReservationDialog");
        ReservationDialog->resize(272, 175);
        verticalLayout = new QVBoxLayout(ReservationDialog);
        verticalLayout->setObjectName("verticalLayout");
        comboClient = new QComboBox(ReservationDialog);
        comboClient->setObjectName("comboClient");

        verticalLayout->addWidget(comboClient);

        comboVol = new QComboBox(ReservationDialog);
        comboVol->setObjectName("comboVol");

        verticalLayout->addWidget(comboVol);

        dateReservation = new QDateEdit(ReservationDialog);
        dateReservation->setObjectName("dateReservation");
        dateReservation->setCalendarPopup(true);
        dateReservation->setDate(QDate(2000, 1, 1));

        verticalLayout->addWidget(dateReservation);

        comboStatut = new QComboBox(ReservationDialog);
        comboStatut->setObjectName("comboStatut");

        verticalLayout->addWidget(comboStatut);

        buttonBox = new QHBoxLayout();
        buttonBox->setObjectName("buttonBox");
        btnCancel = new QPushButton(ReservationDialog);
        btnCancel->setObjectName("btnCancel");

        buttonBox->addWidget(btnCancel);

        btnSave = new QPushButton(ReservationDialog);
        btnSave->setObjectName("btnSave");

        buttonBox->addWidget(btnSave);


        verticalLayout->addLayout(buttonBox);


        retranslateUi(ReservationDialog);

        btnSave->setDefault(true);


        QMetaObject::connectSlotsByName(ReservationDialog);
    } // setupUi

    void retranslateUi(QDialog *ReservationDialog)
    {
        ReservationDialog->setWindowTitle(QCoreApplication::translate("ReservationDialog", "R\303\251servation", nullptr));
        btnCancel->setText(QCoreApplication::translate("ReservationDialog", "Annuler", nullptr));
        btnSave->setText(QCoreApplication::translate("ReservationDialog", "Enregistrer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReservationDialog: public Ui_ReservationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESERVATIONDIALOG_H
