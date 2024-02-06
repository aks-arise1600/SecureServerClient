/**
* @file SecureClient.cpp
* @author Anil Kumar
* @date 6Feb2024
* @brief This class Main Client ui.
* It connect with SSL server and read all QSslSocket data .
*/
#include "SecureClient.h"


SecureClient::SecureClient(QString host, int port)
{
    m_UpdateCredentials(host,port);
    Obj_TcpSocket = new QSslSocket;

    connect (Obj_TcpSocket, SIGNAL(encrypted()), this, SLOT(sl_ready()));
    connect (Obj_TcpSocket, SIGNAL(connected()), this, SLOT(sl_Connected()));
    connect (Obj_TcpSocket, SIGNAL(readyRead()), this, SLOT(sl_DataAvailable()));
    connect (Obj_TcpSocket, SIGNAL(disconnected()), this, SLOT(sl_Disconnected()));
    connect (Obj_TcpSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sl_sslErrors(QList<QSslError>)));

    bool isAddCert = Obj_TcpSocket->addCaCertificates(":/certs/arise1600_ca.crt");
    Obj_TcpSocket->setPrivateKey(":/certs/arise1600_local.key");
    Obj_TcpSocket->setLocalCertificate(":/certs/arise1600_local.crt");
    Obj_TcpSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);

    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<"addCaCertificates"<< isAddCert ;

    objTimer = new QTimer;
    connect(objTimer,SIGNAL(timeout()),SLOT(sl_SendData()));
    objTimer->start(30);
}

void SecureClient::m_UpdateCredentials(QString host, int port)
{
    strHost = host;
    iPort = port;
}

void SecureClient::m_reConnect()
{
    if(Obj_TcpSocket->state()!= QTcpSocket::ConnectedState)
    {
        Obj_TcpSocket->connectToHostEncrypted(strHost,iPort);

        if (Obj_TcpSocket->waitForEncrypted())
        {
            PRINT_NO_QUOTE << TIMESTAMP(__FUNCTION__) <<"Authentication succeeded.";
            emit si_Message("Authentication succeeded.");
        }
        else
        {
            PRINT_NO_QUOTE << TIMESTAMP(__FUNCTION__)<< Obj_TcpSocket->errorString() ;
            Obj_TcpSocket->disconnectFromHost();
            emit si_Message("Error:"+Obj_TcpSocket->errorString());
        }
    }
}

void SecureClient::m_NewBuffer(QByteArray newData)
{
    BufferList << newData.toHex();
}

void SecureClient::sl_ready()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<"Encryption succeeded by server.";
    emit si_Message("Encryption succeeded by server.");
}

void SecureClient::sl_Connected()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<"Client connected to "<< iPort;
    emit si_Message("Connected to server.");
}

void SecureClient::sl_DataAvailable()
{
    QByteArray rcv_data = Obj_TcpSocket->readAll();
    if(rcv_data == "")
        return;
    PRINT_NO_QUOTE << TIMESTAMP( __FUNCTION__ )+"_____ NEW-DATA ";

    emit si_rcvServerData(rcv_data);

}

void SecureClient::sl_Disconnected()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< iPort <<" Client Disconnected";
    emit si_Message("Error: Disconnected from server.");

}

void SecureClient::sl_sslErrors(QList<QSslError> sslErrors)
{
    foreach (QSslError err, sslErrors) {
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) <<err;
    }
}

void SecureClient::sl_SendData()
{
    try{

        if(Obj_TcpSocket->state() != QTcpSocket::ConnectedState)
            m_reConnect();

        if(BufferList.size())
        {
            QByteArray tmpData = QByteArray::fromHex(BufferList[0]);
            if(Obj_TcpSocket->write(tmpData.data(),tmpData.size()) == -1)
            {
                PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__) << "error in write";
            }
            else
                BufferList.removeAt(0);
        }

    }catch(QException &exp)
    {
        throw exp;
    }

}
