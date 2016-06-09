#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "declarations.h"

int lowerPrio(Expression* E);

class Expression : public Literale{
private:
    QString exp;
    Expression(Attributs a):exp(a.s){exp.remove(" ") ; }
    Expression(const Program& e);
    Expression& operator=(const Program& e);
    friend class LiteraleManager;
    friend class ExpressionManager;
    ~Expression() {}
public:
    void eval() const;
    Attributs getValue() const{return Attributs(0,1,0,1,exp) ;}
    QString toString() const ;

};

QString convertToPolish(QString s) ;
 ;


#endif // EXPRESSION_H

