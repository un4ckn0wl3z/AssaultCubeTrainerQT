#include "AssaultCubeTrainerQT.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile theme_file(QString(":/theme/DarkPurple.qss"));
    theme_file.open(QFile::ReadOnly);   //open theme file

    if (theme_file.isOpen())
    {
        a.setStyleSheet(theme_file.readAll());        //set the theme here!
        theme_file.close();
    }
    else
    {
        qDebug("File couldn't be opened!");
    }

     
    AssaultCubeTrainerQT w;
    w.show();
    return a.exec();
}
