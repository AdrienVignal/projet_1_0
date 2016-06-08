#ifndef PROGRAM_H
#define PROGRAM_H
#include "declarations.h"


class Program : public Literale{
private:
    QString prog;
    Program(Attributs a);
    Program(const Program& e);
    Program& operator=(const Program& e);
    friend class LiteraleManager;
    friend class ProgramManager;
    ~Program();
public:
    void eval() const;
    Attributs getValue() const{return Attributs(0,1,0,1,prog) ;}
    QString toString() const ;

};

#endif // PROGRAM_H
