#include "declarations.h"
#include "computer.h"
#include "atome.h"


Atome::~Atome() {
    LiteraleManager::getInstance().deleteLiterale(lit);
}

Attributs Atome::getValue() const {
    return Attributs(name) ;
}

QString Atome::toString() const {
    return lit->toString() ;
}
