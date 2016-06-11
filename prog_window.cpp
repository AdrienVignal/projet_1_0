#include "prog_window.h"
#include "declarations.h"
#include "main_window.h"


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
    fonts << "Programmes et Variables" << "ID";
    progVue->setHorizontalHeaderLabels(fonts);
    progVue->horizontalHeader()->setStretchLastSection(true);
    QStringList liste;


    // ON CREE LE TABLEAU

    for(Item* it = Controleur::getInstance()->getPile().stack.end()-1; it!=Controleur::getInstance()->getPile().stack.begin()-1; --it){
        if(LiteraleManager::getInstance().choix_type(Attributs(it->getLiterale().toString()))==5){
            nb_Affiche++;
        }
    }

    nb_Affiche+=LiteraleManager::getInstance().getMapAtom().size();

    progVue->setRowCount(nb_Affiche) ;
    for(  int i= nb_Affiche ; i>0 ; i--)
    {
        QString str = QString::number(i) ;
        str+=" :";
        liste<<str ;
    }

    progVue->setVerticalHeaderLabels(liste) ;


    for(  int i=0 ; i<nb_Affiche ; i++)
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



void ProgWindow::refresh_content(){
    qDebug()<<"refresh_content  : avant boucle";
    int i = 0;
    if (!Controleur::getInstance()->getPile().stack.empty()){
        for(Item* it = Controleur::getInstance()->getPile().stack.begin(); it!=Controleur::getInstance()->getPile().stack.end(); ++it, i++){
            if(LiteraleManager::getInstance().choix_type(Attributs(it->getLiterale().toString()))==5){
                progVue->item(nb_Affiche-nb-1,0)->setText(it->getLiterale().toString());
                progVue->item(nb_Affiche-nb-1,1)->setText(QString::number(i));
                nb++;
            }
        }
    }
    std::map<QString, Atome*> M = LiteraleManager::getInstance().getMapAtom() ;
    std::map<QString, Atome*>::const_iterator it = M.begin() ;
    while( nb_Affiche-nb-1 >= 0 ){
        progVue->item(nb_Affiche-nb-1,0)->setText(it->second->toString());
        progVue->item(nb_Affiche-nb-1,1)->setText(it->first);
        nb++;
        ++it ;  ;

          }
}

ProgWindow::~ProgWindow(){
    MainWindow::getInstance().refresh();
}

void ProgWindow::action_save_prog(){
    bool ok = false;
    //GESTION PROG
    for(int i=0;i<nb_Affiche-LiteraleManager::getInstance().getMapAtom().size();i++){
        //Controleur::getInstance()->getPile().stack[progVue->item(nb_Affiche-i-1,1)->text().toInt(&ok,10)].setLiterale(LiteraleManager::getInstance().getLit(progVue->item(nb_Affiche-i-1,0)->text()));
        Program& P =(Program&) Controleur::getInstance()->getPile().stack[progVue->item(nb_Affiche-i-1,1)->text().toInt(&ok,10)].getLiterale();
        P.modifProg(progVue->item(nb_Affiche-i-1,0)->text());
    }
    //GESTION VARIABLES
    for(int i=nb_Affiche-LiteraleManager::getInstance().getMapAtom().size();i<nb_Affiche;++i){
        QString varName = progVue->item(nb_Affiche-i-1,1)->text();
        Literale& lit = LiteraleManager::getInstance().addLit(progVue->item(nb_Affiche-i-1,0)->text());
        LiteraleManager::getInstance().deleteLiterale(LiteraleManager::getInstance().getAtome(varName));
        LiteraleManager::getInstance().affect(varName,&lit);
    }
    QMessageBox::information(this,"Changement(s) effectué(s)", "Les modifications ont bien été enregistrées");
    delete this;
    qDebug()<<"action_save_prog";
}

