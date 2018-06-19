#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

#include <QObject>
#include <QString>
#include <Application/card.h> //cards
#include <QTcpSocket>
#include <QDataStream>
#include <QNetworkSession>


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


  public:

      explicit Server(QObject* parent =  nullptr);
      int value() const { return m_value; }
      virtual bool something();

  public slots:

      void dbgTheGameBeginsStateReceived(bool begins);

  signals:

      void valueChanged(int newValue);

  };



#endif // SERVER_H



