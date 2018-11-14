#include "munchkindialog.h"
#include "ui_munchkindialog.h"
#include <QKeyEvent>
#include <QDebug>
#include <QFont>

#define DESPAM_TIMER_PERIOD 1

MunchkinDialog::MunchkinDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MunchkinDialog)
{
    ui->setupUi(this);
    DeSpamTimerInit(1);
    SetUpMunckinDialog();
    SetUpConnections();
    ui->txtEdit_UserText->installEventFilter(this);

}

MunchkinDialog::~MunchkinDialog()
{
    delete ui;
}

void MunchkinDialog::SetUpMunckinDialog()
{
    ui->txtBrowser_TextLog->setReadOnly(true);
    ui->chckBox_SendOnEnterPress->setChecked(true);
}

void MunchkinDialog::SetUpConnections()
{

    QObject::connect(ui->btn_ClearLog, &QPushButton::clicked, this, &MunchkinDialog::SlotClearLog);
    QObject::connect(ui->btn_Send, &QPushButton::clicked, [this] {SlotSendMessage(ui->txtEdit_UserText->toPlainText());});
    QObject::connect(_deSpamTimer, &QTimer::timeout, this, &MunchkinDialog::SlotDeSpamReset);
}

void MunchkinDialog::SlotClearLog()
{
    ui->txtBrowser_TextLog->clear();
}

void MunchkinDialog::SlotSendMessage(const QString &message)
{
    qDebug() << "NAY-001: Executing SlotSendMessage() in MunckinDialog!";
    if (!message.isEmpty() && _sendingAllowed)
    {
        _sendingAllowed = false;
        _deSpamTimer->start();
        emit SignalSendMessage(message);
        ui->txtEdit_UserText->clear();
    }
}

void MunchkinDialog::SlotDeSpamReset()
{
    _sendingAllowed = true;
}

bool MunchkinDialog::eventFilter(QObject *o, QEvent *e)
{

    if (e->type() == QEvent::KeyPress && o == ui->txtEdit_UserText)
    {
       QKeyEvent* event =  static_cast<QKeyEvent*>(e);

       if ((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) && !ui->chckBox_SendOnEnterPress->isChecked())
           return true; //disabling enter!

       if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
       {          
           if (!ui->txtEdit_UserText->toPlainText().isEmpty() && _sendingAllowed)
           {
               emit SignalSendMessage(ui->txtEdit_UserText->toPlainText());
               _sendingAllowed = false;
               _deSpamTimer->start();
               ui->txtEdit_UserText->clear();
           }
           return true;
       }
       return QWidget::eventFilter(o, e);
    }
    else
        return QWidget::eventFilter(o, e);
}

void MunchkinDialog::DeSpamTimerInit(uint32_t timeSeconds)
{
    _deSpamTimer = new QTimer();
    _deSpamTimer->setInterval(timeSeconds*1000);
    _deSpamTimer->setSingleShot(true);
}

void MunchkinDialog::ShowMessage(const QStringList &message)
{
    //useful here
    //https://stackoverflow.com/questions/13559990/how-to-append-text-to-qplaintextedit-without-adding-newline-and-keep-scroll-at

    ui->txtBrowser_TextLog->setFontWeight(QFont::Bold);
    ui->txtBrowser_TextLog->append(message.first() + " : ");
    ui->txtBrowser_TextLog->setFontWeight(QFont::Normal);
    ui->txtBrowser_TextLog->moveCursor(QTextCursor::End);
    ui->txtBrowser_TextLog->insertPlainText(message.last());
    ui->txtBrowser_TextLog->moveCursor(QTextCursor::End);
}
