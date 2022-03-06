#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(const QStringList& text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QStringList headers = {"Nachbarn", "Entfernung"};
    ui->tableWidget->setRowCount(text.size());
    ui->tableWidget->setColumnCount(2);
    for(int i = 0; i < text.size(); i++)
    {
        QStringList lineToken = text.at(i).split(";", QString::SkipEmptyParts);
        for (int j = 0; j < 2; j++) {
            QString value = lineToken.at(j);
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(i, j, item);
        }
    }
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->resizeColumnsToContents();
    myRedoGeometry(this);
    ui->tableWidget->setMaximumSize(myGetQTableWidgetSize(ui->tableWidget));
    ui->tableWidget->setMinimumSize(ui->tableWidget->maximumSize());
}

QSize SecDialog::myGetQTableWidgetSize(QTableWidget *t)
{
    int w = t->verticalHeader()->width() + 4;
    for (int i = 0; i < t->columnCount(); i++)
        w += t->columnWidth(i);
    int h = t->horizontalHeader()->height() + 4;
    for (int i = 0; i < t->rowCount(); i++)
        h += t->rowHeight(i);
    return QSize(w, h);
}

void SecDialog::myRedoGeometry(QWidget *w)
{
    const bool vis = w->isVisible();
    const QPoint pos = w->pos();
    w->hide();
    w->show();
    w->setVisible(vis);
    if (vis && !pos.isNull())
        w->move(pos);
}

SecDialog::~SecDialog()
{
    delete ui;
}
