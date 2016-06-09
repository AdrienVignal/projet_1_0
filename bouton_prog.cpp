#include "bouton_prog.h"

bouton_prog::bouton_prog(){
    lBoutons = new QHBoxLayout;
    save = new QPushButton;
    enter = new QPushButton;

    lBoutons->addWidget(save);
    lBoutons->addWidget(enter);



    save->setFlat(true);
    save->setFocusPolicy(Qt::NoFocus);
    save->setIcon(QIcon("/home/deneux/Documents/UTC/Projets/projet_1_0/images/save.png"));

    enter->setFlat(true);
    enter->setFocusPolicy(Qt::NoFocus);
    enter->setIcon(QIcon("/home/deneux/Documents/UTC/Projets/projet_1_0/images/enter-arrow.png"));

    connect(save, SIGNAL(clicked()), this->parent()->parent(), SLOT(action_save_prog()));
    setLayout(lBoutons);
}

