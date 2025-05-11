#include "executewindow.h"
#include "ui_executewindow.h"

executeWindow::executeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::executeWindow)
{
    ui->setupUi(this);
    resize(1000, 800);
}

executeWindow::~executeWindow()
{
    delete ui;
}
