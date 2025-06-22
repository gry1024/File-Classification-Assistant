// 执行分类窗口（进度条、撤销按钮等）
#include "executewindow.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>


static QString sizeCategory(qint64 s)
{
    if (s < 1024)               return "小文件(<1KB)";
    if (s < 1024*1024)          return "中等文件(1KB-1MB)";
    if (s < 100*1024*1024)      return "大文件(1MB-100MB)";
    return "超大文件(>100MB)";
}

static QString timeCategory(const QDateTime& mt)
{
    QDate today = QDate::currentDate();
    QDateTime today0(today, QTime(0,0));
    if (mt >= today0)                         return "今天";
    if (mt >= today0.addDays(-1))             return "昨天";
    if (mt >= today0.addDays(-today.dayOfWeek()+1)) return "本周";
    if (mt.date().month() == today.month())   return "本月";
    return "更早";
}


ExecuteWindow::ExecuteWindow(const QString &rootPath,
                             const QList<QFileInfo> &files,
                             Mode m,
                             QWidget *parent)
    : QDialog(parent),
    mainLayout(nullptr),
    buttonLayout(nullptr),
    titleLabel(nullptr),
    statusLabel(nullptr),
    progressBar(nullptr),
    finishButton(nullptr),
    undoButton(nullptr),
    progressTimer(nullptr),
    currentProgress(0),
    isProcessing(false),
    isFinished(false),
    rootDir(rootPath),
    fileList(files),
    mode(m),
    currentIndex(0)
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
    isFinished   = false;
    currentIndex = 0;
    currentProgress = 0;

    statusLabel->setText("正在处理文件...");
    progressBar->setValue(0);
    finishButton->setEnabled(false);

    if (!progressTimer) {
        progressTimer = new QTimer(this);
        connect(progressTimer, &QTimer::timeout,
                this, &ExecuteWindow::updateProgress);
    }
    progressTimer->start(20);          // 每 20ms 处理一个文件
}


void ExecuteWindow::updateProgress()
{
    if (!isProcessing) return;

    // 全部处理完
    if (currentIndex >= fileList.size()) {
        onProcessFinished();
        return;
    }

    // 取当前文件并计算目标目录
    QFileInfo fi = fileList.at(currentIndex++);
    QString subDir;
    switch (mode) {
    case ByType:
        subDir = fi.suffix().isEmpty()
                     ? "无后缀"
                     : fi.suffix().toLower();
        break;
    case BySize:
        subDir = sizeCategory(fi.size());
        break;
    case ByTime:
        subDir = timeCategory(fi.lastModified());
        break;
    }

    // 创建子目录并移动文件
    QDir dir(rootDir);
    if (!dir.exists(subDir))
        dir.mkdir(subDir);
    QString dstPath = dir.filePath(subDir + "/" + fi.fileName());
    if (QFile::exists(dstPath))
        QFile::remove(dstPath);            // 简单覆盖
    if (QFile::rename(fi.filePath(), dstPath))
        history << qMakePair(dstPath, fi.filePath());   // 记录

    // 更新进度条
    currentProgress = static_cast<int>(100.0 * currentIndex / fileList.size());
    progressBar->setValue(currentProgress);
    statusLabel->setText(QString("处理进度: %1%").arg(currentProgress));
}



void ExecuteWindow::onProcessFinished()
{
    progressTimer->stop();
    isProcessing = false;
    isFinished   = true;

    progressBar->setValue(100);
    statusLabel->setText("文件分类处理完成！");
    finishButton->setEnabled(true);
    finishButton->setText("完成");

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
    // 处理中 → 中止并撤销已完成部分
    if (isProcessing) {
        progressTimer->stop();
        isProcessing = false;
        undoFileClassification();
        QMessageBox::information(this,"已撤销","已中止并撤销已完成的移动操作。");
        reject();
        return;
    }

    // 已完成 → 撤销全部
    if (isFinished) {
        if (QMessageBox::question(this,"确认撤销",
                                  "确定要撤销刚才的文件分类操作吗？") == QMessageBox::Yes)
        {
            undoFileClassification();
            QMessageBox::information(this,"撤销完成","文件已恢复至原位置。");
            accept();
        }
    }
}

void ExecuteWindow::undoFileClassification()
{
    // 反向移动文件，避免覆盖
    for (int i = history.size() - 1; i >= 0; --i) {
        const QString &src = history[i].first;   // 现位置（分类后）
        const QString &dst = history[i].second;  // 原位置

        // 先把文件搬回
        QDir().mkpath(QFileInfo(dst).absolutePath());
        QFile::rename(src, dst);

        // ---------- 删除可能空掉的目录 ----------
        QDir dir(QFileInfo(src).absolutePath()); // 分类文件所在目录
        while (dir.path() != rootDir) {          // 不越过根目录
            if (!dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries).isEmpty())
                break;                           // 目录还有别的东西，退出
            QDir parent = dir;  parent.cdUp();   // 记录父目录后删除自己
            parent.rmdir(dir.dirName());         // 仅当空时才会成功
            dir = parent;                        // 继续向上
        }
    }
    history.clear();
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
