/**
* @file New_sClient.h
* @author Anil Kumar
* @date 6Feb2024
* @brief Header of New_sClient class .
*/
#ifndef NEW_SCLIENT_H
#define NEW_SCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QDateTime>

#define TIMESTAMP(func)    QString(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ")+func+":$ ")
#define PRINT_NO_QUOTE      qDebug().noquote()

class New_sClient : public QObject
{
    Q_OBJECT
    QString unique_id = 0;
public:
    New_sClient(QString uID = "00");
    QTcpSocket *Obj_TcpSocket = 0;
    QString m_get_id();
public slots:
    void sl_DataAvailable();
private slots :
    void sl_Connected();
    void sl_Disconnected();
    void sl_StateChanged(QAbstractSocket::SocketState state);
signals:
    void si_newData(QString clientId,QByteArray clientData);
};

#endif // NEW_SCLIENT_H
