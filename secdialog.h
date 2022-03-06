#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QTableWidget>
namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(const QStringList &text, QWidget *parent = nullptr);
    static QSize myGetQTableWidgetSize(QTableWidget *t);
    static void myRedoGeometry(QWidget *w);
     ~SecDialog();
private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
