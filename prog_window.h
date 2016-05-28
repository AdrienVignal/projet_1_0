#ifndef PROG_WINDOW_H
#define PROG_WINDOW_H

#include <QtWidgets>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

class ProgWindow : public QWidget
{
    Q_OBJECT

    public:
    ProgWindow();
    private:
    QVBoxLayout *main;
    QTableWidget *progVue;
    QPushButton *valider;
    QPushButton *annuler;
    QHBoxLayout *bottom;
    private slots:
    // A Créer -> connection avec le vector de prog
    //void refresh_content();
    void closeProgWindow();
    void action_annuler();
    void action_valider();
};

#endif // PROG_WINDOW_H
