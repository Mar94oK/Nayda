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
}

void MunchkinDialog::SlotClearLog()
{
    ui->txtBrowser_TextLog->clear();
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
