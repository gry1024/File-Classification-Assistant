#include "mainwindow.h"
#include "classificationwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1000, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//选择需要分类的文件路径
void MainWindow::on_choseFileButton_clicked()
{
    // 创建对话框窗口
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("选择目录");
    dialog->setMinimumWidth(400);

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);
    QHBoxLayout *pathLayout = new QHBoxLayout();

    // 创建路径输入框
    QLineEdit *pathLineEdit = new QLineEdit(dialog);
    pathLineEdit->setPlaceholderText("请选择目录...");

    // 创建浏览按钮
    QPushButton *browseButton = new QPushButton("浏览...", dialog);

    // 创建确定和取消按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("确定", dialog);
    QPushButton *cancelButton = new QPushButton("取消", dialog);

    // 添加控件到布局
    pathLayout->addWidget(pathLineEdit);
    pathLayout->addWidget(browseButton);

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(pathLayout);
    mainLayout->addLayout(buttonLayout);

    // 连接浏览按钮信号槽
    connect(browseButton, &QPushButton::clicked, [=]() {
        QString initialDir = pathLineEdit->text().isEmpty() ?
                                 QDir::homePath() : pathLineEdit->text();

        QString selectedDir = QFileDialog::getExistingDirectory(
            dialog,
            tr("选择目录"),
            initialDir,
            QFileDialog::ShowDirsOnly
            );

        if (!selectedDir.isEmpty()) {
            pathLineEdit->setText(selectedDir);
        }
    });

    // 连接确定和取消按钮
    connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    // 显示对话框（模态方式）
    if (dialog->exec() == QDialog::Accepted) {
        selectedPath = pathLineEdit->text();
        if (!selectedPath.isEmpty()) {
            close();
            // 对话框关闭后自动释放内存
            dialog->deleteLater();
            // 进入分类窗口
            classificationWindow cfwindow(selectedPath);
            // 返回路径选择窗口
            if(cfwindow.exec() == QDialog::Rejected) show();
        }
    }

}

