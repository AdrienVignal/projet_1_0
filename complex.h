#ifndef COMPLEX_H
#define COMPLEX_H
#include "declarations.h"


class Complex : public Literale {
    LNum* Re ;
    LNum* Im ;
    Complex(const Complex& e);
    Complex& operator=(const Complex& e);
    Complex(Attributs a) ;
    //Complex(LNum& r, LNum& i) ;
    //on peut créer un complex à partir d'un attributs, ou de 2 LNum
    virtual ~Complex() ;
    friend class LiteraleManager;
    friend class ComplexManager;
public:
    Attributs getValue() const ; // fct virtuelle qui renvoit les attributs de complex sous forme d'une structure attibuts pour faire des calculs
    QString toString() const ;//fct virtuelle renvoit un chaine pour afficher un complex au bon format
};

#endif // COMPLEX_H
