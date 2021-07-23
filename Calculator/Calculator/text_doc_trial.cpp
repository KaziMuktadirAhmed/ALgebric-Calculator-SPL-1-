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
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);
    QTextCharFormat format;

    format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    cursor.insertText("sup",format);

    // edit->setCurrentCharFormat(format);
    // edit->insertPlainText("sup");
}

void text_doc_trial::on_btn_sub_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);
    QTextCharFormat format;

    format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    cursor.insertText("sub",format);

//    edit->setCurrentCharFormat(format);
//    edit->insertPlainText("sub");
}

void text_doc_trial::on_btn_normal_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);
    QTextCharFormat format;

    format.setVerticalAlignment(QTextCharFormat::AlignNormal);
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    cursor.insertText("normal",format);

//    edit->setCurrentCharFormat(format);
//    edit->insertPlainText("normal");
}

void text_doc_trial::on_btn_copy_clicked()
{
    QTextEdit *edit = ui->textEdit;
    // QTextDocument *doc = edit->document();

    QString qstr = "\n";
    qstr += edit->toHtml();
    // edit->append(qstr);
    // edit->insertPlainText(qstr);

    std::string str = parseHTML(qstr);
    qstr = QString::fromStdString(str);
    edit->append(qstr);
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
        else
            plainString += htmlStr[i];
    }

    return plainString;
}

void text_doc_trial::on_btn_clear_clicked()
{
    QTextEdit *edit = ui->textEdit;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    edit->setTextCursor(cursor);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);
    cursor.deletePreviousChar();
}
