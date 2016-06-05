#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "declarations.h"


class Expression : public Literale{
private:
    QString exp;
    Expression(Attributs a):exp(a.s){}
    Expression(const Program& e);
    Expression& operator=(const Program& e);
    friend class LiteraleManager;
    friend class ExpressionManager;
    ~Expression() {}
public:
    void eval() const;
    Attributs getValue() const{return Attributs(0,1,0,1,exp) ;}
    QString toString() const {return exp;}

};

#endif // EXPRESSION_H
