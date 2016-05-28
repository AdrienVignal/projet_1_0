#include "prog_window.h"

ProgWindow::ProgWindow()

{
    main = new QVBoxLayout();
    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");
    bottom = new QHBoxLayout;
    progVue = new QTableWidget;
    progVue->horizontalHeader()->setVisible(false);   //enlève l'indice de col;
    progVue->horizontalHeader()->setStretchLastSection(true);   //ajuste la largeur à la fenetre
    progVue->setColumnCount(1);
    progVue->setColumnWidth(0, 40);
    progVue->setVerticalHeaderLabels(QStringList() << tr("ID") << tr("Programme"));

    //CONNECT + ACTION

    connect(valider,SIGNAL(clicked()),this, SLOT(action_valider()));
    connect(annuler,SIGNAL(clicked()),this, SLOT(action_annuler()));


    // GESTION DES CONTENEURS
    bottom->addWidget(annuler);
    bottom->addWidget(valider);

    main->addWidget(progVue);
    main->addLayout(bottom);
    setLayout(main);

}


void ProgWindow::closeProgWindow(){
    delete this;
}


void ProgWindow::action_annuler(){
    QMessageBox::information(this,"Changement(s) annulé(s)", "Les modifications n'ont pas été enregistrées");
    closeProgWindow();

}

void ProgWindow::action_valider(){
    QMessageBox::information(this,"Changement(s) effectué(s)", "Les modifications ont bien été enregistrées");
    closeProgWindow();
}

