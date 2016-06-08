#include "declarations.h"
#include "attributs.h"
#include "computer.h"

Attributs::Attributs(double n, double d, double nIm , double dIm, QString m_s) :num(n) , denom(d) , ImNum(nIm) , ImDenom (dIm), s(m_s){
    //simplification des membres
    simplificationRe();
    simplificationIm();
}


void Attributs::simplificationRe(){

    //si tests vrais, rien à faire
    if (num==0) { denom=1; return; }
    if (denom==0) return;
    if(denom == 1) return ;

    if (num > 2147483647 || -1*num> 2147483647) {// si le nombre est plus grand que la plage de valeur d'un int
        num = num/denom ;
        denom = 1 ;
        return ;
    }
    if (denom > 2147483647 || -1*denom> 2147483647) {// si le nombre est plus grand que la plage de valeur d'un int
        num = num/ (double) denom ;
        denom = 1 ;
        return ;
    }
    if ((floor(num)!=num)|| (floor(denom)!= denom)) return ; // si réel, rien à faire
    int a=num, b=denom;
    if (a<0) a=-a; if (b<0) b=-b; // début de l'algo  de calcul du PGCD
    while(a!=b){
        if (a>b) a=a-b;
        else b=b-a;
    if (a==1 || b== 1) return ;
    }
    num/=a; denom/=a;
    if (denom<0) { denom=-denom; num=-num; }
}

void Attributs::simplificationIm(){
    if (ImNum==0) { ImDenom=1; return; }
    if (ImDenom==0) return;
    if (ImDenom == 1) return ;
    if (ImNum > 2147483647 || -1*ImNum > 2147483647 ) {
        ImNum = ImNum/ImDenom ;
        denom = 1 ;
        return ;
    }
    if (ImDenom > 2147483647 || -1*ImDenom > 2147483647 ) {
        ImNum = ImNum/ImDenom ;
        denom = 1 ;
        return ;
    }
    if ((floor(ImNum)!=ImNum)|| (floor(ImDenom)!= ImDenom)) return ;
    int a=ImNum, b=ImDenom;
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){
        if (a>b) a=a-b;
        else b=b-a;
    if (a==1 || b== 1) return ;
    }
    ImNum/=a; ImDenom/=a;
    if (ImDenom<0) { ImDenom=-ImDenom; ImNum=-ImNum; }
}

bool Attributs::operator==(Attributs a) {
    if ((num/(double) denom == a.num/(double) a.denom)&&(ImNum / (double) ImDenom ==a.ImNum / (double) a.ImDenom)) return true ;
    return false ;
}

bool Attributs::operator<(Attributs a) {
    return (num*a.denom < a.num * denom) ;
}
