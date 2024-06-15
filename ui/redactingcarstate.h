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
    void getCarState();
    void addNewCarButton(std::string id);

signals:
    void sendCarStateSignal(std::vector<std::string> carState);

private:
    Ui::RedactingCarState *ui;
    void sendCarState(QAbstractButton *button);

private slots:

    void setStatetable(int idx);

};

#endif // REDACTINGCARSTATE_H
