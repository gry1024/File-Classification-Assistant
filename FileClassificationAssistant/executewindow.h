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

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class ExecuteWindow : public QDialog
{
    Q_OBJECT

public:
    ExecuteWindow(QWidget *parent = nullptr);
    ~ExecuteWindow();

private slots:
    void on_finishButton_clicked(); // 完成按钮
    void on_undoButton_clicked(); // 撤销按钮
    void updateProgress(); // 进度条
    void onProcessFinished(); // 完成分类

private:
    void setupUI();
    void startFileClassification(); // 文件分类处理逻辑（后端）
    void resetProgress();

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QLabel *titleLabel;
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QPushButton *finishButton;
    QPushButton *undoButton;

    QTimer *progressTimer;
    int currentProgress;
    bool isProcessing;
    bool isFinished;
};

#endif // EXECUTEWINDOW_H
