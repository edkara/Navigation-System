#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QDebug>
#include <QTableWidget>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QStringList &list,QWidget *parent = nullptr);
    static QSize myGetQTableWidgetSize(QTableWidget *t);
    static void myRedoGeometry(QWidget *w);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
