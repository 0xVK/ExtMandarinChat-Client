#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :  QDialog(parent),  ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->ChatLog->setReadOnly(1);
    ui->lineMsg->setEnabled(0);
    ui->DisconnectBtn->setEnabled(0);
    ui->sendBtn->setEnabled(0);
    ui->ConnectBtn->setEnabled(0);

    shortsend = new QShortcut(this);
    shortsend->setKey(Qt::Key_Return);

    connect(shortsend,SIGNAL(activated()),this,SLOT(on_sendBtn_clicked()));

    settings = new QSettings ("settings.ini",QSettings::IniFormat);

    if ((!settings->contains("Adress/IP")) || (!settings->contains("Adress/Port")))
         {
            QMessageBox::information(this,"Settings error","Invalid IP or port server!\nPlease check it!");

            ui->lineLogin->setEnabled(0);
            ui->ConnectBtn->setEnabled(0);
         }

    this->setFixedSize(this->size());
    ui->ChatLog->wordWrapMode();

}

Client::~Client()
{
    delete ui;
}

void Client::sendToServer(QString str)
{
    QByteArray array;

    if (ui->radioButton->isChecked())
        array.append("<font color=red>" + str + "</font>");
    if (ui->radioButton_2->isChecked())
        array.append("<font color=green>" + str + "</font>");;
    if (ui->radioButton_3->isChecked())
        array.append("<font color=blue>" + str + "</font>");;
    if (ui->radioButton_4->isChecked())
        array.append("<font color=brown>" + str + "</font>");
    if (ui->radioButton_5->isChecked())
        array.append("<font color=black>" + str + "</font>");


    socket->write(array);
}

void Client::on_ConnectBtn_clicked()
{
    IP = settings->value("Adress/IP").toString();
    port = settings->value("Adress/Port").toInt();

    socket = new QTcpSocket(this);

    socket->connectToHost(IP,port);

    ui->radioButton->setEnabled(1);
    ui->radioButton_2->setEnabled(1);
    ui->radioButton_3->setEnabled(1);
    ui->radioButton_4->setEnabled(1);
    ui->radioButton_5->setEnabled(1);
    ui->lineMsg->setEnabled(1);
    ui->DisconnectBtn->setEnabled(1);
    ui->sendBtn->setEnabled(1);
    ui->ConnectBtn->setEnabled(0);
    ui->lineLogin->setEnabled(0);
    ui->lineMsg->setFocus();

    sendToServer ("[!]:<b> " + ui->lineLogin->text() + "</b> has been connected.");

    connect (socket,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));
    connect (socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotSocketError(QAbstractSocket::SocketError)));

}

void Client::readyReadSlot()
{
    QByteArray array;
    QString string;

    array = socket->readAll();
    string.append(array);

    ui->ChatLog->append(string);
}


void Client::on_sendBtn_clicked()
{
    if (ui->lineMsg->text() != "")
    {
        sendToServer("[<b>" + ui->lineLogin->text() + "</b>]: " + ui->lineMsg->text());
        ui->lineMsg->clear();
    }
}

void Client::on_lineMsg_textChanged(const QString &arg1)
{
    (arg1 == "") ? ui->sendBtn->setEnabled(0) : ui->sendBtn->setEnabled(1);


    ui->progressBar->setValue(arg1.size());

}

void Client::on_DisconnectBtn_clicked()
{
    sendToServer ("[!]: <b>" + ui->lineLogin->text() + "</b> has been disconnected.");
    socket->close();

    ui->lineMsg->setEnabled(0);
    ui->DisconnectBtn->setEnabled(0);
    ui->sendBtn->setEnabled(0);
    ui->ConnectBtn->setEnabled(1);
    ui->lineLogin->setEnabled(1);
}

void Client::slotSocketError (QAbstractSocket::SocketError err)
{
    ui->lineMsg->setEnabled(0);
    ui->DisconnectBtn->setEnabled(0);
    ui->sendBtn->setEnabled(0);
    ui->ConnectBtn->setEnabled(1);
    ui->lineLogin->setEnabled(1);

    QString strError ("[!]: Error: ");

          if (err == 0)
              strError+="Connection refused.";
          if (err == 1)
              strError+="Remote host closed.";
          if (err == 2)
              strError+="Host not found.";
          if (err == 3)
              strError+="Remote host closed.";
          if (err == 4)
              strError+="Socket resource.";
          if (err == 5)
              strError+="Socket timeout.";
          if (err == 7)
              strError+="Network error.";


         ui->ChatLog->append ("[!]: " + strError);
}

void Client::on_lineLogin_textChanged(const QString &arg1)
{
     (arg1.size() < 3) ? ui->ConnectBtn->setEnabled(0) : ui->ConnectBtn->setEnabled(1);

}
