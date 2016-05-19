#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QStack>
#include <math.h>
#include <QRegExp>
#include<string>
#include<iostream>
#include<map>
#include"operateur.h"



class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};

struct Attributs{
public:
    double num ;
    int denom ;
    double ImNum ;
    int ImDenom ;
    Attributs(double n=0 , int d=1, double nIm=0 , int dIm=1):num(n) , denom(d) , ImNum(nIm) , ImDenom (dIm){simplificationRe(); void simplificationIm() ; }
    void simplificationRe() ;
    void simplificationIm() ;
};

class Literale {
protected:
    //int value;
    //Literale(int v):value(v){}
    Literale(){}
    Literale(const Literale& e);
    Literale& operator=(const Literale& e);
    friend class LiteraleManager;
    virtual ~Literale() { }
public:

    virtual QString toString() const = 0 ;
    virtual Attributs getValue()const = 0 ;
    //int getValue() const { return value; }
    Attributs operator+(const Literale&  L) ;
    Attributs operator-(Literale const& L) ;
    Attributs operator*(Literale const& L) ;
    Attributs operator/(Literale const& L) ;

};

class LNum : public Literale {
protected:
    LNum(){}
    LNum(const LNum& e);
    LNum& operator=(const LNum& e);
    friend class LiteraleManager;
    virtual ~LNum() {}
public:
   // virtual int getValue()const = 0 ;
};

class Entier : public LNum {
    int value ;
    Entier(const Entier& e);
    Entier& operator=(const Entier& e);
    Entier(int v):value(v){}
    Entier(Attributs a):value(a.num){}
    virtual ~Entier() {}
    friend class LiteraleManager;
    friend class EntierManager;
public:
    Attributs getValue() const ;
    QString toString() const {return QString::number(value); }


};

class Reel : public LNum {
    double value ;
    Reel(const Reel& e);
    Reel& operator=(const Reel& e);
    Reel(double v):value(v){}
    Reel(Attributs a):value(a.num){}
    virtual ~Reel() {}
    friend class LiteraleManager;
    friend class ReelManager;
public:
    Attributs getValue() const ;
    QString toString() const {return QString::number(value); }
};

class Fraction : public LNum {
    int num ;
    int denom ;
    Fraction(const Fraction& e);
    Fraction& operator=(const Fraction& e);
    Fraction(int n, int d):num(n), denom(d){simplification();}
    Fraction(Attributs a):num(a.num),  denom(a.denom){}
    virtual ~Fraction() {}
    friend class LiteraleManager;
    friend class FractionManager;
public:
    void simplification() ;
    Attributs getValue() const ;
    QString toString() const ;
};

class Complex : public Literale {
    LNum* Re ;
    LNum* Im ;
    Complex(const Complex& e);
    Complex& operator=(const Complex& e);
    Complex(double RN, int RD , double IM , double ID) ;
    Complex(Attributs a, Attributs b) ;
    Complex(Attributs a) ;
    Complex(LNum& r, LNum& i) ;
    virtual ~Complex() ;
    friend class LiteraleManager;
    friend class ComplexManager;
public:
    Attributs getValue() const ;
    QString toString() const ;
};





class LiteraleManager {
protected:
    std::map<int, LiteraleManager*> corres;
    LiteraleManager() ;
    virtual ~LiteraleManager() ;
    LiteraleManager(const LiteraleManager& m);
    LiteraleManager& operator=(const LiteraleManager& m);
    struct Handler{
        LiteraleManager* instance;
        Handler():instance(0){}
        ~Handler(){  delete instance;  }
    };
    static Handler handler;
    void initmap();

public:
    int choix_type(QString s) ;
    int choix_type(Attributs a) ;
    Literale& addLit(QString s) ;
    Literale& addLit(Attributs a) ;
    virtual Literale& getLit(QString s) { }
    virtual Literale& getLit(Attributs a) { }
    void removeLiterale(Literale& e);
    static LiteraleManager& getInstance();
    static void libererInstance();

};





class EntierManager : public LiteraleManager {
    Entier& getLit(QString s)  ;
    Entier& getLit(Attributs a) ;
    EntierManager() {}
    ~EntierManager() {}
    friend class LiteraleManager;
};

class FractionManager : public LiteraleManager {
    FractionManager() {}
    ~FractionManager() {}
    Fraction& getLit(QString s) ;
    Fraction& getLit(Attributs a) ;
    friend class LiteraleManager;

};

class ReelManager : public LiteraleManager {
    Reel& getLit(QString s)  ;
    Reel& getLit(Attributs a) ;
    ReelManager() {}
    ~ReelManager() {}
    friend class LiteraleManager;
};

class ComplexManager : public LiteraleManager {
    Complex& getLit(QString s)  ;
    Complex& getLit(Attributs a) ;
    ComplexManager() {}
    ~ComplexManager() {}
    friend class LiteraleManager;
};



class Item {
    Literale* exp;
public:
    Item():exp(0){}
    void setLiterale(Literale& e) { exp=&e; }
    void raz() { exp=0; }
    Literale& getLiterale() const;
};


class Pile : public QObject {
    Q_OBJECT

    QString message;
    unsigned int nbAffiche;
public:
    QStack<Item>* stack;
    Pile():nbAffiche(4){stack = new QStack<Item> ; }
    ~Pile();
    void push(Literale& e);
    void pop();
    bool estVide() const { return stack->empty() ; }
    unsigned int taille() const { return stack->size() ; }
    void affiche(QTextStream& f) const;
    Literale& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }

signals:
    void modificationEtat();
};


class Controleur ;

class operateur {
public :
    operateur() {}
    virtual ~operateur() {}
    virtual void operator()() = 0;
    virtual bool check(Literale& L) const = 0 ;
};


class adition : public operateur {
public :
    adition() {}
    virtual ~adition() {}
    void operator()() ;
    bool check(Literale& L) const {return true ; }
};

class soustraction : public operateur {
public :
    soustraction() {}
    virtual ~soustraction() {}
    void operator()() ;
    bool check(Literale& L) const {return true ; }
};

class multiplication : public operateur {
public :
    multiplication() {}
    virtual ~multiplication() {}
    void operator()() ;
    bool check(Literale& L) const {return true ; }
};

class division : public operateur {
public :
    division() {}
    virtual ~division() {}
    void operator()() ;
    bool check(Literale& L) const {return true ; }
};

class DIV : public operateur {
public :
    DIV() {}
    virtual ~DIV() {}
    void operator()() ;
    bool check(Literale& L) const;
};

class MOD : public operateur {
public :
    MOD() {}
    virtual ~MOD() {}
    void operator()() ;
    bool check(Literale& L) const;
};

class Ima : public operateur {
public :
    Ima() {}
    virtual ~Ima() {}
    void operator()() ;
    bool check(Literale& L) const;
};






class Controleur {
    LiteraleManager& expMng;
    Pile& expAff;
    std::map <QString , operateur*> fonct ;

    Controleur(LiteraleManager& m, Pile& v):expMng(m), expAff(v){}
    Controleur(const Controleur& c) ;
    ~Controleur() ;
    Controleur& operator = (const Controleur& c) ;

    void initFonct() ;

    struct HandlerC{
        Controleur* instance;
        HandlerC():instance(0){}
        ~HandlerC(){  delete instance;  }
    };
    static HandlerC handlerC;

public:
    void commande(const QString& c);
    Pile& getPile()  {return expAff ; }

    static Controleur* getInstance(LiteraleManager& m, Pile& v);
    static Controleur* getInstance();
    static void libererInstance();

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);



#endif
