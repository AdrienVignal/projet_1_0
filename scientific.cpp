#include "scientific.h"


scientific_pad::scientific_pad(){
    main = new QVBoxLayout();
    ligne1 = new QHBoxLayout();
    ligne2 = new QHBoxLayout();
    ligne3 = new QHBoxLayout();

    sin = new QPushButton("sin");
    sin->setFixedSize(50,50);
    cos = new QPushButton("cos");
    cos->setFixedSize(50,50);
    tan = new QPushButton("tan");
    tan->setFixedSize(50,50);
    puis = new QPushButton("x^");
    puis->setFixedSize(50,50);
    arcsin = new QPushButton("arcsin");
    arcsin->setFixedSize(50,50);
    arccos = new QPushButton("arccos");
    arccos->setFixedSize(50,50);
    arctan = new QPushButton("arctan");
    arctan->setFixedSize(50,50);
    sqrt = new QPushButton("sqrt");
    sqrt->setFixedSize(50,50);
    div = new QPushButton("DIV");
    div->setFixedSize(50,50);
    mod = new QPushButton("MOD");
    mod->setFixedSize(50,50);
    exp = new QPushButton("exp");
    exp->setFixedSize(50,50);
    ln = new QPushButton("ln");
    ln->setFixedSize(50,50);

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
