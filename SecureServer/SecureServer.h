/**
* @file SecureServer.h
* @author Anil Kumar
* @date 6Feb2024
* @brief Header of SecureServer class .
*/
#ifndef SECURESERVER_H
#define SECURESERVER_H
#include <QObject>
#include <QTcpServer>
#include <QSslSocket>
#include <New_sClient.h>
#include <QFile>
#include <QSslKey>
#include <QSslCertificate>
#include <QTimer>

struct uniqueid
{
    quint16 year;
    quint8 month;
    quint8 day;
    quint8 hour;
    quint8 min;
    quint8 sec;
    quint16 msec;
    quint32 extra;
}__attribute__ ((packed));

#define SIZE_OF_UID         sizeof(uniqueid)

union union_uid
{
    uniqueid uID;
    quint8 bytes[SIZE_OF_UID];
};


class SecureServer : public QTcpServer
{
    Q_OBJECT
    QByteArray m_GetNewClientID();
    union_uid tmpId;
    long icount = 1;
    QSslKey key;
    QSslCertificate cert;
public:
    SecureServer();
protected:
    void incomingConnection(qintptr socketDescriptor) override final;
private slots:
    void sl_startListen();
    void sl_NewClientConnection();
    void sl_acptError(QAbstractSocket::SocketError acpt_err);
    void sl_Encrypted();
    void sl_peerVerifyError(QSslError sslError);
    void sl_sslErrors(QList<QSslError> sslErrors);
    void sl_DisconnectedHandler();
    void sl_DataReceived( QString client_uId, QByteArray rawData);
};

#endif // SECURESERVER_H
