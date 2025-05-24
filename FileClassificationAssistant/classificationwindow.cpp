#include "classificationwindow.h"
#include "executewindow.h"
#include "ui_classificationwindow.h"
#include "previewwindow.h"
#include "sizepreviewwindow.h"
#include "timepreviewwindow.h"
#include <QtAlgorithms>
#include <QDir>
#include <QtCharts>
#include <QDateTime>
#include <QDate>

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
    //selectedPath：用户选择的文件夹路径
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

// click"按文件类型分类"
void classificationWindow::on_pushButton_clicked()
{
    // 准备测试数据
    QMap<QString, QStringList> fileData;

    fileData["文本文件"] = QStringList()
                           << "document1.txt" << "readme.txt" << "notes.txt"
                           << "report.txt" << "log.txt" << "data.txt"
                           << "config.txt" << "manual.txt" << "info.txt";

    fileData["Word文档"] = QStringList()
                           << "proposal.doc" << "contract.docx" << "letter.doc"
                           << "resume.docx" << "report.doc" << "manual.docx";

    fileData["PDF文件"] = QStringList()
                          << "handbook.pdf" << "guide.pdf" << "specification.pdf"
                          << "tutorial.pdf" << "brochure.pdf";

    fileData["图片文件"] = QStringList()
                           << "photo1.jpg" << "logo.png" << "chart.jpg"
                           << "diagram.png" << "screenshot.jpg" << "icon.png"
                           << "banner.jpg" << "thumbnail.png" << "pp.png" << "ioio.png" << "kppppppppppppppppphnmmmmmmmmmmmmmmmmmk.png";

    fileData["Excel文件"] = QStringList()
                            << "budget.xlsx" << "data.xls" << "report.xlsx"
                            << "analysis.xls" << "summary.xlsx";

    // 创建并显示预览窗口
    PreviewWindow *previewWindow = new PreviewWindow(this);
    previewWindow->setFileData(fileData);
    previewWindow->exec();

    // 窗口会自动清理，因为使用了exec()
    previewWindow->deleteLater();
}
//click"按文件体积分类"
void classificationWindow::on_pushButton_size_clicked()
{
    QMap<QString, QList<FileInfo>> fileSizeData;

    // 小文件 (< 1KB)
    QList<FileInfo> smallFiles;
    smallFiles << FileInfo("config.ini", 256, "/path/to/config.ini")
               << FileInfo("readme.txt", 512, "/path/to/readme.txt")
               << FileInfo("license.txt", 1000, "/path/to/license.txt")
               << FileInfo("version.info", 128, "/path/to/version.info")
               << FileInfo("changelog.md", 800, "/path/to/changelog.md");
    fileSizeData["小文件 (< 1KB)"] = smallFiles;

    // 中等文件 (1KB - 1MB)
    QList<FileInfo> mediumFiles;
    mediumFiles << FileInfo("document.doc", 50 * 1024, "/path/to/document.doc")          // 50KB
                << FileInfo("presentation.ppt", 200 * 1024, "/path/to/presentation.ppt")  // 200KB
                << FileInfo("spreadsheet.xls", 150 * 1024, "/path/to/spreadsheet.xls")    // 150KB
                << FileInfo("report.pdf", 800 * 1024, "/path/to/report.pdf")              // 800KB
                << FileInfo("manual.pdf", 1000 * 1024, "/path/to/manual.pdf")             // 1000KB
                << FileInfo("data.csv", 75 * 1024, "/path/to/data.csv")                   // 75KB
                << FileInfo("script.py", 25 * 1024, "/path/to/script.py");                // 25KB
    fileSizeData["中等文件 (1KB - 1MB)"] = mediumFiles;

    // 大文件 (1MB - 100MB)
    QList<FileInfo> largeFiles;
    largeFiles << FileInfo("video_sample.mp4", 25 * 1024 * 1024, "/path/to/video_sample.mp4")     // 25MB
               << FileInfo("audio_track.wav", 50 * 1024 * 1024, "/path/to/audio_track.wav")        // 50MB
               << FileInfo("high_res_image.psd", 80 * 1024 * 1024, "/path/to/high_res_image.psd")  // 80MB
               << FileInfo("database_backup.sql", 45 * 1024 * 1024, "/path/to/database_backup.sql") // 45MB
               << FileInfo("software_installer.exe", 35 * 1024 * 1024, "/path/to/software_installer.exe") // 35MB
               << FileInfo("presentation_video.mov", 60 * 1024 * 1024, "/path/to/presentation_video.mov"); // 60MB
    fileSizeData["大文件 (1MB - 100MB)"] = largeFiles;

    // 超大文件 (> 100MB)
    QList<FileInfo> hugeFiles;
    hugeFiles << FileInfo("movie_full_hd.mkv", static_cast<qint64>(1.5 * 1024 * 1024 * 1024), "/path/to/movie_full_hd.mkv")  // 1.5GB
              << FileInfo("system_image.iso", static_cast<qint64>(4.2 * 1024 * 1024 * 1024), "/path/to/system_image.iso")     // 4.2GB
              << FileInfo("virtual_machine.vdi", static_cast<qint64>(8.0 * 1024 * 1024 * 1024), "/path/to/virtual_machine.vdi") // 8GB
              << FileInfo("game_archive.zip", static_cast<qint64>(2.8 * 1024 * 1024 * 1024), "/path/to/game_archive.zip");    // 2.8GB
    fileSizeData["超大文件 (> 100MB)"] = hugeFiles;

    // 创建并显示预览窗口
    SizePreviewWindow *sizePreviewWindow = new SizePreviewWindow(this);
    sizePreviewWindow->setFileData(fileSizeData);
    sizePreviewWindow->exec();

    // 窗口会自动清理，因为使用了exec()
    sizePreviewWindow->deleteLater();
}

// click"按文件修改时间分类"
void classificationWindow::on_pushButton_time_clicked()
{
    // 准备测试数据 - 按文件修改时间分类
    QMap<QString, QList<FileTimeInfo>> fileTimeData;
    QDateTime now = QDateTime::currentDateTime();
    QDateTime today = QDateTime(QDate::currentDate(), QTime(0, 0));
    QDateTime yesterday = today.addDays(-1);  // 添加昨天变量定义
    QDateTime thisWeekStart = QDateTime(today.date().addDays(-today.date().dayOfWeek() + 1), QTime(0, 0));
    QDateTime lastWeekStart = QDateTime(thisWeekStart.date().addDays(-7), QTime(0, 0));
    QDateTime thisMonthStart = QDateTime(QDate(today.date().year(), today.date().month(), 1), QTime(0, 0));
    QDateTime lastMonthStart = QDateTime(thisMonthStart.date().addMonths(-1), QTime(0, 0));
    QDateTime thisYearStart = QDateTime(QDate(today.date().year(), 1, 1), QTime(0, 0));

    // 今天修改的文件
    QList<FileTimeInfo> todayFiles;
    todayFiles << FileTimeInfo("current_work.docx", now.addSecs(-2 * 3600), "/documents/current_work.docx")  // addSecs(-2小时)
               << FileTimeInfo("meeting_notes.txt", now.addSecs(-1 * 3600), "/notes/meeting_notes.txt")      // addSecs(-1小时)
               << FileTimeInfo("project_update.xlsx", now.addSecs(-30 * 60), "/projects/project_update.xlsx") // addSecs(-30分钟)
               << FileTimeInfo("temp_file.tmp", now.addSecs(-15 * 60), "/temp/temp_file.tmp")                // addSecs(-15分钟)
               << FileTimeInfo("log_today.log", now.addSecs(-5 * 60), "/logs/log_today.log");               // addSecs(-5分钟)
    fileTimeData["今天 (5个文件)"] = todayFiles;

    // 昨天修改的文件
    QList<FileTimeInfo> yesterdayFiles;
    yesterdayFiles << FileTimeInfo("report_draft.pdf", yesterday.addSecs(14 * 3600), "/reports/report_draft.pdf")      // +14小时
                   << FileTimeInfo("backup_config.ini", yesterday.addSecs(10 * 3600), "/config/backup_config.ini")     // +10小时
                   << FileTimeInfo("photo_edit.jpg", yesterday.addSecs(16 * 3600), "/images/photo_edit.jpg")           // +16小时
                   << FileTimeInfo("script_v2.py", yesterday.addSecs(9 * 3600), "/scripts/script_v2.py");              // +9小时
    fileTimeData["昨天 (4个文件)"] = yesterdayFiles;

    // 本周修改的文件
    QList<FileTimeInfo> thisWeekFiles;
    thisWeekFiles << FileTimeInfo("weekly_summary.docx", thisWeekStart.addDays(2).addSecs(15 * 3600), "/documents/weekly_summary.docx")
                  << FileTimeInfo("client_proposal.pptx", thisWeekStart.addDays(1).addSecs(10 * 3600), "/presentations/client_proposal.pptx")
                  << FileTimeInfo("database_schema.sql", thisWeekStart.addDays(3).addSecs(14 * 3600), "/database/database_schema.sql")
                  << FileTimeInfo("test_results.csv", thisWeekStart.addDays(4).addSecs(11 * 3600), "/data/test_results.csv")
                  << FileTimeInfo("user_manual.pdf", thisWeekStart.addDays(2).addSecs(9 * 3600), "/docs/user_manual.pdf");
    fileTimeData["本周 (5个文件)"] = thisWeekFiles;

    // 本月修改的文件
    QList<FileTimeInfo> thisMonthFiles;
    thisMonthFiles << FileTimeInfo("monthly_report.xlsx", thisMonthStart.addDays(5).addSecs(14 * 3600), "/reports/monthly_report.xlsx")
                   << FileTimeInfo("system_backup.zip", thisMonthStart.addDays(10).addSecs(2 * 3600), "/backups/system_backup.zip")
                   << FileTimeInfo("invoice_template.docx", thisMonthStart.addDays(15).addSecs(16 * 3600), "/templates/invoice_template.docx")
                   << FileTimeInfo("conference_video.mp4", thisMonthStart.addDays(8).addSecs(10 * 3600), "/videos/conference_video.mp4")
                   << FileTimeInfo("budget_analysis.xlsx", thisMonthStart.addDays(12).addSecs(13 * 3600), "/finance/budget_analysis.xlsx")
                   << FileTimeInfo("design_mockup.psd", thisMonthStart.addDays(18).addSecs(11 * 3600), "/design/design_mockup.psd");
    fileTimeData["本月 (6个文件)"] = thisMonthFiles;

    // 上月修改的文件
    QList<FileTimeInfo> lastMonthFiles;
    lastMonthFiles << FileTimeInfo("archive_data.zip", lastMonthStart.addDays(20).addSecs(10 * 3600), "/archive/archive_data.zip")
                   << FileTimeInfo("old_config.conf", lastMonthStart.addDays(25).addSecs(14 * 3600), "/config/old_config.conf")
                   << FileTimeInfo("expired_logs.log", lastMonthStart.addDays(28).addSecs(8 * 3600), "/logs/expired_logs.log");
    fileTimeData["上月 (3个文件)"] = lastMonthFiles;

    // 更早的文件
    QList<FileTimeInfo> olderFiles;
    olderFiles << FileTimeInfo("annual_report_2023.pdf", QDateTime(QDate(2023,12,15), QTime(16,30)), "/reports/annual_report_2023.pdf")
               << FileTimeInfo("foundation_docs.rar", QDateTime(QDate(2023,6,1), QTime(9,0)), "/archive/foundation_docs.rar")
               << FileTimeInfo("legacy_system.exe", QDateTime(QDate(2022,8,20), QTime(14,15)), "/systems/legacy_system.exe");
    fileTimeData["更早 (3个文件)"] = olderFiles;

    // 创建并显示时间预览窗口
    TimePreviewWindow *timePreviewWindow = new TimePreviewWindow(this);

    timePreviewWindow->setFileData(fileTimeData);
    timePreviewWindow->exec();

    // 清理窗口
    timePreviewWindow->deleteLater();
}

