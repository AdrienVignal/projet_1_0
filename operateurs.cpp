#include "declarations.h"
#include "operateurs.h"
#include "computer.h"

//ensemble des foncteurs concret construit pour éxécuter les opérandes
//ainsi que ci necessaire une méthode check, qui vérifie si tt les condtions sont remplies pour faire le calcul

void adition::operator()() {

    Pile& P = Controleur::getInstance()->getPile() ; // accède à la pile

    if (P.stack.size() >= 2){  //vérifie s'il y a assez de litérale pour exécuter l'instructructuon

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Literale& v2=P.top(); //prend la première litérale
            P.pop();
            if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                Literale& v1=P.top();  //prend la deuxième
                P.pop();
                QString s =v1.toString() ;
                    s.push_back('+');
                    s.push_back(v2.toString());
                    s.remove("'") ;
                    s.push_back("'");
                    s.push_front("'");
                    Attributs res = Attributs(s) ;
                    LiteraleManager::getInstance().removeLiterale(v1);  //destruction des anciennes litérales
                    LiteraleManager::getInstance().removeLiterale(v2);
                    Literale& e=LiteraleManager::getInstance().addLit(res);  //création d'une nouvelle litérale à partir de res
                    P.push(e);  // on push la nouvele litérale
                    return ;
            }
            else{
                P.push(v2);
                if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                    Controleur::getInstance()->commande("");
                    if (Controleur::getInstance()->getErreur())return ;
                }
            }


        }
    Literale& v2=P.top(); //prend la première litérale
    P.pop();

    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }

    Literale& v1=P.top();  //prend la deuxième
    P.pop();
    Attributs res;
    res=v1+v2;   //on additionne tous ça
    LiteraleManager::getInstance().removeLiterale(v1);  //destruction des anciennes litérales
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);  //création d'une nouvelle litérale à partir de res
    P.push(e);  // on push la nouvele litérale
    }

    else{
        P.setMessage("Erreur : pas assez d'arguments");
        return ;
    }
}

void soustraction::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 2){

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Literale& v2=P.top(); //prend la première litérale
            P.pop();
            if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                Literale& v1=P.top();  //prend la deuxième
                P.pop();
                QString s =v1.toString() ;
                    s.push_back('-');
                    s.push_back(v2.toString());
                    s.remove("'") ;
                    s.push_back("'");
                    s.push_front("'");
                    Attributs res = Attributs(s) ;
                    LiteraleManager::getInstance().removeLiterale(v1);  //destruction des anciennes litérales
                    LiteraleManager::getInstance().removeLiterale(v2);
                    Literale& e=LiteraleManager::getInstance().addLit(res);  //création d'une nouvelle litérale à partir de res
                    P.push(e);  // on push la nouvele litérale
                    return ;
            }
            else{
                P.push(v2);
                if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                    Controleur::getInstance()->commande("EVAL");
                    if (Controleur::getInstance()->getErreur())return ;
                }
            }


        }

    Literale& v2=P.top();
    P.pop();

    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v1=P.top();
    P.pop();
    Attributs res;

    res=v1-v2;
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void multiplication::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 2){

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Literale& v2=P.top(); //prend la première litérale
            P.pop();
            if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                Literale& v1=P.top();  //prend la deuxième
                P.pop();
                QString s =v1.toString() ;
                    if(lowerPrio((Expression*) &v1)<2){
                    s.push_front('(');
                    s.push_back(')');
                    }
                    s.push_back('*');
                    if(lowerPrio((Expression*) &v2)<2)  s.push_back('(');
                    s.push_back(v2.toString());
                    if(lowerPrio((Expression*)&v2)<2) s.push_back(')');
                    s.remove("'") ;
                    s.push_back("'");
                    s.push_front("'");
                    Attributs res = Attributs(s) ;
                    LiteraleManager::getInstance().removeLiterale(v1);  //destruction des anciennes litérales
                    LiteraleManager::getInstance().removeLiterale(v2);
                    Literale& e=LiteraleManager::getInstance().addLit(res);  //création d'une nouvelle litérale à partir de res
                    P.push(e);  // on push la nouvele litérale
                    return ;
            }
            else{
                P.push(v2);
                if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                    Controleur::getInstance()->commande("EVAL");
                    if (Controleur::getInstance()->getErreur())return ;
                }
            }


        }
    Literale& v2=P.top();
    P.pop();
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v1=P.top();
    P.pop();
    Attributs res;
    res=v1*v2;


    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void division::operator()() {

    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 2){

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Literale& v2=P.top(); //prend la première litérale
            P.pop();
            if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                Literale& v1=P.top();  //prend la deuxième
                P.pop();
                QString s =v1.toString() ;
                    if(lowerPrio((Expression*) &v1)<2){
                    s.push_front('(');
                    s.push_back(')');
                    }
                    s.push_back('/');
                    if(lowerPrio((Expression*) &v2)<2)  s.push_back('(');
                    s.push_back(v2.toString());
                    if(lowerPrio((Expression*)&v2)<2) s.push_back(')');
                    s.remove("'") ;
                    s.push_back("'");
                    s.push_front("'");
                    Attributs res = Attributs(s) ;
                    LiteraleManager::getInstance().removeLiterale(v1);  //destruction des anciennes litérales
                    LiteraleManager::getInstance().removeLiterale(v2);
                    Literale& e=LiteraleManager::getInstance().addLit(res);  //création d'une nouvelle litérale à partir de res
                    P.push(e);  // on push la nouvele litérale
                    return ;
            }
            else{
                P.push(v2);
                if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                    Controleur::getInstance()->commande("EVAL");
                    if (Controleur::getInstance()->getErreur())return ;
                }
            }


        }

    Literale& v2=P.top();
    P.pop();
    if ((v2.getValue().num == 0) && (v2.getValue().ImNum==0)){
        P.setMessage("Erreur : division par zéro");
        LiteraleManager::getInstance().removeLiterale(v2);
        return ; }

    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v1=P.top();
    P.pop();
    Attributs res;

    res=v1/v2;
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void DIV::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 2){



    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    if (! DIV::check(v2)) return ;

    P.pop() ;
    if ((v2.getValue().num == 0) && (v2.getValue().ImNum==0)){
        P.setMessage("Erreur : division par zéro");
        LiteraleManager::getInstance().removeLiterale(v2);
        return ; }


    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v1=P.top();
    if (! DIV::check(v1)) {
        P.push(v2) ;
        return ;
    }
    P.pop() ;

    Attributs res;
    res= Attributs((int) v1.getValue().num/ (int) v2.getValue().num );
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool DIV::check(Literale& L) const {
    if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
    Controleur::getInstance()->getPile().setMessage("Erreur : Arguments non entiers");
    return false ;
}

void MOD::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v2=P.top();
    if (! MOD::check(v2)) return ;
    P.pop() ;
    if ((v2.getValue().num == 0) && (v2.getValue().ImNum==0)){
        P.setMessage("Erreur : division par zéro");
        LiteraleManager::getInstance().removeLiterale(v2);
        return ; }
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v1=P.top();
    if (! MOD::check(v1)){
        P.push(v2) ;
        return ;
    }
    P.pop() ;

    Attributs res;
    res= Attributs((int) v1.getValue().num % (int) v2.getValue().num );
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool MOD::check(Literale& L) const {
    if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
    Controleur::getInstance()->getPile().setMessage("Erreur : Arguments non entiers");
    return false ;
}

void Ima::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 2){

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Literale& v2=P.top(); //prend la première litérale
            P.pop();
            if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                Literale& v1=P.top();  //prend la deuxième
                P.pop();
                QString s =v1.toString() ;
                    if(lowerPrio((Expression*) &v1)<3){
                    s.push_front('(');
                    s.push_back(')');
                    }
                    s.push_back('$');
                    if(lowerPrio((Expression*) &v2)<3)  s.push_back('(');
                    s.push_back(v2.toString());
                    if(lowerPrio((Expression*)&v2)<3) s.push_back(')');
                    s.remove("'") ;
                    s.push_back("'");
                    s.push_front("'");
                    Attributs res = Attributs(s) ;
                    LiteraleManager::getInstance().removeLiterale(v1);  //destruction des anciennes litérales
                    LiteraleManager::getInstance().removeLiterale(v2);
                    Literale& e=LiteraleManager::getInstance().addLit(res);  //création d'une nouvelle litérale à partir de res
                    P.push(e);  // on push la nouvele litérale
                    return ;
            }
            else{
                P.push(v2);
                if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
                    Controleur::getInstance()->commande("EVAL");
                    if (Controleur::getInstance()->getErreur())return ;
                }
            }


        }

    Literale& v2=P.top();
    if (! Ima::check(v2)) return ;
    P.pop() ;

    Literale& v1=P.top();
    if (! Ima::check(v1)) {
        P.push(v2) ;
        return ;
    }
    P.pop() ;

    Attributs res;
    res= Attributs( v1.getValue().num , v1.getValue().denom  ,  v2.getValue().num , v2.getValue().denom  );
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool Ima::check(Literale& L) const {
    if (LiteraleManager::getInstance().choix_type(L.getValue()) != 4) return true ;
    Controleur::getInstance()->getPile().setMessage("Erreur : Arguments deja complexes");
    return false ;
}

void Neg::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 1){

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }

    Literale& v1=P.top();
    P.pop() ;

    Attributs res;
    res= Attributs( -v1.getValue().num , v1.getValue().denom  ,  -v1.getValue().ImNum , v1.getValue().ImDenom  );
    LiteraleManager::getInstance().removeLiterale(v1);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}


void Num::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 1){

        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }

    Literale& v1=P.top();
    if (! Num::check(v1))
        return ;
    P.pop() ;

    Attributs res;
    res= Attributs( v1.getValue().num , 1 );
    LiteraleManager::getInstance().removeLiterale(v1);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool Num::check(Literale& L) const {
    if (LiteraleManager::getInstance().choix_type(L.getValue()) == 3) return true ;
    if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
    Controleur::getInstance()->getPile().setMessage("Erreur : Arguments sans numerateur");
    return false ;
}

void Den::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    if (! Den::check(v1))
        return ;
    P.pop() ;

    Attributs res;
    res= Attributs( v1.getValue().denom , 1 );
    LiteraleManager::getInstance().removeLiterale(v1);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool Den::check(Literale& L) const {
    if (LiteraleManager::getInstance().choix_type(L.getValue()) == 3) return true ;
    if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
    Controleur::getInstance()->getPile().setMessage("Erreur : Arguments sans denominateur");
    return false ;
}

void Re::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;

    Attributs res;
    res= Attributs( v1.getValue().num , v1.getValue().denom , 0 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Im::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >= 1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;

    Attributs res;
    res= Attributs( v1.getValue().ImNum , v1.getValue().ImDenom , 0 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Eg::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    P.pop() ;

    Attributs res;
    if (v1.getValue()==v2.getValue())
    res= Attributs( 1 , 1);
    else res= Attributs( 0 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Diff::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    P.pop() ;

    Attributs res;
    if (v1.getValue()==v2.getValue())
    res= Attributs( 0 , 1);
    else res= Attributs( 1 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void InfEg::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    if (!InfEg::check(v1) )return ;
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    if (!InfEg::check(v2) ){
        P.push(v1);
        return ;
    }
    P.pop() ;

    Attributs res;
    if (v2.getValue()<v1.getValue())
    res= Attributs( 1 ,1);
    else res= Attributs( 0 , 1);
    if (v1.getValue()==v2.getValue())
        res= Attributs( 1 ,1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool InfEg::check(Literale& L) const {
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 3) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 2) return true ;
Controleur::getInstance()->getPile().setMessage("Erreur : Arguments incomparables");
return false ;
}

void SupEg::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    if (!SupEg::check(v1) )return ;
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    if (!SupEg::check(v2) ){
        P.push(v1);
        return ;
    }
    P.pop() ;

    Attributs res;
    if (v2.getValue()<v1.getValue())
    res= Attributs( 0 ,1);
    else res= Attributs( 1 , 1);
    if (v1.getValue()==v2.getValue())
        res= Attributs( 1 ,1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool SupEg::check(Literale& L) const {
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 3) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 2) return true ;
Controleur::getInstance()->getPile().setMessage("Erreur : Arguments incomparables");
return false ;
}

void Inf::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    if (!Inf::check(v1) )return ;
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    if (!Inf::check(v2) ){
        P.push(v1);
        return ;
    }
    P.pop() ;

    Attributs res;
    if (v2.getValue()<v1.getValue())
    res= Attributs( 1 ,1);
    else res= Attributs( 0 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool Inf::check(Literale& L) const {
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 3) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 2) return true ;
Controleur::getInstance()->getPile().setMessage("Erreur : Arguments incomparables");
return false ;
}

void Sup::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    if (!Sup::check(v1) )return ;
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    if (!Sup::check(v2) ){
        P.push(v1);
        return ;
    }
    P.pop() ;

    Attributs res;
    if (v2.getValue()<v1.getValue())
    res= Attributs( 0 ,1);
    else res= Attributs( 1 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

bool Sup::check(Literale& L) const {
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 3) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 1) return true ;
if (LiteraleManager::getInstance().choix_type(L.getValue()) == 2) return true ;
Controleur::getInstance()->getPile().setMessage("Erreur : Arguments incomparables");
return false ;
}

void ET::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    P.pop() ;

    Attributs res (0,1);
    if ((v2.getValue() == res) || (v1.getValue() == res))
    res= Attributs( 0 ,1);
    else res= Attributs( 1 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void OU::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;
    if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
        Controleur::getInstance()->commande("EVAL");
        if (Controleur::getInstance()->getErreur())return ;
    }
    Literale& v2=P.top();
    P.pop() ;

    Attributs res(0,1);
    if ((v2.getValue() == res) && (v1.getValue() == res))
    res= Attributs( 0 ,1);
    else res= Attributs( 1 , 1);
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void NON::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
    Literale& v1=P.top();
    P.pop() ;

    Attributs res(0,1);
    if ((v1.getValue() == res))
        res = Attributs(1,1) ;
    LiteraleManager::getInstance().removeLiterale(v1);
    Literale& e=LiteraleManager::getInstance().addLit(res);
    P.push(e);
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void CtrlZ::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if(Controleur::getInstance()->nbSaved() >0){
        Controleur::getInstance()->rest() ; }
        else
        P.setMessage("Erreur : UNDO impossible");
}

void CtrlY::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if(Controleur::getInstance()->courrant() >1 ){
        Controleur::getInstance()->unRest() ; }
        else
        P.setMessage("Erreur : REDO impossible");
}

void eval::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){

    Literale& v1=P.top();
    P.pop() ;

    Attributs res = v1.getValue() ;
    int i = LiteraleManager::getInstance().choix_type(res) ;
    if (i!=5 && i!=6){
         P.setMessage("Erreur : argument non évaluable");
         P.push(v1);
         return ;
    }
    if (i == 5) ((Program&) v1).eval() ;
    if (i == 6) ((Expression&) v1).eval() ;

    if (Controleur::getInstance()->getErreur()) {
        Controleur::getInstance()->cancel() ;
        P.setMessage("Erreur : mauvaise syntaxe");
    }
    else{
    LiteraleManager::getInstance().removeLiterale(v1);
    }

    return ;
    }
        P.setMessage("Erreur : pas assez d'arguments");

}


void Cos::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qCos(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qCos(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}
void Sin::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qSin(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qSin(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}
void Tan::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qTan(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qTan(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}
void Arccos::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qAcos(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);

        }
        else{
        Attributs res(QMATH_H::qAcos(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}
void Arcsin::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qAsin(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qAsin(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}
void Arctan::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qAtan(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qAtan(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Exp::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qExp(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qExp(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Ln::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qLn(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qLn(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Sqrt::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qSqrt(v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
        }
        else{
        Attributs res(QMATH_H::qSqrt(v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Pow::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v1=P.top();
        P.pop();
        if (LiteraleManager::getInstance().choix_type(P.top().getValue())==6) {
            Controleur::getInstance()->commande("EVAL");
            if (Controleur::getInstance()->getErreur())return ;
        }
        Literale& v2=P.top();
        P.pop();
        if(std::isnan(QMATH_H::qPow(v2.getValue().num,v1.getValue().num))){
            P.setMessage("Erreur argument incorrect");
            P.push(v1);
            P.push(v2);
        }
        else{
        Attributs res(QMATH_H::qPow(v2.getValue().num,v1.getValue().num),1);

        LiteraleManager::getInstance().removeLiterale(v1);
        LiteraleManager::getInstance().removeLiterale(v2);
        Literale& e=LiteraleManager::getInstance().addLit(res);
        P.push(e);
        }
    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void Aff::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){

      if (LiteraleManager::getInstance().choix_type(P.top().getValue())!=6) {
           P.setMessage("Erreur : mauvais arguments");
           return ;
       }
    QRegExp exp("^[A-Z]([A-Z]|\\d)*$");
    Literale& v1=P.top();
    QString s = v1.toString() ;
    s.remove("'") ;

    if (!s.contains(exp)){
        P.setMessage("Erreur : mauvaise expression");
        return ; }

    if (Controleur::getInstance()->estUnOperateur(s)){
        P.setMessage("Erreur : nom deja pris");
        return ; }

    P.pop() ;
    Literale& v2=P.top();
    P.pop() ;

    Attributs res = v2.getValue() ;
    LiteraleManager::getInstance().removeLiterale(v1);
    LiteraleManager::getInstance().removeLiterale(v2);
    Literale& e=LiteraleManager::getInstance().addLit(res);

    LiteraleManager::getInstance().affect(s , &e);
    }


    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}


void Forget::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){
      if (LiteraleManager::getInstance().choix_type(P.top().getValue())!=6) {
           P.setMessage("Erreur : mauvais arguments");
           return ;
       }
    Literale& v1=P.top();
    QString s = v1.toString() ;
    s.remove("'") ;
    if (!LiteraleManager::getInstance().isVariable(s)){
        P.setMessage("Erreur : variable non affectée");
        return ; }

    P.pop() ;
    LiteraleManager::getInstance().removeLiterale(v1);
    Atome* A = LiteraleManager::getInstance().getAtome(s) ;
    LiteraleManager::getInstance().removeLiterale(*A);
    }


    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void dup::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){

        Literale& v1=P.top();
        Literale& e=LiteraleManager::getInstance().addLit(v1.getValue());
        P.push(e);

    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void drop::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=1){

        Literale& v1=P.top();
        P.pop() ;
        LiteraleManager::getInstance().removeLiterale(v1);

    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}

void echange::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){

        Literale& v1=P.top();
        P.pop() ;
        Literale& v2=P.top();
        P.pop() ;

        Literale& e1=LiteraleManager::getInstance().addLit(v1.getValue());
        Literale& e2=LiteraleManager::getInstance().addLit(v2.getValue());
        LiteraleManager::getInstance().removeLiterale(v1);
        LiteraleManager::getInstance().removeLiterale(v2);
        P.push(e1);
        P.push(e2);

    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}


void vide::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    while (!P.stack.empty()){
        Literale& v1=P.top();
        P.pop() ;
        LiteraleManager::getInstance().removeLiterale(v1);
    }
}

void SI::operator()() {
    Pile& P = Controleur::getInstance()->getPile() ;
    if (P.stack.size() >=2){

        Literale& v1=P.top();
        P.pop() ;
        Literale& v2=P.top();

        Attributs res(0,1);
        if (v1.getValue() == res) {
             P.pop() ;
             LiteraleManager::getInstance().removeLiterale(v2);
        }
        else{
            Controleur::getInstance()->commande("EVAL");
        }
        LiteraleManager::getInstance().removeLiterale(v1);

    }
    else{
        P.setMessage("Erreur : pas assez d'arguments");
    }
}
