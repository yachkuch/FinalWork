#include "redactingcarstate.h"
#include "ui_redactingcarstate.h"

#include "Protocol.h"
#include <QDebug>

RedactingCarState::RedactingCarState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RedactingCarState)
{
    ui->setupUi(this);
    connect(ui->buttonBox,&QDialogButtonBox::clicked,this,&RedactingCarState::sendCarState);
}

RedactingCarState::~RedactingCarState()
{
    delete ui;
}

CarStateMes RedactingCarState::getCarState()
{
    CarStateMes carState = {
    .id = ui->uniqNumber->text().toInt(),
    .brand = ui->Type->text().toStdString(),
    .distance = ui->distance->text().toInt(),
    .fuel = ui->fuel->value(),
    .state = ui->state->itemText(ui->state->currentIndex()).toStdString(),
    };
    return carState;
}

void RedactingCarState::sendCarState(QAbstractButton *button)
{
    if(button->text() == "ОК") getCarState();
}
