#ifndef ATTRIBUTS_H
#define ATTRIBUTS_H
#include "declarations.h"

//création d'une structure attributs afin de manipuller plus simplement les litérales numériques
//permet aussi de créer plus facilement les litérales numériques, en faisant les controles necessaires

struct Attributs{
public:
    double num ;
    double denom ;
    double ImNum ;
    double ImDenom ;
    QString s;
    Attributs(double n=0 , double d=1, double nIm=0 , double dIm=1, QString m_s= "") ;
    Attributs(QString m_s):num(0) , denom(1) , ImNum(0) , ImDenom(1) , s(m_s) {}
    void simplificationRe() ;
    void simplificationIm() ;
    bool operator==(Attributs a) ;
    bool operator<(Attributs a) ;

};

#endif // ATTRIBUTS_H
