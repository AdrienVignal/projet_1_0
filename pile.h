#ifndef PILE_H
#define PILE_H
#include "declarations.h"

class Item { //objet faisant l'intermédiaire entre la pile et les litérale, afin d'apporter plus de souplesse
    Literale* exp;
public:
    Item():exp(0){}
    void setLiterale(Literale& e) { exp=&e; }
    void raz() { exp=0; }
    Literale& getLiterale() const;
};


class Pile : public QObject {
    Q_OBJECT
    QString message;  //message à afficher sur la prompteur
    unsigned int nbAffiche;  //nb d'élément à afficher
    bool modif ;
public:
    QStack<Item> stack;  //contener QStack. Il est en public afin d'éviter de faire getQStack() si on veut manipuer la pile
    Pile():nbAffiche(5) , modif(false){stack = *(new QStack<Item> ); }
    ~Pile() ;
    void push(Literale& e);
    void pop();
    bool estVide() const { return stack.empty() ; }
    unsigned int taille() const { return stack.size() ; }
    void affiche(QTextStream& f) const;
    Literale& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) ;
    QString getMessage() const { return message; }
    bool isModified(){return modif ; }
    void NoModif() {modif = false ; }


signals:
    void modificationEtat();

private slots :


    void aug_pile() {
        this->setNbItemsToAffiche(nbAffiche+1);
    }

    void dim_pile() {
        if(getNbItemsToAffiche()>1) this->setNbItemsToAffiche(nbAffiche-1);
    }
};
#endif // PILE_H
