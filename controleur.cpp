#include "declarations.h"
#include "controleur.h"
#include "computer.h"

Controleur* Controleur::getInstance(){
    return handlerC.instance;
}

void Controleur::libererInstance(){
    LiteraleManager::libererInstance() ;
    delete(handlerC.instance) ;
    handlerC.instance=0;
}

Controleur::HandlerC Controleur::handlerC=Controleur::HandlerC();

Controleur* Controleur::getInstance(LiteraleManager& m, Pile& v){
    if (handlerC.instance==0) {
        handlerC.instance=new Controleur( m,  v);
        handlerC.instance->initFonct();
    }
    return handlerC.instance;
}


bool estUneLiterale(const QString s){
    //utilisation des exp régulières pour tester si les chaines sont des litérales
   if(s.startsWith("["))return true ;
   if(s.startsWith("'"))return true ;
   QRegExp ri("^(\\d+)$"); // début + 1..* digit + fin
   if(s.contains(ri)) return true ;
   QRegExp rr("^(\\d+)\\.(\\d+)$");     // début + 1..* digit + . + 1..* digit + fin
   if(s.contains(rr)) return true ;
   QRegExp rf("^(\\d+)/(\\d+)$");   // début + 1..* digit + / + 1..* digit + fin
   if(s.contains(rf)) return true ;
   QRegExp rim("^\\d+((\\.|/)\\d+)?\\$\\d+((\\.|/)\\d+)?$");    // début + 1..* digit + éventuelement ( (/ suivi de 1..* digit) ou (. suivi de 1..*digit))
                                                                // + $ + 1..* digit + éventuelement ( (/ suivi de 1..* digit) ou (. suivi de 1..*digit)) + fin
   if(s.contains(rim)) return true ;
   return false;
}


void Controleur::initFonct() { //création des foncteurs, et entré dans le map
    fonct["+"] = new adition ;
    fonct["-"] = new soustraction ;
    fonct["*"] = new multiplication ;
    fonct["/"] = new division ;
    fonct["DIV"] = new DIV ;
    fonct["MOD"] = new MOD ;
    fonct["$"] = new Ima ;
    fonct["NEG"] = new Neg ;
    fonct["NUM"] = new Num ;
    fonct["DEN"] = new Den ;
    fonct["RE"] = new Re ;
    fonct["IM"] = new Im ;
    fonct["="] = new Eg ;
    fonct["!="] = new Diff ;
    fonct["<="] = new InfEg ;
    fonct[">="] = new SupEg ;
    fonct["<"] = new Inf ;
    fonct[">"] = new Sup ;
    fonct["AND"] = new ET ;
    fonct["OR"] = new OU ;
    fonct["NOT"] = new NON ;
    fonct["UNDO"] = new CtrlZ;
    fonct["REDO"] = new CtrlY;

}

Controleur::~Controleur() {}

void Controleur::sauvegarde() {
    saves.getID();
    QVector<Literale*> c = expMng.getCreated();


    if (expAff.isModified() )
        //saves.addState(expAff.stack , expMng.getUsed() , expMng.getCreated()) ;
        saves.addState(expAff.stack , expMng.getUsed() , c) ;
    expAff.NoModif();
   //qDebug()<<"taille mem = "<<saves.getSize() ;
   //qDebug()<<"courrant = "<<saves.getCourrant() ;

   saves.getID();

}

void Controleur::commande(const QString& c){
    if (estUneLiterale(c))
        expAff.push(expMng.addLit(c));  //on met dans la pile
    else{
        if(fonct.find(c) == fonct.end())  //vérifie que c est bien unr clé de map
            expAff.setMessage("Erreur : commande inconnue");
        else
            (*fonct[c])(); //appelle de la surcharge de opérateur() du foncteur approprié
    }

}
void Controleur::rest() {
    expAff.stack = saves.GetState() ;
    expAff.NoModif();
}

void Controleur::unRest() {
    expAff.stack = saves.GetStateDown() ;
    expAff.NoModif();
}

QString Controleur::getProg(QString s){
    int i = 1 ;   //pointeur sur un char
    int count = 1 ;  //compte le nb de [ et ]
    QString rslt = "[" ; //on est censé commencer le prog par [
    while (i<s.size() && count != 0){  //tant que on a des char, ou tant que la [ n'est pas fermée
        if (s[i].toLatin1() == '[') ++count ;  //si on ouvre un prog dans le prog, on augmente count
        if (s[i].toLatin1() == ']') --count ;   //si un prog se ferme, on dec count
        rslt.push_back(s[i]);                 //on ajoute les char au fur et à mesure
        ++i ;
    }
    if (count > 0) rslt = "" ; //on vérifie que tt les progs ouverts soient fermés
    if (!rslt.endsWith(" ]")) rslt = "" ;   //on vérifie un peu la base, c'est à  dire que il y est des espaces et des crochets
    if (!rslt.startsWith("[ ")) rslt = "" ;
    return rslt ;

}

