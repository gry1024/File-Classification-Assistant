#include "classificationwindow.h"
#include "ui_classificationwindow.h"

classificationWindow::classificationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::classificationWindow)
{
    ui->setupUi(this);
    resize(1000, 800);
}

classificationWindow::~classificationWindow()
{
    delete ui;
}
