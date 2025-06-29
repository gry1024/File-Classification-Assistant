// previewwindow.cpp
//文件类型分类预览窗口
#include "previewwindow.h"
#include <QFileInfo>
#include <QDir>
#include "executewindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QHeaderView>
#include <QSizePolicy>
#include <QLineEdit>
#include <QScreen>
#include <QFileInfo>
#include <QDir>
#include "filepreviewdialog.h"


//new
FileItemWidget::FileItemWidget(const QString &fileName, bool isSelected, QWidget *parent)
    : QWidget(parent), m_fileName(fileName), m_isSelected(isSelected) {

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 3, 5, 3);
    layout->setSpacing(8);

    // 文件名标签
    QLabel *fileNameLabel = new QLabel(fileName);
    fileNameLabel->setToolTip(fileName);
    fileNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    fileNameLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 11px;"
        "    color: #333333;"
        "    background-color: transparent;"
        "    border: none;"
        "    padding: 1px;"
        "    margin: 0px;"
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

    layout->addWidget(fileNameLabel);
    layout->addWidget(m_selectButton);

    setFixedHeight(28);

    connect(m_selectButton, &QPushButton::clicked, this, &FileItemWidget::onSelectButtonClicked);

    // 添加预览按钮
    m_previewButton = new QPushButton("预览");
    m_previewButton->setFixedSize(50, 20);
    m_previewButton->setStyleSheet(
        "QPushButton {"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    padding: 2px 5px;"
        "    font-size: 10px;"
        "    background-color: #f8f9fa;"
        "}"
        "QPushButton:hover {"
        "    border-color: #4a90e2;"
        "}"
        );

    // 在布局中添加预览按钮
    layout->addWidget(m_previewButton);

    // 连接预览按钮信号
    connect(m_previewButton, &QPushButton::clicked, [this] {
        emit previewRequested(m_fileName);
    });
}

bool FileItemWidget::isSelected() const {
    return m_isSelected;
}

QString FileItemWidget::fileName() const {
    return m_fileName;
}

void FileItemWidget::onSelectButtonClicked() {
    m_isSelected = !m_isSelected;
    m_selectButton->setText(m_isSelected ? "已选中" : "未选中");
    emit selectionChanged(m_fileName, m_isSelected);
}



FileTypeWidget::FileTypeWidget(const QString &fileType, const QStringList &files, QWidget *parent)
    : QFrame(parent), m_fileType(fileType), m_files(files)
{
    setupUI();
    populateFileList();
}

QString FileTypeWidget::getDefaultFolderName(const QString &fileType)
{
    if (fileType.contains("文本")) return "txt";
    if (fileType.contains("Word")) return "doc";
    if (fileType.contains("PDF")) return "pdf";
    if (fileType.contains("图片")) return "images";
    if (fileType.contains("Excel")) return "xls";
    return fileType.toLower();
}

QStringList FileTypeWidget::getSelectedFiles() const
{
    QStringList selectedFiles;
    for (auto it = m_fileSelection.begin(); it != m_fileSelection.end(); ++it) {
        if (it.value()) {
            selectedFiles << it.key();
        }
    }
    return selectedFiles;
}

QString FileTypeWidget::getFolderName() const
{
    return m_folderNameEdit->text().trimmed();
}

void FileTypeWidget::selectAll()
{
    for (int i = 0; i < m_fileList->count(); ++i) {
        QListWidgetItem *item = m_fileList->item(i);
        FileItemWidget *widget = qobject_cast<FileItemWidget*>(m_fileList->itemWidget(item));
        if (widget && !widget->isSelected()) {
            widget->m_selectButton->click();
        }
    }
}

void FileTypeWidget::deselectAll()
{
    for (int i = 0; i < m_fileList->count(); ++i) {
        QListWidgetItem *item = m_fileList->item(i);
        FileItemWidget *widget = qobject_cast<FileItemWidget*>(m_fileList->itemWidget(item));
        if (widget && widget->isSelected()) {
            widget->m_selectButton->click();
        }
    }
}

void FileTypeWidget::setupUI()
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

    m_titleLabel = new QLabel(QString("文件类型: %1 (%2个文件)").arg(m_fileType).arg(m_files.size()));
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setWordWrap(true);
    layout->addWidget(m_titleLabel);

    // 添加右上角切换按钮
    QHBoxLayout *titleLayout = new QHBoxLayout();

    //每个文件子类的全选/全不选
    m_toggleSelectButton = new QPushButton("全不选");
    m_toggleSelectButton->setFixedSize(50, 20);
    m_toggleSelectButton->setStyleSheet(
        "QPushButton {"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    padding: 2px 4px;"
        "    font-size: 9px;"
        "    background-color: #f0f0f0;"
        "}"
        "QPushButton:hover {"
        "    background-color: #e0e0e0;"
        "}"
        );
    connect(m_toggleSelectButton, &QPushButton::clicked, this, &FileTypeWidget::onToggleSelectClicked);

    // 让标题和按钮按 8:2 比例占宽度
    titleLayout->addWidget(m_titleLabel, 8);
    titleLayout->addWidget(m_toggleSelectButton, 2);

    m_toggleSelectButton->setFixedHeight(22);
    m_toggleSelectButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_toggleSelectButton->setStyleSheet(
        "QPushButton { border: 1px solid #ccc; border-radius: 3px; padding: 1px 6px; font-size: 9px; }"
        "QPushButton:hover { background-color: #eee; }"
        );
    layout->addLayout(titleLayout);


    // 文件夹名称输入框
    QLabel *folderLabel = new QLabel("目标文件夹名称:");
    folderLabel->setStyleSheet("font-size: 10px; margin: 1px; padding: 2px;");
    layout->addWidget(folderLabel);

    m_folderNameEdit = new QLineEdit();
    m_folderNameEdit->setText(getDefaultFolderName(m_fileType));
    m_folderNameEdit->setPlaceholderText("输入文件夹名称");
    layout->addWidget(m_folderNameEdit);

    // 创建文件列表
    m_fileList = new QListWidget();
    m_fileList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_fileList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_fileList->setAlternatingRowColors(true);
    m_fileList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 连接信号槽
    connect(m_fileList, &QListWidget::itemClicked, this, &FileTypeWidget::onFileItemClicked);

    layout->addWidget(m_fileList, 1);

    setLayout(layout);
}

void FileTypeWidget::onToggleSelectClicked()
{
    if (m_isAllSelected) {
        // 执行取消全选
        for (int i = 0; i < m_fileList->count(); ++i) {
            QListWidgetItem *item = m_fileList->item(i);
            FileItemWidget *widget = qobject_cast<FileItemWidget*>(m_fileList->itemWidget(item));
            if (widget && widget->isSelected()) {
                widget->m_selectButton->click();
            }
        }
        m_toggleSelectButton->setText("全选");
    } else {
        // 执行全选
        for (int i = 0; i < m_fileList->count(); ++i) {
            QListWidgetItem *item = m_fileList->item(i);
            FileItemWidget *widget = qobject_cast<FileItemWidget*>(m_fileList->itemWidget(item));
            if (widget && !widget->isSelected()) {
                widget->m_selectButton->click();
            }
        }
        m_toggleSelectButton->setText("全不选");
    }

    m_isAllSelected = !m_isAllSelected;
}

void FileTypeWidget::populateFileList()
{
    m_fileList->clear();
    m_fileSelection.clear();

    for (const QString &file : m_files) {
        // 初始化文件选择状态为选中
        m_fileSelection[file] = true;

        // 创建自定义文件项组件
        FileItemWidget *fileItem = new FileItemWidget(file, true, this);

        // 将自定义组件添加到列表中
        QListWidgetItem *listItem = new QListWidgetItem(m_fileList);
        listItem->setSizeHint(QSize(fileItem->width(), 28));  // 固定高度28像素
        m_fileList->setItemWidget(listItem, fileItem);

        // 连接选择状态变化信号
        connect(fileItem, &FileItemWidget::selectionChanged,
                this, &FileTypeWidget::onFileSelectionChanged);
        connect(fileItem, &FileItemWidget::previewRequested,
                this, &FileTypeWidget::previewFileRequested);
    }
}

void FileTypeWidget::onFileSelectionChanged(const QString &fileName, bool selected) {
    m_fileSelection[fileName] = selected;
}

void FileTypeWidget::onFileItemClicked(QListWidgetItem *item)
{
    if (item) {
        FileItemWidget *widget = qobject_cast<FileItemWidget*>(m_fileList->itemWidget(item));
        if (widget){
            QString fileName = widget->fileName();
            QMessageBox::information(this, "文件选择",
                                    QString("您选择了文件:\n%1\n文件类型: %2").arg(fileName, m_fileType));
        }
    }
}


PreviewWindow::PreviewWindow(const QString& rootPath,
                             const QMap<QString, QString> &folderMap,
                             QWidget *parent)
    : QDialog(parent),
    rootDir(rootPath),
    folderNameMap(folderMap)
{
    setupUI();
    setModal(true);

    // 获取屏幕尺寸并设置合适的窗口大小
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();


    int windowWidth = static_cast<int>(screenWidth * 0.9);
    int windowHeight = static_cast<int>(screenHeight * 0.9);

    resize(windowWidth, windowHeight);
    move((screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
}

void PreviewWindow::setupUI()
{
    setWindowTitle("文件分类预览");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    // 标题标签
    QLabel *titleLabel = new QLabel("文件分类预览 (点击按钮可切换文件选中状态)");
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

    // 创建水平滚动区域 - 禁用垂直滚动条
    m_horizontalScrollArea = new QScrollArea();
    m_horizontalScrollArea->setWidgetResizable(true);
    m_horizontalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // 禁用垂直滚动条
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

    connect(selectAllBtn, &QPushButton::clicked, this, &PreviewWindow::selectAllFiles);
    connect(deselectAllBtn, &QPushButton::clicked, this, &PreviewWindow::deselectAllFiles);
    connect(closeBtn, &QPushButton::clicked, this, &PreviewWindow::onCloseButtonClicked);
    connect(refreshBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "刷新", "刷新文件列表完成！");
    });
    connect(executeBtn, &QPushButton::clicked, this, &PreviewWindow::onExecuteButtonClicked);

    buttonLayout->addWidget(selectAllBtn);
    buttonLayout->addWidget(deselectAllBtn);
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(closeBtn);
    buttonLayout->addWidget(executeBtn);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void PreviewWindow::setFileData(const QMap<QString, QStringList> &fileTypeData)
{
    clearContent();
    createFileTypeWidgets(fileTypeData);
}

void PreviewWindow::clearContent()
{
    // 清除现有的文件类型小部件
    for (FileTypeWidget *widget : m_fileTypeWidgets) {
        m_contentLayout->removeWidget(widget);
        widget->deleteLater();
    }
    m_fileTypeWidgets.clear();
}

void PreviewWindow::createFileTypeWidgets(const QMap<QString, QStringList> &fileTypeData)
{
    // 为每种文件类型创建小部件
    for (auto it = fileTypeData.begin(); it != fileTypeData.end(); ++it) {
        const QString &fileType = it.key();
        const QStringList &files = it.value();

        FileTypeWidget *typeWidget = new FileTypeWidget(fileType, files, m_contentWidget);
        m_fileTypeWidgets.append(typeWidget);
        m_contentLayout->addWidget(typeWidget);

        connect(typeWidget, &FileTypeWidget::previewFileRequested,
                this, &PreviewWindow::onPreviewFileRequested);
    }

    // 添加弹性空间
    m_contentLayout->addStretch();

    // 更新内容区域大小
    int totalWidth = m_fileTypeWidgets.size() * 340;
    m_contentWidget->setMinimumWidth(totalWidth);

    // 移除固定高度设置，让内容区域自适应
    m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PreviewWindow::selectAllFiles()
{
    for (FileTypeWidget *widget : m_fileTypeWidgets) {
        widget->selectAll();
    }
}

void PreviewWindow::deselectAllFiles()
{
    for (FileTypeWidget *widget : m_fileTypeWidgets) {
        widget->deselectAll();
    }
}

void PreviewWindow::onCloseButtonClicked()
{
    accept();
}

void PreviewWindow::onExecuteButtonClicked()
{
    //--------------------------------------------------
    // 1. 收集所有选中的文件名
    //--------------------------------------------------
    QStringList selectedNames;
    QMap<QString, QString> folderMapping;
    for (FileTypeWidget *widget : m_fileTypeWidgets)
    {
        QString folderName = widget->getFolderName();  // 获取用户设置的文件夹名称
        QStringList selectedFiles = widget->getSelectedFiles();
        selectedNames.append(selectedFiles);
        for (const QString &file : selectedFiles)
        {
            folderMapping[file] = folderName;  // 记录文件名对应的文件夹名称
        }
    }

    if (selectedNames.isEmpty()) {
        QMessageBox::information(this,"提示","没有选中的文件，无法执行分类。");
        return;
    }

    //--------------------------------------------------
    // 2. 组合成绝对路径 -> QList<QFileInfo>
    //--------------------------------------------------
    QList<QFileInfo> fileList;
    for (const QString &name : std::as_const(selectedNames)) {
        QString absPath = QDir(rootDir).filePath(name);
        if (QFile::exists(absPath))
            fileList << QFileInfo(absPath);
    }

    //--------------------------------------------------
    // 3. 创建并执行 ExecuteWindow（按文件类型分类）
    //--------------------------------------------------
    ExecuteWindow *executeWindow =
        new ExecuteWindow(rootDir, fileList, folderMapping, this);

    int result = executeWindow->exec();

    //--------------------------------------------------
    // 4. 给用户反馈
    //--------------------------------------------------
    if (result == QDialog::Accepted) {
        QMessageBox::information(this, "操作完成",
                                 "文件分类处理已成功完成！\n您可以查看分类结果。");
    } else {
        QMessageBox::information(this, "操作取消",
                                 "文件分类操作已被取消或撤销。");
    }
}

void PreviewWindow::onPreviewFileRequested(const QString& fileName) {
    QString filePath = QDir(rootDir).filePath(fileName);
    QFileInfo fileInfo(filePath);

    if (!fileInfo.exists()) {
        QMessageBox::warning(this, "预览错误", "文件不存在: " + filePath);
        return;
    }

    FilePreviewDialog previewDialog(fileInfo, this);
    previewDialog.exec();
}
