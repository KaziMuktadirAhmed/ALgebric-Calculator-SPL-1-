#include "Graph_Plotter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Graph_Plotter w;
    w.show();
    return a.exec();
}
