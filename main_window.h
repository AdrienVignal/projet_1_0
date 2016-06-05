#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "computer.h"
#include "secondwindow.h"
#include "prog_window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();
    private:
    SecondWindow* editWindow;
    ProgWindow* progWindow;
    QWidget* mainArea;
    QHBoxLayout* mainSet;

    // ON DECLARE DES WIDGETS COMME PARENTS DES LAYOUTS POUR UTILISER LES METHODES SHOW/HIDE
    QWidget* keyboard;
    ///QWidget* scientificPad;
    QWidget* controlScreen;

    //ON DECLARE 3 LAYOUTS QUI ENGLOBERONT LES SOUS ENSEMBLES DE L'APPLI
    QHBoxLayout* Lkeyboard;
    ///QVBoxLayout* LscientificPad;
    QVBoxLayout* LcontrolScreen;

    // ARCHITECTURE DU CONTROLSCREEN
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;

    Pile* pile;
    Controleur* controleur;

    // ARCHITECTURE DU KEYBOARD

    QVBoxLayout* num_pad;
    QVBoxLayout* op_pad;
    QHBoxLayout* ligne1;
    QHBoxLayout* ligne2;
    QHBoxLayout* ligne3;
    QHBoxLayout* ligne4;
    QPushButton* b1;
    QPushButton* b2;
    QPushButton* b3;
    QPushButton* b4;
    QPushButton* b5;
    QPushButton* b6;
    QPushButton* b7;
    QPushButton* b8;
    QPushButton* b9;
    QPushButton* b0;
    QPushButton* bplus;
    QPushButton* bmoins;
    QPushButton* bdiv;
    QPushButton* bmult;

    //ARCHITECTURE DU SCIENTIFIQUEPAD
    //
    //
    //


    //TOOLBAR
    /*UNDO/REDO  => done
     *BIP SONORE SI MESSAGE  //QObject::connect(pushbutton, SIGNAL(clicked()), qsound_mon_son, SLOT(play()));
     *AFFICHER X DERNIERS ELEM PILE (BOUTON +/-)
     *SECONDE VUE => GESTION MINI PROG/MODIF PARAM CALCU
    */

    private slots:

    void afficher_clavier(){
        if(keyboard->isHidden()){
            keyboard->show();
            //this->size_max();
        }else{
            keyboard->hide();
            //this->size_min();
        }
    }
    /*void afficher_scientique(){
        if(scientificPad->isHidden()) scientificPad->show();
        else scientificPad->hide();
        this->resize()
    }*/
    void openEditProg();
    void openProgWindow();
    void afficher_APropos();
    void refresh();
    void getNextCommande(QString repet = "");
    /*void size_min(){
        this->setFixedSize(200,300);
    }
    void size_max(){
        this->setFixedSize(600,300);
    }*/
};


#endif // MAIN_WINDOW_H
