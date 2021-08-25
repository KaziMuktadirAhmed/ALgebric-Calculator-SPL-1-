#ifndef ALGEBRIC_CALCULATOR_H
#define ALGEBRIC_CALCULATOR_H

#include <QMainWindow>
#include "Graph_Plotter.h"
#include "Print_Output.h"

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

    void on_btn_calculate_clicked();

    void on_btn_clear_clicked();

    void on_btn_exp_2_clicked();

private:
    Graph_Plotter *graph_plotter;
    Ui::Algebric_Calculator *ui;

    Print_Output print_output;

    std::string parseHTML(QString htmlInput);

};

#endif // ALGEBRIC_CALCULATOR_H
