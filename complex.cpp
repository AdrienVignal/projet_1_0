#include "declarations.h"
#include "computer.h"
#include "complex.h"


Complex::Complex(Attributs a) {
    Re = (LNum*) &(LiteraleManager::getInstance().addLit( Attributs(a.num , a.denom) )) ; // initialisation de la litérale partie Réelle
    Im = (LNum*) &(LiteraleManager::getInstance().addLit(Attributs (a.ImNum , a.ImDenom)));// initialisation de la litérale partie Im
}

//Complex::Complex(LNum& r, LNum& i): Re(&r) , Im(&i)  {}

Complex::~Complex()  {
    //LiteraleManager::getInstance().deleteLiterale(Re);//détruit la partie réelle
    //LiteraleManager::getInstance().deleteLiterale(Im);// détruit la partie im
}

Attributs Complex::getValue() const {
    return Attributs(Re->getValue().num , Re->getValue().denom , Im->getValue().num , Im->getValue().denom) ;
}

QString Complex::toString() const {
    QString s = Re->toString() ;
    s.push_back('$');
    s.append(Im->toString()) ;
    return s ;
}
