/**
* @file SecureServer.cpp
* @author Anil Kumar
* @date 6Feb2024
* @brief SecureServer class handle all incomming QSslSocket with TLS Handshake.
*/

#include "SecureServer.h"

SecureServer::SecureServer()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) << "SupportsSsl = " <<QSslSocket::supportsSsl() <<",sslBuilVersion = "<< QSslSocket::sslLibraryBuildVersionString()
                  << ",sslLibVersion = "<< QSslSocket::sslLibraryVersionString();

    QFile keyFile(":/certs/arise1600_local.key");
    keyFile.open(QIODevice::ReadOnly);
    key = QSslKey(keyFile.readAll(), QSsl::Rsa);
    keyFile.close();

    QFile certFile(":/certs/arise1600_local.crt");
    certFile.open(QIODevice::ReadOnly);
    cert = QSslCertificate(certFile.readAll());
    certFile.close();

    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) << "Certificate Version "<<cert.version();

    connect(this, SIGNAL(newConnection()), this, SLOT(sl_NewClientConnection()));
    connect(this,SIGNAL(acceptError(QAbstractSocket::SocketError)),SLOT(sl_acptError(QAbstractSocket::SocketError)));
    sl_startListen();
}

QByteArray SecureServer::m_GetNewClientID()
{
    QByteArray uniqueID;
    QDateTime dt = QDateTime::currentDateTime();
    tmpId.uID.year = dt.date().year();
    tmpId.uID.month = dt.date().month();
    tmpId.uID.day = dt.date().day();
    tmpId.uID.hour = dt.time().hour();
    tmpId.uID.min = dt.time().minute();
    tmpId.uID.sec = dt.time().second();
    tmpId.uID.msec = dt.time().msec();
    tmpId.uID.extra = icount ++;

    uniqueID = QByteArray::fromRawData((char*)tmpId.bytes,SIZE_OF_UID);

    return uniqueID.toHex();
}

void SecureServer::sl_startListen()
{
    if (! listen(QHostAddress::Any, 4747))
    {
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<<4747 << " Server not started."<<errorString();
        QTimer::singleShot(5000,this,SLOT(sl_startListen()));
    }
    else
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<<4747 << "Server is started. Listening . . . ";
}

void SecureServer::sl_NewClientConnection()
{
    QString id = QString::fromStdString( m_GetNewClientID().toStdString()) ;

    New_sClient *obj_client = new New_sClient(id);
    obj_client->Obj_TcpSocket = nextPendingConnection();
    obj_client->Obj_TcpSocket->setObjectName(id);

    connect(obj_client->Obj_TcpSocket,SIGNAL(readyRead()),obj_client,SLOT(sl_DataAvailable()));
    connect(obj_client->Obj_TcpSocket,SIGNAL(disconnected()),SLOT(sl_DisconnectedHandler()));
    connect(obj_client,SIGNAL(si_newData(QString,QByteArray)),SLOT(sl_DataReceived(QString,QByteArray)));

    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) << "new Client "+id+"  ";
}

void SecureServer::sl_acptError(QAbstractSocket::SocketError acpt_err)
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) << acpt_err;
}

void SecureServer::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket(this);

    connect(sslSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sl_sslErrors(QList<QSslError>)));
    if(sslSocket->setSocketDescriptor(socketDescriptor))
    {
        sslSocket->setPrivateKey(key);
        sslSocket->setLocalCertificate(cert);
        sslSocket->addCaCertificates(":/certs/arise1600_ca.crt");
        sslSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);
        sslSocket->startServerEncryption();

        addPendingConnection(sslSocket);
    }
    else
    {
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<"Unable to set SocketDescriptor";
        delete sslSocket;
    }

}

void SecureServer::sl_Encrypted()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) << "Encrypted OK";
}

void SecureServer::sl_peerVerifyError(QSslError sslError)
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<sslError;
}

void SecureServer::sl_sslErrors(QList<QSslError> sslErrors)
{
    foreach (QSslError err, sslErrors)
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<err;
}

void SecureServer::sl_DisconnectedHandler()
{
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    PRINT_NO_QUOTE<<TIMESTAMP(__FUNCTION__) << clientSocket->objectName() << "client disconnected.";
    clientSocket->deleteLater();
}

void SecureServer::sl_DataReceived( QString client_uId, QByteArray rawData)
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< "clientid    ="+client_uId;
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< "dataSize    ="+QString::number(rawData.size()) <<"\n" << rawData;
}
