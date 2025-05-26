// 文件面板及分类方案选择主界面
#ifndef CLASSIFICATIONWINDOW_H
#define CLASSIFICATIONWINDOW_H
#include <QDialog>
#include <QMap>
#include <QtCharts>
#include <QFileInfo>

namespace Ui {
class classificationWindow;
}

class classificationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit classificationWindow(const QString& Path, QWidget *parent = nullptr);
    ~classificationWindow();

private slots:
    void initChart();
    void updateFileStatistics();
    void updateChart(const QMap<QString, int>& fileTypeCount, int totalCount);
    void on_backButton_clicked();
    void on_pushButton_clicked(); // "按文件类型分类"
    void on_pushButton_size_clicked(); // "按文件体积分类"
    void on_pushButton_time_clicked(); // "按文件修改时间分类"

private:
    QString getFileSizeCategory(qint64 fileSize);
    QString formatFileSize(qint64 size);

    Ui::classificationWindow *ui;
    QString selectedPath = ""; // 选择的文件目录路径

    // 文件类型图表相关
    QChartView *fileTypeChartView;
    QChart *fileTypeChart;

};

#endif // CLASSIFICATIONWINDOW_H
