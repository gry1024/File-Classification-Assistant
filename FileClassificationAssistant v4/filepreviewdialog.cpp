// filepreviewdialog.cpp
#include "filepreviewdialog.h"
#include <QPlainTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>
#include <QScreen>
#include <QApplication>
#include <QSizePolicy>

FilePreviewDialog::FilePreviewDialog(const QFileInfo& fileInfo, QWidget* parent)
    : QDialog(parent), m_fileInfo(fileInfo)
{
    setWindowTitle("文件预览 - " + fileInfo.fileName());
    resize(800, 600);

    // 创建主布局
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(5, 5, 5, 5);

    // 创建预览区域
    if (isImageFile(fileInfo.suffix())) {
        m_imagePreview = new QLabel(this);
        m_imagePreview->setAlignment(Qt::AlignCenter);
        m_imagePreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QScrollArea* scrollArea = new QScrollArea(this);
        scrollArea->setWidget(m_imagePreview);
        scrollArea->setWidgetResizable(true);
        m_layout->addWidget(scrollArea);
    } else {
        m_textPreview = new QPlainTextEdit(this);
        m_textPreview->setReadOnly(true);
        m_textPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_layout->addWidget(m_textPreview);
    }

    loadFileContent();
}

void FilePreviewDialog::loadFileContent() {
    if (isImageFile(m_fileInfo.suffix())) {
        QPixmap pixmap(m_fileInfo.filePath());
        if (pixmap.isNull()) {
            QMessageBox::warning(this, "预览错误", "无法加载图片文件: " + m_fileInfo.fileName());
            return;
        }

        // 缩放图片以适应屏幕
        QScreen* screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();
        int maxWidth = screenGeometry.width() * 0.8;
        int maxHeight = screenGeometry.height() * 0.8;

        if (pixmap.width() > maxWidth || pixmap.height() > maxHeight) {
            pixmap = pixmap.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }

        m_imagePreview->setPixmap(pixmap);
    }
    else if (isTextFile(m_fileInfo.suffix())) {
        QFile file(m_fileInfo.filePath());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "预览错误", "无法打开文件: " + m_fileInfo.fileName());
            return;
        }

        QTextStream in(&file);
        in.setEncoding(QStringConverter::Utf8);
        QString content = in.readAll();
        file.close();

        // 限制大文件预览
        const qint64 maxFileSize = 5 * 1024 * 1024; // 5MB
        if (m_fileInfo.size() > maxFileSize) {
            content = content.left(1024 * 1024) +
                      "\n\n[文件过大，已截断预览 - 完整大小: " +
                      QString::number(m_fileInfo.size() / 1024.0 / 1024.0, 'f', 2) + " MB]";
        }

        m_textPreview->setPlainText(content);
    }
    else {
        if (m_textPreview) {
            m_textPreview->setPlainText("不支持预览此类型文件: " + m_fileInfo.fileName());
        } else {
            QLabel* label = new QLabel("不支持预览此类型文件: " + m_fileInfo.fileName(), this);
            m_layout->addWidget(label);
        }
    }
}

bool FilePreviewDialog::isImageFile(const QString& suffix) const {
    static const QStringList imageExtensions = {"jpg", "jpeg", "png", "bmp", "gif", "tiff", "webp"};
    return imageExtensions.contains(suffix.toLower());
}

bool FilePreviewDialog::isTextFile(const QString& suffix) const {
    static const QStringList textExtensions = {
        "txt", "cpp", "h", "hpp", "c", "cs", "java", "py", "js", "html", "css",
        "xml", "json", "ini", "conf", "md", "log", "csv", "php", "sql", "sh", "bat"
    };
    return textExtensions.contains(suffix.toLower());
}
