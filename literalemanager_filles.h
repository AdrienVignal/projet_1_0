#ifndef LITERALEMANAGER_FILLES_H
#define LITERALEMANAGER_FILLES_H
#include "declarations.h"
#include "literalemanager_mere.h"
#include "literale.h"


class EntierManager : public LiteraleManager {

    Entier& getLit(Attributs a) ; //créé un objet entier
    EntierManager() {}
    ~EntierManager();
    friend class LiteraleManager;
};

class FractionManager : public LiteraleManager {
    FractionManager() {}
    ~FractionManager() ;
    Fraction& getLit(Attributs a) ; //créé un objet fraction
    friend class LiteraleManager;

};

class ReelManager : public LiteraleManager {
    Reel& getLit(Attributs a) ; //créé un objet réel
    ReelManager() {}
    ~ReelManager() ;
    friend class LiteraleManager;
};

class ComplexManager : public LiteraleManager {
    Complex& getLit(Attributs a) ;  //créé un objet complex
    ComplexManager() {}
    ~ComplexManager() ;
    friend class LiteraleManager;
};

class ProgramManager : public LiteraleManager{
    Program& getLit(Attributs a) ;  //créé un objet program
    ProgramManager() {}
    ~ProgramManager() ;
    friend class LiteraleManager;
};

#endif // LITERALEMANAGER_FILLES_H
