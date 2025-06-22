// timepreviewwindow.cpp
//文件修改时间分类预览窗口
#include "timepreviewwindow.h"
#include "executewindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QHeaderView>
#include <QSizePolicy>
#include <QLineEdit>
#include <QScreen>
#include <QDate>
#include <QFileInfo>
#include <QDir>

FileTimeItemWidget::FileTimeItemWidget(const FileTimeInfo &fileInfo, bool isSelected, QWidget *parent)
    : QWidget(parent), m_fileInfo(fileInfo), m_isSelected(isSelected) {

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 3, 5, 3);
    layout->setSpacing(8);

    // 文件名和修改时间标签
    QString displayText = QString("%1\n%2").arg(fileInfo.fileName, formatDateTime(fileInfo.modifiedTime));
    QLabel *fileInfoLabel = new QLabel(displayText);
    fileInfoLabel->setToolTip(QString("文件: %1\n修改时间: %2")
                                  .arg(fileInfo.fileName, fileInfo.modifiedTime.toString("yyyy-MM-dd hh:mm:ss")));
    fileInfoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fileInfoLabel->setWordWrap(true);
    fileInfoLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 10px;"
        "    color: #333333;"
        "    background-color: transparent;"
        "    border: none;"
        "    padding: 1px;"
        "    margin: 0px;"
        "    line-height: 1.2;"
        "}"
        );

    // 选择按钮
    m_selectButton = new QPushButton(isSelected ? "已选中" : "未选中");
    m_selectButton->setCheckable(true);
    m_selectButton->setChecked(isSelected);
    m_selectButton->setStyleSheet(
        "QPushButton {"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    padding: 3px 6px;"
        "    min-width: 55px;"
        "    font-size: 10px;"
        "    background-color: #f8f9fa;"
        "}"
        "QPushButton:checked {"
        "    background-color: #4a90e2;"
        "    color: white;"
        "    border-color: #4a90e2;"
        "}"
        "QPushButton:hover {"
        "    border-color: #4a90e2;"
        "}"
        );

    layout->addWidget(fileInfoLabel);
    layout->addWidget(m_selectButton);

    setFixedHeight(40);

    connect(m_selectButton, &QPushButton::clicked, this, &FileTimeItemWidget::onSelectButtonClicked);
}

bool FileTimeItemWidget::isSelected() const {
    return m_isSelected;
}

QString FileTimeItemWidget::fileName() const {
    return m_fileInfo.fileName;
}

QDateTime FileTimeItemWidget::modifiedTime() const {
    return m_fileInfo.modifiedTime;
}

FileTimeInfo FileTimeItemWidget::getFileInfo() const {
    return m_fileInfo;
}

QString FileTimeItemWidget::formatDateTime(const QDateTime &dateTime) const {
    QDate today = QDate::currentDate();
    QDate fileDate = dateTime.date();

    if (fileDate == today) {
        return QString("今天 %1").arg(dateTime.toString("hh:mm"));
    } else if (fileDate == today.addDays(-1)) {
        return QString("昨天 %1").arg(dateTime.toString("hh:mm"));
    } else if (fileDate.year() == today.year()) {
        return dateTime.toString("MM-dd hh:mm");
    } else {
        return dateTime.toString("yyyy-MM-dd");
    }
}

void FileTimeItemWidget::onSelectButtonClicked() {
    m_isSelected = !m_isSelected;
    m_selectButton->setText(m_isSelected ? "已选中" : "未选中");
    emit selectionChanged(m_fileInfo, m_isSelected);
}

// FileTimeTypeWidget 实现
FileTimeTypeWidget::FileTimeTypeWidget(const QString &timeRange, const QList<FileTimeInfo> &files, QWidget *parent)
    : QFrame(parent), m_timeRange(timeRange), m_files(files)
{
    setupUI();
    populateFileList();
}

QString FileTimeTypeWidget::getDefaultFolderName(const QString &timeRange)
{
    if (timeRange.contains("今天") || timeRange.contains("天内")) return "today_files";
    if (timeRange.contains("本周") || timeRange.contains("周内")) return "this_week";
    if (timeRange.contains("本月") || timeRange.contains("月内")) return "this_month";
    if (timeRange.contains("本年") || timeRange.contains("年内")) return "this_year";
    if (timeRange.contains("更早")) return "older_files";
    if (timeRange.contains("昨天")) return "yesterday_files";
    if (timeRange.contains("上周")) return "last_week";
    if (timeRange.contains("上月")) return "last_month";
    return timeRange.toLower().replace(" ", "_").replace("(", "").replace(")", "");
}

QList<FileTimeInfo> FileTimeTypeWidget::getSelectedFiles() const
{
    QList<FileTimeInfo> selectedFiles;
    for (const FileTimeInfo &fileInfo : m_files) {
        if (m_fileSelection.value(fileInfo.fileName, false)) {
            selectedFiles << fileInfo;
        }
    }
    return selectedFiles;
}

QString FileTimeTypeWidget::getFolderName() const
{
    return m_folderNameEdit->text().trimmed();
}

void FileTimeTypeWidget::selectAll()
{
    for (int i = 0; i < m_fileList->count(); ++i) {
        QListWidgetItem *item = m_fileList->item(i);
        FileTimeItemWidget *widget = qobject_cast<FileTimeItemWidget*>(m_fileList->itemWidget(item));
        if (widget && !widget->isSelected()) {
            widget->m_selectButton->click();
        }
    }
}

void FileTimeTypeWidget::deselectAll()
{
    for (int i = 0; i < m_fileList->count(); ++i) {
        QListWidgetItem *item = m_fileList->item(i);
        FileTimeItemWidget *widget = qobject_cast<FileTimeItemWidget*>(m_fileList->itemWidget(item));
        if (widget && widget->isSelected()) {
            widget->m_selectButton->click();
        }
    }
}

void FileTimeTypeWidget::setupUI()
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    setLineWidth(1);
    setMinimumWidth(280);
    setMaximumWidth(320);
    setMinimumHeight(550);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // 设置样式
    setStyleSheet(
        "QFrame {"
        "    border: 2px solid #cccccc;"
        "    border-radius: 8px;"
        "    background-color: #f9f9f9;"
        "    margin: 5px;"
        "}"
        "QLabel {"
        "    font-weight: bold;"
        "    font-size: 11px;"
        "    color: #333333;"
        "    background-color: #e6e6e6;"
        "    padding: 5px;"
        "    border-radius: 4px;"
        "    margin: 2px;"
        "}"
        "QLineEdit {"
        "    border: 1px solid #cccccc;"
        "    border-radius: 4px;"
        "    padding: 3px;"
        "    margin: 2px;"
        "    background-color: white;"
        "    font-size: 11px;"
        "}"
        "QListWidget {"
        "    border: 1px solid #dddddd;"
        "    border-radius: 4px;"
        "    background-color: white;"
        "    margin: 2px;"
        "}"
        "QListWidget::item {"
        "    padding: 0px;"
        "    border-bottom: 1px solid #eeeeee;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #f0f8ff;"
        "}"
        );

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->setSpacing(2);

    m_titleLabel = new QLabel(QString("修改时间: %1 (%2个文件)").arg(m_timeRange).arg(m_files.size()));
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setWordWrap(true);
    layout->addWidget(m_titleLabel);

    // 文件夹名称输入框
    QLabel *folderLabel = new QLabel("目标文件夹名称:");
    folderLabel->setStyleSheet("font-size: 10px; margin: 1px; padding: 2px;");
    layout->addWidget(folderLabel);

    m_folderNameEdit = new QLineEdit();
    m_folderNameEdit->setText(getDefaultFolderName(m_timeRange));
    m_folderNameEdit->setPlaceholderText("输入文件夹名称");
    layout->addWidget(m_folderNameEdit);

    // 创建文件列表
    m_fileList = new QListWidget();
    m_fileList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_fileList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_fileList->setAlternatingRowColors(true);
    m_fileList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(m_fileList, &QListWidget::itemClicked, this, &FileTimeTypeWidget::onFileItemClicked);

    layout->addWidget(m_fileList, 1);
    setLayout(layout);
}

void FileTimeTypeWidget::populateFileList()
{
    m_fileList->clear();
    m_fileSelection.clear();

    for (const FileTimeInfo &fileInfo : m_files) {
        // 初始化文件选择状态为选中
        m_fileSelection[fileInfo.fileName] = true;

        // 创建自定义文件项组件
        FileTimeItemWidget *fileItem = new FileTimeItemWidget(fileInfo, true, this);

        // 将自定义组件添加到列表中
        QListWidgetItem *listItem = new QListWidgetItem(m_fileList);
        listItem->setSizeHint(QSize(fileItem->width(), 40));  // 高度40像素
        m_fileList->setItemWidget(listItem, fileItem);

        // 连接选择状态变化信号
        connect(fileItem, &FileTimeItemWidget::selectionChanged,
                this, &FileTimeTypeWidget::onFileSelectionChanged);
    }
}

void FileTimeTypeWidget::onFileSelectionChanged(const FileTimeInfo &fileInfo, bool selected) {
    m_fileSelection[fileInfo.fileName] = selected;
}

void FileTimeTypeWidget::onFileItemClicked(QListWidgetItem *item)
{
    if (item) {
        FileTimeItemWidget *widget = qobject_cast<FileTimeItemWidget*>(m_fileList->itemWidget(item));
        if (widget) {
            FileTimeInfo fileInfo = widget->getFileInfo();
            QMessageBox::information(this, "文件选择",
                                     QString("您选择了文件:\n文件名: %1\n修改时间: %2\n时间分类: %3")
                                         .arg(fileInfo.fileName)
                                         .arg(fileInfo.modifiedTime.toString("yyyy-MM-dd hh:mm:ss"))
                                         .arg(m_timeRange));
        }
    }
}

// TimePreviewWindow 实现
TimePreviewWindow::TimePreviewWindow(const QString& rootPath, QWidget *parent)
    : QDialog(parent),
    rootDir(rootPath)
{
    setupUI();
    setModal(true);

    // 获取屏幕尺寸并设置合适的窗口大小
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 设置窗口大小为屏幕的90%
    int windowWidth = static_cast<int>(screenWidth * 0.9);
    int windowHeight = static_cast<int>(screenHeight * 0.9);

    resize(windowWidth, windowHeight);

    // 居中显示
    move((screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
}

void TimePreviewWindow::setupUI()
{
    setWindowTitle("文件修改时间分类预览");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    // 标题标签
    QLabel *titleLabel = new QLabel("文件修改时间分类预览 (点击按钮可切换文件选中状态)");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 15px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    padding: 10px;"
        "    background-color: #ecf0f1;"
        "    border-radius: 6px;"
        "}"
        );
    mainLayout->addWidget(titleLabel);

    // 创建水平滚动区域
    m_horizontalScrollArea = new QScrollArea();
    m_horizontalScrollArea->setWidgetResizable(true);
    m_horizontalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_horizontalScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_horizontalScrollArea->setFrameStyle(QFrame::StyledPanel);

    // 设置滚动区域的样式
    m_horizontalScrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 8px;"
        "    background-color: #ffffff;"
        "}"
        "QScrollBar:horizontal {"
        "    border: 1px solid #bdc3c7;"
        "    background: #ecf0f1;"
        "    height: 15px;"
        "    border-radius: 7px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: #3498db;"
        "    border-radius: 7px;"
        "    min-width: 30px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "    background: #2980b9;"
        "}"
        );

    // 创建内容容器
    m_contentWidget = new QWidget();
    m_contentLayout = new QHBoxLayout(m_contentWidget);
    m_contentLayout->setContentsMargins(10, 10, 10, 10);
    m_contentLayout->setSpacing(10);
    m_contentLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    m_horizontalScrollArea->setWidget(m_contentWidget);
    mainLayout->addWidget(m_horizontalScrollArea, 1);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    QPushButton *selectAllBtn = new QPushButton("全选");
    QPushButton *deselectAllBtn = new QPushButton("全不选");
    QPushButton *refreshBtn = new QPushButton("刷新");
    QPushButton *closeBtn = new QPushButton("关闭");
    QPushButton *executeBtn = new QPushButton("执行");

    // 统一按钮样式
    QString buttonStyle =
        "QPushButton {"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "    font-size: 12px;"
        "    min-width: 80px;"
        "}";

    selectAllBtn->setStyleSheet(buttonStyle +
                                "QPushButton {"
                                "    background-color: #27ae60;"
                                "    color: white;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #229954;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: #1e8449;"
                                "}");

    deselectAllBtn->setStyleSheet(buttonStyle +
                                  "QPushButton {"
                                  "    background-color: #f39c12;"
                                  "    color: white;"
                                  "}"
                                  "QPushButton:hover {"
                                  "    background-color: #e67e22;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "    background-color: #d35400;"
                                  "}");

    refreshBtn->setStyleSheet(buttonStyle +
                              "QPushButton {"
                              "    background-color: #3498db;"
                              "    color: white;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #2980b9;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #21618c;"
                              "}");

    closeBtn->setStyleSheet(buttonStyle +
                            "QPushButton {"
                            "    background-color: #e74c3c;"
                            "    color: white;"
                            "}"
                            "QPushButton:hover {"
                            "    background-color: #c0392b;"
                            "}"
                            "QPushButton:pressed {"
                            "    background-color: #a93226;"
                            "}");
    executeBtn->setStyleSheet(buttonStyle +
                              "QPushButton {"
                              "    background-color: #16a085;"
                              "    color: white;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #138d75;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #117964;"
                              "}");

    connect(selectAllBtn, &QPushButton::clicked, this, &TimePreviewWindow::selectAllFiles);
    connect(deselectAllBtn, &QPushButton::clicked, this, &TimePreviewWindow::deselectAllFiles);
    connect(closeBtn, &QPushButton::clicked, this, &TimePreviewWindow::onCloseButtonClicked);
    connect(refreshBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "刷新", "刷新文件列表完成！");
    });
    connect(executeBtn, &QPushButton::clicked, this, &TimePreviewWindow::onExecuteButtonClicked);

    buttonLayout->addWidget(selectAllBtn);
    buttonLayout->addWidget(deselectAllBtn);
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(closeBtn);
    buttonLayout->addWidget(executeBtn);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void TimePreviewWindow::setFileData(const QMap<QString, QList<FileTimeInfo>> &fileTimeData)
{
    clearContent();
    createFileTimeTypeWidgets(fileTimeData);
}

void TimePreviewWindow::clearContent()
{
    // 清除现有的文件时间分类小部件
    for (FileTimeTypeWidget *widget : m_fileTimeTypeWidgets) {
        m_contentLayout->removeWidget(widget);
        widget->deleteLater();
    }
    m_fileTimeTypeWidgets.clear();
}

void TimePreviewWindow::createFileTimeTypeWidgets(const QMap<QString, QList<FileTimeInfo>> &fileTimeData)
{
    // 为每个文件时间范围创建小部件
    for (auto it = fileTimeData.begin(); it != fileTimeData.end(); ++it) {
        const QString &timeRange = it.key();
        const QList<FileTimeInfo> &files = it.value();

        FileTimeTypeWidget *timeWidget = new FileTimeTypeWidget(timeRange, files, m_contentWidget);
        m_fileTimeTypeWidgets.append(timeWidget);
        m_contentLayout->addWidget(timeWidget);
    }

    // 添加弹性空间
    m_contentLayout->addStretch();

    // 更新内容区域大小
    int totalWidth = m_fileTimeTypeWidgets.size() * 340;
    m_contentWidget->setMinimumWidth(totalWidth);

    // 让内容区域自适应
    m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TimePreviewWindow::selectAllFiles()
{
    for (FileTimeTypeWidget *widget : m_fileTimeTypeWidgets) {
        widget->selectAll();
    }
}

void TimePreviewWindow::deselectAllFiles()
{
    for (FileTimeTypeWidget *widget : m_fileTimeTypeWidgets) {
        widget->deselectAll();
    }
}

void TimePreviewWindow::onCloseButtonClicked()
{
    accept();
}

void TimePreviewWindow::onExecuteButtonClicked()
{
    // 1. 收集选中的 FileTimeInfo
    QList<FileTimeInfo> selectedInfos;
    for (FileTimeTypeWidget *w : m_fileTimeTypeWidgets)
        selectedInfos << w->getSelectedFiles();

    if (selectedInfos.isEmpty()) {
        QMessageBox::information(this,"提示","没有选中的文件，无法执行分类。");
        return;
    }

    // 2. 转成 QList<QFileInfo>
    QList<QFileInfo> fileList;
    QDir base(rootDir);
    for (const FileTimeInfo &info : std::as_const(selectedInfos)) {
        QString abs = info.filePath.isEmpty()
        ? base.filePath(info.fileName)
        : info.filePath;
        if (QFile::exists(abs))
            fileList << QFileInfo(abs);
    }

    // 3. 调用 ExecuteWindow（按修改时间分类）
    ExecuteWindow *exeWin =
        new ExecuteWindow(rootDir, fileList, ExecuteWindow::ByTime, this);

    int result = exeWin->exec();

    // 4. 结果提示
    if (result == QDialog::Accepted) {
        QMessageBox::information(this, "操作完成",
                                 "文件分类处理已成功完成！\n您可以查看分类结果。");
    } else {
        QMessageBox::information(this, "操作取消",
                                 "文件分类操作已被取消或撤销。");
    }
}
