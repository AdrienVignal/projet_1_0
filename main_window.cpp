#include "main_window.h"
#include "declarations.h"

MainWindow::MainWindow()
{
    //CREATION DU MENU
    setWindowTitle("CalcUTC");
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
    actionRedo->setIcon(QIcon("/home/deneux/Bureau/UTC/Lo21/Projet/calcutc_v2/calcUTC_v2/arrow_redo.png"));
    actionRedo->setShortcut(QKeySequence(tr("Ctrl+y")));

    QAction *actionUndo = new QAction("&Undo", this);  // AJOUT DU "Undo"
    menuOption->addAction(actionUndo);
    actionUndo->setIcon(QIcon("/home/deneux/Bureau/UTC/Lo21/Projet/calcutc_v2/calcUTC_v2/arrow_undo.png"));
    actionUndo->setShortcut(QKeySequence(tr("Ctrl+z")));

    QMenu *menuAide = menuBar()->addMenu("&Aide");
    QAction *actionAPropos = new QAction("&A propos", this);  // AJOUT DU "A PROPOS"
    menuAide->addAction(actionAPropos);

    // GESTION DES SIGNAUX ET SLOTS DU MENU
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Escape"));
    //  connect(actionProg, SIGNAL(triggered()), this, SLOT()
    connect(actionClavier, SIGNAL(triggered()), this, SLOT(afficher_clavier()));
    actionClavier->setCheckable(true);
    actionScientifique->setCheckable(true);
    connect(actionProg,SIGNAL(triggered(bool)), this, SLOT(openProgWindow()));
    connect(actionProgEdit,SIGNAL(triggered()), this, SLOT(openEditProg())); // OOUVRE LE QEDITTEXT
    connect(actionAPropos,SIGNAL(triggered(bool)), this, SLOT(afficher_APropos()));


    //INITIALISATION DES OBJETS DU .h
    QWidget *mainArea = new QWidget;
    mainArea->setStyleSheet("background:#F0FFFF");
    mainSet = new QHBoxLayout;

    keyboard = new QWidget();
    keyboard->hide();
    controlScreen = new QWidget();
    controlScreen->setFixedSize(QSize(200, 300));

    pile = new Pile ;
    controleur = Controleur::getInstance(LiteraleManager::getInstance() , *pile) ;
    message = new QLineEdit() ;
    commande = new QLineEdit() ;
    vuePile = new QTableWidget (pile->getNbItemsToAffiche(),1) ;



    message->setReadOnly(true);    //empèche d'écrire dans la lineEdit
    message->setStyleSheet("background: blue; color: yellow");

    vuePile->horizontalHeader()->setVisible(false);   //enlève l'indice de col
    vuePile->horizontalHeader()->setStretchLastSection(true);   //ajuste la largeur à la fenetre
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers) ;  //empèche d'écrire dans les cellules

    QStringList liste;
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
    

    //GESTION DES CONNECTS DU CONTROLSCREEN
    connect (commande, SIGNAL (returnPressed()) , this , SLOT(getNextCommande())) ;
    connect(pile , SIGNAL (modificationEtat()) , this, SLOT(refresh())) ;


    //BOUTONS DU KEYBOARD
    b1 = new QPushButton("1");
    b1->setFixedSize(45,45);
    b2 = new QPushButton("2");
    b2->setFixedSize(45,45);
    b3 = new QPushButton("3");
    b3->setFixedSize(45,45);
    b4 = new QPushButton("4");
    b4->setFixedSize(45,45);
    b5 = new QPushButton("5");
    b5->setFixedSize(45,45);
    b6 = new QPushButton("6");
    b6->setFixedSize(45,45);
    b7 = new QPushButton("7");
    b7->setFixedSize(45,45);
    b8 = new QPushButton("8");
    b8->setFixedSize(45,45);
    b9 = new QPushButton("9");
    b9->setFixedSize(45,45);
    b0 = new QPushButton("0");
    b0->setFixedSize(100,45);

    bplus = new QPushButton("+");
    bplus->setFixedSize(90,45);
    bmoins = new QPushButton("-");
    bmoins->setFixedSize(90,45);
    bdiv = new QPushButton("/");
    bdiv->setFixedSize(90,45);
    bmult = new QPushButton("x");
    bmult->setFixedSize(90,45);

    ligne1 = new QHBoxLayout();
    ligne1->setContentsMargins(3,3,3,3);
    ligne2 = new QHBoxLayout();
    ligne2->setContentsMargins(3,3,3,3);
    ligne3 = new QHBoxLayout();
    ligne3->setContentsMargins(3,3,3,3);
    ligne4 = new QHBoxLayout();
    ligne4->setContentsMargins(3,3,3,3);
    num_pad = new QVBoxLayout();
    op_pad = new QVBoxLayout();
    //LAYOUT DU KEYBOARD

    ligne1->addWidget(b1);
    ligne1->addWidget(b2);
    ligne1->addWidget(b3);

    ligne2->addWidget(b4);
    ligne2->addWidget(b5);
    ligne2->addWidget(b6);

    ligne3->addWidget(b7);
    ligne3->addWidget(b8);
    ligne3->addWidget(b9);

    ligne4->addWidget(b0);

    op_pad ->addWidget(bplus);
    op_pad ->addWidget(bmoins);
    op_pad ->addWidget(bdiv);
    op_pad ->addWidget(bmult);

    num_pad->addLayout(ligne1);
    num_pad->addLayout(ligne2);
    num_pad->addLayout(ligne3);
    num_pad->addLayout(ligne4);



    //CREATION DES LIENS ENTRE LES LAYOUTS



    mainSet->addWidget(controlScreen);
    mainSet->addWidget(keyboard);


    LcontrolScreen = new QVBoxLayout;
    controlScreen->setLayout(LcontrolScreen);
    LcontrolScreen->addWidget(message);
    LcontrolScreen->addWidget(vuePile);
    LcontrolScreen->addWidget(commande);

    Lkeyboard = new QHBoxLayout;
    keyboard->setLayout(Lkeyboard);
    Lkeyboard->addLayout(num_pad);
    Lkeyboard->addLayout(op_pad);

    mainArea->setLayout(mainSet);
    setCentralWidget(mainArea);
}

void MainWindow::afficher_APropos()
{
    QMessageBox::information(this,"CalcUTC", "Ce logiciel a été créé par Adrien et Antonin dans le cadre d'un projet universitaire");
}

void MainWindow::refresh()
{ //affiche état pile et message éventuel
message->setText(pile->getMessage())
       ;
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

            c = controleur->getExp(source) ;
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

            c = controleur->getProg(source) ;
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
}


