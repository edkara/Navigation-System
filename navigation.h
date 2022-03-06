#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "dialog.h"
#include "secdialog.h"
#include "graph.h"
#include "thirddialog.h"
#include <QMainWindow>
#include <QRadioButton>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Navigation; }
QT_END_NAMESPACE

class Navigation : public QMainWindow
{
    Q_OBJECT

public:
    Navigation(QWidget *parent = nullptr);
    ~Navigation();
    void loadVertices();
    void loadEdges();
    Graph getGraph();
    void pick();
    void resetButtons();
    int count();

private slots:
    void on_information_clicked();
    void on_entfernung_clicked();
    void on_alle_orte_clicked();
    void on_speichern_clicked();
    void on_routing_clicked();
    void on_hinzufuegen_clicked();

private:
    Ui::Navigation *ui = nullptr;
    QString first_button = "";
    Graph g;
};

inline int calcY(double lat){
    double ref = 54.323334;
    double comp1 = ref - 48.137154;
    int comp2 = 66 - 600;
    double factor = comp2 / comp1;
    int erg = (ref-lat) * factor;
    return -erg + 89;
}

inline int calcX(double lon){
    double ref = 6.783333;
    double comp1 = ref - 13.737262;
    int comp2 = 70 - 500;
    double factor = comp2 / comp1;
    int erg = (lon-ref) * factor;
    return erg + 70;
}

#endif // NAVIGATION_H
