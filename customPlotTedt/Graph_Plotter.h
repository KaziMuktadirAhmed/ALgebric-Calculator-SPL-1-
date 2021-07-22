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

    void addPoint(double x, double y);
    void clearData();
    void plot();

private slots:
    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_btn_zoomFull_clicked();

    void on_btn_back_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;

    QWidget *parent;

};
#endif // MAINWINDOW_H
