/********************************************************************************
** Form generated from reading UI file 'TicketWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKETWIDGET_H
#define UI_TICKETWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TicketWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textTicket;
    QHBoxLayout *buttonBox;
    QPushButton *btnClose;
    QPushButton *btnPrint;

    void setupUi(QDialog *TicketWidget)
    {
        if (TicketWidget->objectName().isEmpty())
            TicketWidget->setObjectName("TicketWidget");
        TicketWidget->resize(507, 335);
        TicketWidget->setStyleSheet(QString::fromUtf8("color:white;"));
        verticalLayout = new QVBoxLayout(TicketWidget);
        verticalLayout->setObjectName("verticalLayout");
        textTicket = new QTextEdit(TicketWidget);
        textTicket->setObjectName("textTicket");
        textTicket->setReadOnly(true);

        verticalLayout->addWidget(textTicket);

        buttonBox = new QHBoxLayout();
        buttonBox->setObjectName("buttonBox");
        btnClose = new QPushButton(TicketWidget);
        btnClose->setObjectName("btnClose");

        buttonBox->addWidget(btnClose);

        btnPrint = new QPushButton(TicketWidget);
        btnPrint->setObjectName("btnPrint");

        buttonBox->addWidget(btnPrint);


        verticalLayout->addLayout(buttonBox);


        retranslateUi(TicketWidget);

        QMetaObject::connectSlotsByName(TicketWidget);
    } // setupUi

    void retranslateUi(QDialog *TicketWidget)
    {
        TicketWidget->setWindowTitle(QCoreApplication::translate("TicketWidget", "Ticket", nullptr));
        btnClose->setText(QCoreApplication::translate("TicketWidget", "Fermer", nullptr));
        btnPrint->setText(QCoreApplication::translate("TicketWidget", "Imprimer en PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicketWidget: public Ui_TicketWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKETWIDGET_H
