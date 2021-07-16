#include "text_doc_trial.h"
#include "ui_text_doc_trial.h"

text_doc_trial::text_doc_trial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::text_doc_trial)
{
    ui->setupUi(this);
    this->parent = parent;
}

text_doc_trial::~text_doc_trial()
{
    parent->show();
    delete ui;
}

void text_doc_trial::on_btn_back_clicked()
{
    this->~text_doc_trial();
}

void text_doc_trial::on_btn_sup_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextCharFormat format;

    format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);

    edit->setCurrentCharFormat(format);
}

void text_doc_trial::on_btn_sub_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextCharFormat format;

    format.setVerticalAlignment(QTextCharFormat::AlignSubScript);

    edit->setCurrentCharFormat(format);
}

void text_doc_trial::on_btn_normal_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextCharFormat format;

    format.setVerticalAlignment(QTextCharFormat::AlignNormal);

    edit->setCurrentCharFormat(format);
}
