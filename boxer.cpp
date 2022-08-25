#include "boxer.h"
#include <QDataStream>

#include <QDebug>

BoxeR::BoxeR() : file(nullptr)
{
}

BoxeR::~BoxeR()
{
    if (file) file->close();
}

void BoxeR::load()
{
    file = new QFile("./task.bin", this);
    if (!file) return;
    if (!file->open(QIODevice::ReadWrite))
    {
        emit end(false);
        return;
    }
    qDebug() << "Open file";
    emit end(true);
}

void BoxeR::nextRecord()
{
    qDebug() << "Next record";
    if (file->atEnd()) return;
    QDataStream stream(file);

    int len = 0;
    stream.readRawData((char*)&len, sizeof len);
    QByteArray b;
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString task = QString::fromUtf8(b);
    qDebug() << "Read:" + task;

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString endTask = QString::fromUtf8(b);

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString progress = QString::fromUtf8(b);

    emit loadTask(task, endTask, progress);

//    if (file->atEnd()) return;
//    QDataStream stream(file);

//    int len = 0;
//    stream.readRawData((char*)&len, sizeof len);
//    QByteArray b;
//    b.resize(len);
//    stream.readRawData(b.data(), len);
//    QString task = QString::fromUtf8(b);

//    stream.readRawData((char*)&len, sizeof len);
//    b.resize(len);
//    stream.readRawData(b.data(), len);
//    QDate endTask = QDate::fromString(b, "DD-MM-YYYY");

//    char progress;
//    stream.readRawData(&progress, sizeof(char));
//    emit loadTask(task, endTask, progress);
}

void BoxeR::saveRecord(QString task, QString endTask, QString progress)
{
    QDataStream stream(file);

    auto bytes = task.toUtf8();
    int len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);

    bytes = endTask.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);

    bytes = progress.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);

//    QDataStream stream(file);

//    auto bytes = task.toUtf8();
//    int len = bytes.length();
//    stream.writeRawData((char*)&len, sizeof len);
//    stream.writeRawData(bytes.data(), len);

//    bytes = endTask.toString("DD-MM-YYYY").toUtf8();
//    len = bytes.length();
//    stream.writeRawData((char*)&len, sizeof len);
//    stream.writeRawData(bytes.data(), len);

//    stream.writeRawData(&progress, sizeof progress);
}

