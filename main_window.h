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
#include "controleur.h"
#include "scientific.h"
#include "keyboard.h"
#include "prog_window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();
    static MainWindow& getInstance();
    static void libererInstance();
    void setTextEnter(QString s){
        text_enter = s;
    }

    void printText();
    friend class ProgWindow;
    void getNextCommande(QString repet = "");

    private:

    SecondWindow* editWindow;
    ProgWindow* progWindow;
    QWidget* mainArea;
    QHBoxLayout* mainSet;
    // SINGLETON NECESSAIRE POUR CONNECT LE SLOT ENTER
    struct Handler{
        MainWindow* instance;
        Handler():instance(0){}
        ~Handler(){delete instance;}
    };
    static Handler handler;
    // ON DECLARE DES WIDGETS COMME PARENTS DES LAYOUTS POUR UTILISER LES METHODES SHOW/HIDE
    Keyboard* keyboard;
    scientific_pad* scientificPad;
    QWidget* controlScreen;

    //ON DECLARE 3 LAYOUTS QUI ENGLOBERONT LES SOUS ENSEMBLES DE L'APPLI
    QHBoxLayout* Lkeyboard;
    QVBoxLayout* LcontrolScreen;

    // ARCHITECTURE DU CONTROLSCREEN
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QHBoxLayout* topLayout;
    QPushButton* sound_lock;


    QHBoxLayout* middleLayout;
    QHBoxLayout* bottomLayout;
    QVBoxLayout* boutons_droits;
    QPushButton* enter;
    QPushButton* pile_plus;
    QPushButton* pile_moins;
    bool sound_enabled = true;
    QVBoxLayout* leftLayout;
    Pile* pile;
    Controleur* controleur;


    QString text_enter;
    //TOOLBAR
    /*UNDO/REDO  => done

     *AFFICHER X DERNIERS ELEM PILE (BOUTON +/-)
     *SECONDE VUE => GESTION MINI PROG/MODIF PARAM CALCU
    */

    private slots:
    void bip(){
        if(sound_enabled)
            QApplication::beep();
    }

    void sound_disable(){
        if(sound_enabled){
            sound_enabled = false;
            sound_lock->setIcon(QIcon("\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\version finale\\projet_1_0\\images/speaker_disabled.png"));
        }
        else{
            sound_enabled = true;
            sound_lock->setIcon(QIcon("\\Users\\Adrien\\Documents\\Adrien\\UTC\\GI 02\\LO21\\Projet\\version finale\\projet_1_0\\images/speaker.png"));
        }
    }

    void afficher_clavier(){
        if(keyboard->isHidden()){
            keyboard->show();
            if(scientificPad->isHidden()){
                size_moy();
            }else{
                size_max();
            }

        }else{
            keyboard->hide();
            if(scientificPad->isHidden()){
                size_min();
            }else{
                size_moy();
            }
        }
    }

    void afficher_scientique(){
        if(scientificPad->isHidden()){
            scientificPad->show();
            if(keyboard->isHidden()){
                size_moy();
            }else{
                size_max();
            }

        }else{
            scientificPad->hide();
            if(keyboard->isHidden()){
                size_min();
            }else{
                size_moy();
            }
        }
    }
    void pile_create();
    void openEditProg();
    void openProgWindow();
    void afficher_APropos();
    void refresh();
    void slot_getNextCommande() {getNextCommande();}
    void keyboardButtonPressed()
    {
        QPushButton* button = qobject_cast<QPushButton*>( sender() );

        if ( button )
        {
            commande->insert( button->text() );
        }
    }
    void size_min(){
        this->setFixedSize(300,350);
    }
    void size_moy(){
        this->setFixedSize(600,350);
    }
    void size_max(){
        this->setFixedSize(900,350);
    }
    void open_context();
    void save_context();

};


#endif // MAIN_WINDOW_H
