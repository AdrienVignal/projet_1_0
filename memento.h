#ifndef MEMENTO_H
#define MEMENTO_H
#include "declarations.h"
#include "literalemanager_mere.h"

struct mem{
private:
    QStack<Item> stack ;
    QVector<Literale*> used ;
    QVector<Literale*> created ;
    mem(QStack<Item> s , QVector<Literale*> u ,QVector<Literale*> c  ): stack(s),used(u) , created(c){}
    mem& operator=(const mem& e) ;
    friend class Memento ;
public:
    QStack<Item> getStack() {return stack ; }
    QVector<Literale*>& getUsed() {return used ; }
    QVector<Literale*>& getCreated() {return created ; }
};


class Memento
{

    int MaxSaves ;
    int courrant ;
    std::deque<mem> save;
    //QVector<QStack<Item> > save ;
    Memento( ) ;
    ~Memento() {}
    Memento(const Memento& e) ;
    Memento& operator=(const Memento& e) ;
    friend class Controleur ;

public:
    int getSize(){return save.size() ; }
    QStack<Item> GetState();
    QStack<Item> GetStateDown() ;
    void addState(QStack<Item> st , QVector<Literale*> u ,QVector<Literale*> c ) ;
    void setMax ( int n) ;
    int getCourrant() {return courrant ; }
    int nbSaved() {return save.size() ;  }
    void getID() ;
};


class Caretaker{

};

#endif // MEMENTO_H
