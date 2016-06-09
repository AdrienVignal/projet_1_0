#include"qcomputer.h"
#include<QApplication>
#include <QWidget>
#include "computer.h"

QComputer::QComputer (QWidget *parent):QWidget (parent)
{
    pile = new Pile ;
    //controleur = new Controleur (LiteraleManager::getInstance() , *pile) ;
    controleur = Controleur::getInstance(LiteraleManager::getInstance() , *pile) ;
    message = new QLineEdit(this) ;
    commande = new QLineEdit (this) ;
    vuePile = new QTableWidget (pile->getNbItemsToAffiche(),1,this) ;

    couche = new QVBoxLayout(this) ;
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande) ;


    setWindowTitle("UTComputer");
    message->setReadOnly(true);    //empèche d'écrire dans la lineEdit
    message->setStyleSheet("background: blue; color: yellow");

    vuePile->horizontalHeader()->setVisible(false);   //enlève l'indice de col
    vuePile->horizontalHeader()->setStretchLastSection(true);   //ajuste la largeur à la fenetre
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers) ;  //empèche d'écrire dans les cellules

    QStringList liste;
    for(unsigned int i=pile->getNbItemsToAffiche() ; i>0 ; i--)
    {
        QString str = QString::number(i) ;
        str+=" :";
        liste<<str ;
    }

    vuePile->setVerticalHeaderLabels(liste) ;
    for(unsigned int i=0 ; i<pile->getNbItemsToAffiche() ; i++)
    {
        vuePile->setItem(i , 0 , new QTableWidgetItem("")) ;
    }
    connect (commande, SIGNAL (returnPressed()) , this , SLOT(getNextCommande())) ;
    connect(pile , SIGNAL (modificationEtat()) , this, SLOT(refresh())) ;
    setLayout(couche) ;
}

void QComputer::refresh()
{ //affiche état pile et message éventuel
message->setText(pile->getMessage())
       ;
//on efface tt ce qui est affiché
for(unsigned int i = 0 ; i<pile->getNbItemsToAffiche() ; i++)
    vuePile->item(i,0)->setText("") ;

unsigned int nb = 0 ;

for(Item* it= (pile->stack->end() -1)   ; it!= (pile->stack->begin()-1) and nb < pile->getNbItemsToAffiche() ; --it , ++nb)

    vuePile->item(pile->getNbItemsToAffiche()-nb-1,0)->setText((it->getLiterale()).toString()) ;




}

void QComputer::getNextCommande()
{
    //message->setText(commande->text()) ;  //marque dans la ligne de commande l'entrée
    pile->setMessage("");

    QString source =commande->text() ;
    QTextStream s (&source) ;
    QString c ;
    s>> c ;
    while (c != "") {
    controleur->commande(c) ;
    commande->clear() ;
    s>>c ;
    }
}
