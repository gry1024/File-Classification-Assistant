// filepreviewdialog.h
#ifndef FILEPREVIEWDIALOG_H
#define FILEPREVIEWDIALOG_H

#include <QDialog>
#include <QFileInfo>

class QPlainTextEdit;
class QLabel;
class QVBoxLayout;

class FilePreviewDialog : public QDialog {
    Q_OBJECT
public:
    explicit FilePreviewDialog(const QFileInfo& fileInfo, QWidget* parent = nullptr);

private:
    void loadFileContent();
    bool isImageFile(const QString& suffix) const;
    bool isTextFile(const QString& suffix) const;

    QFileInfo m_fileInfo;
    QPlainTextEdit* m_textPreview;
    QLabel* m_imagePreview;
    QVBoxLayout* m_layout;
};

#endif // FILEPREVIEWDIALOG_H
