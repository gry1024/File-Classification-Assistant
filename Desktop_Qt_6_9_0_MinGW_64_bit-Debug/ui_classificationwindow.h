/********************************************************************************
** Form generated from reading UI file 'classificationwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSIFICATIONWINDOW_H
#define UI_CLASSIFICATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_classificationWindow
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;

    void setupUi(QDialog *classificationWindow)
    {
        if (classificationWindow->objectName().isEmpty())
            classificationWindow->setObjectName("classificationWindow");
        classificationWindow->resize(1000, 800);
        classificationWindow->setMinimumSize(QSize(400, 300));
        verticalLayout = new QVBoxLayout(classificationWindow);
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(classificationWindow);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        retranslateUi(classificationWindow);
        QObject::connect(pushButton, &QPushButton::clicked, classificationWindow, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(classificationWindow);
    } // setupUi

    void retranslateUi(QDialog *classificationWindow)
    {
        classificationWindow->setWindowTitle(QCoreApplication::translate("classificationWindow", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("classificationWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class classificationWindow: public Ui_classificationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSIFICATIONWINDOW_H
