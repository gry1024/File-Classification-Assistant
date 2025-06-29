// 文件面板及分类方案选择主界面
#ifndef CLASSIFICATIONWINDOW_H
#define CLASSIFICATIONWINDOW_H
#include <QDialog>
#include <QMap>
#include <QtCharts>
#include <QFileInfo>
#include <QDirIterator>
#include <QFileInfo>
#include <QDateTime>

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

    void on_doubleSpinBox_smallKB_valueChanged(double value); // 第一个文件大小区间
    void on_doubleSpinBox_smallMB_valueChanged(double value); // 第二个文件大小区间
    void on_doubleSpinBox_lowerMB_valueChanged(double value); // 第三个文件大小区间下界
    void on_doubleSpinBox_upperMB_valueChanged(double value); // 第三个文件大小区间上界
    void on_doubleSpinBox_largeMB_valueChanged(double value); // 第四个文件区间

    void on_checkBox_smallKB_clicked(bool state);   // 文件大小 第一个选择框
    void on_checkBox_smallMB_clicked(bool state);   // 文件大小 第二个选择框
    void on_checkBox_betweenMB_clicked(bool state); // 文件大小 第三个选择框
    void on_checkBox_largeMB_clicked(bool state);   // 文件大小 第四个选择框

    void on_checkBox_type1_clicked(bool state); // 类型选择1
    void on_checkBox_type2_clicked(bool state); // 类型选择2

    void on_checkBox_days_clicked(bool state);   // 文件日期 天数选择框
    void on_checkBox_months_clicked(bool state); // 文件日期 月数选择框
    void on_checkBox_years_clicked(bool state);  // 文件日期 年数选择框

    void on_spinBox_days_valueChanged(int value);   // 文件日期 天数
    void on_spinBox_months_valueChanged(int value); // 文件日期 月数
    void on_spinBox_years_valueChanged(int value);  // 文件日期 年数

private:
    QString getFileSizeCategory(qint64 fileSize);
    QString formatFileSize(qint64 size);

    Ui::classificationWindow *ui;
    QString selectedPath = ""; // 选择的文件目录路径

    // 文件类型图表相关
    QChartView *fileTypeChartView;
    QChart *fileTypeChart;
private:
    QList<QFileInfo> collectAllFiles() const;   // 递归收集文件

    bool is_smallKB_used;
    bool is_smallMB_used;
    bool is_betweenMB_used;
    bool is_largeMB_used;

    bool is_type1_activated;
    bool is_type2_activated;

    bool is_days_used;
    bool is_months_used;
    bool is_years_used;
};

#endif // CLASSIFICATIONWINDOW_H
