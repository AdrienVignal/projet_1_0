#include "declarations.h"
#include "pile.h"
#include "computer.h"


Literale& Item::getLiterale() const {
        if (exp==0) throw ComputerException("Item : tentative d'acces a une literale inexistante");
        return *exp;
}

void Pile::push(Literale& e){
    Item temp ;
    temp.setLiterale(e) ;
    stack.push(temp) ;
    modificationEtat();
    modif = true ;
}

void Pile::pop(){
    stack.pop() ;
    modificationEtat();
    modif = true ;
}

void Pile::setMessage(const QString& m){
    message=m;
    modificationEtat();
    if (!m.isEmpty())
    Controleur::getInstance()->erreur(true) ;
}


void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    //Item* data = stack.data() ;
    for( int i=nbAffiche; i>0; i--) {
        if (i<=stack.size()) f<<i<<": "<<stack[stack.size()-i].getLiterale().toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}


Pile::~Pile(){
    delete[] (&stack) ;
}


Literale& Pile::top() const {
    if (stack.size() ==0) throw ComputerException("aucune literale sur la pile");
    Item temp = stack.top() ;
    return temp.getLiterale();
}
