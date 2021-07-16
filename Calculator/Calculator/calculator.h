#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_btn_next_clicked();

    void on_pushButton_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_18_clicked();

private:
    Ui::Calculator *ui;
    Dialog *dlg;
};
#endif // CALCULATOR_H
