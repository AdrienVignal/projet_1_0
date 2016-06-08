#include "declarations.h"
#include "computer.h"
#include "program.h"

using namespace std;

Program::Program(Attributs a){
    prog = a.s;
}

Program::~Program(){
    delete this;
}

Program::Program(const Program &e) {
    prog=e.getValue().s;
}

Program& Program::operator=(const Program& e){

}

QString Program::toString() const {
    QString source = prog;
    QTextStream s (&source) ;
    QString c ;
    QString result  = "" ;
    s>> c ;
    while (c != "") {
        result.push_back(c);
        result.push_back(' ');
         s>> c ;
    }
    return result ;
}


void Program::eval() const{
    QString source = prog;
    source.remove(0,1) ; //on enlève[
    source.remove(source.size()-1 , 1) ;// on enlève ]
    QTextStream s (&source) ;
    QString c ;
    s>> c ;

    while (c != "") {
        Controleur::getInstance()->commande(c) ;
        s>>c ;
    }
}


