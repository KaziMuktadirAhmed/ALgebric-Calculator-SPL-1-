#ifndef TEXT_DOC_TRIAL_H
#define TEXT_DOC_TRIAL_H

#include <QDialog>

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

private:
    QWidget *parent;

    Ui::text_doc_trial *ui;
};

#endif // TEXT_DOC_TRIAL_H
