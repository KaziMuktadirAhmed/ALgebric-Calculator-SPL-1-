#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_btn_next_clicked()
{
    this->hide();
    dlg = new Dialog(this);
    dlg->show();
}

void Calculator::on_pushButton_clicked()
{
    QPushButton *btn = ui->pushButton;

    QString qstr = btn->text();

    ui->display->insert(qstr);
}

void Calculator::on_pushButton_19_clicked()
{
    // QPushButton *btn = ui->pushButton_19;

    this->close();
}

void Calculator::on_pushButton_18_clicked()
{
    ui->display->clear();
}
