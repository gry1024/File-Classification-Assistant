#ifndef CLASSIFICATIONWINDOW_H
#define CLASSIFICATIONWINDOW_H
#include <QtCharts>
#include <QDialog>
#include <QScrollArea>
#include <QHBoxLayout>

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

private:
    Ui::classificationWindow *ui;
    QString selectedPath = "";
    QChartView *fileTypeChartView; // 用于显示饼图的视图
    QChart *fileTypeChart; // 饼图的图表对象


};

#endif // CLASSIFICATIONWINDOW_H
