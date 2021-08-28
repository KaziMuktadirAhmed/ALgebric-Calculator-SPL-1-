#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "Term.h"
#include "Parser.h"
#include "Algebraic_Opeartion.h"
#include "Process_Linear_Expression.h"
#include "Process_Quadratic_Expression.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Graph_Plotter : public QMainWindow
{
    Q_OBJECT

public:
    Graph_Plotter(QWidget *parent = nullptr);
    ~Graph_Plotter();

    void plot_graph(std::vector<Term> input);
    void addPoint(double x, double y);
    void clearData();
    void plot();

private slots:

    void on_btn_clear_clicked();

    void on_btn_zoomFull_clicked();

    void on_btn_back_clicked();

    void on_btn_zoomCenter_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;

    QWidget *parent;

    double calculate_term (Term term, double val_x);
    double calculate_line(std::vector<Term> input, double val_x);

};
#endif // MAINWINDOW_H
