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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_classificationWindow
{
public:
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
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
    QCheckBox *checkBox_6;
    QWidget *volumeWidget;
    QPushButton *pushButton_size;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QDoubleSpinBox *doubleSpinBox_2;
    QDoubleSpinBox *doubleSpinBox_3;
    QDoubleSpinBox *doubleSpinBox_4;
    QCheckBox *checkBox_5;
    QDoubleSpinBox *doubleSpinBox_5;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox;
    QWidget *widget_6;
    QPushButton *pushButton_time;
    QCheckBox *checkBox_7;
    QSpinBox *spinBox;
    QLabel *label_6;
    QCheckBox *checkBox_8;
    QSpinBox *spinBox_2;
    QCheckBox *checkBox_9;
    QSpinBox *spinBox_3;
    QLabel *label_4;
    QPushButton *backButton;

    void setupUi(QDialog *classificationWindow)
    {
        if (classificationWindow->objectName().isEmpty())
            classificationWindow->setObjectName("classificationWindow");
        classificationWindow->resize(1000, 800);
        classificationWindow->setMinimumSize(QSize(400, 300));
        widget_2 = new QWidget(classificationWindow);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(6, 733, 176, 62));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
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
        checkBox->setGeometry(QRect(10, 50, 521, 18));
        checkBox->setChecked(true);
        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 131, 31));
        checkBox_6 = new QCheckBox(widget_4);
        checkBox_6->setObjectName("checkBox_6");
        checkBox_6->setGeometry(QRect(10, 70, 511, 18));
        volumeWidget = new QWidget(scrollAreaWidgetContents_2);
        volumeWidget->setObjectName("volumeWidget");
        volumeWidget->setGeometry(QRect(10, 210, 541, 150));
        pushButton_size = new QPushButton(volumeWidget);
        pushButton_size->setObjectName("pushButton_size");
        pushButton_size->setGeometry(QRect(10, 10, 131, 31));
        checkBox_2 = new QCheckBox(volumeWidget);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(270, 50, 251, 18));
        checkBox_2->setChecked(true);
        checkBox_3 = new QCheckBox(volumeWidget);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setGeometry(QRect(10, 80, 381, 16));
        checkBox_3->setChecked(true);
        checkBox_4 = new QCheckBox(volumeWidget);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setGeometry(QRect(10, 50, 181, 18));
        doubleSpinBox_2 = new QDoubleSpinBox(volumeWidget);
        doubleSpinBox_2->setObjectName("doubleSpinBox_2");
        doubleSpinBox_2->setGeometry(QRect(310, 50, 131, 21));
        doubleSpinBox_2->setMaximum(9999.989999999999782);
        doubleSpinBox_2->setSingleStep(10.000000000000000);
        doubleSpinBox_2->setValue(1.000000000000000);
        doubleSpinBox_3 = new QDoubleSpinBox(volumeWidget);
        doubleSpinBox_3->setObjectName("doubleSpinBox_3");
        doubleSpinBox_3->setGeometry(QRect(30, 80, 151, 21));
        doubleSpinBox_3->setMaximum(9999.989999999999782);
        doubleSpinBox_3->setSingleStep(10.000000000000000);
        doubleSpinBox_3->setValue(1.000000000000000);
        doubleSpinBox_4 = new QDoubleSpinBox(volumeWidget);
        doubleSpinBox_4->setObjectName("doubleSpinBox_4");
        doubleSpinBox_4->setGeometry(QRect(230, 80, 131, 21));
        doubleSpinBox_4->setMaximum(9999.989999999999782);
        doubleSpinBox_4->setSingleStep(10.000000000000000);
        doubleSpinBox_4->setValue(100.000000000000000);
        checkBox_5 = new QCheckBox(volumeWidget);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setGeometry(QRect(10, 110, 461, 18));
        checkBox_5->setChecked(true);
        doubleSpinBox_5 = new QDoubleSpinBox(volumeWidget);
        doubleSpinBox_5->setObjectName("doubleSpinBox_5");
        doubleSpinBox_5->setGeometry(QRect(60, 110, 141, 21));
        doubleSpinBox_5->setMaximum(9999.989999999999782);
        doubleSpinBox_5->setSingleStep(50.000000000000000);
        doubleSpinBox_5->setValue(100.000000000000000);
        label_5 = new QLabel(volumeWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(160, 20, 371, 16));
        label_7 = new QLabel(volumeWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(210, 50, 40, 16));
        label_8 = new QLabel(volumeWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(450, 50, 40, 16));
        label_9 = new QLabel(volumeWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(370, 80, 40, 16));
        label_10 = new QLabel(volumeWidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(190, 80, 40, 16));
        label_11 = new QLabel(volumeWidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(210, 110, 40, 16));
        doubleSpinBox = new QDoubleSpinBox(volumeWidget);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setGeometry(QRect(50, 50, 141, 22));
        doubleSpinBox->setMaximum(9999.989999999999782);
        doubleSpinBox->setValue(1.000000000000000);
        widget_6 = new QWidget(scrollAreaWidgetContents_2);
        widget_6->setObjectName("widget_6");
        widget_6->setGeometry(QRect(10, 360, 541, 151));
        pushButton_time = new QPushButton(widget_6);
        pushButton_time->setObjectName("pushButton_time");
        pushButton_time->setGeometry(QRect(10, 10, 131, 31));
        checkBox_7 = new QCheckBox(widget_6);
        checkBox_7->setObjectName("checkBox_7");
        checkBox_7->setGeometry(QRect(10, 60, 331, 18));
        checkBox_7->setChecked(true);
        spinBox = new QSpinBox(widget_6);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(30, 60, 81, 21));
        spinBox->setMaximum(9999);
        spinBox->setValue(7);
        spinBox->setDisplayIntegerBase(10);
        label_6 = new QLabel(widget_6);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(160, 20, 381, 16));
        checkBox_8 = new QCheckBox(widget_6);
        checkBox_8->setObjectName("checkBox_8");
        checkBox_8->setGeometry(QRect(10, 90, 301, 18));
        spinBox_2 = new QSpinBox(widget_6);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(30, 90, 81, 21));
        spinBox_2->setMaximum(999);
        spinBox_2->setValue(1);
        checkBox_9 = new QCheckBox(widget_6);
        checkBox_9->setObjectName("checkBox_9");
        checkBox_9->setGeometry(QRect(10, 120, 301, 18));
        spinBox_3 = new QSpinBox(widget_6);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(30, 120, 81, 21));
        spinBox_3->setValue(1);
        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 361, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft PhagsPa")});
        font.setPointSize(10);
        font.setBold(false);
        label_4->setFont(font);
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        backButton = new QPushButton(classificationWindow);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(10, 740, 981, 50));
        backButton->setMinimumSize(QSize(0, 50));
        backButton->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

        retranslateUi(classificationWindow);

        QMetaObject::connectSlotsByName(classificationWindow);
    } // setupUi

    void retranslateUi(QDialog *classificationWindow)
    {
        classificationWindow->setWindowTitle(QCoreApplication::translate("classificationWindow", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("classificationWindow", "\345\210\206\347\261\273\346\226\271\346\241\210\351\200\211\346\213\251 ", nullptr));
        label->setText(QCoreApplication::translate("classificationWindow", "\346\226\207\344\273\266\347\273\237\350\256\241\351\235\242\346\235\277", nullptr));
        totalFileCountLabel->setText(QCoreApplication::translate("classificationWindow", "\346\226\207\344\273\266\346\200\273\346\225\260\357\274\232", nullptr));
        pathLabel->setText(QCoreApplication::translate("classificationWindow", "\350\267\257\345\276\204\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("classificationWindow", "\346\263\250\357\274\232\344\270\215\345\214\205\345\220\253\345\217\252\350\257\273/\347\263\273\347\273\237/\351\232\220\350\227\217\346\226\207\344\273\266\345\217\212\346\226\207\344\273\266\345\244\271", nullptr));
        checkBox->setText(QCoreApplication::translate("classificationWindow", "\345\215\240\346\257\224\345\260\217\344\272\2165%\347\232\204\346\226\207\344\273\266\345\275\222\347\261\273\344\270\272\342\200\234\345\205\266\344\273\226\342\200\235\357\274\210\344\270\215\345\213\276\351\200\211\345\210\231\344\270\215\344\272\210\345\244\204\347\220\206\357\274\211", nullptr));
        pushButton->setText(QCoreApplication::translate("classificationWindow", "\346\214\211\346\226\207\344\273\266\347\261\273\345\236\213\345\210\206\347\261\273", nullptr));
        checkBox_6->setText(QCoreApplication::translate("classificationWindow", "\345\215\240\346\257\224\345\260\217\344\272\2165%\347\232\204\346\226\207\344\273\266\344\271\237\345\210\206\345\210\253\345\215\225\347\213\254\350\277\233\350\241\214\345\275\222\347\261\273\357\274\210\344\270\215\345\213\276\351\200\211\345\210\231\344\270\215\344\272\210\345\244\204\347\220\206\357\274\211", nullptr));
        pushButton_size->setText(QCoreApplication::translate("classificationWindow", "\346\214\211\346\226\207\344\273\266\344\275\223\347\247\257\345\210\206\347\261\273", nullptr));
        checkBox_2->setText(QCoreApplication::translate("classificationWindow", "\345\260\217\344\272\216                                                        ", nullptr));
        checkBox_3->setText(QString());
        checkBox_4->setText(QCoreApplication::translate("classificationWindow", "\345\260\217\344\272\216                                                                  ", nullptr));
        checkBox_5->setText(QCoreApplication::translate("classificationWindow", "\345\244\247\344\272\216                                                               ", nullptr));
        label_5->setText(QCoreApplication::translate("classificationWindow", "\346\263\250\357\274\232\350\214\203\345\233\264\345\246\202\346\234\211\351\207\215\345\217\240\357\274\214\351\207\215\345\217\240\350\214\203\345\233\264\345\206\205\347\232\204\346\226\207\344\273\266\345\260\206\344\274\232\350\242\253\345\244\215\345\210\266\345\244\232\344\273\275", nullptr));
        label_7->setText(QCoreApplication::translate("classificationWindow", "K", nullptr));
        label_8->setText(QCoreApplication::translate("classificationWindow", "M", nullptr));
        label_9->setText(QCoreApplication::translate("classificationWindow", "M", nullptr));
        label_10->setText(QCoreApplication::translate("classificationWindow", "M \342\200\224\342\200\224", nullptr));
        label_11->setText(QCoreApplication::translate("classificationWindow", "M", nullptr));
        pushButton_time->setText(QCoreApplication::translate("classificationWindow", "\346\214\211\344\277\256\346\224\271\346\227\266\351\227\264\345\210\206\347\261\273", nullptr));
        checkBox_7->setText(QCoreApplication::translate("classificationWindow", "                                   \345\244\251\345\206\205", nullptr));
        label_6->setText(QCoreApplication::translate("classificationWindow", "\346\263\250\357\274\232\350\214\203\345\233\264\345\246\202\346\234\211\351\207\215\345\217\240\357\274\214\351\207\215\345\217\240\350\214\203\345\233\264\345\206\205\347\232\204\346\226\207\344\273\266\345\260\206\344\274\232\350\242\253\345\244\215\345\210\266\345\244\232\344\273\275", nullptr));
        checkBox_8->setText(QCoreApplication::translate("classificationWindow", "                                   \346\234\210\345\206\205", nullptr));
        checkBox_9->setText(QCoreApplication::translate("classificationWindow", "                                   \345\271\264\345\206\205", nullptr));
        label_4->setText(QCoreApplication::translate("classificationWindow", "\350\256\276\347\275\256\345\245\275\345\220\216 \347\202\271\345\207\273\346\214\211\351\222\256\346\237\245\347\234\213\345\210\206\347\261\273\346\225\210\346\236\234\351\242\204\350\247\210", nullptr));
        backButton->setText(QCoreApplication::translate("classificationWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class classificationWindow: public Ui_classificationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSIFICATIONWINDOW_H
