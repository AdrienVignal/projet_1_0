#include <QApplication>
#include "main_window.h"

int main(int argc, char* argv[]){
QApplication app(argc, argv);
//MainWindow fenetre=MainWindow::getInstance();
MainWindow& fenetre =MainWindow::getInstance();
fenetre.show();
return app.exec();
}
