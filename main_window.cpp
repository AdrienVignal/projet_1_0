#include "main_window.h"
#include "declarations.h"
#include "prog_window.h"
#include <Qt>

MainWindow::MainWindow()
{
    //CREATION DU MENU
    setWindowTitle("CalcUTC");
    this->size_min();
    QMenu *menuOption = menuBar()->addMenu("&Option");
    QAction *actionQuitter = new QAction("&Quitter", this); //AJOUT DE QUITTER
    menuOption->addAction(actionQuitter);
    QAction *actionProgEdit = new QAction("Nouveau programme", this); // Ajout d'une action créer nouveau programme qui ouvre un QEDITTEXT
    menuOption->addAction(actionProgEdit);

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    QAction *actionClavier = new QAction("&Clavier", this);   //OPTION D'AFFICHAGE DU CLAVIER ET DES FONCTIONS SCIENTIFIQUES
    menuAffichage->addAction(actionClavier);
    QAction *actionScientifique = new QAction("&Mode scientifique", this);
    menuAffichage->addAction(actionScientifique);
    QAction *actionProg = new QAction("&Gestion Programme",this);
    menuAffichage->addAction(actionProg);


    QAction *actionRedo = new QAction("&Redo", this);  // AJOUT DU "Redo"
    menuOption->addAction(actionRedo);
    actionRedo->setIcon(QIcon("C:\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\projet_1_0-master\\projet_1_0\\images\\arrow_redo.png"));
    actionRedo->setShortcut(QKeySequence(tr("Ctrl+y")));

    QAction *actionUndo = new QAction("&Undo", this);  // AJOUT DU "Undo"
    menuOption->addAction(actionUndo);
    actionUndo->setIcon(QIcon("C:\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\projet_1_0-master\\projet_1_0\\images\\arrow_undo.png"));
    actionUndo->setShortcut(QKeySequence(tr("Ctrl+z")));

    QMenu *menuAide = menuBar()->addMenu("&Aide");
    QAction *actionAPropos = new QAction("&A propos", this);  // AJOUT DU "A PROPOS"
    menuAide->addAction(actionAPropos);

    // GESTION DES SIGNAUX ET SLOTS DU MENU
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Escape"));
    connect(actionScientifique, SIGNAL(triggered()), this, SLOT(afficher_scientique()));
    connect(actionClavier, SIGNAL(triggered()), this, SLOT(afficher_clavier()));
    actionClavier->setCheckable(true);
    actionScientifique->setCheckable(true);
    // CONNECT DU PROGEDIT

    connect(actionProg,SIGNAL(triggered(bool)), this, SLOT(openProgWindow()));
    connect(actionProgEdit,SIGNAL(triggered()), this, SLOT(openEditProg())); // OUVRE LE QEDITTEXT
    connect(actionAPropos,SIGNAL(triggered(bool)), this, SLOT(afficher_APropos()));


    //INITIALISATION DES OBJETS DU .h
    mainArea = new QWidget;
    mainSet = new QHBoxLayout;
    scientificPad = new scientific_pad;
    scientificPad->hide();


    keyboard = new Keyboard();
    keyboard->hide();
    controlScreen = new QWidget();
    controlScreen->setFixedSize(QSize(280, 300));

    pile = new Pile ;
    controleur = Controleur::getInstance(LiteraleManager::getInstance() , *pile) ;
    message = new QLineEdit() ;
    commande = new QLineEdit() ;
    commande->setFocus();
    vuePile = new QTableWidget (pile->getNbItemsToAffiche(),1) ;
    pile_create();
    topLayout = new QHBoxLayout();

    middleLayout = new QHBoxLayout();
    boutons_droits = new QVBoxLayout();

    bottomLayout = new QHBoxLayout();
    pile_plus = new QPushButton();
    pile_moins = new QPushButton();
    enter = new QPushButton();

    leftLayout = new QVBoxLayout();
    leftLayout->addWidget(vuePile);
    vuePile->setStyleSheet("background : rgba(35,141,214,45)");

    commande->setStyleSheet("background : rgba(35,141,214,45)");
    //MIDDLELAYOUT SETTINGS

    middleLayout->addLayout(leftLayout);
    middleLayout->addLayout(boutons_droits);

    boutons_droits->addWidget(pile_plus);
    boutons_droits->addWidget(pile_moins);

    //BOTTOM LAYOUT SETTINGS

    bottomLayout->addWidget(commande);
    bottomLayout->addWidget(enter);
    enter->setIcon(QIcon("C:\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\projet_1_0-master\\projet_1_0\\images\\enter-arrow.png"));
    enter->setFlat(true);
    enter->setFocusPolicy(Qt::NoFocus);

    connect(enter,SIGNAL(clicked(bool)),this,SLOT(getNextCommande()));

    //BOUTON PILE SETTINGS + CONNECT
    pile_plus->setIcon(QIcon("C:\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\projet_1_0-master\\projet_1_0\\images\\add.png"));
    pile_plus->setFlat(true);
    pile_plus->setFocusPolicy(Qt::NoFocus);
    pile_moins->setIcon(QIcon("C:\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\projet_1_0-master\\projet_1_0\\images\\minus.png"));
    pile_moins->setFlat(true);
    pile_moins->setFocusPolicy(Qt::NoFocus);

    connect(pile_plus,SIGNAL(clicked(bool)),pile,SLOT(aug_pile()));
    connect(pile_plus,SIGNAL(clicked(bool)),this,SLOT(pile_create()));
    connect(pile_moins,SIGNAL(clicked(bool)),pile,SLOT(dim_pile()));
    connect(pile_moins,SIGNAL(clicked(bool)),this,SLOT(pile_create()));

    // MESSAGE SETTINGS

    message->setReadOnly(true);    //empèche d'écrire dans la lineEdit
    message->setStyleSheet("background: blue; color: yellow");
    message->setAlignment(Qt::AlignHCenter);
    message->setFixedHeight(45);

    //VUE PLIE SETTINGS

    vuePile->horizontalHeader()->setVisible(false);   //enlève l'indice de col
    vuePile->horizontalHeader()->setStretchLastSection(true);   //ajuste la largeur à la fenetre
    vuePile->setSelectionMode(QAbstractItemView::NoSelection);
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers) ;  //empèche d'écrire dans les cellules

    //SOUND_LOCK SETTINGS
    sound_lock = new QPushButton();
    sound_lock->setIcon(QIcon("C:\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\projet_1_0-master\\projet_1_0\\images\\speaker.png"));
    sound_lock->setFlat(true);
    sound_lock->setFocusPolicy(Qt::NoFocus);
    connect(sound_lock,SIGNAL(clicked(bool)),this,SLOT(sound_disable()));

    //TOPLAYOUT SETTINGS


    // LA PILE


    

    //GESTION DES CONNECTS DU CONTROLSCREEN
    connect(commande, SIGNAL (returnPressed()) , this , SLOT(getNextCommande())) ;
    connect(pile , SIGNAL (modificationEtat()) , this, SLOT(refresh())) ;

    //GESTION DES CONNECTS DU KEYBOARD

    connect(keyboard->b1,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b2,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b3,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b4,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b5,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b6,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b7,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b8,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b9,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->b0,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->bplus,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->bmoins,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->bdiv,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->bmult,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));
    connect(keyboard->clear,SIGNAL(clicked(bool)),commande, SLOT(clear()));
    connect(keyboard->space,SIGNAL(clicked(bool)),this, SLOT(keyboardButtonPressed()));


    //CREATION DES LIENS ENTRE LES LAYOUTS


    mainSet->addWidget(scientificPad);
    scientificPad->setStyleSheet("background : rgba(35,141,214,45)");
    mainSet->addWidget(controlScreen);
    message->setStyleSheet("background : rgba(35,186,117,45)");
    vuePile->setStyleSheet("background : rgba(35,141,214,25)");;
    mainSet->addWidget(keyboard);
    keyboard->setStyleSheet("background : rgba(35,141,214,45)");


    topLayout->addWidget(message);
    topLayout->addWidget(sound_lock);

    LcontrolScreen = new QVBoxLayout;
    controlScreen->setLayout(LcontrolScreen);
    LcontrolScreen->addLayout(topLayout);
    LcontrolScreen->addLayout(middleLayout);
    LcontrolScreen->addLayout(bottomLayout);


    mainArea->setLayout(mainSet);
    setCentralWidget(mainArea);
}

void MainWindow::afficher_APropos()
{
    QMessageBox::information(this,"CalcUTC", "Ce logiciel a été créé par Adrien et Antonin dans le cadre d'un projet universitaire");
}

void MainWindow::refresh()
{ //affiche état pile et message éventuel
message->setText(pile->getMessage());
if(message->text()!=""){
    this->bip();
}
//on efface tt ce qui est affiché
for(unsigned int i = 0 ; i<pile->getNbItemsToAffiche() ; i++)
    vuePile->item(i,0)->setText("") ;

unsigned int nb = 0 ;

for(Item* it= (pile->stack.end() -1)   ; it!= (pile->stack.begin()-1) and nb < pile->getNbItemsToAffiche() ; --it , ++nb)

    vuePile->item(pile->getNbItemsToAffiche()-nb-1,0)->setText((it->getLiterale()).toString()) ;


}
void MainWindow::openEditProg(){
    editWindow = new SecondWindow(); // Be sure to destroy you window somewhere
    editWindow->show();
}

void MainWindow::openProgWindow(){
    progWindow = new ProgWindow();
    progWindow->refresh_content();
    progWindow->show();
}



void MainWindow::getNextCommande(QString repet)
  {
    pile->setMessage("");
    QString source ;

    if (repet.isEmpty())
        source =commande->text() ;
    else
        source = repet ;

    QString c ;
    QTextStream s (&source) ;
    s>> c ;

    while (c != "") {
        if(c.startsWith('\'')) {//regarde s'il y a une quote
            source = s.readAll() ; //on prend tout ce qu'il y a dans la textStream
            source.push_front(c); //on remet c

            c = getExp(source) ;
            if (!c.isEmpty()){ //si c contient qqch
                controleur->commande(c) ; //on la traite
                commande->clear() ;
                controleur->sauvegarde();
                refresh() ;
                source.remove(c)  ; //on l'enlève de source
                getNextCommande(source) ; //on rappelle la fct avec l'exp en moins
                return ;
            }
            //sinon, alors l'expression est mal écrite, et on annule toute la suite.
            message->setText("exp fausse");
            commande->clear() ;
            return ;
        }

        if(c.startsWith('[')) {//regarde s'il y a [
            source = s.readAll() ; //on prend tout ce qu'il y a dans la textStream
            source.push_front(c); //on remet c

            c = getProg(source) ;
            if (!c.isEmpty()){ //si c contient qqch
                controleur->commande(c) ; //on la traite
                commande->clear() ;
                controleur->sauvegarde();
                refresh() ;
                source.remove(c)  ; //on l'enlève de source
                getNextCommande(source) ; //on rappelle la fct avec l'exp en moins
                return ;
            }

            //sinon, c'est faux, on annule la suite
            message->setText("prog faux");
            commande->clear() ;
            return ;
        }

        controleur->commande(c) ;
        commande->clear() ;
        s>>c ;


    }
    controleur->sauvegarde();
    refresh() ;
    qDebug()<<"erreur = "<<controleur->getErreur() ;
    controleur->erreur(false) ;

}

void MainWindow::pile_create(){
    QStringList liste;
    vuePile->setRowCount(pile->getNbItemsToAffiche()) ;
    for(unsigned int i=pile->getNbItemsToAffiche() ; i>0 ; i--)
    {
        QString str = QString::number(i) ;
        str+=" :";
        liste<<str ;
    }

    vuePile->setVerticalHeaderLabels(liste) ;
    for(unsigned int i=0 ; i<pile->getNbItemsToAffiche() ; i++)
    {
        vuePile->setItem(i , 0 , new QTableWidgetItem("")) ;
    }
    refresh();
}
