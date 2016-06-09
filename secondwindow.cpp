#include "secondwindow.h"
#include "main_window.h"

SecondWindow::SecondWindow(){
    valider = new QPushButton("Valider");
    effacer = new QPushButton("Effacer");
    main = new QVBoxLayout;
    bottom = new QHBoxLayout;
    progEdit = new QTextEdit;


    bottom->addWidget(effacer);
    bottom->addWidget(valider);

    connect(effacer,SIGNAL(clicked(bool)),progEdit,SLOT(clear()));


    connect(valider,SIGNAL(clicked(bool)),this,SLOT(send_text()));

    main->addWidget(progEdit);
    main->addLayout(bottom);
    setLayout(main);
}


void SecondWindow::send_text(){
    MainWindow::getInstance().setTextEnter(progEdit->toPlainText());
    MainWindow::getInstance().printText();
    this->close();
}
