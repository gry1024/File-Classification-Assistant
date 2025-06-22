// 按文件修改时间分类效果预览
#ifndef TIMEPREVIEWWINDOW_H           // 防止头文件被重复包含
#define TIMEPREVIEWWINDOW_H

#include <QDialog>                    // 基础对话框类
#include <QVBoxLayout>                // 垂直布局管理器
#include <QHBoxLayout>                // 水平布局管理器
#include <QLabel>                     // 文本标签控件
#include <QPushButton>                // 按钮控件
#include <QScrollArea>                // 滚动区域控件
#include <QListWidget>                // 列表控件
#include <QFrame>                     // 框架控件
#include <QLineEdit>                  // 单行文本输入框
#include <QMap>                       // 键值对映射容器
#include <QStringList>                // 字符串列表容器
#include <QDateTime>                  // 日期时间处理类

// 前向声明
class FileTimeItemWidget;             // 单个文件时间项组件
class FileTimeTypeWidget;             // 文件时间分类组件

// 文件时间信息结构体
struct FileTimeInfo {                 // 存储文件时间相关信息
    QString fileName;                 // 文件名
    QDateTime modifiedTime;           // 文件修改时间
    QString filePath;                 // 文件完整路径(可选)
    qint64 fileSize;                  // 文件大小(可选)

    FileTimeInfo() : fileSize(0) {}   // 默认构造函数
    FileTimeInfo(const QString &name, const QDateTime &time, const QString &path = QString(), qint64 size = 0)
        : fileName(name), modifiedTime(time), filePath(path), fileSize(size) {}  // 带参构造函数
};

// 单个文件项组件
class FileTimeItemWidget : public QWidget  // 表示文件列表中的单个文件项
{
    Q_OBJECT

public:
    explicit FileTimeItemWidget(const FileTimeInfo &fileInfo, bool isSelected = true, QWidget *parent = nullptr);

    bool isSelected() const;          // 返回文件选中状态
    QString fileName() const;         // 返回文件名
    QDateTime modifiedTime() const;   // 返回文件修改时间
    FileTimeInfo getFileInfo() const; // 返回完整文件信息

    QPushButton *m_selectButton;      // 选择按钮(公开以便外部控制)

signals:
    void selectionChanged(const FileTimeInfo &fileInfo, bool selected);  // 选中状态变化信号

private slots:
    void onSelectButtonClicked();     // 选择按钮点击事件处理

private:
    FileTimeInfo m_fileInfo;          // 文件时间信息
    bool m_isSelected;                // 当前选中状态
    QString formatDateTime(const QDateTime &dateTime) const;  // 日期时间格式化
};

// 文件时间分类组件
class FileTimeTypeWidget : public QFrame  // 表示特定时间范围的文件组
{
    Q_OBJECT

public:
    explicit FileTimeTypeWidget(const QString &timeRange, const QList<FileTimeInfo> &files, QWidget *parent = nullptr);

    QString getTimeRange() const { return m_timeRange; }  // 返回时间范围字符串
    QList<FileTimeInfo> getSelectedFiles() const;  // 返回选中的文件列表
    QString getFolderName() const;    // 返回文件夹名称

    void selectAll();                 // 全选文件
    void deselectAll();               // 取消全选

private slots:
    void onFileSelectionChanged(const FileTimeInfo &fileInfo, bool selected);  // 文件选中状态变化处理
    void onFileItemClicked(QListWidgetItem *item);  // 文件项点击事件处理

private:
    void setupUI();                   // 初始化UI界面
    void populateFileList();          // 填充文件列表
    QString getDefaultFolderName(const QString &timeRange);  // 生成默认文件夹名称

    QString m_timeRange;              // 时间范围描述
    QList<FileTimeInfo> m_files;      // 属于此时间范围的文件列表
    QMap<QString, bool> m_fileSelection;  // 文件名到选中状态的映射

    QLabel *m_titleLabel;             // 标题标签
    QLineEdit *m_folderNameEdit;      // 文件夹名称编辑框
    QListWidget *m_fileList;          // 文件列表控件
};

// 主预览窗口
class TimePreviewWindow : public QDialog  // 基于修改时间的文件预览主窗口
{
    Q_OBJECT

public:
    explicit TimePreviewWindow(const QString& rootPath,
                               QWidget *parent = nullptr);

    void setFileData(const QMap<QString, QList<FileTimeInfo>> &fileTimeData);  // 设置文件时间数据

private slots:
    void selectAllFiles();            // 全选所有文件
    void deselectAllFiles();          // 取消全选所有文件
    void onCloseButtonClicked();      // 关闭按钮点击事件处理
    void onExecuteButtonClicked();    // 执行

private:
    QString      rootDir;
    void setupUI();                   // 初始化UI布局
    void clearContent();              // 清除窗口内容
    void createFileTimeTypeWidgets(const QMap<QString, QList<FileTimeInfo>> &fileTimeData);  // 创建时间分类组件

    QScrollArea *m_horizontalScrollArea;  // 水平滚动区域
    QWidget *m_contentWidget;         // 内容容器部件
    QHBoxLayout *m_contentLayout;     // 内容布局管理器
    QList<FileTimeTypeWidget*> m_fileTimeTypeWidgets;  // 时间分类组件列表
};

#endif // TIMEPREVIEWWINDOW_H
