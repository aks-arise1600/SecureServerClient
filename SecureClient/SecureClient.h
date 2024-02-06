/**
* @file SecureClient.h
* @author Anil Kumar
* @date 6Feb2024
* @brief Header of SecureClient class .
*/
#ifndef SECURECLIENT_H
#define SECURECLIENT_H
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QSslSocket>
#include <QTimer>
#include <QException>

#define TIMESTAMP(func)    QString(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ")+func+":$ ")
#define PRINT_NO_QUOTE      qDebug().noquote()


class SecureClient: public QObject
{
    Q_OBJECT
public:
    SecureClient(QString host = "127.0.0.1", int port = 4747);
    void m_UpdateCredentials(QString host, int port);
    QSslSocket *Obj_TcpSocket = 0;
    QString strHost;
    int iPort = 0;
    QTimer *objTimer = 0;
    void m_reConnect();
    void m_NewBuffer(QByteArray newData);
    QByteArrayList BufferList;
signals:
    void si_Message(QString);
    void si_rcvServerData(QByteArray);
private slots :
    void sl_ready();
    void sl_Connected();
    void sl_DataAvailable();
    void sl_Disconnected();
    void sl_sslErrors(QList<QSslError> sslErrors);
    void sl_SendData();
};

#endif // SECURECLIENT_H
