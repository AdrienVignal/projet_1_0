#include "declarations.h"
#include "computer.h"
#include "expression.h"



QString Expression::toString() const {
    return exp ;
}


void Expression::eval() const{
    QString source = convertToPolish(exp) ;
    QTextStream s (&source) ;
    QString c ;
    s>> c ;

    while (c != "") {
        Controleur::getInstance()->commande(c) ;
        s>>c ;
    }
}

QString convertToPolish(QString s) {
    s.remove(" ") ;  //on enlève les espaces et les '
    s.remove("'") ;

    QMap<QChar , int> charSpe ;
    charSpe['+'] = 1 ;
    charSpe['-'] = 1 ;
    charSpe['/'] = 2 ;
    charSpe['*'] = 2 ;
    charSpe['$'] = 3 ;
    charSpe[','] = 0 ;
    int i = 0 ;                  //pointeur pour se déplacer dans la chaine
    QString result = "" ;
    QString op = "" ;  //variable tempon pour retenir un opérateur ;
    bool neg = false ;

    if (s[0]=='-'){
        neg = true ;   //si on a un - en début, alors il faudra finir par un NEG à la fin du prog
        s.remove(0,1) ;//on enlève -
    }




    while(i<s.size()){

        if (s[i]=='('){
            QString temp = getPara(s) ;         //on prend le bloc ( .... ) ;
                if (temp.isEmpty()) return "ERROR" ; //si vide, erreur
            int taille = temp.size() ;
            s.remove(i , taille) ;              //on l'enlève de la chaine source
            temp.remove(0,1) ;
            temp.remove(temp.size()-1 ,1 ) ;    //on enlève ( et )
            temp = convertToPolish(temp) ;      //récursivité, pour convertir son contenu
            result.push_back(temp);             //on push le resultat
            result.push_back(" "); //on met un espace
            if (neg){ //si il y avait - devant :
                result.push_back("NEG ");
                neg = false ;
            }
        }

        else{
            if (s[i].isDigit()){ //si on a un nombre
                while((i<s.size()) && (!charSpe.contains(s[i]))){  //tant qu'on voit pas d'op spé, et qu'il y a des trucs
                    result.push_back(s[i]);   //on le met dans result
                    s.remove(i,1) ;          //on l'enlève de source
                }
                result.push_back(" "); //on met un espace
                if (neg){ //si il y avait - devant :
                    result.push_back("NEG ");
                    neg = false ;
                }
            }

            else{
                if (charSpe.contains(s[i])){ //si on a un op spé
                    if (!op.isEmpty()){  //si jamais un op normal est sauvegardé
                        result.push_back(op); //on l'ajoute
                        op = "" ; //on remet à 0
                        result.push_back(" "); //on met un espace
                    }
                   if (i> 0) {  //si jamais il est pas en tête de chaine
                       if (charSpe[s[i]]>charSpe[s[i-1]]){ //on teste les priorités , si supérieur :
                           i++ ; //on save
                       }
                       else{ //si inf ou égal
                       --i ;  //on traite l'op en tête
                       result.push_back(s[i]);  //on le push
                       result.push_back(" "); //on met un espace
                       s.remove(i,1) ;   //on le détruit
                       }
                   }
                   else{
                   if (s[i]==',') s.remove(i,1) ;  //enlève , qui sert juste de séparateur
                   else i++ ;   //on "sauvegarde" l'op spé
                    }
                }

                else{

                    if (s[i].isLetter() ){ //si on a une lettre, alors 2 cas : opérateur (opérande) ,  variable (atome)
                        QString temp ;
                        while((i<s.size()) && s[i].isLetterOrNumber() ){  //tant qu'on a des lettres ou des chiffres
                            temp.push_back(s[i]);   //on sauvegarde dans op
                            s.remove(i,1) ;          //on l'enlève de source
                        }
                        if (Controleur::getInstance()->estUnOperateur(temp) )
                            op = temp ;
                        else
                            if(LiteraleManager::getInstance().isVariable(temp)){

                                result.push_back(temp) ;
                                result.push_back(" ");
                            }
                            else
                            return "ERROR" ;
                        if (neg){ //si il y avait - devant :
                            result.push_back("NEG ");
                            neg = false ;
                        }
                    }
                    }
                }
            }
        }
    if (!op.isEmpty()){  //si jamais un op normal est sauvegardé
        result.push_back(op); //on l'ajoute
        op = "" ; //on remet à 0
        result.push_back(" "); //on met un espace
    }

    while (i> 0) {  //si jamais il est pas en tête de chaine
        i-- ;    //on dec i
        result.push_back(s[i]);  //on le push
        result.push_back(" "); //on met un espace
        s.remove(i,1) ;   //on le détruit

    }
    qDebug()<<"Le resultat est : "<<result ;
    return result ;
}

int lowerPrio(Expression* E)  {
    QString s = E->toString() ;
    int i = 5 ; //on commence à 5, si jamais il y a des op en plus, avec plus de prio

    QMap<QChar , int> charSpe ;
    charSpe['+'] = 1 ;
    charSpe['-'] = 1 ;
    charSpe['/'] = 2 ;
    charSpe['*'] = 2 ;
    charSpe['$'] = 3 ;
    charSpe[','] = 0 ;

    while(!s.isEmpty()){
        if(s[0]=='('){    //si bloc (..) , on veut l'enlever
            QString temp = getPara(s) ;         //on prend le bloc ( .... ) ;
            int taille = temp.size() ;
            if (taille == 0) s ="" ;
            s.remove(0 , taille) ;              //on l'enlève de la chaine source
            }
        else{
            if(charSpe.contains(s[0])) if(i > charSpe[s[0]]) i = charSpe[s[0]] ;  //si op spé, et si prio plus gd, on augmente
            s.remove(0,1) ;
        }

        }
    return i ;
    }



