#ifndef EDITFAMILYWINDOW_H
#define EDITFAMILYWINDOW_H

#include <QWidget>

namespace Ui {
class editFamilyWindow;
}

class editFamilyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit editFamilyWindow(QWidget *parent = nullptr);
    ~editFamilyWindow();

private:
    Ui::editFamilyWindow *ui;
};

#endif // EDITFAMILYWINDOW_H
