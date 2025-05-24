#ifndef SIZEPREVIEWWINDOW_H
#define SIZEPREVIEWWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QListWidget>
#include <QFrame>
#include <QLineEdit>
#include <QMap>
#include <QStringList>

// 前向声明
class FileSizeItemWidget;
class FileSizeTypeWidget;

// 文件信息结构体
struct FileInfo {
    QString fileName;
    qint64 fileSize;    // 文件大小（字节）
    QString filePath;   // 可选：文件路径

    FileInfo() : fileSize(0) {}
    FileInfo(const QString &name, qint64 size, const QString &path = QString())
        : fileName(name), fileSize(size), filePath(path) {}
};

// 单个文件项组件
class FileSizeItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileSizeItemWidget(const FileInfo &fileInfo, bool isSelected = true, QWidget *parent = nullptr);

    bool isSelected() const;
    QString fileName() const;
    qint64 fileSize() const;
    FileInfo getFileInfo() const;

    QPushButton *m_selectButton;  // 公开访问以便外部控制
    QString formatFileSize(qint64 size) const;

signals:
    void selectionChanged(const FileInfo &fileInfo, bool selected);

private slots:
    void onSelectButtonClicked();

private:
    FileInfo m_fileInfo;
    bool m_isSelected;

};

// 文件体积分类组件
class FileSizeTypeWidget : public QFrame
{
    Q_OBJECT

public:
    explicit FileSizeTypeWidget(const QString &sizeRange, const QList<FileInfo> &files, QWidget *parent = nullptr);

    QString getSizeRange() const { return m_sizeRange; }
    QList<FileInfo> getSelectedFiles() const;
    QString getFolderName() const;

    void selectAll();
    void deselectAll();

private slots:
    void onFileSelectionChanged(const FileInfo &fileInfo, bool selected);
    void onFileItemClicked(QListWidgetItem *item);

private:
    void setupUI();
    void populateFileList();
    QString getDefaultFolderName(const QString &sizeRange);

    QString m_sizeRange;
    QList<FileInfo> m_files;
    QMap<QString, bool> m_fileSelection;  // 文件名 -> 选中状态

    QLabel *m_titleLabel;
    QLineEdit *m_folderNameEdit;
    QListWidget *m_fileList;
};

// 主预览窗口
class SizePreviewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SizePreviewWindow(QWidget *parent = nullptr);

    void setFileData(const QMap<QString, QList<FileInfo>> &fileSizeData);

private slots:
    void selectAllFiles();
    void deselectAllFiles();
    void onCloseButtonClicked();

private:
    void setupUI();
    void clearContent();
    void createFileSizeTypeWidgets(const QMap<QString, QList<FileInfo>> &fileSizeData);

    QScrollArea *m_horizontalScrollArea;
    QWidget *m_contentWidget;
    QHBoxLayout *m_contentLayout;
    QList<FileSizeTypeWidget*> m_fileSizeTypeWidgets;
};

#endif // SIZEPREVIEWWINDOW_H
