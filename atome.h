#ifndef ATOME_H
#define ATOME_H
#include "declarations.h"


class Atome : public Literale {
    Literale* lit ;
    QString name ;
    Atome(const Atome& e);
    Atome& operator=(const Atome& e);
    Atome(QString s , Literale* a):name(s) , lit(a){}
    virtual ~Atome() ;
    friend class LiteraleManager;
    friend class AtomeManager;
public:
    Attributs getValue() const ; // fct virtuelle qui renvoit les attributs de complex sous forme d'une structure attibuts pour faire des calculs
    QString toString() const ;//fct virtuelle renvoit un chaine pour afficher un complex au bon format
    QString Name() const {return name ; }
    Literale* getLit() const {return lit;}
    Attributs getVar() const {return lit->getValue() ;  }
};


#endif // ATOME_H
