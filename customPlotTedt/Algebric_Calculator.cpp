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
