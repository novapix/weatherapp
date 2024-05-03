#include "include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.resize(480, 960);
  w.show();
  return QApplication::exec();
}
