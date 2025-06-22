/********************************************************************************
** Form generated from reading UI file 'sizepreviewwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIZEPREVIEWWINDOW_H
#define UI_SIZEPREVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_sizepreviewwindow
{
public:

    void setupUi(QDialog *sizepreviewwindow)
    {
        if (sizepreviewwindow->objectName().isEmpty())
            sizepreviewwindow->setObjectName("sizepreviewwindow");
        sizepreviewwindow->resize(400, 300);

        retranslateUi(sizepreviewwindow);

        QMetaObject::connectSlotsByName(sizepreviewwindow);
    } // setupUi

    void retranslateUi(QDialog *sizepreviewwindow)
    {
        sizepreviewwindow->setWindowTitle(QCoreApplication::translate("sizepreviewwindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sizepreviewwindow: public Ui_sizepreviewwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIZEPREVIEWWINDOW_H
