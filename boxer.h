#ifndef BOXER_H
#define BOXER_H

#include <QFile>
#include <QDate>
#include <QObject>

    class BoxeR : public QObject
{
    Q_OBJECT
public:
    explicit BoxeR();
    virtual ~BoxeR();
    Q_INVOKABLE
        void load();
    Q_INVOKABLE
        void nextRecord();
    Q_INVOKABLE
        void saveRecord(QString, QString, QString);
private:
    QFile *file;
signals:
    void end(bool succed);
    //void loadTask(QString task, QDate endTask, char progress);
    void loadTask(QString task, QString endTask, QString progress);
private slots:
};

#endif // BOXER_H
