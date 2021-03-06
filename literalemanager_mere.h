#ifndef LITERALEMANAGER_MERE_H
#define LITERALEMANAGER_MERE_H
#include "declarations.h"
#include "literale.h"
#include "lnum.h"
#include "complex"
#include "program.h"
#include "expression.h"

class LiteraleManager { //SINGLETON et FACTORY
protected:
    std::map<int, LiteraleManager*> corres;  //tab de correspondance entre un entier (1,2 ...)  et une fille de literale manager (entierManager ...)
    std::map<QString , Atome*> variables ;  //tab de corres entre un nom d'atome, et son adresse.
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
    void deleteTab() ;
    QVector<Literale*> tab ;
    QVector<Literale*> created ;
    QVector<Literale*> used ;
public:
    std::map<QString, Atome*> getMapAtom() const {return variables;}
    int choix_type(Attributs a) ;  //permet de choisir le type de litérale à construire en fct d'
    Literale& addLit(QString s) ;  //lance la procédure de création d'une litérale à partir d'une chaine
    Literale& addLit(Attributs a) ; //lance la procédure de création d'une litérale à partir d'un attribut
    virtual Literale& getLit(Attributs a) {} //fct virtuelle pemettant de créer un nouvel objet en fonvtion de son type
    void removeLiterale(Literale& L) ; //ajoute L à la liste deleted
    void deleteLiterale(Literale* L) ; //détruit definitivement une litérale
    void deleteLiteraleTab(QVector<Literale*>& V) ; //détruit definitivement un tableau de litérale
    static LiteraleManager& getInstance();
    static void libererInstance();
    QVector<Literale*> getUsed() {QVector<Literale*>tmp = used ;used.clear() ; return tmp ;  }
    QVector<Literale*> getCreated() {QVector<Literale*>tmp = created ;created.clear() ; return tmp ; }
    void affect(QString s, Literale* L);
    virtual Atome& getLit(QString s, Literale* a) {  }
    bool isVariable(QString s) ;
    Atome* getAtome(QString c) { return variables[c]  ; }
    bool activeVar(QVector<Literale*> V) ;
    bool desactiveVar(QVector<Literale*> V) ;


    friend class ProgWindow;
};

#endif // LITERALEMANAGER_MERE_H
