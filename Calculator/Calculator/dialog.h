#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "text_doc_trial.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btn_back_clicked();

    void on_btn_next_clicked();

private:
    QWidget *parent;

    Ui::Dialog *ui;

    text_doc_trial *textdoctrial;
};

#endif // DIALOG_H
