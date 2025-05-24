#ifndef TIMEPREVIEWWINDOW_H
#define TIMEPREVIEWWINDOW_H

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
#include <QDateTime>

// 前向声明
class FileTimeItemWidget;
class FileTimeTypeWidget;

// 文件时间信息结构体
struct FileTimeInfo {
    QString fileName;
    QDateTime modifiedTime;     // 修改时间
    QString filePath;           // 可选：文件路径
    qint64 fileSize;           // 可选：文件大小

    FileTimeInfo() : fileSize(0) {}
    FileTimeInfo(const QString &name, const QDateTime &time, const QString &path = QString(), qint64 size = 0)
        : fileName(name), modifiedTime(time), filePath(path), fileSize(size) {}
};

// 单个文件项组件
class FileTimeItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileTimeItemWidget(const FileTimeInfo &fileInfo, bool isSelected = true, QWidget *parent = nullptr);

    bool isSelected() const;
    QString fileName() const;
    QDateTime modifiedTime() const;
    FileTimeInfo getFileInfo() const;

    QPushButton *m_selectButton;  // 公开访问以便外部控制

signals:
    void selectionChanged(const FileTimeInfo &fileInfo, bool selected);

private slots:
    void onSelectButtonClicked();

private:
    FileTimeInfo m_fileInfo;
    bool m_isSelected;
    QString formatDateTime(const QDateTime &dateTime) const;
};

// 文件时间分类组件
class FileTimeTypeWidget : public QFrame
{
    Q_OBJECT

public:
    explicit FileTimeTypeWidget(const QString &timeRange, const QList<FileTimeInfo> &files, QWidget *parent = nullptr);

    QString getTimeRange() const { return m_timeRange; }
    QList<FileTimeInfo> getSelectedFiles() const;
    QString getFolderName() const;

    void selectAll();
    void deselectAll();

private slots:
    void onFileSelectionChanged(const FileTimeInfo &fileInfo, bool selected);
    void onFileItemClicked(QListWidgetItem *item);

private:
    void setupUI();
    void populateFileList();
    QString getDefaultFolderName(const QString &timeRange);

    QString m_timeRange;
    QList<FileTimeInfo> m_files;
    QMap<QString, bool> m_fileSelection;  // 文件名 -> 选中状态

    QLabel *m_titleLabel;
    QLineEdit *m_folderNameEdit;
    QListWidget *m_fileList;
};

// 主预览窗口
class TimePreviewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TimePreviewWindow(QWidget *parent = nullptr);

    void setFileData(const QMap<QString, QList<FileTimeInfo>> &fileTimeData);

private slots:
    void selectAllFiles();
    void deselectAllFiles();
    void onCloseButtonClicked();

private:
    void setupUI();
    void clearContent();
    void createFileTimeTypeWidgets(const QMap<QString, QList<FileTimeInfo>> &fileTimeData);

    QScrollArea *m_horizontalScrollArea;
    QWidget *m_contentWidget;
    QHBoxLayout *m_contentLayout;
    QList<FileTimeTypeWidget*> m_fileTimeTypeWidgets;
};

#endif // TIMEPREVIEWWINDOW_H
