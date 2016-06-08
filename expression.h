<<<<<<< HEAD
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "declarations.h"

QString convertToPolish(QString s) ;

class Expression : public Literale{
private:
    QString exp;
    Expression(Attributs a):exp(a.s){convertToPolish(exp) ; }
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



#endif // EXPRESSION_H
=======
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
    QString toString() const ;

};

QString convertToPolish(QString s) ;


#endif // EXPRESSION_H
>>>>>>> c9539195318c65cb60efa2ffe8cbf55b9dd7361d
