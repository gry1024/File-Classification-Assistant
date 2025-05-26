// 执行分类窗口（进度条、撤销按钮等）
#include "executewindow.h"
#include <QMessageBox>
#include <QApplication>

ExecuteWindow::ExecuteWindow(QWidget *parent)
    : QDialog(parent)
    , mainLayout(nullptr)
    , buttonLayout(nullptr)
    , titleLabel(nullptr)
    , statusLabel(nullptr)
    , progressBar(nullptr)
    , finishButton(nullptr)
    , undoButton(nullptr)
    , progressTimer(nullptr)
    , currentProgress(0)
    , isProcessing(false)
    , isFinished(false)
{
    setupUI();
    startFileClassification();
}

ExecuteWindow::~ExecuteWindow()
{
    if (progressTimer) {
        progressTimer->stop();
        delete progressTimer;
    }
}

void ExecuteWindow::setupUI()
{
    setWindowTitle("文件分类执行中...");
    setFixedSize(400, 200);
    setModal(true);

    // 主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 标题标签
    titleLabel = new QLabel("正在执行文件分类处理", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { font-size: 16px; font-weight: bold; color: #2c3e50; }");
    mainLayout->addWidget(titleLabel);

    // 状态标签
    statusLabel = new QLabel("准备开始...", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("QLabel { font-size: 12px; color: #7f8c8d; }");
    mainLayout->addWidget(statusLabel);

    // 进度条
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #3498db;"
        "    border-radius: 3px;"
        "}"
        );
    mainLayout->addWidget(progressBar);

    // 按钮布局
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    // 结束按钮
    finishButton = new QPushButton("结束", this);
    finishButton->setEnabled(false);
    finishButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #27ae60;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2ecc71;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #95a5a6;"
        "    color: #7f8c8d;"
        "}"
        );
    connect(finishButton, &QPushButton::clicked, this, &ExecuteWindow::on_finishButton_clicked);

    // 撤销按钮
    undoButton = new QPushButton("撤销", this);
    undoButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #c0392b;"
        "}"
        );
    connect(undoButton, &QPushButton::clicked, this, &ExecuteWindow::on_undoButton_clicked);

    buttonLayout->addStretch();
    buttonLayout->addWidget(finishButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    // 创建定时器
    progressTimer = new QTimer(this);
    connect(progressTimer, &QTimer::timeout, this, &ExecuteWindow::updateProgress);
}

void ExecuteWindow::startFileClassification()
{
    isProcessing = true;
    isFinished = false;
    currentProgress = 0;

    statusLabel->setText("正在处理文件...");
    progressBar->setValue(0);
    finishButton->setEnabled(false);

    // 这里应该调用实际的文件分类处理逻辑
    // 目前使用定时器模拟进度更新
    progressTimer->start(100); // 每100ms更新一次进度
}

void ExecuteWindow::updateProgress()
{
    if (!isProcessing) {
        return;
    }

    // 模拟进度更新（实际应用中应该从文件处理逻辑获取真实进度）
    currentProgress += (rand() % 3 + 1); // 随机增加1-3的进度

    if (currentProgress >= 100) {
        currentProgress = 100;
        onProcessFinished();
    }

    progressBar->setValue(currentProgress);
    statusLabel->setText(QString("处理进度: %1%").arg(currentProgress));
}

void ExecuteWindow::onProcessFinished()
{
    progressTimer->stop();
    isProcessing = false;
    isFinished = true;

    statusLabel->setText("文件分类处理完成！");
    finishButton->setEnabled(true);
    finishButton->setText("完成");

    // 可以在这里添加完成后的其他操作
    QMessageBox::information(this, "处理完成", "文件分类处理已成功完成！");
}

void ExecuteWindow::on_finishButton_clicked()
{
    if (isFinished) {
        accept(); // 关闭对话框并返回Accepted
    }
}

void ExecuteWindow::on_undoButton_clicked()
{
    QString message;
    if (isProcessing) {
        message = "确定要中止当前的文件分类处理吗？\n这将撤销所有已处理的操作。";
    } else if (isFinished) {
        message = "确定要撤销已完成的文件分类操作吗？\n这将恢复文件到处理前的状态。";
    } else {
        message = "确定要撤销操作吗？";
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认撤销",
        message,
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // 这里应该调用实际的撤销逻辑
        if (isProcessing) {
            progressTimer->stop();
            isProcessing = false;
        }

        // 执行撤销操作的代码应该在这里
        // undoFileClassification();

        QMessageBox::information(this, "撤销完成", "文件分类操作已成功撤销！");
        reject(); // 关闭对话框并返回Rejected
    }
}

void ExecuteWindow::resetProgress()
{
    currentProgress = 0;
    isProcessing = false;
    isFinished = false;
    progressBar->setValue(0);
    statusLabel->setText("准备开始...");
    finishButton->setEnabled(false);
    finishButton->setText("结束");
}
