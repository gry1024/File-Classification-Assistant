#ifndef EXECUTEWINDOW_H
#define EXECUTEWINDOW_H

#include <QDialog>

namespace Ui {
class executeWindow;
}

class executeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit executeWindow(QWidget *parent = nullptr);
    ~executeWindow();

private:
    Ui::executeWindow *ui;
    void executeClassify();
};

#endif // EXECUTEWINDOW_H
