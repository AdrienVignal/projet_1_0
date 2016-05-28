#include "secondwindow.h"

SecondWindow::SecondWindow(){
    valider = new QPushButton("Valider");
    effacer = new QPushButton("Effacer");
    main = new QVBoxLayout;
    bottom = new QHBoxLayout;
    progEdit = new QTextEdit;


    bottom->addWidget(effacer);
    bottom->addWidget(valider);

    main->addWidget(progEdit);
    main->addLayout(bottom);
    setLayout(main);
}

void SecondWindow::closeEditProg(){
    delete this;
}
