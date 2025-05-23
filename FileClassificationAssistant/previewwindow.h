#ifndef PREVIEWWINDOW_H                          // 防止头文件重复包含的宏定义
#define PREVIEWWINDOW_H                          // 头文件保护宏结束标记（与#endif对应）

// 包含必要的Qt头文件，每个组件对应一个头文件
#include <QLineEdit>            // 用于创建文件夹名称输入框的单行文本编辑框
#include <QWidget>              // 所有用户界面元素的基类
#include <QDialog>              // 对话框窗口基类，用于模态/非模态对话框
#include <QScrollArea>          // 提供滚动视图的组件，用于实现内容滚动
#include <QHBoxLayout>          // 水平布局管理器，用于横向排列子组件
#include <QVBoxLayout>          // 垂直布局管理器，用于纵向排列子组件
#include <QLabel>               // 用于显示文本或图像的标签组件
#include <QFrame>               // 带边框和背景的框架组件，用于分组和视觉分隔
#include <QScrollBar>           // 独立滚动条组件，用于自定义滚动逻辑
#include <QPushButton>          // 可点击的按钮组件，用于触发操作
#include <QListWidget>          // 可显示列表项的组件，支持项目选择和交互
#include <QListWidgetItem>      // 列表组件中的单个项目类
#include <QMap>                 // 基于哈希表的键值对容器，用于快速查找
#include <QStringList>          // 字符串列表容器，用于存储文件路径等字符串集合

// ====================== 文件项组件类 ======================
class FileItemWidget : public QWidget {          // 继承自QWidget，代表单个文件项
    Q_OBJECT                                    // Qt元对象系统宏，支持信号槽机制

public:
    // 构造函数：初始化文件项组件，参数为文件名、初始选中状态、父组件指针
    explicit FileItemWidget(const QString &fileName, bool isSelected, QWidget *parent = nullptr);

    // 获取文件选中状态（只读）
    bool isSelected() const;

    // 获取文件名（只读）
    QString fileName() const;

    // 公开选择按钮指针，供外部实现全选/全不选功能直接操作
    QPushButton *m_selectButton;

signals:
    // 选中状态变化信号：当文件选中状态改变时发出，携带文件名和新状态
    void selectionChanged(const QString &fileName, bool selected);

private slots:
    // 按钮点击事件处理槽函数：切换选中状态并发送信号
    void onSelectButtonClicked();

private:
    QString m_fileName;                           // 存储文件名的成员变量
    bool m_isSelected;                            // 存储选中状态的成员变量（true=选中）
};

// ====================== 文件类型组件类 ======================
class FileTypeWidget : public QFrame
{
    Q_OBJECT                                    // 元对象系统支持

public:
    // 构造函数：初始化文件类型组件，参数为文件类型名、文件列表、父组件指针
    explicit FileTypeWidget(const QString &fileType, const QStringList &files, QWidget *parent = nullptr);

    // 获取当前类型中所有被选中的文件列表
    QStringList getSelectedFiles() const;

    // 获取用户输入的目标文件夹名称（用于存储该类型文件）
    QString getFolderName() const;

    // 全选功能：选中该类型下的所有文件
    void selectAll();

    // 全不选功能：取消选中该类型下的所有文件
    void deselectAll();

private:
    QString m_fileType;                           // 文件类型名称（如"txt"、"pdf"）
    QStringList m_files;                          // 该类型下的所有文件路径列表
    QListWidget *m_fileList;                      // 显示文件列表的QListWidget控件
    QLabel *m_titleLabel;                         // 显示类型标题的标签（如"文件类型: txt (5个文件)"）
    QLineEdit *m_folderNameEdit;                  // 输入目标文件夹名称的单行编辑框
    QMap<QString, bool> m_fileSelection;          // 键值对：文件名→是否选中（用于记录状态）

    void setupUI();                               // 私有函数：初始化UI布局
    void populateFileList();                      // 私有函数：向列表中填充文件项
    // 私有函数：根据文件类型自动生成默认文件夹名称（如"txt"→"txt_files"）
    QString getDefaultFolderName(const QString &fileType);

private slots:
    // 处理文件列表项点击事件的槽函数（如显示文件详情）
    void onFileItemClicked(QListWidgetItem *item);

    // 处理文件选中状态变化的槽函数（更新内部状态映射）
    void onFileSelectionChanged(const QString &fileName, bool selected);
};

// ====================== 主预览窗口类 ======================
class PreviewWindow : public QDialog
{
    Q_OBJECT                                    // 元对象系统支持

public:
    // 构造函数：初始化预览窗口，参数为父组件指针
    explicit PreviewWindow(QWidget *parent = nullptr);

    // 设置文件数据：传入文件类型与文件列表的映射，用于更新窗口显示
    void setFileData(const QMap<QString, QStringList> &fileTypeData);

private:
    QScrollArea *m_horizontalScrollArea;        // 水平滚动区域，用于显示多个文件类型组件
    QWidget *m_contentWidget;                   // 内容容器Widget，作为滚动区域的子部件
    QHBoxLayout *m_contentLayout;               // 水平布局管理器，管理文件类型组件的排列
    QList<FileTypeWidget*> m_fileTypeWidgets;    // 存储所有文件类型组件的列表

    void setupUI();                             // 私有函数：初始化窗口整体UI布局
    void clearContent();                        // 私有函数：清除现有文件类型组件（用于刷新）
    // 私有函数：根据传入的文件类型数据创建并添加文件类型组件到窗口
    void createFileTypeWidgets(const QMap<QString, QStringList> &fileTypeData);

private slots:
    // 处理关闭按钮点击事件的槽函数（关闭对话框）
    void onCloseButtonClicked();

    // 全选所有文件：遍历所有类型组件并调用selectAll()
    void selectAllFiles();

    // 全不选所有文件：遍历所有类型组件并调用deselectAll()
    void deselectAllFiles();
};

#endif // PREVIEWWINDOW_H                         // 头文件保护宏结束标记
