#include "declarations.h"

#include "computer.h"
#include "literalemanager_filles.h"


//fonction factory concrètes
//on créé un nouvel objet en appelant son constructeur, dont on a les droits

EntierManager::~EntierManager(){}

FractionManager::~FractionManager(){}

ReelManager::~ReelManager(){}

ComplexManager::~ComplexManager(){}

ProgramManager::~ProgramManager(){}

ExpressionManager::~ExpressionManager(){}


Fraction& FractionManager::getLit(Attributs a) {
    return *(new Fraction(a)) ;
}


Entier& EntierManager::getLit(Attributs a) {
    return *(new Entier(a)) ;
}


Reel& ReelManager::getLit(Attributs a) {
    return *(new Reel(a)) ;
}

Complex& ComplexManager::getLit(Attributs a) {
    return *(new Complex(a)) ;

}

Program& ProgramManager::getLit(Attributs a){
    return *(new Program(a)) ;
}

Expression& ExpressionManager::getLit(Attributs a){
    return *(new Expression(a)) ;
}



