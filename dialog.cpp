#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QStringList &list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QStringList headers = {"Ort", "Breitengrad", "Längengrad"};
    ui->tableWidget->setRowCount(list.size());
    ui->tableWidget->setColumnCount(3);
    for(int i = 0; i < list.size(); i++)
    {
        QStringList lineToken = list.at(i).split(";", QString::SkipEmptyParts);
        for (int j = 0; j < 3; j++) {
            QString value = lineToken.at(j);
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(i, j, item);
        }
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //myRedoGeometry(this);
    //ui->tableWidget->setMaximumSize(myGetQTableWidgetSize(ui->tableWidget));
    ui->tableWidget->setMinimumSize(ui->tableWidget->maximumSize());
}

QSize Dialog::myGetQTableWidgetSize(QTableWidget *t)
{
    int w = t->verticalHeader()->width() + 4;
    for (int i = 0; i < t->columnCount(); i++)
        w += t->columnWidth(i);
    int h = t->horizontalHeader()->height() + 4;
    for (int i = 0; i < t->rowCount(); i++)
        h += t->rowHeight(i);
    return QSize(w, h);
}

void Dialog::myRedoGeometry(QWidget *w)
{
    const bool vis = w->isVisible();
    const QPoint pos = w->pos();
    w->hide();
    w->show();
    w->setVisible(vis);
    if (vis && !pos.isNull())
        w->move(pos);
}

Dialog::~Dialog()
{
    delete ui;
}

