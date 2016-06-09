#ifndef LITERALEMANAGER_MERE_H
#define LITERALEMANAGER_MERE_H
#include "declarations.h"
#include "literale.h"
#include "lnum.h"
#include "complex"

class LiteraleManager { //SINGLETON et FACTORY
protected:
    std::map<int, LiteraleManager*> corres;  //tab de correspondance entre un entier (1,2 ...)  et une fille de literale manager (entierManager ...)
    LiteraleManager() ;
    virtual ~LiteraleManager() ;
    LiteraleManager(const LiteraleManager& m);
    LiteraleManager& operator=(const LiteraleManager& m);
    struct Handler{
        LiteraleManager* instance;
        Handler():instance(0){}
        ~Handler(){  delete instance;  }
    };
    static Handler handler;
    void initmap();

public:
    int choix_type(Attributs a) ;  //permet de choisir le type de litérale à construire en fct d'un attibut
    Literale& addLit(QString s) ;  //lance la procédure de création d'une litérale à partir d'une chaine
    Literale& addLit(Attributs a) ; //lance la procédure de création d'une litérale à partir d'un attribut
    virtual Literale& getLit(Attributs a) { }  //fct virtuelle pemettant de créer un nouvel objet en fonvtion de son type
    void removeLiterale(Literale& e);  //détruit une litérale
    static LiteraleManager& getInstance();
    static void libererInstance();

};

#endif // LITERALEMANAGER_MERE_H
