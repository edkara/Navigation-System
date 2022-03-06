#include "thirddialog.h"
#include "ui_thirddialog.h"

ThirdDialog::ThirdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdDialog)
{
    ui->setupUi(this);

    QFormLayout *myLay = new QFormLayout(this);
    QString inputTitles[] = {"Ort: ", "Breitengrad: ", "Längengrad: "};
    QString inputs[3];
    for (int i = 0; i < 3; ++i)
    {
        QLabel *tLabel = new QLabel(QString(inputTitles[i]), this);
        QLineEdit *tLine = new QLineEdit(this);
        myLay->addRow(tLabel, tLine);
        infoFields << tLine;
    }
    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    myLay->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                        this, &ThirdDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &ThirdDialog::reject);
    Q_ASSERT(conn);
    setLayout(myLay);
}

QStringList ThirdDialog::getStrings(QWidget *parent, bool *ok)
{
    ThirdDialog *dialog = new ThirdDialog(parent);
    QStringList list;
    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;
    if (ret) {
        foreach (auto field, dialog->infoFields) {
            list << field->text();
        }
    }
    dialog->deleteLater();
    return list;
}


ThirdDialog::~ThirdDialog()
{
    delete ui;
}
