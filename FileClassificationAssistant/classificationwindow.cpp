// 文件面板及分类方案选择主界面
#include "classificationwindow.h"
#include "ui_classificationwindow.h"
#include "previewwindow.h"
#include "sizepreviewwindow.h"
#include "timepreviewwindow.h"
#include <QtAlgorithms>
#include <QDir>
#include <QtCharts>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>

#include <QFileInfo>
#include <QDateTime>



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


// 把 selectedPath 下所有文件都收集出来
QList<QFileInfo> classificationWindow::collectAllFiles() const
{
    QDir dir(selectedPath);
    return dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot |
                                 QDir::Hidden | QDir::System | QDir::Readable,
                             QDir::Name);      // 排序方式随意
}

// 初始化文件类型图表配置
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
    fileTypeChart->setMargins(QMargins(10, 10, 10, 10));

    // 设置图表标题
    fileTypeChart->setTitle("文件类型占比");

    // 隐藏图例
    fileTypeChart->legend()->hide();
}


void classificationWindow::updateFileStatistics(){
    //selectedPath：用户选择的文件夹路径
    QDir dir(selectedPath);
    if (!dir.exists()) {
        return;
    }
    // 统计文件总数
    int totalFileCount = 0;
    qint64 totalFileSize = 0;
    // 用于存储文件类型及其数量的映射
    QMap<QString, int> fileTypeCount;
    // 用于存储文件大小分类及其数量和总大小的映射
    QMap<QString, int> fileSizeCount;
    QMap<QString, qint64> fileSizeTotalSize;

    // 遍历目录下的文件
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::Readable);
    for (const QFileInfo &fileInfo : fileList) {
        if (fileInfo.isFile()) {
            totalFileCount++;
            qint64 fileSize = fileInfo.size();
            totalFileSize += fileSize;

            // 统计文件类型
            QString fileType = fileInfo.suffix();
            if (fileTypeCount.contains(fileType)) {
                fileTypeCount[fileType]++;
            } else {
                fileTypeCount[fileType] = 1;
            }

            // 统计文件大小分类
            QString sizeCategory = getFileSizeCategory(fileSize);
            if (fileSizeCount.contains(sizeCategory)) {
                fileSizeCount[sizeCategory]++;
                fileSizeTotalSize[sizeCategory] += fileSize;
            } else {
                fileSizeCount[sizeCategory] = 1;
                fileSizeTotalSize[sizeCategory] = fileSize;
            }
        }
    }

    // 分组逻辑示例：将占比小于一定比例的文件类型合并为"其他"
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
    ui->totalFileCountLabel->setText(QString("文件总数：%1      文件类型数：%2      总大小：%3").arg(totalFileCount).arg(fileTypeCount.size()).arg(formatFileSize(totalFileSize)));

    // 绘制文件类型饼图
    initChart();
    updateChart(groupedFileTypeCount, totalFileCount);
}

// 获取文件大小分类
QString classificationWindow::getFileSizeCategory(qint64 fileSize)
{
    if (fileSize < 1024) {
        return "小文件 (< 1KB)";
    } else if (fileSize < 1024 * 1024) {
        return "中等文件 (1KB - 1MB)";
    } else if (fileSize < 100 * 1024 * 1024) {
        return "大文件 (1MB - 100MB)";
    } else {
        return "超大文件 (> 100MB)";
    }
}

// 格式化文件大小显示
QString classificationWindow::formatFileSize(qint64 size)
{
    if (size < 1024) {
        return QString("%1 B").arg(size);
    } else if (size < 1024 * 1024) {
        return QString("%1 KB").arg(QString::number(size / 1024.0, 'f', 1));
    } else if (size < 1024 * 1024 * 1024) {
        return QString("%1 MB").arg(QString::number(size / (1024.0 * 1024.0), 'f', 1));
    } else {
        return QString("%1 GB").arg(QString::number(size / (1024.0 * 1024.0 * 1024.0), 'f', 1));
    }
}

// 更新文件类型图表数据
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

// click"按文件类型分类"
void classificationWindow::on_pushButton_clicked()
{
    QMap<QString, QStringList> fileData;          // <类型, 文件名列表>
    QMap<QString, QString> folderMap;             // 文件夹名称映射

    const auto files = collectAllFiles();
    for (const QFileInfo &fi : files)
    {
        QString suffix = fi.suffix().toLower();
        if (suffix.isEmpty()) suffix = "无后缀";

        fileData[suffix] << fi.fileName();        // 只展示文件名，如需完整路径改成 fi.filePath()
        folderMap[fi.fileName()] = suffix;
    }

    // 打开预览
    PreviewWindow *w = new PreviewWindow(selectedPath,folderMap, this);
    w->setFileData(fileData);
    w->exec();
    w->deleteLater();
}

//click"按文件体积分类"
void classificationWindow::on_pushButton_size_clicked()
{
    QMap<QString, QList<FileInfo>> fileSizeData;      // <区间, 文件信息列表>
    QMap<QString, QString> folderMap;

    const auto files = collectAllFiles();
    for (const QFileInfo &fi : files)
    {
        qint64 sz = fi.size();
        QString cat = getFileSizeCategory(sz);        // 您已有的函数
        fileSizeData[cat] << FileInfo(fi.fileName(), sz, fi.filePath());
        folderMap[fi.fileName()] = cat;
    }

    SizePreviewWindow *w = new SizePreviewWindow(selectedPath, folderMap, this);
    w->setFileData(fileSizeData);
    w->exec();
    w->deleteLater();
}

// 工具：返回所属时间段名称
static QString timeBucket(const QDateTime& mtime)
{
    QDateTime now   = QDateTime::currentDateTime();
    QDateTime today0(now.date(), QTime(0,0));
    QDateTime yesterday0 = today0.addDays(-1);
    QDateTime week0 = today0.addDays(-today0.date().dayOfWeek()+1);      // 周一 0 点
    QDateTime month0(QDate(today0.date().year(), today0.date().month(), 1), QTime(0,0));
    QDateTime year0 (QDate(today0.date().year(), 1, 1),QTime(0,0));

    if (mtime >= today0)                 return "今天";
    if (mtime >= yesterday0)             return "昨天";
    if (mtime >= week0)                  return "本周";
    if (mtime >= month0)                 return "本月";
    if (mtime >= year0)                  return "今年";
    return "更早";
}

void classificationWindow::on_pushButton_time_clicked()
{
    QMap<QString, QList<FileTimeInfo>> fileTimeData;  // <区间, 文件信息列表>
    QMap<QString, QString> folderMap;

    const auto files = collectAllFiles();
    for (const QFileInfo &fi : files)
    {
        QString bucket = timeBucket(fi.lastModified());
        fileTimeData[bucket] << FileTimeInfo(fi.fileName(), fi.lastModified(), fi.filePath());
        folderMap[fi.fileName()] = bucket;
    }

    // 打开预览
    TimePreviewWindow *w = new TimePreviewWindow(selectedPath,folderMap, this);
    w->setFileData(fileTimeData);
    w->exec();
    w->deleteLater();
}
