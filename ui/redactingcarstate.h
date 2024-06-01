#ifndef REDACTINGCARSTATE_H
#define REDACTINGCARSTATE_H

#include <QWidget>

namespace Ui {
class RedactingCarState;
}

class RedactingCarState : public QWidget
{
    Q_OBJECT

public:
    explicit RedactingCarState(QWidget *parent = nullptr);
    ~RedactingCarState();

private:
    Ui::RedactingCarState *ui;
};

#endif // REDACTINGCARSTATE_H
