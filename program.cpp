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


void Program::eval() const{
    QString source = prog;
    QTextStream s (&source) ;
    QString c ;
    s>> c ;
    QRegExp rp("[.*]\\s+\\w+\\s+STO");
    /*if(c.contains(rp)){

    }*/
    while (c != "") {
        if(c[0].toLatin1()=='['){
            c.remove(0,1);
        }
        else if(c[c.length()-1].toLatin1()==']'){
            c.remove(c.length()-1,1);
        }
        Controleur::getInstance()->commande(c) ;
        s>>c ;
    }
}


