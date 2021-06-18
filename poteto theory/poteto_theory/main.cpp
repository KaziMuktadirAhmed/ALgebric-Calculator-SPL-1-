#include "mainwindow.h"

#include <QApplication>
#include <QTextEdit>
#include <QtGui>

int main(int argc, char **argv){
  QApplication app(argc, argv);
  QTextEdit edit;
  QTextDocument *doc = edit.document();
  QTextCursor cursor(doc);
  cursor.insertText("abc");
  QTextCharFormat fmt;
  fmt.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
  cursor.insertText("xyz", fmt);
  edit.show();
  return app.exec();
}
