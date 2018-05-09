#include "recordsform.h"
#include "ui_recordsform.h"

#include <QFile>
#include <QTextStream>
#include <QFontDatabase>

#define COUNT 5
#define FONT_SIZE 32

RecordsForm::RecordsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordsForm)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/rc.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont rc(family, FONT_SIZE, QFont::Bold);

    QFile inputFile("records.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       int i = 0;

       while (!in.atEnd() && i < COUNT)
       {
          QStringList line = in.readLine().split("$");

          QLabel *label =  new QLabel();
          label->setFont(rc);
          label->setAlignment(Qt::AlignJustify);
          label->setText(line[0] + "  " + line[1]);
          label->setMinimumWidth(341);

          ui->verticalLayout->addWidget(label);
          i++;
       }
       inputFile.close();
    }
}

RecordsForm::~RecordsForm()
{
    delete ui;
}
