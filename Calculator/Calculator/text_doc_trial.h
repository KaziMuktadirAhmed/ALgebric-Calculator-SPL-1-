#ifndef TEXT_DOC_TRIAL_H
#define TEXT_DOC_TRIAL_H

#include <QDialog>
#include <QtDebug>
#include <QTextCursor>
#include <bits/stdc++.h>
#include <cstdlib>
#include <string>

namespace Ui {
class text_doc_trial;
}

class text_doc_trial : public QDialog
{
    Q_OBJECT

public:
    explicit text_doc_trial(QWidget *parent = nullptr);
    ~text_doc_trial();

private slots:
    void on_btn_back_clicked();

    void on_btn_sup_clicked();

    void on_btn_sub_clicked();

    void on_btn_normal_clicked();

    void on_btn_copy_clicked();

    void on_btn_clear_clicked();

    void on_btn_html_clicked();

private:
    QWidget *parent;
    std::string parseHTML(QString htmlInput);

    Ui::text_doc_trial *ui;
};

#endif // TEXT_DOC_TRIAL_H
