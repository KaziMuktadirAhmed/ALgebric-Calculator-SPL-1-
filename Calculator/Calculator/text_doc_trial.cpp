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

void text_doc_trial::on_btn_copy_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextDocument *doc = edit->document();

    QString qstr = "\n";
    qstr += doc->toHtml();
    // edit->append(qstr);
    // edit->insertPlainText(qstr);

    std::string str = parseHTML(qstr);
    qstr = QString::fromStdString(str);
    edit->append(qstr);
} 

void text_doc_trial::on_btn_test_clicked()
{
    QTextEdit *edit = ui->textEdit;
    // QTextDocument *doc = edit->document();

    QTextCursor cursor = edit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}

std::string text_doc_trial::parseHTML(QString htmlInput)
{
    std::string plainString, htmlStr = htmlInput.toStdString();
    size_t ind_p_start = htmlStr.find("<p"), ind_p_end = htmlStr.find("</p");
    size_t start_read_int = htmlStr.find(">", ind_p_start) + 1;

    for (size_t i=start_read_int; i<ind_p_end; ++i) {
        if (htmlStr[i] == '<') {
            if(htmlStr[i+1] == '/')
                for (;htmlStr[i] != '>'; ++i);
            if(htmlStr[i+1] == 's'){
                for (;htmlStr[i] != '>'; ++i);
                plainString += "^";
            }
        }
        else{
            plainString += htmlStr[i];
        }
    }

    return plainString;
}
