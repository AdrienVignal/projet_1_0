#include "computer.h"
#include <algorithm>

LiteraleManager::Handler LiteraleManager::handler=LiteraleManager::Handler();


LiteraleManager& LiteraleManager::getInstance(){
    if (handler.instance==0) {

        handler.instance=new LiteraleManager;
        handler.instance->initmap();
    }
	return *handler.instance;
}

void LiteraleManager::libererInstance(){

    handler.instance=0;
}

/*
QString  Entier::toString() const {
    return QString::number(value);
}
*/

Attributs Literale::operator+(const Literale&  L) {
    Attributs A1 = this->getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 = Attributs(A1.num * A2.denom + A1.denom * A2.num , A1.denom * A2.denom  ,
                             A1.ImNum * A2.ImDenom + A1.ImDenom * A2.ImNum , A1.ImDenom * A2.ImDenom) ;
    if (floor(A3.num)!= A3.num)
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;

}

Attributs Literale::operator-(Literale const& L) {
    Attributs A1 = getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 = Attributs(A1.num * A2.denom - A1.denom * A2.num , A1.denom * A2.denom   ,
                             A1.ImNum * A2.ImDenom - A1.ImDenom * A2.ImNum , A1.ImDenom * A2.ImDenom) ;
    if (floor(A3.num)!= A3.num)
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;

}

Attributs Literale::operator*(Literale const& L) {
    Attributs A1 = getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 ;
    if ((A1.ImNum == 0)&& (A2.ImNum == 0))
        A3 = Attributs(A1.num  * A2.num , A1.denom * A2.denom ) ;
    else
        A3 = Attributs ( A1.num * A2.num * A1.ImDenom * A2.ImDenom -  A1.ImNum * A2.ImNum * A1.denom * A2.denom  ,
                         A1.ImDenom * A2.ImDenom * A1.denom * A2.denom ,
                         A1.num * A2.ImNum * A1.ImDenom * A2.denom +  A1.ImNum * A2.num * A1.denom * A2.ImDenom  ,
                         A1.ImDenom * A2.denom * A1.denom * A2.ImDenom ) ;

    if (floor(A3.num)!= A3.num)
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;
}



Attributs Literale::operator/(Literale const& L) {
    Attributs A1 = getValue() ;
    Attributs A2 = L.getValue() ;
    Attributs A3 ;
    if ((A1.ImNum == 0)&& (A2.ImNum == 0)){
        if (floor(A2.num)!= A2.num)
            A3 = Attributs((A1.num * (double) A2.denom )/((double) A1.denom * A2.num),1 ) ;
        else A3 = Attributs(A1.num * (double) A2.denom ,(double) A1.denom * A2.num ) ;
    }
    else {
        //if ( (floor(((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) ) == (((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) )) &&
             //(floor(((double) A2.ImNum / A2.ImDenom) * ((double) A2.ImNum / A2.ImDenom) ) == (((double) A2.ImNum / A2.ImDenom) * ((double) A2.ImNum / A2.ImDenom) )))
        if ((floor (A2.num * A2.num) == (A2.num * A2.num)) &&(floor (A2.ImNum * A2.ImNum) == (A2.ImNum * A2.ImNum)))
            /*
            A3 = Attributs ( ((double)(A1.num * A2.num) / (A1.denom * A2.denom))   +  ((double) (A1.ImNum * A2.ImNum) / (A1.ImDenom * A2.ImDenom)) ,
                             ((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) ,
                             ((double) (A1.ImNum * A2.num) /( A1.ImDenom * A2.denom)) -( (double)  (A1.num * A2.ImNum)  / (A1.denom * A2.ImDenom)) ,
                             ((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) ) ;
                             */
            A3 = Attributs ( (((double)(A1.num * A2.num) / (A1.denom * A2.denom))   +  ((double) (A1.ImNum * A2.ImNum) / (A1.ImDenom * A2.ImDenom))) * (A2.denom * A2.denom * A2.ImDenom * A2.ImDenom) ,
                             A2.num * A2.num * A2.ImDenom *A2.ImDenom + A2.denom * A2.denom * A2.ImNum *A2.ImNum ,
                             (((double) (A1.ImNum * A2.num) /( A1.ImDenom * A2.denom)) -( (double)  (A1.num * A2.ImNum)  / (A1.denom * A2.ImDenom))) * (A2.denom * A2.denom * A2.ImDenom * A2.ImDenom),
                             A2.num * A2.num * A2.ImDenom *A2.ImDenom + A2.denom * A2.denom * A2.ImNum *A2.ImNum  ) ;
        else
            A3 = Attributs ( ((double)(A1.num * A2.num) / (A1.denom * A2.denom))   +  ((double) (A1.ImNum * A2.ImNum) / (A1.ImDenom * A2.ImDenom)) ,
                             ((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) + ((double) A2.ImNum / A2.ImDenom) * ((double) A2.ImNum / A2.ImDenom) ,
                             ((double) (A1.ImNum * A2.num) /( A1.ImDenom * A2.denom)) -( (double)  (A1.num * A2.ImNum)  / (A1.denom * A2.ImDenom)) ,
                             ((double) A2.num / A2.denom) * ((double) A2.num / A2.denom) + ((double) A2.ImNum / A2.ImDenom) * ((double) A2.ImNum / A2.ImDenom) ) ;
    }

    if (floor(A3.num)!= A3.num)
    A3 = Attributs( (double) A3.num/A3.denom ,1, A3.ImNum , A3.ImDenom)   ;
    if (floor(A3.ImNum)!= A3.ImNum)
    A3 = Attributs(  A3.num , A3.denom ,(double) A3.ImNum/A3.ImDenom ,1)   ;
    return A3 ;

}

Attributs Entier::getValue() const {
    Attributs A = Attributs( value ) ;
    return A ;
}

Attributs Reel::getValue() const {
    Attributs A = Attributs( value ) ;
    return A ;
}

void Fraction::simplification(){
    if (num==0) { denom=1; return; }
    if (denom==0) return;
    int a=num, b=denom;
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    num/=a; denom/=a;
    if (denom<0) { denom=-denom; num=-num; }
}

void Attributs::simplificationRe(){
    if (num==0) { denom=1; return; }
    if (denom==0) return;
    if ((floor(num)!=num)|| (floor(denom)!= denom)) return ;
    int a=num, b=denom;
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    num/=a; denom/=a;
    if (denom<0) { denom=-denom; num=-num; }
}

void Attributs::simplificationIm(){
    if (ImNum==0) { ImDenom=1; return; }
    if (ImDenom==0) return;
    if ((floor(ImNum)!=ImNum)|| (floor(ImDenom)!= ImDenom)) return ;
    int a=ImNum, b=ImDenom;
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    ImNum/=a; ImDenom/=a;
    if (ImDenom<0) { ImDenom=-ImDenom; ImNum=-ImNum; }
}


Attributs Fraction::getValue() const {
    Attributs A = Attributs( num, denom ) ;
    return A ;
}

QString Fraction::toString() const {
    QString s = QString::number(num);
    s.push_back('/');
    s.append(QString::number(denom)) ;
    return s ;
}

Complex::Complex(double RN, int RD , double IM , double ID){
    Re  =(LNum*)  &(LiteraleManager::getInstance().addLit(Attributs(RN , RD) )) ;
    Im =(LNum*) &( LiteraleManager::getInstance().addLit(Attributs(IM , ID) )) ;
}

Complex::Complex(Attributs a, Attributs b) {

    Re = (LNum*) &(LiteraleManager::getInstance().addLit(a) ) ;
    Im = (LNum*) &(LiteraleManager::getInstance().addLit(b));
}

Complex::Complex(Attributs a) {
    Re = (LNum*) &(LiteraleManager::getInstance().addLit( Attributs(a.num , a.denom) )) ;
    Im = (LNum*) &(LiteraleManager::getInstance().addLit(Attributs (a.ImNum , a.ImDenom)));
}

Complex::Complex(LNum& r, LNum& i): Re(&r) , Im(&i)  {}

Complex::~Complex()  {
    LiteraleManager::getInstance().removeLiterale(*Re);
    LiteraleManager::getInstance().removeLiterale(*Im);
}

Attributs Complex::getValue() const {
    return Attributs(Re->getValue().num , Re->getValue().denom , Im->getValue().num , Im->getValue().denom) ;
}

QString Complex::toString() const {
    QString s = Re->toString() ;
    s.push_back('$');
    s.append(Im->toString()) ;
    return s ;
}

LiteraleManager::LiteraleManager() {}
LiteraleManager::~LiteraleManager() {
    for (int i = 1 ; i< 5 ; ++i) delete corres[i] ;
}


Literale& Item::getLiterale() const {
        if (exp==0) throw ComputerException("Item : tentative d'acces a une literale inexistante");
        return *exp;
}

void LiteraleManager::removeLiterale(Literale& e){
    delete(&e) ;
}

int LiteraleManager::choix_type(QString s) {
    QRegExp rInt("^\\d+$");
    if(s.contains(rInt)) return 1 ;
    QRegExp rFrac("^(\\d+)/(\\d+)$");
    if(s.contains(rFrac)) return 3 ;
    QRegExp rReel("^(\\d+)\\.(\\d+)$");
    if(s.contains(rReel)) return 2 ;
    QRegExp rIm("^\\d+(.\\d+)?\\$\\d+(.\\d+)?$");
    if(s.contains(rIm)) return 4 ;

}

int LiteraleManager::choix_type(Attributs a) {
    if (a.ImNum != 0) return 4 ;
    if (a.denom == 1 && floor(a.num)==a.num) return 1 ;
    if (a.denom == 1 && floor(a.num)!=a.num) return 2 ;
    if (a.denom != 1 && floor(a.num)==a.num) return 3 ;
    if (a.denom != 1 && floor(a.num)!=a.num) throw ComputerException("Fraction : fraction mal construite");
}

void LiteraleManager::initmap() {
    corres[1] = new EntierManager;
    corres[2] = new ReelManager;
    corres[3] = new FractionManager;
    corres[4] = new ComplexManager;
}




Literale& LiteraleManager::addLit(QString s) {
    int i = choix_type(s) ;
    return corres[i]->getLit(s);
}

Literale& LiteraleManager::addLit(Attributs a) {
    int i = choix_type(a ) ;
    return corres[i]->getLit(a);
}

Fraction& FractionManager::getLit(QString s) {
    QString num = "" ;
    QString denom = "" ;
    int i = 0 ;
    while (s[i].toLatin1()&& (s[i].toLatin1()!= '/') )
        num.push_back(s[i++]);

    if (s[i].toLatin1()) ++i ;

    while (s[i].toLatin1() )
        denom.push_back(s[i++]);


    if(num.isEmpty()) num = "0" ;
    if(denom.isEmpty()) denom = "1" ;
    return *(new Fraction(num.toInt() , denom.toInt())) ;
}
Fraction& FractionManager::getLit(Attributs a) {
    return *(new Fraction(a.num , a.denom)) ;
}


Entier& EntierManager::getLit(QString s) {
    return *(new Entier(s.toInt())) ;
}
Entier& EntierManager::getLit(Attributs a) {
    return *(new Entier(a.num)) ;
}


Reel& ReelManager::getLit(QString s) {
    return *(new Reel(s.toDouble())) ;
}
Reel& ReelManager::getLit(Attributs a) {
    return *(new Reel(a.num)) ;
}

Complex& ComplexManager::getLit(QString s)  {
    QString ReString = "" ;
    QString ImString = "" ;
    int i = 0 ;
    while (s[i].toLatin1()&& (s[i].toLatin1()!= '$') )
        ReString.push_back(s[i++]);

    if (s[i].toLatin1()) ++i ;

    while (s[i].toLatin1() )
        ImString.push_back(s[i++]);


    if(ReString.isEmpty()) ReString = "0/1" ;
    if(ImString.isEmpty()) ImString = "0/1" ;
    return *(new Complex((LNum&) LiteraleManager::getInstance().addLit(ReString) ,(LNum&) LiteraleManager::getInstance().addLit(ImString) )) ;
}
Complex& ComplexManager::getLit(Attributs a) {
    return *(new Complex(a )) ;
}


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
    for( int i=nbAffiche; i>0; i--) {
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
   QRegExp ri("^(\\d+)$");
   if(s.contains(ri)) return true ;
   QRegExp rr("^(\\d+)\\.(\\d+)$");
   if(s.contains(rr)) return true ;
   QRegExp rf("^(\\d+)/(\\d+)$");
   if(s.contains(rf)) return true ;
   QRegExp rim("^\\d+(.\\d+)?\\$\\d+(.\\d+)?$");
   if(s.contains(rim)) return true ;
   return false;
}


void Controleur::commande(const QString& c){
    if (estUnNombre(c)){
        expAff.push(expMng.addLit(c));
	}else{
		
		if (estUnOperateur(c)){
			if (expAff.taille()>=2) {
                Literale& v2=expAff.top();
				expAff.pop();
                Literale& v1=expAff.top();
				expAff.pop();
                Attributs res;

                if (c=="+") res=v1+v2;
				if (c=="-") res=v1-v2;
				if (c=="*") res=v1*v2;
                if (c=="/") {
                    if (v2.getValue().num != 0) res=v1/v2;
                    else {
                        expAff.setMessage("Erreur : division par zéro");
                        res=v1.getValue();
                    }
                }
                expMng.removeLiterale(v1);
                expMng.removeLiterale(v2);
                Literale& e=expMng.addLit(res);
				expAff.push(e);
			}else{
				expAff.setMessage("Erreur : pas assez d'arguments");
			}
		}else expAff.setMessage("Erreur : commande inconnue");
	}
}

