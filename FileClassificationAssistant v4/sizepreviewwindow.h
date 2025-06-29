// 按文件体积分类效果预览窗口
#ifndef SIZEPREVIEWWINDOW_H           // 头文件保护符，防止重复包含
#define SIZEPREVIEWWINDOW_H

#include <QDialog>                    // 对话框基类
#include <QVBoxLayout>                // 垂直布局管理器
#include <QHBoxLayout>                // 水平布局管理器
#include <QLabel>                     // 文本标签
#include <QPushButton>                // 按钮控件
#include <QScrollArea>                // 滚动区域控件
#include <QListWidget>                // 列表控件
#include <QFrame>                     // 框架控件
#include <QLineEdit>                  // 单行文本编辑框
#include <QMap>                       // 键值对容器
#include <QStringList>                // 字符串列表
#include <QDateTime>                  // 日期时间处理类

// 前向声明
class FileSizeItemWidget;             // 前向声明文件项组件类
class FileSizeTypeWidget;             // 前向声明文件类型组件类

// 文件信息结构体
struct FileInfo {                     // 存储文件元数据的结构体
    QString fileName;                 // 文件名
    qint64 fileSize;                  // 文件大小（字节）
    QString filePath;                 // 可选：文件路径
    FileInfo() : fileSize(0) {}       // 默认构造函数
    FileInfo(const QString &name, qint64 size, const QString &path = QString())
        : fileName(name), fileSize(size), filePath(path) {}  // 带参构造函数
};

// 单个文件项组件
class FileSizeItemWidget : public QWidget  // 表示文件列表中的单个文件项
{
    Q_OBJECT
public:
    explicit FileSizeItemWidget(const FileInfo &fileInfo, bool isSelected = true, QWidget *parent = nullptr);
    bool isSelected() const;          // 返回文件项的选中状态
    QString fileName() const;         // 返回文件名
    qint64 fileSize() const;          // 返回文件大小
    FileInfo getFileInfo() const;     // 返回完整文件信息
    QPushButton *m_selectButton;      // 公开访问以便外部控制
    QString formatFileSize(qint64 size) const;  // 将字节数格式化为可读字符串

signals:
    void selectionChanged(const FileInfo &fileInfo, bool selected);  // 选中状态变化信号
    void previewRequested(const QString &fileName);

private slots:
    void onSelectButtonClicked();     // 选择按钮点击事件处理槽

private:
    FileInfo m_fileInfo;              // 存储的文件信息
    bool m_isSelected;                // 当前选中状态
    QPushButton* m_previewButton;
};

// 文件体积分类组件
class FileSizeTypeWidget : public QFrame  // 表示特定大小范围的文件组
{
    Q_OBJECT
public:
    explicit FileSizeTypeWidget(const QString &sizeRange, const QList<FileInfo> &files, QWidget *parent = nullptr);
    QString getSizeRange() const { return m_sizeRange; }  // 返回大小范围字符串
    QList<FileInfo> getSelectedFiles() const;  // 返回所有选中的文件
    QString getFolderName() const;    // 返回文件夹名称
    void selectAll();                 // 选中所有文件
    void deselectAll();               // 取消选中所有文件

private slots:
    void onFileSelectionChanged(const FileInfo &fileInfo, bool selected);  // 文件选中状态变化处理
    void onFileItemClicked(QListWidgetItem *item);  // 文件项点击事件处理

    void onToggleSelectClicked();

private:
    void setupUI();                   // 初始化UI布局
    void populateFileList();          // 填充文件列表
    QString getDefaultFolderName(const QString &sizeRange);  // 生成默认文件夹名称
    QString m_sizeRange;              // 当前组件表示的大小范围
    QList<FileInfo> m_files;          // 属于此范围的文件列表
    QMap<QString, bool> m_fileSelection;  // 文件名 -> 选中状态映射
    QLabel *m_titleLabel;             // 标题标签
    QLineEdit *m_folderNameEdit;      // 文件夹名称编辑框
    QListWidget *m_fileList;          // 文件列表控件

    QPushButton *m_toggleSelectButton;  // 子类全（不）选
    bool m_isAllSelected = true;        // 初始全选状态

signals:
    void previewFileRequested(const QString& fileName);
};

// 主预览窗口
class SizePreviewWindow : public QDialog  // 主预览窗口类
{
    Q_OBJECT
public:
    explicit SizePreviewWindow(const QString& rootPath,
                               const QMap<QString, QString> &folderMap,
                               QWidget *parent = nullptr);
    void setFileData(const QMap<QString, QList<FileInfo>> &fileSizeData);  // 设置文件数据
    QMap<QString, double> getCustomThresholds() const;

private slots:
    void selectAllFiles();            // 选中所有文件
    void deselectAllFiles();          // 取消选中所有文件
    void onCloseButtonClicked();      // 关闭按钮点击事件处理
    void onExecuteButtonClicked();    // 执行
    void onPreviewFileRequested(const QString& fileName);

private:
    QString rootDir;
    void setupUI();                   // 初始化UI布局
    void clearContent();              // 清除窗口内容
    void createFileSizeTypeWidgets(const QMap<QString, QList<FileInfo>> &fileSizeData);  // 创建文件类型组件
    QScrollArea *m_horizontalScrollArea;  // 水平滚动区域
    QWidget *m_contentWidget;         // 内容容器
    QHBoxLayout *m_contentLayout;     // 内容布局
    QList<FileSizeTypeWidget*> m_fileSizeTypeWidgets;  // 文件类型组件列表
    QMap<QString, QString> folderNameMap;
    QMap<QString, double> m_customThresholds;
};

#endif // SIZEPREVIEWWINDOW_H
