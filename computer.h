#ifndef _COMPUTER_H
#define _COMPUTER_H


#include "declarations.h"
#include "literale.h"
#include "lnum.h"
#include "complex.h"
#include "literalemanager_mere.h"
#include "literalemanager_filles.h"
#include "pile.h"
#include "operateurs.h"
#include "controleur.h"
#include "attributs.h"
#include "expression.h"


//fichier permettant d'inclure tous les autres


//gère les exceptions
class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};


#endif
