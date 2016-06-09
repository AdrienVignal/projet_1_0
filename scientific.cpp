#include "scientific.h"


scientific_pad::scientific_pad(){
    main = new QVBoxLayout();
    ligne1 = new QHBoxLayout();
    ligne2 = new QHBoxLayout();
    ligne3 = new QHBoxLayout();

    sin = new QPushButton("SIN");
    sin->setFixedSize(55,55);
    sin->setFocusPolicy(Qt::NoFocus);
    cos = new QPushButton("COS");
    cos->setFixedSize(55,55);
    cos->setFocusPolicy(Qt::NoFocus);
    tan = new QPushButton("TAN");
    tan->setFixedSize(55,55);
    tan->setFocusPolicy(Qt::NoFocus);
    puis = new QPushButton("POW");
    puis->setFixedSize(55,55);
    puis->setFocusPolicy(Qt::NoFocus);
    arcsin = new QPushButton("ARCSIN");
    arcsin->setFixedSize(55,55);
    arcsin->setFocusPolicy(Qt::NoFocus);
    arccos = new QPushButton("ARCCOS");
    arccos->setFixedSize(55,55);
    arccos->setFocusPolicy(Qt::NoFocus);
    arctan = new QPushButton("ARCTAN");
    arctan->setFixedSize(55,55);
    arctan->setFocusPolicy(Qt::NoFocus);
    sqrt = new QPushButton("SQRT");
    sqrt->setFixedSize(55,55);
    sqrt->setFocusPolicy(Qt::NoFocus);
    div = new QPushButton("DIV");
    div->setFixedSize(55,55);
    div->setFocusPolicy(Qt::NoFocus);
    mod = new QPushButton("MOD");
    mod->setFixedSize(55,55);
    mod->setFocusPolicy(Qt::NoFocus);
    exp = new QPushButton("EXP");
    exp->setFixedSize(55,55);
    exp->setFocusPolicy(Qt::NoFocus);
    ln = new QPushButton("LN");
    ln->setFixedSize(55,55);
    ln->setFocusPolicy(Qt::NoFocus);


    ligne1->addWidget(sin);
    ligne1->addWidget(cos);
    ligne1->addWidget(tan);
    ligne1->addWidget(puis);

    ligne2->addWidget(arcsin);
    ligne2->addWidget(arccos);
    ligne2->addWidget(arctan);
    ligne2->addWidget(sqrt);

    ligne3->addWidget(div);
    ligne3->addWidget(mod);
    ligne3->addWidget(exp);
    ligne3->addWidget(ln);

    main->addLayout(ligne1);
    main->addLayout(ligne2);
    main->addLayout(ligne3);


    setLayout(main);

}
