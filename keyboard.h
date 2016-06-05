#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <declarations.h>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


struct Keyboard: public QWidget{
    Q_OBJECT
public :
    QHBoxLayout* main;
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
    QPushButton* clear;
    QPushButton* space;
    Keyboard();
    ~Keyboard(){delete this;}
};

#endif // KEYBOARD_H
