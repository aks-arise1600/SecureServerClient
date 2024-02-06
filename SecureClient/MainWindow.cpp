/**
* @file MainWindow.cpp
* @author Anil Kumar
* @date 6Feb2024
* @brief This class Main Client ui.
* It create SecureClient to conection with SSL server and display server data on UI.
*/
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if(!is_connected)
    {
        if(objClient)
            emit objClient->m_UpdateCredentials(ui->lineEdit_host->text(),ui->lineEdit_port->text().toInt());
        else
        {
            objClient = new SecureClient(ui->lineEdit_host->text(),ui->lineEdit_port->text().toInt());
            connect(objClient,SIGNAL(si_Message(QString)),SLOT(sl_ClientMsg(QString)));
            connect(objClient,SIGNAL(si_rcvServerData(QByteArray)),SLOT(sl_GetServerData(QByteArray)));
        }
    }
}

void MainWindow::on_pushButton_Send_clicked()
{
    if(ui->lineEdit_sendTxt->text()=="")
    {
        QMessageBox::warning(this,"No Data","No Data is available to write !!");
        return;
    }

    if(objClient)
    {
        objClient->m_NewBuffer(ui->lineEdit_sendTxt->text().toLatin1());
        ui->plainTextEdit->appendPlainText("SEND: "+ui->lineEdit_sendTxt->text());
    }
}

void MainWindow::sl_ClientMsg(QString msg)
{
    PRINT_NO_QUOTE << TIMESTAMP(__FUNCTION__) << msg;

    if(msg.contains("Authentication succeeded"))
    {
        is_connected = true;
        ui->pushButton_Connect->setDisabled(true);
        ui->label_Status->setText("Connected securly !!");
    }
    else if(msg.contains("Error"))
    {
        is_connected = false;
        ui->pushButton_Connect->setDisabled(false);
        ui->label_Status->clear();
    }
}

void MainWindow::sl_GetServerData(QByteArray rcvData)
{
    QString txt = "RECV: "+QString::fromStdString(rcvData.toStdString());
    ui->plainTextEdit->appendPlainText(txt);
}
