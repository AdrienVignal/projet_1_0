#ifndef OPERATEURS_H
#define OPERATEURS_H
#include "declarations.h"


//ensemble des focnteurs qui serviront d'operateurs



class operateur { //virtual
public :
    operateur() {}
    virtual ~operateur() {}
    virtual void operator()() = 0;  //surcharge de () afin d'avoir le même comportement qu'un fonction.
                                    //l'ensemble des focnteurs retournent void, et n'ont aucun arguments
                                    // ils depilent la pile, font les tests et calculs necessaire, et rempilent la pile dans l'operator ()
    virtual int arite() = 0 ;
};


class adition : public operateur {
public :
    adition() {}
    virtual ~adition() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class soustraction : public operateur {
public :
    soustraction() {}
    virtual ~soustraction() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class multiplication : public operateur {
public :
    multiplication() {}
    virtual ~multiplication() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class division : public operateur {
public :
    division() {}
    virtual ~division() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class DIV : public operateur {
public :
    DIV() {}
    virtual ~DIV() {}
    void operator()() ;
    bool check(Literale& L) const;
    int arite() {return 2 ;}
};

class MOD : public operateur {
public :
    MOD() {}
    virtual ~MOD() {}
    void operator()() ;
    bool check(Literale& L) const;
    int arite() {return 2 ;}
};

class Ima : public operateur {
public :
    Ima() {}
    virtual ~Ima() {}
    void operator()() ;
    bool check(Literale& L) const;
    int arite() {return 2 ;}
};

class Neg : public operateur {
public :
    Neg() {}
    virtual ~Neg() {}
    void operator()() ;
    int arite() {return 1 ;}
};

class Num : public operateur {
public :
    Num() {}
    virtual ~Num() {}
    void operator()() ;
    bool check(Literale& L) const ;
    int arite() {return 1 ;}
};

class Den : public operateur {
public :
    Den() {}
    virtual ~Den() {}
    void operator()() ;
    bool check(Literale& L) const ;
    int arite() {return 1 ;}
};

class Re : public operateur {
public :
    Re() {}
    virtual ~Re() {}
    void operator()() ;
    int arite() {return 1 ;}
};

class Im : public operateur {
public :
    Im() {}
    virtual ~Im() {}
    void operator()() ;
    int arite() {return 1 ;}
};

class Eg : public operateur {
public :
    Eg() {}
    virtual ~Eg() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class Diff : public operateur {
public :
    Diff() {}
    virtual ~Diff() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class InfEg : public operateur {
public :
    InfEg() {}
    virtual ~InfEg() {}
    void operator()() ;
    bool check(Literale& L) const ;
    int arite() {return 2 ;}
};

class SupEg : public operateur {
public :
    SupEg() {}
    virtual ~SupEg() {}
    void operator()() ;
    bool check(Literale& L) const ;
    int arite() {return 2 ;}
};

class Inf : public operateur {
public :
    Inf() {}
    virtual ~Inf() {}
    void operator()() ;
    bool check(Literale& L) const ;
    int arite() {return 2 ;}
};

class Sup : public operateur {
public :
    Sup() {}
    virtual ~Sup() {}
    void operator()() ;
    bool check(Literale& L) const ;
    int arite() {return 2 ;}
};

class ET : public operateur {
public :
    ET() {}
    virtual ~ET() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class OU : public operateur {
public :
    OU() {}
    virtual ~OU() {}
    void operator()() ;
    int arite() {return 2 ;}
};

class NON : public operateur {
public :
    NON() {}
    virtual ~NON() {}
    void operator()() ;
    int arite() {return 1 ;}
};


class CtrlZ : public operateur {
public :
    CtrlZ() {}
    virtual ~CtrlZ() {}
    void operator()() ;
    int arite() {return 0 ;}
};

class CtrlY : public operateur {
public :
    CtrlY() {}
    virtual ~CtrlY() {}
    void operator()() ;
    int arite() {return 0 ;}
};

class eval : public operateur {
public :
    eval() {}
    virtual ~eval() {}
    void operator()() ;
    int arite() {return 1 ;}
};
#endif // OPERATEURS_H

