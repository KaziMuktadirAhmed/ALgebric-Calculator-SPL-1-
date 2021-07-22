// #include "Graph_Plotter.h"
#include "Algebric_Calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Algebric_Calculator w;
    w.show();
    return a.exec();
}
