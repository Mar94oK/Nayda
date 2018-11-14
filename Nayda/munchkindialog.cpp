#include "munchkindialog.h"
#include "ui_munchkindialog.h"
#include <QKeyEvent>
#include <QDebug>

MunchkinDialog::MunchkinDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MunchkinDialog)
{
    ui->setupUi(this);
    SetUpMunckinDialog();
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
}

void MunchkinDialog::SlotClearLog()
{
    ui->txtBrowser_TextLog->clear();
}

void MunchkinDialog::SlotSendMessage(const QString &message)
{
    if (!message.isEmpty())
        emit SignalSendMessage(message);
}

bool MunchkinDialog::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::KeyPress && o == ui->txtEdit_UserText)
    {
       QKeyEvent* event =  static_cast<QKeyEvent*>(e);
       if (event->key() == Qt::Key_Enter)
       {
           emit SignalSendMessage(ui->txtEdit_UserText->toPlainText());
       }
       return true;
    }
    else
        return QWidget::eventFilter(o, e);
}

void MunchkinDialog::ShowMessage(const QString &message)
{
    ui->txtBrowser_TextLog->setText(message);
}
