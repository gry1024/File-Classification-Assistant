// 选择目录窗口
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_choseFileButton_clicked(); //选择路径 按钮

private:
    QString selectedPath = "";
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
