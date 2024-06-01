#include "redactingcarstate.h"
#include "ui_redactingcarstate.h"

RedactingCarState::RedactingCarState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RedactingCarState)
{
    ui->setupUi(this);
}

RedactingCarState::~RedactingCarState()
{
    delete ui;
}
