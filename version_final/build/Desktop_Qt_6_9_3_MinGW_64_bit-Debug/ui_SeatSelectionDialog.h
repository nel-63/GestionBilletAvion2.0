/********************************************************************************
** Form generated from reading UI file 'SeatSelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEATSELECTIONDIALOG_H
#define UI_SEATSELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_SeatSelectionDialog
{
public:

    void setupUi(QDialog *SeatSelectionDialog)
    {
        if (SeatSelectionDialog->objectName().isEmpty())
            SeatSelectionDialog->setObjectName("SeatSelectionDialog");
        SeatSelectionDialog->resize(400, 300);

        retranslateUi(SeatSelectionDialog);

        QMetaObject::connectSlotsByName(SeatSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *SeatSelectionDialog)
    {
        SeatSelectionDialog->setWindowTitle(QCoreApplication::translate("SeatSelectionDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SeatSelectionDialog: public Ui_SeatSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEATSELECTIONDIALOG_H
