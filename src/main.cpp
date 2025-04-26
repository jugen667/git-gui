//========================
// - Info -
// - about -
// - File -
// - Author : juju80gen -
//========================

//==============
// - INCLUDES -
//==============
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <QtGui>
#include <QApplication>
#include <QLabel>

//==========
// - MAIN -
//==========

int main(int argc, char **argv) {
 QApplication app(argc, argv);
 QLabel label("Hello, world!");
 label.show();
 return app.exec();
}