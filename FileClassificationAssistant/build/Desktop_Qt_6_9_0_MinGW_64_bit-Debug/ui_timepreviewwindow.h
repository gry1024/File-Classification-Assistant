/********************************************************************************
** Form generated from reading UI file 'timepreviewwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEPREVIEWWINDOW_H
#define UI_TIMEPREVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_timepreviewwindow
{
public:

    void setupUi(QDialog *timepreviewwindow)
    {
        if (timepreviewwindow->objectName().isEmpty())
            timepreviewwindow->setObjectName("timepreviewwindow");
        timepreviewwindow->resize(400, 300);

        retranslateUi(timepreviewwindow);

        QMetaObject::connectSlotsByName(timepreviewwindow);
    } // setupUi

    void retranslateUi(QDialog *timepreviewwindow)
    {
        timepreviewwindow->setWindowTitle(QCoreApplication::translate("timepreviewwindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class timepreviewwindow: public Ui_timepreviewwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEPREVIEWWINDOW_H
