#include "IO.hpp"
#include "window.hpp"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
  LoadAll();

  QApplication app(argc, argv);
  MainWindow window;
  window.show();
  return app.exec();
}
