#ifndef LNUM_H
#define LNUM_H
#include"declarations.h"
#include "attributs.h"


class LNum : public Literale {//ABSTRAITE
protected:
    LNum(){}
    LNum(const LNum& e);
    LNum& operator=(const LNum& e);
    friend class LiteraleManager;
    virtual ~LNum() {}
public:
};

class Entier : public LNum {
    int value ;
    Entier(const Entier& e);
    Entier& operator=(const Entier& e);
    Entier(Attributs a):value(a.num){}
    virtual ~Entier() {}
    friend class LiteraleManager;
    friend class EntierManager;
public:
    Attributs getValue() const ;  //cf Literale
    QString toString() const {return QString::number(value); } //cf Literale


};

class Reel : public LNum {
    double value ;
    Reel(const Reel& e);
    Reel& operator=(const Reel& e);
    Reel(Attributs a):value(a.num){}
    virtual ~Reel() {}
    friend class LiteraleManager;
    friend class ReelManager;
public:
    Attributs getValue() const ;//cf Literale
    QString toString() const {return QString::number(value); } //cf Literale
};

class Fraction : public LNum {
    int num ;
    int denom ;
    Fraction(const Fraction& e);
    Fraction& operator=(const Fraction& e);
    Fraction(Attributs a):num(a.num),  denom(a.denom){}
    virtual ~Fraction() {}
    friend class LiteraleManager;
    friend class FractionManager;
public:
    void simplification() ;
    Attributs getValue() const ;//cf Literale
    QString toString() const ;//cf Literale
};


#endif // LNUM_H
