#include "classificationwindow.h"
#include "executewindow.h"
#include "ui_classificationwindow.h"
#include <QtAlgorithms>
#include <QDir>
#include <QtCharts>

classificationWindow::classificationWindow(const QString& Path, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::classificationWindow)
{
    ui->setupUi(this);
    selectedPath = Path;
    resize(1000, 800);
    qDebug() << "selectedPath:" << selectedPath;
    updateFileStatistics();

}

classificationWindow::~classificationWindow()
{
    delete ui;
}

// 初始化图表配置
void classificationWindow::initChart()
{
    // 创建图表和视图
    fileTypeChart = new QChart();
    fileTypeChartView = ui->fileTypeChartView;
    fileTypeChartView->setChart(fileTypeChart);

    // 设置抗锯齿
    fileTypeChartView->setRenderHint(QPainter::Antialiasing);
    // 设置动画效果
    fileTypeChart->setAnimationOptions(QChart::AllAnimations);

    // 设置图表边距
    fileTypeChart->setMargins(QMargins(10, 20, 10, 40));  // 下边距增加
    // fileTypeChart->setMargins(QMargins(10, 10, 10, 10));

    // 设置图表标题
    fileTypeChart->setTitle("文件类型占比");

    // 隐藏图例（关键代码）
    fileTypeChart->legend()->hide();

}

void classificationWindow::updateFileStatistics(){
    QDir dir(selectedPath);
    if (!dir.exists()) {
        return;
    }

    // 统计文件总数
    int totalFileCount = 0;
    // 用于存储文件类型及其数量的映射
    QMap<QString, int> fileTypeCount;

    // 遍历目录下的文件
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::Readable);
    for (const QFileInfo &fileInfo : fileList) {
        if (fileInfo.isFile()) {
            totalFileCount++;
            QString fileType = fileInfo.suffix();
            if (fileTypeCount.contains(fileType)) {
                fileTypeCount[fileType]++;
            } else {
                fileTypeCount[fileType] = 1;
            }
        }
    }
    // 分组逻辑示例：将占比小于一定比例的文件类型合并为“其他”
    QMap<QString, int> groupedFileTypeCount;
    int thresholdCount = totalFileCount * 0.05; // 占比小于5%的归为其他
    for (const QString &type : fileTypeCount.keys()) {
        int count = fileTypeCount[type];
        if (count >= thresholdCount) {
            groupedFileTypeCount[type] = count;
        } else {
            if (!groupedFileTypeCount.contains("其他")) {
                groupedFileTypeCount["其他"] = 0;
            }
            groupedFileTypeCount["其他"] += count;
        }
    }
    // 更新数据显示
    ui->pathLabel->setWordWrap(true);
    ui->pathLabel->setText(QString("路径：%1").arg(selectedPath));
    ui->totalFileCountLabel->setText(QString("文件总数：%1      文件类型数：%2").arg(totalFileCount).arg(fileTypeCount.size()));

    // 绘制饼图
    initChart();
    updateChart(groupedFileTypeCount, totalFileCount);
}

// 更新图表数据
void classificationWindow::updateChart(const QMap<QString, int>& fileTypeCount, int totalCount)
{
    // 清除现有系列
    fileTypeChart->removeAllSeries();

    // 创建饼图系列
    QPieSeries *series = new QPieSeries();

    // 添加数据到系列
    for (auto it = fileTypeCount.begin(); it != fileTypeCount.end(); ++it) {
        QString fileType = it.key();
        int count = it.value();
        double percentage = (double)count / totalCount * 100;

        // 添加扇形
        QPieSlice *slice = series->append(
            QString("%1(%2个)").arg(fileType).arg(count),
            count
            );

        // 强制显示完整标签
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside); // 标签位置在外部
        slice->setLabelArmLengthFactor(0.2);  // 调整标签延伸线长度



    }

    // 将系列添加到图表
    fileTypeChart->addSeries(series);
}



// 返回
void classificationWindow::on_backButton_clicked()
{
    close();
}

