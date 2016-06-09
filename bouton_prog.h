#ifndef BOUTON_PROG_H
#define BOUTON_PROG_H
#include "declarations.h"
#include <QtWidgets>

class bouton_prog : public QWidget{
    QHBoxLayout* lBoutons;
    QPushButton* save;
    QPushButton* enter;
public :
    bouton_prog();

};

#endif // BOUTON_PROG_H
