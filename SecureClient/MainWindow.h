/**
* @file MainWindow.h
* @author Anil Kumar
* @date 6Feb2024
* @brief Header of MainWindow class .
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SecureClient.h>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Send_clicked();
    void sl_ClientMsg(QString msg);
    void sl_GetServerData(QByteArray rcvData);
private:
    Ui::MainWindow *ui;
    SecureClient *objClient = 0;
    bool is_connected = false;
};

#endif // MAINWINDOW_H
