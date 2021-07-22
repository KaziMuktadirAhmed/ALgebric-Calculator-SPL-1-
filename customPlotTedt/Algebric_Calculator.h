#ifndef ALGEBRIC_CALCULATOR_H
#define ALGEBRIC_CALCULATOR_H

#include <QMainWindow>
#include "Graph_Plotter.h"

namespace Ui {
class Algebric_Calculator;
}

class Algebric_Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Algebric_Calculator(QWidget *parent = nullptr);
    ~Algebric_Calculator();

private slots:
    void on_btn_graph_plotter_clicked();

private:
    Graph_Plotter *graph_plotter;
    Ui::Algebric_Calculator *ui;

};

#endif // ALGEBRIC_CALCULATOR_H
