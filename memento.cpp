#include "declarations.h"
#include "computer.h"
#include "memento.h"

Memento::Memento( ):MaxSaves(3), courrant( 0){
    QStack<Item> s ;
    QVector<Literale*> u ;
    QVector<Literale*> c ;
    addState(s,u,c);
}

QStack<Item> Memento::GetState(){

    if (save.size() == 0){
        Controleur::getInstance()->getPile().setMessage("ERREUR : UNDO impossible");
        QStack<Item> s ;
        return s ;
    }
    LiteraleManager::getInstance().desactiveVar(save[courrant-1].getCreated()) ;
    LiteraleManager::getInstance().activeVar(save[courrant-1].getUsed()) ;
    return save[courrant++].getStack() ;

}

QStack<Item> Memento::GetStateDown() {
    if (courrant > 1) 
        courrant  = courrant -2 ;

    LiteraleManager::getInstance().activeVar(save[courrant].getCreated()) ;
    LiteraleManager::getInstance().desactiveVar(save[courrant+1].getUsed()) ;
    return save[courrant++].getStack();
}

QStack<Item> Memento::GetState0() {
LiteraleManager::getInstance().activeVar(save[courrant-1].getCreated()) ;
LiteraleManager::getInstance().desactiveVar(save[courrant].getUsed()) ;
return save[courrant-1].getStack() ;
}

void Memento::addState(QStack<Item> st , QVector<Literale*> u ,QVector<Literale*> c ) {

    mem s(st , u , c) ;
    if (courrant == 0){
        if (save.size()==1) courrant = 1 ;
        save.push_front(s);
        return ;
    }
    if (courrant == 1){
        if (save.size() == MaxSaves+1){
            mem old = save.back() ;
            save.pop_back();
            LiteraleManager::getInstance().deleteLiteraleTab(old.getUsed())  ;
        }
        save.push_front(s);
        return ;
    }
    --courrant ;
    while(courrant!= 0){
        mem tooNew = save.front() ;
        save.pop_front();
        LiteraleManager::getInstance().deleteLiteraleTab(tooNew.getCreated())  ;
        --courrant ;
    }
    save.push_front(s);
    ++courrant ;

}

void Memento::setMax ( int n) {
    if (n>0){
    while (n > save.size()+1){
        mem old = save.back() ;
        save.pop_back();
        LiteraleManager::getInstance().deleteLiteraleTab(old.getUsed())  ;
    }
    MaxSaves = n ;
    courrant = 1 ;
    }
    else{
       Controleur::getInstance()->getPile().setMessage("ERREUR : Taille trop petite");
    }
}

void Memento::getID() {
    save[0] ;
    int i ;
    for (i=0 ;i< save.size() ; ++i ){
         //qDebug()<<i<<" : id = "<<save[i].getStack().back().getLiterale().getValue().num ;
        //if (!(save[i].getStack().empty()))
       // qDebug()<<i<<" : id = "<<save[i].getStack().top().getLiterale().getValue().num ;
        //else qDebug()<<i<<" : id = NULL " ;
    }
}




