#ifndef REDACTINGCARSTATE_H
#define REDACTINGCARSTATE_H

#include <QWidget>

struct CarStateMes;
class QAbstractButton;
namespace Ui {
class RedactingCarState;
}

class RedactingCarState : public QWidget
{
    Q_OBJECT

public:
    explicit RedactingCarState(QWidget *parent = nullptr);
    ~RedactingCarState();
    CarStateMes getCarState();

private:
    Ui::RedactingCarState *ui;
    void sendCarState(QAbstractButton *button);
};

#endif // REDACTINGCARSTATE_H
