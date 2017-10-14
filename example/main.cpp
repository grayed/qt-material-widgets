#include <QDebug>
#include <QtWidgets/QApplication>
#include "mainsheet.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  Q_INIT_RESOURCE(resources);
  
  MainSheet window;
  window.show();

  return a.exec();
}
