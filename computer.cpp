#include "computer.h"
#include <algorithm>

LiteraleManager::Handler LiteraleManager::handler=LiteraleManager::Handler();


LiteraleManager& LiteraleManager::getInstance(){
    if (handler.instance==0) handler.instance=new LiteraleManager;
	return *handler.instance;
}

void LiteraleManager::libererInstance(){
	delete handler.instance;
    handler.instance=0;
}


QString  Literale::toString() const {
    return QString::number(value);
}

void LiteraleManager::agrandissementCapacite() {
    Literale** newtab=new Literale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Literale**  old=exps;
	exps=newtab;
	nbMax=(nbMax+1)*2;
	delete old;
}

Literale& LiteraleManager::addLiterale(int v){
	if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Literale(v);
	return *exps[nb-1];
}

void LiteraleManager::removeLiterale(Literale& e){
	unsigned int i=0;
	while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Literale inexistante");
	delete exps[i];
	i++;
	while(i<nb) { exps[i-1]=exps[i]; i++; }
	nb--;
}

LiteraleManager::~LiteraleManager(){
	for(unsigned int i=0; i<nb; i++) delete exps[i];
	delete[] exps;
}

Literale& Item::getLiterale() const {
        if (exp==0) throw ComputerException("Item : tentative d'acces a une literale inexistante");
        return *exp;
}

/*
void Pile::agrandissementCapacite() {
    Item* newtab=new Item[(nbMax+1)*2];
	for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
    Item*  old=items;
	items=newtab;
	nbMax=(nbMax+1)*2;
	delete[] old;
}



void Pile::push(Literale& e){
	if (nb==nbMax) agrandissementCapacite();
    items[nb].setLiterale(e);
	nb++;
    modificationEtat();
}

void Pile::pop(){
	nb--;
	items[nb].raz();
    modificationEtat();
}
*/

void Pile::push(Literale& e){
    Item temp ;
    temp.setLiterale(e) ;
    stack->push(temp) ;
    modificationEtat();
}

void Pile::pop(){
    stack->pop() ;
    modificationEtat();
}


void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    Item* data = stack->data() ;
    for(unsigned int i=nbAffiche; i>0; i--) {
        if (i<=stack->size()) f<<i<<": "<<data[stack->size()-i].getLiterale().toString()<<"\n";
        else f<<i<<": \n";
	}
    f<<"---------------------------------------------\n";
}


Pile::~Pile(){
    delete[] stack ;
}


Literale& Pile::top() const {
    if (stack->size() ==0) throw ComputerException("aucune literale sur la pile");
    Item temp = stack->top() ;
    return temp.getLiterale();
}
	


bool estUnOperateur(const QString s){
	if (s=="+") return true;
	if (s=="-") return true;
	if (s=="*") return true;
	if (s=="/") return true;
	return false;
}

bool estUnNombre(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}


void Controleur::commande(const QString& c){
    if (estUnNombre(c)){
        expAff.push(expMng.addLiterale(c.toInt()));
	}else{
		
		if (estUnOperateur(c)){
			if (expAff.taille()>=2) {
				int v2=expAff.top().getValue();
                expMng.removeLiterale(expAff.top());
				expAff.pop();
				int v1=expAff.top().getValue();
                expMng.removeLiterale(expAff.top());
				expAff.pop();
				int res;
				if (c=="+") res=v1+v2;
				if (c=="-") res=v1-v2;
				if (c=="*") res=v1*v2;
                if (c=="/") {
                    if (v2!=0) res=v1/v2;
                    else {
                        expAff.setMessage("Erreur : division par zéro");
                        res=v1;
                    }
                }
                Literale& e=expMng.addLiterale(res);
				expAff.push(e);
			}else{
				expAff.setMessage("Erreur : pas assez d'arguments");
			}
		}else expAff.setMessage("Erreur : commande inconnue");
	}
}

