#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventbutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void init();

private slots:
    void onButtonClick(EventButton* btn);
    void onBackClick();
    void onClearClick();
    void onClearEverythingClick();
    //void on
};

#endif // MAINWINDOW_H
