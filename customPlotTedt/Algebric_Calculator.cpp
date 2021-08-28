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
    QTextEdit *edit = ui->txtedt_input;

    QString qstr = "", temp_qstr = "";
    qstr += edit->toHtml();

    std::string str = parseHTML(qstr);

    if (str.length() == 0)    return;

    print_output.clear_all();
    print_output.take_input_from_ui(str);

    // test
    QTextEdit *newEdit = ui->txtedt_output;
    newEdit->clear();

    QString tempa_qstr = QString::fromStdString(print_output.print_line(print_output.return_graph_expression()));
    newEdit->setText(tempa_qstr);
    // end of test

    graph_plotter = new Graph_Plotter(this);
    graph_plotter->plot_graph(print_output.return_graph_expression());

    this->hide();
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

void Algebric_Calculator::on_btn_exp_2_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);
    QTextCharFormat sup_format, normal_format;

    sup_format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    normal_format.setVerticalAlignment(QTextCharFormat::AlignNormal);
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("2",sup_format);
    cursor.insertText(" ", normal_format);
}

void Algebric_Calculator::on_btn_1_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("1");
}

void Algebric_Calculator::on_btn_2_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("2");
}

void Algebric_Calculator::on_btn_3_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("3");
}

void Algebric_Calculator::on_btn_4_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("4");
}

void Algebric_Calculator::on_btn_5_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("5");
}

void Algebric_Calculator::on_btn_6_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("6");
}

void Algebric_Calculator::on_btn_7_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("7");
}

void Algebric_Calculator::on_btn_8_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("8");
}

void Algebric_Calculator::on_btn_9_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("9");
}

void Algebric_Calculator::on_btn_0_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("0");
}

void Algebric_Calculator::on_btn_dot_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText(".");
}

void Algebric_Calculator::on_btn_x_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("x");
}

void Algebric_Calculator::on_btn_equal_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("=");
}

void Algebric_Calculator::on_btn_plus_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("+");
}

void Algebric_Calculator::on_btn_minus_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("-");
}

void Algebric_Calculator::on_btn_mul_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("*");
}

void Algebric_Calculator::on_btn_div_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.insertText("/");
}

void Algebric_Calculator::on_btn_delete_clicked()
{
    QTextEdit *edit = ui->txtedt_input;
    QTextDocument *doc = edit->document();
    QTextCursor cursor(doc);

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveMode::MoveAnchor);

    cursor.deletePreviousChar();
}
