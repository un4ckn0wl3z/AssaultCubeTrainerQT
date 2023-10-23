#include "AssaultCubeTrainerQT.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile theme_file(QString(":/theme/DarkPurple.qss"));
    theme_file.open(QFile::ReadOnly);

    if (theme_file.isOpen())
    {
        a.setStyleSheet(theme_file.readAll());
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
