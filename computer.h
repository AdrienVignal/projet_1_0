#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QStack>
using namespace std;

class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};

class Literale {
    int value;
    Literale(int v):value(v){}
    Literale(const Literale& e);
    Literale& operator=(const Literale& e);
    friend class LiteraleManager;
public:
    QString toString() const;
    int getValue() const { return value; }
};



class LiteraleManager {
    Literale** exps;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    LiteraleManager():exps(0),nb(0),nbMax(0){}
    ~LiteraleManager();
    LiteraleManager(const LiteraleManager& m);
    LiteraleManager& operator=(const LiteraleManager& m);

    struct Handler{
        LiteraleManager* instance;
        Handler():instance(0){}
        // destructeur appel? ? la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    Literale& addLiterale(int v);
    void removeLiterale(Literale& e);
    static LiteraleManager& getInstance();
    static void libererInstance();
    class Iterator {
        friend class LiteraleManager;
        Literale** currentExp;
        unsigned int nbRemain;
        Iterator(Literale** u, unsigned nb):currentExp(u),nbRemain(nb){}
    public:
        Iterator():currentExp(0),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw ComputerException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }
        Literale& current() const {
            if (isDone())
                throw ComputerException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
    Iterator getIterator() {
        return Iterator(exps,nb);
    }
    class iterator {
        Literale** current;
        iterator(Literale** u):current(u){}
        friend class LiteraleManager;
    public:
        iterator():current(0){}
        Literale& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(exps); }
    iterator end() { return iterator(exps+nb); }

    class const_iterator {
        Literale** current;
        const_iterator(Literale** u):current(u){}
        friend class LiteraleManager;
    public:
        const_iterator():current(0){}
        Literale& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };
    const_iterator begin() const { return const_iterator(exps); }
    const_iterator end() const { return const_iterator(exps+nb); }
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

/*
class Pile : public QObject {
    Q_OBJECT
    QStack<Item> stack;
    Item* items;
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    Pile():items(0),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();
    void push(Literale& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Literale& top() const;
    void setNbItemsToAffiche(unsigned int n) { nb=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }
    class iterator {
        Item* current;
        iterator(Item* u):current(u){}
        friend class Pile;
    public:
        iterator():current(0){}
        Literale& operator*() const { return current->getLiterale(); }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(items+nb-1); }
    iterator end() { return iterator(items-1); }

    class const_iterator {
        Item* current;
        const_iterator(Item* u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(0){}
        const Literale& operator*() const { return current->getLiterale(); }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(items+nb-1); }
    const_iterator end() const { return const_iterator(items-1); }

signals:
    void modificationEtat();
};
*/


class Controleur {
    LiteraleManager& expMng;
    Pile& expAff;
public:
    Controleur(LiteraleManager& m, Pile& v):expMng(m), expAff(v){}
    void commande(const QString& c);

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);


#endif
