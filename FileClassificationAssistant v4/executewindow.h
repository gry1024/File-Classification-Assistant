// 执行分类窗口（进度条、撤销按钮等）
#ifndef EXECUTEWINDOW_H
#define EXECUTEWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QFileInfo>
#include <QPair>

class ExecuteWindow : public QDialog
{
    Q_OBJECT
public:

    // 新构造：需要根目录、待处理文件列表和分类模式
    ExecuteWindow(const QString& rootPath,
                  const QList<QFileInfo>& files,
                  const QMap<QString, QString> & floderMap,
                  QWidget *parent = nullptr);
    ~ExecuteWindow();

private slots:
    void updateProgress();            // 每次处理 1 个文件
    void onProcessFinished();         // 全部完成
    void on_finishButton_clicked();   // 完成按钮
    void on_undoButton_clicked();     // 撤销 / 中止

private:
    void setupUI();
    void startFileClassification();   // 启动定时器
    void undoFileClassification();    // 撤销已移动文件
    void resetProgress();

    // ---------- UI ----------
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QLabel      *titleLabel;
    QLabel      *statusLabel;
    QProgressBar*progressBar;
    QPushButton *finishButton;
    QPushButton *undoButton;

    // ---------- 运行数据 ----------
    QTimer                       *progressTimer;
    int                           currentProgress;
    bool                          isProcessing;
    bool                          isFinished;

    QString                       rootDir;     // 根目录
    QList<QFileInfo>              fileList;    // 要处理的文件
    QMap<QString,QString>         floderNameMap;
    int                           currentIndex;// 当前处理到的文件下标
    QList<QPair<QString,QString>> history;     // <现路径, 原路径> 用于撤销
};

#endif // EXECUTEWINDOW_H
