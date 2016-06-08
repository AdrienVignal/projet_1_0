#include "declarations.h"
#include "computer.h"
#include "lnum.h"


Attributs Entier::getValue() const {
    Attributs A = Attributs( value ) ;
    return A ;
}

Attributs Reel::getValue() const {
    Attributs A = Attributs( value ) ;
    return A ;
}


Attributs Fraction::getValue() const {
    Attributs A = Attributs( num, denom ) ;
    return A ;
}


QString Fraction::toString() const {
    QString s = QString::number(num);
    s.push_back('/');
    s.append(QString::number(denom)) ;
    return s ;
}
