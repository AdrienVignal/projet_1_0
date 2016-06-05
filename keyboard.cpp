#include "keyboard.h"


Keyboard::Keyboard(){

    //BOUTONS DU KEYBOARD
    b1 = new QPushButton("1");
    b1->setFixedSize(45,45);
    b1->setFocusPolicy(Qt::NoFocus);
    b2 = new QPushButton("2");
    b2->setFixedSize(45,45);
    b2->setFocusPolicy(Qt::NoFocus);
    b3 = new QPushButton("3");
    b3->setFixedSize(45,45);
    b3->setFocusPolicy(Qt::NoFocus);
    b4 = new QPushButton("4");
    b4->setFocusPolicy(Qt::NoFocus);
    b4->setFixedSize(45,45);
    b5 = new QPushButton("5");
    b5->setFocusPolicy(Qt::NoFocus);
    b5->setFixedSize(45,45);
    b6 = new QPushButton("6");
    b6->setFocusPolicy(Qt::NoFocus);
    b6->setFixedSize(45,45);
    b7 = new QPushButton("7");
    b7->setFocusPolicy(Qt::NoFocus);
    b7->setFixedSize(45,45);
    b8 = new QPushButton("8");
    b8->setFocusPolicy(Qt::NoFocus);
    b8->setFixedSize(45,45);
    b9 = new QPushButton("9");
    b9->setFocusPolicy(Qt::NoFocus);
    b9->setFixedSize(45,45);
    b0 = new QPushButton("0");
    b0->setFocusPolicy(Qt::NoFocus);
    b0->setFixedSize(45,45);

    space = new QPushButton(" ");
    space->setFocusPolicy(Qt::NoFocus);
    space->setFixedSize(45,45);
    clear = new QPushButton("C");
    clear->setFocusPolicy(Qt::NoFocus);
    clear->setFixedSize(45,45);

    bplus = new QPushButton("+");
    bplus->setFocusPolicy(Qt::NoFocus);
    bplus->setFixedSize(90,45);
    bmoins = new QPushButton("-");
    bmoins->setFocusPolicy(Qt::NoFocus);
    bmoins->setFixedSize(90,45);
    bdiv = new QPushButton("/");
    bdiv->setFocusPolicy(Qt::NoFocus);
    bdiv->setFixedSize(90,45);
    bmult = new QPushButton("*");
    bmult->setFixedSize(90,45);
    bmult->setFocusPolicy(Qt::NoFocus);

    ligne1 = new QHBoxLayout();
    ligne1->setContentsMargins(3,3,3,3);
    ligne2 = new QHBoxLayout();
    ligne2->setContentsMargins(3,3,3,3);
    ligne3 = new QHBoxLayout();
    ligne3->setContentsMargins(3,3,3,3);
    ligne4 = new QHBoxLayout();
    ligne4->setContentsMargins(3,3,3,3);
    num_pad = new QVBoxLayout();
    op_pad = new QVBoxLayout();

    //LAYOUT DU KEYBOARD

    ligne1->addWidget(b1);
    ligne1->addWidget(b2);
    ligne1->addWidget(b3);

    ligne2->addWidget(b4);
    ligne2->addWidget(b5);
    ligne2->addWidget(b6);

    ligne3->addWidget(b7);
    ligne3->addWidget(b8);
    ligne3->addWidget(b9);

    ligne4->addWidget(clear);
    ligne4->addWidget(b0);
    ligne4->addWidget(space);

    op_pad ->addWidget(bplus);
    op_pad ->addWidget(bmoins);
    op_pad ->addWidget(bdiv);
    op_pad ->addWidget(bmult);

    num_pad->addLayout(ligne1);
    num_pad->addLayout(ligne2);
    num_pad->addLayout(ligne3);
    num_pad->addLayout(ligne4);

    main = new QHBoxLayout();
    main->addLayout(num_pad);
    main->addLayout(op_pad);

    setLayout(main);
}
