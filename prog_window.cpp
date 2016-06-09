#include "prog_window.h"
#include "literalemanager_mere.h"

ProgWindow::ProgWindow() : nb_Affiche(0) , nb(0)

{
    main = new QVBoxLayout();
    valider = new QPushButton("Valider");
    bottom = new QHBoxLayout;
    progVue = new QTableWidget(this);
    //ajuste la largeur à la fenetre
    progVue->setColumnCount(2);
    progVue->setColumnWidth(0,500);
    progVue->setColumnWidth(1, 40);

    QStringList fonts;
    fonts << "Programmes" << "pID";
    progVue->setHorizontalHeaderLabels(fonts);
    progVue->horizontalHeader()->setStretchLastSection(true);
    QStringList liste;


    // ON CREE LE TABLEAU

    LiteraleManager& litMan = LiteraleManager::getInstance();
    for(int i = litMan.tab.size(); i>0; --i){
        if(litMan.choix_type(LiteraleManager::getInstance().tab[i-1]->getValue())==5){
            nb_Affiche++;
        }
    }

    progVue->setRowCount(nb_Affiche) ;
    for(unsigned int i= nb_Affiche ; i>0 ; i--)
    {
        QString str = QString::number(i) ;
        str+=" :";
        liste<<str ;
    }

    progVue->setVerticalHeaderLabels(liste) ;


    for(unsigned int i=0 ; i<nb_Affiche ; i++)
    {
        progVue->setItem(i , 0 , new QTableWidgetItem("")) ;
        progVue->setItem(i , 1 , new QTableWidgetItem("")) ;
        progVue->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        progVue->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    }


    //CONNECT + ACTION

    connect(valider,SIGNAL(clicked()),this, SLOT(action_save_prog()));


    // GESTION DES CONTENEURS

    bottom->addWidget(valider);

    main->addWidget(progVue);
    main->addLayout(bottom);
    setFixedSize(686,400);
    setLayout(main);

}


void ProgWindow::closeProgWindow(){
    delete this;
}

void ProgWindow::refresh_content(){

    LiteraleManager& litMan = LiteraleManager::getInstance();
    for(int i = litMan.tab.size(); i>0; --i){
        if(litMan.choix_type(LiteraleManager::getInstance().tab[i-1]->getValue())==5){
            progVue->item(nb_Affiche-nb-1,0)->setText((litMan.tab[i-1]->toString()));
            progVue->item(nb_Affiche-nb-1,1)->setText(QString::number(i));
            nb++;
        }
    }
}


void ProgWindow::action_save_prog(){
    bool ok = false;
    LiteraleManager& litMan = LiteraleManager::getInstance();
    for(int i = 0; i<nb; i++){
        litMan.tab[progVue->item(i,1)->text().toInt(&ok,10)]=&litMan.getLit(Attributs(0,1,0,1,progVue->item(i,0)->text()));
    }
    QMessageBox::information(this,"Changement(s) effectué(s)", "Les modifications ont bien été enregistrées");
    closeProgWindow();
    qDebug()<<"action_save_prog";
}
