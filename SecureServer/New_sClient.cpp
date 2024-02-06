/**
* @file New_sClient.cpp
* @author Anil Kumar
* @date 6Feb2024
* @brief New_sClient class has unique id and QTcpSocket for each new connections.
*/
#include "New_sClient.h"

New_sClient::New_sClient(QString uID)
{
    unique_id = uID;
}

QString New_sClient::m_get_id()
{
    return unique_id;
}

/**
 * @brief New_sClient::sl_Connected
 */
void New_sClient::sl_Connected()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" Client Connected";
}

/**
 * @brief New_sClient::sl_DataAvailable
 */
void New_sClient::sl_DataAvailable()
{
    QByteArray rcv_data = Obj_TcpSocket->readAll();
    if(rcv_data == "")
        return;

    emit si_newData(unique_id,rcv_data);

    QByteArray ack = "ACK OK at ";
    ack.append(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:ss:ss:zzz"));
    Obj_TcpSocket->write(ack);
    Obj_TcpSocket->waitForBytesWritten();
}

/**
 * @brief New_sClient::sl_Disconnected
 */
void New_sClient::sl_Disconnected()
{
    PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" Client Disconnected";
    delete Obj_TcpSocket;
}

void New_sClient::sl_StateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" ConnectedState";
        break;
    case QAbstractSocket::BoundState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" BoundState";
        break;
    case QAbstractSocket::ListeningState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        PRINT_NO_QUOTE <<TIMESTAMP(__FUNCTION__)<< unique_id+" ClosingState";
        break;
    default:
        break;
    }
}
