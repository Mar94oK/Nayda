#ifndef MUNCHKINDIALOG_H
#define MUNCHKINDIALOG_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QTimer>

namespace Ui {
class MunchkinDialog;
}

class MunchkinDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MunchkinDialog(QWidget *parent = 0);
    ~MunchkinDialog();

private:
    Ui::MunchkinDialog *ui;

private:

    void SetUpMunckinDialog();
    void SetUpConnections();
    void ShowMessage(const QStringList& message);

signals:

    void SignalSendMessage(const QString& message);

private slots:

    void SlotClearLog();
    void SlotSendMessage(const QString& message);
    void SlotDeSpamReset();

public slots:

    void SlotShowMessage(const QStringList& message) { ShowMessage(message);}

public:

    bool eventFilter(QObject *o, QEvent *e);

private:

    QTimer* _deSpamTimer;
    void DeSpamTimerInit(uint32_t timeSeconds);
    bool _sendingAllowed = true;


};



#endif // MUNCHKINDIALOG_H
