#ifndef MUNCHKINDIALOG_H
#define MUNCHKINDIALOG_H

#include <QWidget>
#include <QString>
#include <QStringList>

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

public slots:

    void SlotShowMessage(const QStringList& message) { ShowMessage(message);}

public:

    bool eventFilter(QObject *o, QEvent *e);

};



#endif // MUNCHKINDIALOG_H
