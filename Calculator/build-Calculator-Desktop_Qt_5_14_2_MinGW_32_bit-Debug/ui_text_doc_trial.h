/********************************************************************************
** Form generated from reading UI file 'text_doc_trial.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXT_DOC_TRIAL_H
#define UI_TEXT_DOC_TRIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_text_doc_trial
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn_back;
    QPushButton *btn_normal;
    QPushButton *btn_sup;
    QTextEdit *textEdit;
    QPushButton *btn_sub;
    QPushButton *btn_test;
    QPushButton *btn_copy;

    void setupUi(QDialog *text_doc_trial)
    {
        if (text_doc_trial->objectName().isEmpty())
            text_doc_trial->setObjectName(QString::fromUtf8("text_doc_trial"));
        text_doc_trial->resize(400, 300);
        gridLayout = new QGridLayout(text_doc_trial);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_back = new QPushButton(text_doc_trial);
        btn_back->setObjectName(QString::fromUtf8("btn_back"));
        btn_back->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #C0C0C0;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #A9A9A9;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}"));

        gridLayout->addWidget(btn_back, 5, 0, 1, 3);

        btn_normal = new QPushButton(text_doc_trial);
        btn_normal->setObjectName(QString::fromUtf8("btn_normal"));
        btn_normal->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #C0C0C0;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #A9A9A9;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}"));

        gridLayout->addWidget(btn_normal, 2, 2, 1, 1);

        btn_sup = new QPushButton(text_doc_trial);
        btn_sup->setObjectName(QString::fromUtf8("btn_sup"));
        btn_sup->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #C0C0C0;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #A9A9A9;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}"));

        gridLayout->addWidget(btn_sup, 2, 0, 1, 1);

        textEdit = new QTextEdit(text_doc_trial);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 0, 0, 1, 3);

        btn_sub = new QPushButton(text_doc_trial);
        btn_sub->setObjectName(QString::fromUtf8("btn_sub"));
        btn_sub->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #C0C0C0;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #A9A9A9;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}"));

        gridLayout->addWidget(btn_sub, 2, 1, 1, 1);

        btn_test = new QPushButton(text_doc_trial);
        btn_test->setObjectName(QString::fromUtf8("btn_test"));
        btn_test->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #C0C0C0;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #A9A9A9;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}"));

        gridLayout->addWidget(btn_test, 4, 2, 1, 1);

        btn_copy = new QPushButton(text_doc_trial);
        btn_copy->setObjectName(QString::fromUtf8("btn_copy"));
        btn_copy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #C0C0C0;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #A9A9A9;\n"
"	broder: 1px solid gray;\n"
"	padding: 5px;\n"
"}"));

        gridLayout->addWidget(btn_copy, 4, 0, 1, 2);


        retranslateUi(text_doc_trial);

        QMetaObject::connectSlotsByName(text_doc_trial);
    } // setupUi

    void retranslateUi(QDialog *text_doc_trial)
    {
        text_doc_trial->setWindowTitle(QCoreApplication::translate("text_doc_trial", "Dialog", nullptr));
        btn_back->setText(QCoreApplication::translate("text_doc_trial", "back", nullptr));
        btn_normal->setText(QCoreApplication::translate("text_doc_trial", "Normal", nullptr));
        btn_sup->setText(QCoreApplication::translate("text_doc_trial", "Superscript", nullptr));
        btn_sub->setText(QCoreApplication::translate("text_doc_trial", "Subscript", nullptr));
        btn_test->setText(QCoreApplication::translate("text_doc_trial", "test button", nullptr));
        btn_copy->setText(QCoreApplication::translate("text_doc_trial", "copy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class text_doc_trial: public Ui_text_doc_trial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXT_DOC_TRIAL_H