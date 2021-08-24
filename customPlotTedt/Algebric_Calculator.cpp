#include "Algebric_Calculator.h"
#include "ui_Algebric_Calculator.h"

Algebric_Calculator::Algebric_Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Algebric_Calculator)
{
    ui->setupUi(this);
}

Algebric_Calculator::~Algebric_Calculator()
{
    delete ui;
}

void Algebric_Calculator::on_btn_graph_plotter_clicked()
{
    this->hide();
    graph_plotter = new Graph_Plotter(this);
    graph_plotter->show();
}

void Algebric_Calculator::on_btn_calculate_clicked()
{
    QTextEdit *edit = ui->txtedt_input;

    QString qstr = "", temp_qstr = "";
    qstr += edit->toHtml();

    std::string str = parseHTML(qstr);

    if (str.length() == 0)    return;

    print_output.clear_all();
    print_output.take_input_from_ui(str);
    str = print_output.solve();

    edit = ui->txtedt_output;
    edit->clear();

    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);
    QTextCharFormat sup_format, normal_format;

    sup_format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    normal_format.setVerticalAlignment(QTextCharFormat::AlignNormal);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    bool found_exp = false;
    qstr = "";
    temp_qstr = "";

    for (size_t i=0; i<str.length(); ++i){
        if (!found_exp) {
            if (str[i] == '^' || i == str.length()-1) {
                found_exp = true;
                cursor.insertText(qstr, normal_format);
                qstr = "";
            }
            else
                qstr += str[i];
        }
        else {
            if (str[i] <= '0' || str[i] >= '9' || i == str.length()-1) {
                found_exp = false;
                cursor.insertText(temp_qstr, sup_format);
                temp_qstr = "";
            }
            else
                temp_qstr += str[i];
        }
    }
    // cursor.insertText(qstr, normal_format);
}

std::string Algebric_Calculator::parseHTML(QString htmlInput)
{
    std::string plainString, htmlStr = htmlInput.toStdString();
    size_t ind_p_start = htmlStr.find("<p"), ind_p_end = htmlStr.find("</p");
    size_t start_read_int = htmlStr.find(">", ind_p_start) + 1;

    while(ind_p_start != std::string::npos){
        for (size_t i=start_read_int; i<ind_p_end; ++i) {
            if (htmlStr[i] == '<') {
                if(htmlStr[i+1] == '/')
                    for (;htmlStr[i] != '>'; ++i);
                else if(htmlStr[i+1] == 's'){
                    for (;htmlStr[i] != '>'; ++i);
                    plainString += "^";
                }
                else
                    for (;htmlStr[i] != '>'; ++i);
            }
            else
                plainString += htmlStr[i];
        }

        ind_p_start = htmlStr.find("<p", ind_p_end);
        start_read_int = htmlStr.find(">", ind_p_start) + 1;
        ind_p_end = htmlStr.find("</p", start_read_int);
    }

    return plainString;
}

void Algebric_Calculator::on_btn_clear_clicked()
{
    QTextEdit *edit = ui->txtedt_output;
    edit->clear();

    edit = ui->txtedt_input;
    edit->clear();

    print_output.clear_all();
}
