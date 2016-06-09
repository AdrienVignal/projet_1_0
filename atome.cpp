#include "declarations.h"
#include "computer.h"
#include "atome.h"


Atome::~Atome() {
}

Attributs Atome::getValue() const {
    return lit->getValue() ;
}


QString Atome::toString() const {
    return lit->toString() ;
}
