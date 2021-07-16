#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->parent = parent;
}

Dialog::~Dialog()
{
    parent->show();
    delete ui;
}

void Dialog::on_btn_back_clicked()
{
    this->~Dialog();
}

void Dialog::on_btn_next_clicked()
{
    this->hide();
    textdoctrial = new text_doc_trial(this);
    textdoctrial->show();
}
