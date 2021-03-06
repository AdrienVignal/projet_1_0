#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "declarations.h"
#include "memento.h"

class Controleur { //SINGLETON
    LiteraleManager& expMng;
    Pile& expAff;
    Memento saves ;
    std::map <QString , operateur*> fonct ;
    bool err ;
    //on met privé tous les consructueurs
    Controleur(LiteraleManager& m, Pile& v):expMng(m), expAff(v) , err(false){ }
    Controleur(const Controleur& c) ;
    ~Controleur() ;
    Controleur& operator = (const Controleur& c) ;
    void initFonct() ; // initialise le map fonct avec les focnteurs

    struct HandlerC{ //permet de récupérer l'instance
        Controleur* instance;
        HandlerC():instance(0){}
        ~HandlerC(){  delete instance;  }
    };
    static HandlerC handlerC;

public:
    void commande(const QString& c);   //fonction qui gère l'éxcution des commadnes
    Pile& getPile()  {return expAff ; }   //renvoit l'adresse de la pile
    void sauvegarde() ;
    static Controleur* getInstance(LiteraleManager& m, Pile& v);
    static Controleur* getInstance();
    static void libererInstance();
    int nbSaved() {return (saves.nbSaved() - saves.getCourrant()) * (saves.getCourrant() != 0); }
    int courrant() {return saves.getCourrant() ; }
    void rest() ;
    void unRest() ;
    QString getProg(QString s) ;
    QString getExp(QString s) ;
    bool estUnOperateur(const QString s){return fonct.find(s) != fonct.end() ; }
    void erreur(bool b) {err = b ; }
    bool getErreur() {return err ; }
    void cancel() ;
};

bool estUneLiterale(const QString s);
QString getProg(QString s) ;
QString getExp(QString s) ;
QString getPara(QString s) ;



#endif // CONTROLEUR_H
