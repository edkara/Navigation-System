#ifndef THIRDDIALOG_H
#define THIRDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QFrame>
#include <QtWidgets>
#include <QDebug>

namespace Ui {
class ThirdDialog;
}

class QLineEdit;
class QLabel;

class ThirdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdDialog(QWidget *parent = nullptr);
    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);
    ~ThirdDialog();

private:
    QList<QLineEdit*> infoFields;
    Ui::ThirdDialog *ui;
};

#endif // THIRDDIALOG_H
