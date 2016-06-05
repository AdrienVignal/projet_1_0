#include "declarations.h"
#include "literale.h"
#include "computer.h"


Attributs Literale::operator+(const Literale&  L) {

    //calcul d'une adition
    // le schéma le plus compliqué est ((a/b) + (c/d) i) + ((x/y) + (w/z)i)
    //on va donc traiter ce cas là, et les autres en découleront

    Attributs A1 = this->getValue() ;
    Attributs A2 = L.getValue() ;

    Attributs A3 = Attributs(A1.num * A2.denom + A1.denom * A2.num , A1.denom * A2.denom  ,
                            A1.ImNum * A2.ImDenom + A1.ImDenom * A2.ImNum , A1.ImDenom * A2.ImDenom) ;

    if (floor(A3.num)!= A3.num) // on vérifie qu'il n'y ai pas de fraction avec un num décimal
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;  //si c'est le cas, on transforme en réel
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;

}

Attributs Literale::operator-(Literale const& L) {

    //calcul d'une soutraction
    // le schéma le plus compliqué est ((a/b) + (c/d) i) - ((x/y) + (w/z)i)
    //on va donc traiter ce cas là, et les autres en découleront

    Attributs A1 = getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 = Attributs(A1.num * A2.denom - A1.denom * A2.num , A1.denom * A2.denom   ,
                             A1.ImNum * A2.ImDenom - A1.ImDenom * A2.ImNum , A1.ImDenom * A2.ImDenom) ;
    if (floor(A3.num)!= A3.num)// on vérifie qu'il n'y ai pas de fraction avec un num décimal
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;//si c'est le cas, on transforme en réel
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;

}

Attributs Literale::operator*(Literale const& L) {


    //calcul d'une soutraction
    // le schéma le plus compliqué est ((a/b) + (c/d) i) * ((x/y) + (w/z)i)
    //on va donc traiter ce cas là, et les autres en découleront


    Attributs A1 = getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 ;
    if ((A1.ImNum == 0)&& (A2.ImNum == 0))
        A3 = Attributs(A1.num  * A2.num , A1.denom * A2.denom ) ;
    else
        A3 = Attributs ( A1.num * A2.num * A1.ImDenom * A2.ImDenom -  A1.ImNum * A2.ImNum * A1.denom * A2.denom  ,
                         A1.ImDenom * A2.ImDenom * A1.denom * A2.denom ,
                         A1.num * A2.ImNum * A1.ImDenom * A2.denom +  A1.ImNum * A2.num * A1.denom * A2.ImDenom  ,
                         A1.ImDenom * A2.denom * A1.denom * A2.ImDenom ) ;

    if (floor(A3.num)!= A3.num) //on vérifie qu'il n'y ai pas de fraction avec un num décimal
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ; //si c'est le cas, on transforme en réel
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;
}



Attributs Literale::operator/(Literale const& L) {

    //calcul d'un division, l'opérateur le plus complexe
    //on divise en 3 cas :
    //si on a affaire à 2 nombres réels
    //si le résultat de la division donne des fractions
    //si on a une division avec des nombres réels


    Attributs A1 = getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 ;

    //cas 1
    if ((A1.ImNum == 0)&& (A2.ImNum == 0)){
        if (floor(A2.num)!= A2.num)
            A3 = Attributs((A1.num * (double) A2.denom )/((double) A1.denom * A2.num),1 ) ;
        else A3 = Attributs(A1.num * (double) A2.denom ,(double) A1.denom * A2.num ) ;
    }
    else {

        //cas 2
        if ((floor (A2.num * A2.num) == (A2.num * A2.num)) &&(floor (A2.ImNum * A2.ImNum) == (A2.ImNum * A2.ImNum)))
            A3 = Attributs ( (((double)(A1.num * A2.num) / (A1.denom * A2.denom))   +  ((double) (A1.ImNum * A2.ImNum) / (A1.ImDenom * A2.ImDenom))) * (A2.denom * A2.denom * A2.ImDenom * A2.ImDenom) ,
                             A2.num * A2.num * A2.ImDenom *A2.ImDenom + A2.denom * A2.denom * A2.ImNum *A2.ImNum ,
                             (((double) (A1.ImNum * A2.num) /( A1.ImDenom * A2.denom)) -( (double)  (A1.num * A2.ImNum)  / (A1.denom * A2.ImDenom))) * (A2.denom * A2.denom * A2.ImDenom * A2.ImDenom),
                             A2.num * A2.num * A2.ImDenom *A2.ImDenom + A2.denom * A2.denom * A2.ImNum *A2.ImNum  ) ;
        else

            //cas 3
            A3 = Attributs ( (double) (((double)(A1.num * A2.num) / (A1.denom * A2.denom))   +  ((double) (A1.ImNum * A2.ImNum) / (A1.ImDenom * A2.ImDenom))) /
                             (double) (((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) + ((double) A2.ImNum / A2.ImDenom) * ((double) A2.ImNum / A2.ImDenom)) , 1 ,
                             (double) (((double) (A1.ImNum * A2.num) /( A1.ImDenom * A2.denom)) -( (double)  (A1.num * A2.ImNum)  / (A1.denom * A2.ImDenom))) /
                             (double) (((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) + ((double) A2.ImNum / A2.ImDenom) * ((double) A2.ImNum / A2.ImDenom)) , 1 );
    }
    if (floor(A3.num)!= A3.num) //on vérifie qu'il n'y ai pas de fraction avec un num décimal
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;

}
