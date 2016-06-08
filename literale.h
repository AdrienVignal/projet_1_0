#ifndef LITERALE_H
#define LITERALE_H
#include "declarations.h"

class Literale {
protected:
    //un litérale ne peut être créer que par une litérale manager, donc on met en privé les constructeurs et destructeur
    Literale(){}
    Literale(const Literale& e);
    Literale& operator=(const Literale& e);
    friend class LiteraleManager;
    virtual ~Literale() { }
public:

    virtual QString toString() const = 0 ;  //fonction virtuelle pure qui renvoit une chaine pour afficher une litérale au bon format
    virtual Attributs getValue()const = 0 ;  //fonction virtuelle pure qui revoit un attibuts pour faire des calculs

    //surchage des operateurs, pour manipuler les litérales entre elles.
    Attributs operator+(const Literale&  L) ;
    Attributs operator-(Literale const& L) ;
    Attributs operator*(Literale const& L) ;
    Attributs operator/(Literale const& L) ;

};



#endif // LITERALE_H
