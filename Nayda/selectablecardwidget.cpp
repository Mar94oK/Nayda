#include "selectablecardwidget.h"
#include "ui_selectablecardwidget.h"

SelectableCardWidget::SelectableCardWidget(SelectableCardMode mode, CommonCardViewData data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectableCardWidget)
{
    ui->setupUi(this);
}

SelectableCardWidget::~SelectableCardWidget()
{
    delete ui;
}
