/********************************************************************************
** Form generated from reading UI file 'executewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXECUTEWINDOW_H
#define UI_EXECUTEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_executeWindow
{
public:

    void setupUi(QDialog *executeWindow)
    {
        if (executeWindow->objectName().isEmpty())
            executeWindow->setObjectName("executeWindow");
        executeWindow->resize(1000, 800);

        retranslateUi(executeWindow);

        QMetaObject::connectSlotsByName(executeWindow);
    } // setupUi

    void retranslateUi(QDialog *executeWindow)
    {
        executeWindow->setWindowTitle(QCoreApplication::translate("executeWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class executeWindow: public Ui_executeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXECUTEWINDOW_H
