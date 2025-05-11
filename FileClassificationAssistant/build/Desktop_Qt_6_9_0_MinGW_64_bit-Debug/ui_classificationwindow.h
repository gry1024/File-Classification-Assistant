/********************************************************************************
** Form generated from reading UI file 'classificationwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSIFICATIONWINDOW_H
#define UI_CLASSIFICATIONWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_classificationWindow
{
public:
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *backButton;
    QLabel *label_2;
    QLabel *label;
    QWidget *widget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *totalFileCountLabel;
    QLabel *pathLabel;
    QChartView *fileTypeChartView;
    QLabel *label_3;
    QWidget *widget_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *widget_4;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QWidget *volumeWidget;
    QPushButton *pushButton_2;
    QWidget *widget_6;
    QPushButton *pushButton_3;
    QLabel *label_4;

    void setupUi(QDialog *classificationWindow)
    {
        if (classificationWindow->objectName().isEmpty())
            classificationWindow->setObjectName("classificationWindow");
        classificationWindow->resize(1000, 800);
        classificationWindow->setMinimumSize(QSize(400, 300));
        widget_2 = new QWidget(classificationWindow);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(6, 733, 991, 61));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        backButton = new QPushButton(widget_2);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(0, 50));

        horizontalLayout_2->addWidget(backButton);

        label_2 = new QLabel(classificationWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(430, 10, 561, 20));
        label = new QLabel(classificationWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 411, 16));
        widget = new QWidget(classificationWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 30, 411, 701));
        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 411, 701));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 409, 699));
        totalFileCountLabel = new QLabel(scrollAreaWidgetContents);
        totalFileCountLabel->setObjectName("totalFileCountLabel");
        totalFileCountLabel->setGeometry(QRect(10, 70, 401, 20));
        pathLabel = new QLabel(scrollAreaWidgetContents);
        pathLabel->setObjectName("pathLabel");
        pathLabel->setGeometry(QRect(10, 10, 401, 51));
        fileTypeChartView = new QChartView(scrollAreaWidgetContents);
        fileTypeChartView->setObjectName("fileTypeChartView");
        fileTypeChartView->setGeometry(QRect(10, 100, 391, 281));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 670, 391, 16));
        scrollArea->setWidget(scrollAreaWidgetContents);
        widget_3 = new QWidget(classificationWindow);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(430, 30, 561, 701));
        scrollArea_2 = new QScrollArea(widget_3);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(0, 0, 561, 701));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 559, 699));
        widget_4 = new QWidget(scrollAreaWidgetContents_2);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(10, 60, 541, 150));
        checkBox = new QCheckBox(widget_4);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(10, 50, 361, 18));
        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 131, 31));
        volumeWidget = new QWidget(scrollAreaWidgetContents_2);
        volumeWidget->setObjectName("volumeWidget");
        volumeWidget->setGeometry(QRect(10, 210, 541, 150));
        pushButton_2 = new QPushButton(volumeWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 10, 131, 31));
        widget_6 = new QWidget(scrollAreaWidgetContents_2);
        widget_6->setObjectName("widget_6");
        widget_6->setGeometry(QRect(10, 360, 541, 200));
        pushButton_3 = new QPushButton(widget_6);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 10, 131, 31));
        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 361, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft PhagsPa")});
        font.setPointSize(10);
        font.setBold(false);
        label_4->setFont(font);
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(classificationWindow);

        QMetaObject::connectSlotsByName(classificationWindow);
    } // setupUi

    void retranslateUi(QDialog *classificationWindow)
    {
        classificationWindow->setWindowTitle(QCoreApplication::translate("classificationWindow", "Dialog", nullptr));
        backButton->setText(QCoreApplication::translate("classificationWindow", "\350\277\224\345\233\236", nullptr));
        label_2->setText(QCoreApplication::translate("classificationWindow", "\345\210\206\347\261\273\346\226\271\346\241\210\351\200\211\346\213\251 ", nullptr));
        label->setText(QCoreApplication::translate("classificationWindow", "\346\226\207\344\273\266\347\273\237\350\256\241\351\235\242\346\235\277", nullptr));
        totalFileCountLabel->setText(QCoreApplication::translate("classificationWindow", "\346\226\207\344\273\266\346\200\273\346\225\260\357\274\232", nullptr));
        pathLabel->setText(QCoreApplication::translate("classificationWindow", "\350\267\257\345\276\204\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("classificationWindow", "\346\263\250\357\274\232\344\270\215\345\214\205\345\220\253\345\217\252\350\257\273/\347\263\273\347\273\237/\351\232\220\350\227\217\346\226\207\344\273\266\345\217\212\346\226\207\344\273\266\345\244\271", nullptr));
        checkBox->setText(QCoreApplication::translate("classificationWindow", "\345\215\240\346\257\224\345\260\217\344\272\2165%\347\232\204\346\226\207\344\273\266\345\275\222\347\261\273\344\270\272\342\200\234\345\205\266\344\273\226\342\200\235\357\274\210\344\270\215\345\213\276\351\200\211\345\210\231\344\270\215\344\272\210\345\244\204\347\220\206\357\274\211", nullptr));
        pushButton->setText(QCoreApplication::translate("classificationWindow", "\346\214\211\346\226\207\344\273\266\347\261\273\345\236\213\345\210\206\347\261\273", nullptr));
        pushButton_2->setText(QCoreApplication::translate("classificationWindow", "\346\214\211\346\226\207\344\273\266\344\275\223\347\247\257\345\210\206\347\261\273", nullptr));
        pushButton_3->setText(QCoreApplication::translate("classificationWindow", "\346\214\211\344\277\256\346\224\271\346\227\266\351\227\264\345\210\206\347\261\273", nullptr));
        label_4->setText(QCoreApplication::translate("classificationWindow", "\350\256\276\347\275\256\345\245\275\345\220\216 \347\202\271\345\207\273\346\214\211\351\222\256\346\237\245\347\234\213\345\210\206\347\261\273\346\225\210\346\236\234\351\242\204\350\247\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class classificationWindow: public Ui_classificationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSIFICATIONWINDOW_H
