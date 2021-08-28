#include "Graph_Plotter.h"
#include "ui_Graph_Plotter.h"

Graph_Plotter::Graph_Plotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->parent = parent;

    // custom plot
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    // ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");

    ui->plot->xAxis->setRange(-10.0, 10.0);
    ui->plot->yAxis->setRange(-10.0, 10.0);

    // interactive zoom and drag
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iSelectAxes, true);
    ui->plot->setInteraction(QCP::iSelectPlottables, true);
}

Graph_Plotter::~Graph_Plotter()
{
    parent->show();
    delete ui;
}

void Graph_Plotter::plot_graph(std::vector<Term> input)
{
    clearData();

    double val_x, val_y;

    for (val_x = -100.0; val_x<100.0; val_x+=0.1){
        val_y = calculate_line(input, val_x);

        qv_x.append(val_x);
        qv_y.append(val_y);
    }

    plot();
}

void Graph_Plotter::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void Graph_Plotter::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void Graph_Plotter::plot()
{
    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void Graph_Plotter::on_btn_clear_clicked()
{
    clearData();
    plot();
}

void Graph_Plotter::on_btn_zoomFull_clicked()
{
    ui->plot->xAxis->setRange(*std::min_element(qv_x.begin(), qv_x.end()), *std::max_element(qv_x.begin(), qv_x.end()));
    ui->plot->yAxis->setRange(*std::min_element(qv_y.begin(), qv_y.end()), *std::max_element(qv_y.begin(), qv_y.end()));
    plot();
}

void Graph_Plotter::on_btn_back_clicked()
{
    this->~Graph_Plotter();
}

double Graph_Plotter::calculate_term(Term term, double val_x)
{
    double val_y = 0.0, temp = 1;

    if (!term.isBrace && !term.isOperator && !term.isEqualSign)
    {
        if (term.isFraction)    val_y = (double)term.co_efficient_fraction[0] / (double)term.co_efficient_fraction[1];
        else val_y = term.co_efficient;

        if (!term.isConstant) {
            for (int i=0; i<term.get_variable_count(); ++i) {
                for (int j=0; j<term.variable_and_exponent[i].second; ++j)
                    temp *= val_x;
            }

            val_y *= temp;
        }
    }

    return val_y;
}

double Graph_Plotter::calculate_line(std::vector<Term> input, double val_x)
{
    double val_y = 0.0, multiplyer = 1, temp = 0.0;

    for (int i=0; input[i].isEqualSign == false; ++i) {
        if (!input[i].isOperator && !input[i].isBrace) {
            temp = calculate_term(input[i], val_x);

            if (i > 0){
                if (input[i-1].awperator[0] == '+')
                    multiplyer = 1;
                else if (input[i-1].awperator[0] == '-')
                    multiplyer = -1;
            }

            val_y += multiplyer*temp;
        }
    }

    return val_y;
}

void Graph_Plotter::on_btn_zoomCenter_clicked()
{
    ui->plot->xAxis->setRange(-10.0, 10.0);
    ui->plot->yAxis->setRange(-10.0, 10.0);
    plot();
}
