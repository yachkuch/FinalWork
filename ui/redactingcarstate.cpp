#include "redactingcarstate.h"
#include "ui_redactingcarstate.h"

#include "Protocol.h"
#include <QAction>
#include <QDebug>

RedactingCarState::RedactingCarState(QWidget *parent) : QWidget(parent),
                                                        ui(new Ui::RedactingCarState)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &RedactingCarState::sendCarState);
    connect(ui->comboBox, &QComboBox::activated, this, &RedactingCarState::setStatetable);
}

RedactingCarState::~RedactingCarState()
{
    delete ui;
}

void RedactingCarState::getCarState()
{
    CarStateMes carState = {
        .id = ui->uniqNumber->text().toInt(),
        .brand = ui->Type->text().toStdString(),
        .distance = ui->distance->text().toInt(),
        .fuel = ui->fuel->value(),
        .state = ui->state->itemText(ui->state->currentIndex()).toStdString(),
    };
    emit(sendCarStateSignal(carState.toVector()));
}

void RedactingCarState::addNewCarButton(std::string id)
{
    auto act = ui->comboBox_2->actions();
    for(const auto &ac : act)
    {
        if(ac->text() == QString(id.data()))
            return;
    }
    ui->comboBox_2->addItem(QString(id.data()));
}
/// @brief
/// @param button
void RedactingCarState::sendCarState(QAbstractButton *button)
{
    //if (button->text() == "&ОК")
    //{
        getCarState();
    //}
    //qDebug() << button->text();
}


void RedactingCarState::setStatetable(int idx)
{
    if(idx == 0) ui->comboBox_2->show();
    else ui->comboBox_2->hide();
}
