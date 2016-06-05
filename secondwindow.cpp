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

    // CONNECT
    connect(valider,SIGNAL(clicked()),this, SLOT(action_valider()));
    connect(effacer,SIGNAL(clicked()),this, SLOT(action_effacer()));
}

void SecondWindow::closeEditProg(){
    delete this;
}

void SecondWindow::action_effacer(){
    QMessageBox::information(this,"Changement(s) annulé(s)", "Les modifications n'ont pas été enregistrées");
    closeEditProg();

}

void SecondWindow::action_valider(){
    QMessageBox::information(this,"Changement(s) effectué(s)", "Les modifications ont bien été enregistrées");
    closeEditProg();
}

