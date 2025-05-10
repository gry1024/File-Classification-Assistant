#ifndef CLASSIFICATIONWINDOW_H
#define CLASSIFICATIONWINDOW_H

#include <QDialog>

namespace Ui {
class classificationWindow;
}

class classificationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit classificationWindow(QWidget *parent = nullptr);
    ~classificationWindow();

private:
    Ui::classificationWindow *ui;
};

#endif // CLASSIFICATIONWINDOW_H
