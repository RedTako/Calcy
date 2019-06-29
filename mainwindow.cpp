#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unordered_map>
#include <functional>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    std::vector<EventButton*> arr = {
        ui->btn0,
        ui->btn1,
        ui->btn2,
        ui->btn3,
        ui->btn4,
        ui->btn5,
        ui->btn6,
        ui->btn7,
        ui->btn8,
        ui->btn9,
        ui->btnPlus,
        ui->btnMinus,
        ui->btnMultiply,
        ui->btnDivide,
        ui->btnLeftBracket,
        ui->btnRightBracket,
        ui->btnDecimal
    };



    auto connectButton = [&](EventButton*& btn) {
        connect(btn, &EventButton::clickedSender, this, &MainWindow::onButtonClick);
    };

    auto simpleConnect = [&](EventButton*& btn, const std::function<void(void)>& func) {
        connect(btn, &EventButton::clicked, this, func);
    };

    auto backButton = [&]() {
        QString str = ui->input->text();
        QString buf = "";
        for(int i = 0; i < str.size() - 1; i++)
            buf += str[i];
        ui->input->setText(buf);
    };

    auto clearButton = [&]() {
        ui->input->clear();
    };

    auto equalsButton = [&]() {
        ui->input->validate();
    };

    for(size_t i = 0; i < arr.size(); i++)
    {
        connectButton(arr[i]);
    }

    simpleConnect(ui->btnBack, backButton);
    simpleConnect(ui->btnClear, clearButton);
    simpleConnect(ui->btnEquals, equalsButton);


}

void MainWindow::onButtonClick(EventButton *btn)
{
    auto txt = ui->input->text();
    ui->input->setText(txt + btn->text());
}

void MainWindow::onBackClick()
{

}

void MainWindow::onClearClick()
{

}

void MainWindow::onClearEverythingClick()
{

}
