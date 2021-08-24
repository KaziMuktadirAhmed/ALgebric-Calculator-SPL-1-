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
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    // ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    // interactive zoom and drag
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
}

Graph_Plotter::~Graph_Plotter()
{
    parent->show();
    delete ui;
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


void Graph_Plotter::on_btn_add_clicked()
{
    addPoint(ui->bx_x->value(), ui->bx_y->value());
    plot();
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
