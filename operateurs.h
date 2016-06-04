#ifndef OPERATEURS_H
#define OPERATEURS_H
#include "declarations.h"


//ensemble des focnteurs qui serviront d'opérateurs



class operateur { //virtual
public :
    operateur() {}
    virtual ~operateur() {}
    virtual void operator()() = 0;  //surcharge de () afin d'avoir le même comportement qu'un fonction.
                                    //l'ensemble des focnteurs retournent void, et n'ont aucun arguments
                                    // ils dépilent la pile, font les tests et calculs necessaire, et rempilent la pile dans l'operator ()
};


class adition : public operateur {
public :
    adition() {}
    virtual ~adition() {}
    void operator()() ;
};

class soustraction : public operateur {
public :
    soustraction() {}
    virtual ~soustraction() {}
    void operator()() ;
};

class multiplication : public operateur {
public :
    multiplication() {}
    virtual ~multiplication() {}
    void operator()() ;
};

class division : public operateur {
public :
    division() {}
    virtual ~division() {}
    void operator()() ;
};

class DIV : public operateur {
public :
    DIV() {}
    virtual ~DIV() {}
    void operator()() ;
    bool check(Literale& L) const;
};

class MOD : public operateur {
public :
    MOD() {}
    virtual ~MOD() {}
    void operator()() ;
    bool check(Literale& L) const;
};

class Ima : public operateur {
public :
    Ima() {}
    virtual ~Ima() {}
    void operator()() ;
    bool check(Literale& L) const;
};

class Neg : public operateur {
public :
    Neg() {}
    virtual ~Neg() {}
    void operator()() ;
};

class Num : public operateur {
public :
    Num() {}
    virtual ~Num() {}
    void operator()() ;
    bool check(Literale& L) const ;
};

class Den : public operateur {
public :
    Den() {}
    virtual ~Den() {}
    void operator()() ;
    bool check(Literale& L) const ;
};

class Re : public operateur {
public :
    Re() {}
    virtual ~Re() {}
    void operator()() ;
};

class Im : public operateur {
public :
    Im() {}
    virtual ~Im() {}
    void operator()() ;
};

class Eg : public operateur {
public :
    Eg() {}
    virtual ~Eg() {}
    void operator()() ;
};

class Diff : public operateur {
public :
    Diff() {}
    virtual ~Diff() {}
    void operator()() ;
};

class InfEg : public operateur {
public :
    InfEg() {}
    virtual ~InfEg() {}
    void operator()() ;
    bool check(Literale& L) const ;
};

class SupEg : public operateur {
public :
    SupEg() {}
    virtual ~SupEg() {}
    void operator()() ;
    bool check(Literale& L) const ;
};

class Inf : public operateur {
public :
    Inf() {}
    virtual ~Inf() {}
    void operator()() ;
    bool check(Literale& L) const ;
};

class Sup : public operateur {
public :
    Sup() {}
    virtual ~Sup() {}
    void operator()() ;
    bool check(Literale& L) const ;
};

class ET : public operateur {
public :
    ET() {}
    virtual ~ET() {}
    void operator()() ;
};

class OU : public operateur {
public :
    OU() {}
    virtual ~OU() {}
    void operator()() ;
};

class NON : public operateur {
public :
    NON() {}
    virtual ~NON() {}
    void operator()() ;
};


class CtrlZ : public operateur {
public :
    CtrlZ() {}
    virtual ~CtrlZ() {}
    void operator()() ;
};

class CtrlY : public operateur {
public :
    CtrlY() {}
    virtual ~CtrlY() {}
    void operator()() ;
};

#endif // OPERATEURS_H
