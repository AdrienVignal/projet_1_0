#ifndef PROG_WINDOW_H
#define PROG_WINDOW_H

#include <QtWidgets>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "declarations.h"
#include "bouton_prog.h"


class ProgWindow : public QWidget
{
    Q_OBJECT

    public:
    ProgWindow();
    ~ProgWindow();
    void refresh_content();

    private:
    QVBoxLayout *main;
    QTableWidget *progVue;
      int nb_Affiche;
      int nb ;
    QPushButton *valider;
    QHBoxLayout *bottom;
    private slots:

    void action_save_prog();


};

#endif // PROG_WINDOW_H
