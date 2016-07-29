#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QTime>
#include <QShortcut>
#include <QSettings>
#include <QMessageBox>
#include <QPushButton>
#include <QFont>
#include <QPalette>

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT
    QTcpSocket *socket;
    QShortcut *shortsend;
    QSettings *settings;
    QString IP;
    int port;

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    void sendToServer (QString str);

private slots:
    void on_ConnectBtn_clicked();
    void readyReadSlot ();
    void on_sendBtn_clicked();
    void on_lineMsg_textChanged(const QString &arg1);
    void on_DisconnectBtn_clicked();
    void slotSocketError (QAbstractSocket::SocketError);

    void on_lineLogin_textChanged(const QString &arg1);

private:
    Ui::Client *ui;
};

#endif // CLIENT_H
