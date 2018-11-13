#ifndef MUNCHKINDIALOG_H
#define MUNCHKINDIALOG_H

#include <QWidget>
#include <QString>

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


signals:

    void SignalSendMessage(const QString& message);

private slots:

    void SlotClearLog();

public:

    bool eventFilter(QObject *o, QEvent *e);

};

#endif // MUNCHKINDIALOG_H
