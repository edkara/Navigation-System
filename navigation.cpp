#include "navigation.h"
#include "ui_navigation.h"

Navigation::Navigation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Navigation)
{
    ui->setupUi(this);
    loadVertices();
    loadEdges();
    ui->buttonGroup->setExclusive(false);
    QList<QAbstractButton*> meine_staedte = ui->buttonGroup->buttons();
    for (QAbstractButton* button : meine_staedte){
        connect(button, &QAbstractButton::clicked, [this, button](){
            pick();
        });
    }
}

void Navigation::loadVertices()
{
    QFile file("D:/QTProjects/vertices.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "error", file.errorString());
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList lineToken = line.split(";", QString::SkipEmptyParts);
        g.addVertex(lineToken.at(0).toStdString(),lineToken.at(1).toDouble(),lineToken.at(2).toDouble());
    }
    file.close();
}

void Navigation::loadEdges()
{
    QFile file("D:/QTProjects/edges.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "error", file.errorString());
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList lineToken = line.split(";", QString::SkipEmptyParts);
        g.addEdge(lineToken.at(0).toStdString(), lineToken.at(1).toStdString());
    }
    file.close();
}

Graph Navigation::getGraph()
{
    return g;
}

void Navigation::pick()
{
    if(first_button=="")
    {
        first_button=ui->buttonGroup->checkedButton()->objectName();
        return;
    }
}

void Navigation::resetButtons()
{
    QList<QAbstractButton*> meine_staedte = ui->buttonGroup->buttons();
    for (QAbstractButton* button : meine_staedte){
        button->setChecked(false);
    }
    first_button = "";
}

int Navigation::count()
{
    int count = 0;
    QList<QAbstractButton*> meine_staedte = ui->buttonGroup->buttons();
    for (QAbstractButton* button : meine_staedte){ //adding function with lambda and Pointer to abstract Button
        if(button->isChecked())
        {
            count++;
        }
    }
    return count;
}

Navigation::~Navigation()
{
    delete ui;
}

void Navigation::on_alle_orte_clicked()
{
    vector<Vertex> vertices = g.getVertices();
    QStringList list;
    for(unsigned int i = 0; i<vertices.size();i++)
    {
        QString v = QString::fromStdString(vertices.at(i).name)+";"+QVariant(vertices.at(i).latitude).toString()+";"
                +QVariant(vertices.at(i).longitude).toString();
        list.append(v);
    }
    Dialog *dialog = new Dialog(list, this);
    dialog->setModal(false);
    dialog->show();
}

void Navigation::on_information_clicked()
{
    int numberOfChecked = count();
    if(numberOfChecked==1)
    {
        QString str = ui->buttonGroup->checkedButton()->objectName();
        Vertex *v = g.getVertex(str.toStdString());
        QStringList neighbours;
        for(unsigned int i=0; i<v->adjList.size();i++)
        {
            QString neighbour = QString::fromStdString(v->adjList.at(i).dest->name)+";"+QVariant(v->adjList.at(i).distance).toString()+" km";
            neighbours.append(neighbour);
        }
        SecDialog *dialog = new SecDialog(neighbours, this);
        dialog->setModal(false);
        dialog->show();
        resetButtons();
    }
    else
    {
        int ret = 0;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Sie haben gar keine oder mehr als eine Stadt ausgewählt!");
        msgBox.setInformativeText("Wählen Sie bitte genau eine Stadt!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Cancel);
        ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Cancel:
        {
            resetButtons();
        }
        default:
            break;
        }
    }
}

void Navigation::on_entfernung_clicked()
{
    int numberOfChecked = count();
    if(numberOfChecked==2)
    {
        int ret = 0;
        QString first = first_button;
        QString second = ui->buttonGroup->checkedButton()->objectName();
        Vertex* start = g.getVertex(first.toStdString());
        Vertex* dest = g.getVertex(second.toStdString());
        double distance = g.calcDist(*start,*dest);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Entfernung");
        msgBox.setText("Die Entfernung beträgt "+QVariant(distance).toString()+" km");
        msgBox.setStandardButtons(QMessageBox::Ok);
        ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Ok:
        {
            resetButtons();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        int ret = 0;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Sie haben nur eine oder mehr als zwei Städte ausgewählt!");
        msgBox.setInformativeText("Wählen Sie bitte genau zwei Städte!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Cancel);
        ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Cancel:
        {
            resetButtons();
            break;
        }
        default:
            break;
        }
    }
}

void Navigation::on_speichern_clicked()
{
    g.saveVertices();
    g.saveEdges();
}

void Navigation::on_routing_clicked()
{
    int numberOfChecked = count();
    if(numberOfChecked==2)
    {
        int ret = 0;
        QString first = first_button;
        QString second = ui->buttonGroup->checkedButton()->objectName();
        g.djistra(first.toStdString());
        string path = g.printPath(first.toStdString(),second.toStdString());
        QMessageBox msgBox;
        msgBox.setWindowTitle("Routing");
        msgBox.setText(QString::fromStdString(path));
        msgBox.setStandardButtons(QMessageBox::Ok);
        ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Ok:
        {
            resetButtons();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        int ret = 0;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Sie haben nur eine oder mehr als zwei Städte ausgewählt!");
        msgBox.setInformativeText("Wählen Sie bitte genau zwei Städte!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Cancel);
        ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Cancel:
        {
            resetButtons();
            break;
        }
        default:
            break;
        }
    }
}

void Navigation::on_hinzufuegen_clicked()
{
    bool ok;
    QStringList list = ThirdDialog::getStrings(this, &ok);
    QAbstractButton* button = new QRadioButton(ui->centralwidget);
    button->setText(list.at(0));
    button->setMinimumSize(100,11);
    button->setGeometry(calcX(list.at(2).toDouble()),calcY(list.at(1).toDouble()), 0, 0);
    ui->buttonGroup->addButton(button);
    button->setObjectName(list.at(0));
    connect(button, &QAbstractButton::clicked, this, &Navigation::pick);
    button->show();
    g.addVertex(list.at(0).toStdString(),list.at(1).toDouble(),list.at(2).toDouble());
    g.connectNearest(list.at(0).toStdString());
}
