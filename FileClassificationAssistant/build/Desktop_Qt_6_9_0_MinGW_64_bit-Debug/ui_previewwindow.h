/********************************************************************************
** Form generated from reading UI file 'previewwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWWINDOW_H
#define UI_PREVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_previewwindow
{
public:

    void setupUi(QDialog *previewwindow)
    {
        if (previewwindow->objectName().isEmpty())
            previewwindow->setObjectName("previewwindow");
        previewwindow->resize(1000, 800);

        retranslateUi(previewwindow);

        QMetaObject::connectSlotsByName(previewwindow);
    } // setupUi

    void retranslateUi(QDialog *previewwindow)
    {
        previewwindow->setWindowTitle(QCoreApplication::translate("previewwindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class previewwindow: public Ui_previewwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWWINDOW_H
