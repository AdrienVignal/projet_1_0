#include "declarations.h"
#include "computer.h"
#include "expression.h"




QString Expression::toString() const {
    QString source = exp;
    QTextStream s (&source) ;
    QString c ;
    QString result  = "" ;
    s>> c ;
    while (c != "") {
        result.push_back(c);
        result.push_back(' ');
         s>> c ;
    }
    return result ;
}


void Expression::eval() const{
}

QString convertToPolish(QString s) {
    s.remove(" ") ;  //on enlève les espaces et les '
    s.remove("'") ;
    QSet<QChar> charSpe ;  //création des 5 opérateurs spéciaux
    charSpe.insert('+') ;
    charSpe.insert('-') ;
    charSpe.insert('*') ;
    charSpe.insert('/') ;
    charSpe.insert('$') ;
    charSpe.insert(',') ; //pas un opérateur spécial, mais ce comporte pareil
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
            if (  s[i].isDigit()){ //si on a un nombre
                while((i<s.size()) && (!charSpe.contains(s[i]))){  //tant qu'on voit pas d'op spé, et qu'il y a des trucs
                    if (!s[i].isDigit()) return "ERROR" ; //si pas nb ou op spé, erreur
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
                       i-- ;    //on dec i
                       result.push_back(s[i]);  //on le push
                       result.push_back(" "); //on met un espace
                       s.remove(i,1) ;   //on le détruit
                   }
                   if (s[i]==',') s.remove(i,1) ;  //enlève , qui sert juste de séparateur
                   else i++ ;   //on "sauvegarde" l'op spé
                    }

                else{
                    if (s[i].isLetter() ){ //si on a une lettre, alors 3 cas : opérateur (opérande) ,  variable (atome) , ou racourcis d'opérateur (atome)
                        QString temp ;
                        while((i<s.size()) && s[i].isLetterOrNumber() ){  //tant qu'on a des lettres ou des chiffres
                            temp.push_back(s[i]);   //on sauvegarde dans op
                            s.remove(i,1) ;          //on l'enlève de source
                        }

                        if (Controleur::getInstance()->estUnOperateur(temp) )
                            op = temp ;
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

    if (i> 0) {  //si jamais il est pas en tête de chaine
        i-- ;    //on dec i
        result.push_back(s[i]);  //on le push
        result.push_back(" "); //on met un espace
        s.remove(i,1) ;   //on le détruit
    }
    qDebug()<<"Le resultat est : "<<result ;
    return result ;
}






