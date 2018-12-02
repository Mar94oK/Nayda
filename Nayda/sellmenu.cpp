#include "sellmenu.h"
#include "ui_sellmenu.h"

SellMenu::SellMenu(const std::vector<SimpleCard> &data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellMenu)
{
    ui->setupUi(this);
}

SellMenu::~SellMenu()
{
    delete ui;
}
