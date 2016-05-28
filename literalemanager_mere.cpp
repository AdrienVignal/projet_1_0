#include "declarations.h"
#include "computer.h"
#include "literalemanager_mere.h"


//fonctions factory abstraite

LiteraleManager::Handler LiteraleManager::handler=LiteraleManager::Handler();  //initialisation du paramètre static


LiteraleManager& LiteraleManager::getInstance(){
    if (handler.instance==0) {
        handler.instance=new LiteraleManager;
        handler.instance->initmap();
    }
    return *handler.instance;
}

LiteraleManager::LiteraleManager() {}
LiteraleManager::~LiteraleManager() {
    for (int i = 1 ; i< 5 ; ++i) delete corres[i] ;
}


void LiteraleManager::libererInstance(){
    delete(handler.instance) ;
    handler.instance=0;
}


void LiteraleManager::removeLiterale(Literale& e){
    delete(&e) ;
}

int LiteraleManager::choix_type(Attributs a) {
    if (a.s.startsWith("["))
        return 5;
    if (a.ImNum != 0) // si imaginaire , retourne  4
        return 4 ;
    if (a.denom == 1 && floor(a.num)==a.num && a.num<=2147483647 && -1*a.num <= 2147483647 )
        return 1 ;  // si entier pas trop grand, retourne 1
    if ((a.denom == 1 && floor(a.num)!=a.num)|| a.num>2147483647 || a.denom> 2147483647 || -1*a.num > 2147483647 || -1*a.denom > 2147483647 )
        return 2 ;  //si réel, ou si entier trop grand, ou si numérateur/dénominateur trop grand, retourne 2
    if ((a.denom != 1 && floor(a.num)==a.num) && (a.num <= 2147483647 && a.denom <= 2147483647) && (-1*a.num <= 2147483647 && -1*a.denom <= 2147483647) )
        return 3 ;  //si fraction, et si numérateur/dénominateur pas trop grand, retourne 3
}

void LiteraleManager::initmap() {

    //initialisation de la table de correspondance
    corres[1] = new EntierManager;
    corres[2] = new ReelManager;
    corres[3] = new FractionManager;
    corres[4] = new ComplexManager;
    corres[5] = new ProgramManager;
}


Literale& LiteraleManager::addLit(QString s) {

    //on a une chaine de caractère s qui est un nombre, et on veut mettre chque élément de cette chaine à sa place dans un attribut


    Attributs A ;

    if(s.startsWith("[")){
        A = Attributs(0,1,0,1,s);
    }

    QRegExp ri("^(\\d+)$"); //test entier
    if(s.contains(ri)) {
        A = Attributs(s.toDouble() );  //A  = l'entier
    }


    QRegExp rr("^(\\d+)\\.(\\d+)$"); // test réel
    if(s.contains(rr)) {
        A =Attributs( s.toDouble()) ; // A = réel
    }


    QRegExp rf("^(\\d+)/(\\d+)$");  //test fraction
    if(s.contains(rf)) {
        QString numStr , denomStr ;
        QRegExp rx("(\\d+)");
        QRegExp rx2("(/\\d+)$");
        s.contains(rx) ;
        s.contains(rx2) ;
        numStr = rx.cap(1) ;        //récupération numérateur (string)
        denomStr = rx2.cap(1) ;     //récupération dénominateur (string)
        denomStr.remove(0,1) ;
        A = Attributs(numStr.toDouble() , denomStr.toDouble() ) ;  //création de l'arttibut A = (num , denom)
    }


    QRegExp rim("^\\d+((\\.|/)\\d+)?\\$\\d+((\\.|/)\\d+)?$");  //test imaginaire
    if(s.contains(rim)) {
        QString Re , Im ;
        QRegExp rx("^\\d+((\\.|/)\\d+)?\\$");
        QRegExp rx2("\\$\\d+((\\.|/)\\d+)?$");
        s.contains(rx) ;
        Re = rx.cap(0) ;  // récupération partie réelle (string)
        Re.remove(Re.size()-1, 1) ;
        s.contains(rx2) ;
        Im = rx2.cap(0) ; // récupération partie imaginaire (string)
        Im.remove(0 , 1) ;
        Literale& LRe = addLit(Re) ;  //rappel de la fonction pour construire le litéral de la partie réelle
        Literale& LIm = addLit(Im) ;    //rappel de la fonction pour construire le litéral de la partie im
        A = Attributs (LRe.getValue().num , LRe.getValue().denom , LIm.getValue().num , LIm.getValue().denom) ;  //entrée de attribut
        delete(&LRe) ; //supression des litérale créées
        delete(&LIm) ;
    }
    int i = choix_type(A) ;  //retourne le type de A
    return corres[i]->getLit(A) ; //construit la litérale en fct du type et de A

}


Literale& LiteraleManager::addLit(Attributs a) {
    int i = choix_type(a ) ; //vérifie le type de a
    return corres[i]->getLit(a);  //construit la litérale appropriéee
}
