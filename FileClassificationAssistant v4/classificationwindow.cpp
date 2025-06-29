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

    ui->checkBox_smallKB->setChecked(false);
    is_smallKB_used = false;

    is_type1_activated = true;
    is_type2_activated = false;

    is_days_used = true;
    is_months_used = false;
    is_years_used = false;
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
    fileTypeChart->setMargins(QMargins(10, 1, 10, 10));

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
    if (is_type1_activated) {
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
    }
    else if (is_type2_activated) {
        for (const QString & type : fileTypeCount.keys()) {
            int count = fileTypeCount[type];
            groupedFileTypeCount[type] = count;
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
    double smallKB = ui->doubleSpinBox_smallKB->value();
    double smallMB = ui->doubleSpinBox_smallMB->value();
    double lowerMB = ui->doubleSpinBox_lowerMB->value();
    double upperMB = ui->doubleSpinBox_upperMB->value();
    double largeMB = ui->doubleSpinBox_largeMB->value();
    if (fileSize <= smallKB * 1024 && is_smallKB_used) {
        return QString("小文件 (< %1KB)").arg(smallKB);
    } else if (fileSize <= smallMB * 1024 * 1024 && is_smallMB_used) {
        return QString("中等文件 (< %1MB)").arg(smallMB);
    } else if (fileSize <= upperMB * 1024 * 1024 && fileSize >= lowerMB * 1024 * 1024 && is_betweenMB_used) {
        return QString("大文件 (%1MB - %2MB)").arg(lowerMB).arg(upperMB);
    } else if (fileSize >= largeMB * 1024 * 1024 && is_largeMB_used) {
        return QString("超大文件 (> %1MB)").arg(largeMB);
    }
    return QString("其他大小文件");
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
    const auto files = collectAllFiles();
    int totalCount = files.size();

    // 统计每种后缀出现的次数
    QMap<QString, int> suffixCount;
    for (const QFileInfo &fi : files) {
        QString suffix = fi.suffix().toLower();
        if (suffix.isEmpty()) suffix = "无后缀";
        suffixCount[suffix]++;
    }

    QMap<QString, QStringList> fileData;          // <类型, 文件名列表>
    QMap<QString, QString> folderMap;             // 文件夹名称映射

    if (is_type1_activated) {
        // TYPE1 策略: 占比5%以下合并为"其他"
        double threshold = totalCount * 0.05; // 最小数量阈值

        // 构建分类映射 (后缀 -> 最终分类名)
        QMap<QString, QString> suffixToCategory;
        for (auto it = suffixCount.constBegin(); it != suffixCount.constEnd(); ++it) {
            QString suffix = it.key();
            if (it.value() >= threshold) {
                suffixToCategory[suffix] = suffix; // 占比大保留原名
            } else {
                suffixToCategory[suffix] = "其他";  // 占比小合并为"其他"
            }
        }

        // 使用映射表归类文件
        for (const QFileInfo &fi : files) {
            QString suffix = fi.suffix().toLower();
            if (suffix.isEmpty()) suffix = "无后缀";
            QString category = suffixToCategory[suffix];

            fileData[category] << fi.fileName();
            folderMap[fi.fileName()] = category;
        }
    }
    else if (is_type2_activated) {
        // TYPE2 策略: 所有类型独立处理 (不合并)
        for (const QFileInfo &fi : files) {
            QString suffix = fi.suffix().toLower();
            if (suffix.isEmpty()) suffix = "无后缀";

            fileData[suffix] << fi.fileName();
            folderMap[fi.fileName()] = suffix;
        }
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

    int days = ui->spinBox_days->value();
    int months = ui->spinBox_months->value();
    int years = ui->spinBox_years->value();

    const auto files = collectAllFiles();
    for (const QFileInfo &fi : files)
    {
        QDateTime file_time = fi.lastModified();
        QDateTime curr = QDateTime::currentDateTime();
        QDateTime days_back = curr.addDays(-days);
        QDateTime months_back = curr.addDays(-months * 30);
        QDateTime years_back = curr.addDays(-years * 365);

        QString bucket;

        if (file_time >= days_back && is_days_used)
        {
            bucket = QString("%1天内").arg(days);
        }

        else if (file_time >= months_back && is_months_used)
        {
            bucket = QString("%1月内").arg(months);
        }

        else if (file_time >= years_back && is_years_used)
        {
            bucket = QString("%1年内").arg(years);
        }

        if (bucket == "")
        {
            bucket = timeBucket(file_time);
        }

        fileTimeData[bucket] << FileTimeInfo(fi.fileName(), fi.lastModified(), fi.filePath());
        folderMap[fi.fileName()] = bucket;
    }

    // 打开预览
    TimePreviewWindow *w = new TimePreviewWindow(selectedPath,folderMap, this);
    w->setFileData(fileTimeData);
    w->exec();
    w->deleteLater();
}


void classificationWindow::on_doubleSpinBox_smallKB_valueChanged(double value)
{
    ui->doubleSpinBox_smallKB->setValue(value);
}

void classificationWindow::on_doubleSpinBox_smallMB_valueChanged(double value)
{
    ui->doubleSpinBox_smallMB->setValue(value);
}

void classificationWindow::on_doubleSpinBox_lowerMB_valueChanged(double value)
{
    ui->doubleSpinBox_lowerMB->setValue(value);
}

void classificationWindow::on_doubleSpinBox_upperMB_valueChanged(double value)
{
    ui->doubleSpinBox_upperMB->setValue(value);
}

void classificationWindow::on_doubleSpinBox_largeMB_valueChanged(double value)
{
    ui->doubleSpinBox_largeMB->setValue(value);
}

void classificationWindow::on_checkBox_smallKB_clicked(bool state)
{
    is_smallKB_used = state;
}

void classificationWindow::on_checkBox_smallMB_clicked(bool state)
{
    is_smallMB_used = state;
}

void classificationWindow::on_checkBox_betweenMB_clicked(bool state)
{
    is_betweenMB_used = state;
}

void classificationWindow::on_checkBox_largeMB_clicked(bool state)
{
    is_largeMB_used = state;
}

void classificationWindow::on_checkBox_type1_clicked(bool state)
{
    ui->checkBox_type2->setChecked(!state);
    is_type2_activated = !state;
    is_type1_activated = state;
    updateFileStatistics();
}

void classificationWindow::on_checkBox_type2_clicked(bool state)
{
    ui->checkBox_type1->setChecked(!state);
    is_type1_activated = !state;
    is_type2_activated = state;
    updateFileStatistics();
}

void classificationWindow::on_checkBox_days_clicked(bool state)
{
    is_days_used = state;
}

void classificationWindow::on_checkBox_months_clicked(bool state)
{
    is_months_used = state;
}

void classificationWindow::on_checkBox_years_clicked(bool state)
{
    is_years_used = state;
}

void classificationWindow::on_spinBox_days_valueChanged(int value)
{
    ui->spinBox_days->setValue(value);
}

void classificationWindow::on_spinBox_months_valueChanged(int value)
{
    ui->spinBox_months->setValue(value);
}

void classificationWindow::on_spinBox_years_valueChanged(int value)
{
    ui->spinBox_years->setValue(value);
}
