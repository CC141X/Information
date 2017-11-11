#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QSplashScreen* splash = new QSplashScreen;
  splash->setPixmap(QPixmap(":/resources/images/logo_startup.png"));
  splash->show();

  Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
  splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);

//  loadModules();
  splash->showMessage(QObject::tr("Establishing connections..."), topRight, Qt::white);
//  establishConnections();

  MainWindow w;
  w.show();
  splash->finish(&w);
  delete splash;
  splash = 0;

  return a.exec();
}
