#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setMinimumSize(980, 800);
  QPalette myPallete(Qt::red, Qt::lightGray);
  a.setPalette(myPallete);
  w.show();

  return a.exec();
}
