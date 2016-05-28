#include "declarations.h"
#include "computer.h"
#include "literalemanager_filles.h"


//fonction factory concrètes
//on créé un nouvel objet en appelant son constructeur, dont on a les droits

Fraction& FractionManager::getLit(Attributs a) {
    return *(new Fraction(a)) ;
}


Entier& EntierManager::getLit(Attributs a) {
    return *(new Entier(a.num)) ;
}


Reel& ReelManager::getLit(Attributs a) {
    return *(new Reel(a.num/a.denom)) ;
}

Complex& ComplexManager::getLit(Attributs a) {
    return *(new Complex(a)) ;
}

Program& ProgramManager::getLit(Attributs a){
    return *(new Program(a)) ;
}
