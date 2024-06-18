#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QStandardItemModel>
#include <unordered_map>

namespace Ui {
class ClientWindow;
}
class Networker ;
class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:

    void addButtom(std::string namer);

    Ui::ClientWindow *ui;

    std::shared_ptr<Networker> networker;

    QStandardItemModel* model{nullptr};

    std::unordered_map<int,int> row_to_index;

private slots:
    void setTableData(std::string data);
    void sendGettingCarMessage();


    void run();
    void senRequest();
};

#endif // CLIENTWINDOW_H
