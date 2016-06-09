#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QtWidgets>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>


class SecondWindow : public QWidget
{
    Q_OBJECT

    public:
    SecondWindow();
    private:
    QVBoxLayout *main;
    QTextEdit *progEdit;
    QPushButton *valider;
    QPushButton *effacer;
    QHBoxLayout *bottom;
    private slots:
    void send_text();
};
#endif // SECONDWINDOW_H
