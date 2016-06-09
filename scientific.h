#ifndef SCIENTIFIC_H
#define SCIENTIFIC_H
#include <declarations.h>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

class scientific_pad : public QWidget{
    Q_OBJECT
public:
    QVBoxLayout* main;
    QHBoxLayout* ligne1;
    QHBoxLayout* ligne2;
    QHBoxLayout* ligne3;
    QPushButton* sin;
    QPushButton* cos;
    QPushButton* tan;
    QPushButton* puis;
    QPushButton* arcsin;
    QPushButton* arccos;
    QPushButton* arctan;
    QPushButton* sqrt;
    QPushButton* div;
    QPushButton* mod;
    QPushButton* exp;
    QPushButton* ln;
    scientific_pad();
};

#endif // SCIENTIFIC_H
