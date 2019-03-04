#ifndef CHANGESKIN_H
#define CHANGESKIN_H

#include <QFile>
#include <QApplication>
#include <QDebug>

class changeskin
{
public:
changeskin();

static void setStyle(const QString & style) {
    qDebug()<<"setStyle is start";
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}
};

#endif // CHANGESKIN_H
