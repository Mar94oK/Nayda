#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

#include <QObject>
#include <QString>
#include <Application/card.h> //cards
#include <QTcpSocket>
#include <QDataStream>
#include <QNetworkSession>

typedef QPair<QString, QString> serverSettings;


  class Server : public QObject
  {
      Q_OBJECT

  private:

     int m_value;
     Game_Card_Stock _Main_Doors;
     Game_Card_Stock _Main_Treausures;
     Game_Card_Stock _Fold_Doors;
     Game_Card_Stock _Fold_Treasures;
     Game_Card_Stock _Basis_Doors;
     Game_Card_Stock _Basis_Treasures;

  private:

    QTcpSocket *tcpSocket = nullptr;
    QNetworkSession *networkSession = nullptr;
    QDataStream *inputStream;
    QDataStream *outputSream;
    serverSettings _srvrSettings;

  public:

      explicit Server(QObject* parent =  nullptr);
      int value() const { return m_value; }
      virtual bool something();

  public slots:

      void dbgTheGameBeginsStateReceived(bool begins);

  /*
   *    These slots are only used for debug the connection.
   *    Please, see the FortuneClient and FortuneServer examples;
   *
   */
  private slots:

//      void requestNewFortune();
//      void readFortune();
//      void displayError(QAbstractSocket::SocketError socketError);
//      void enableGetFortuneButton();
//      void sessionOpened();

  public slots:

      void saveServerSettings(serverSettings settings)
      {
          _srvrSettings = settings;
      }


  signals:

      void valueChanged(int newValue);

  };



#endif // SERVER_H



