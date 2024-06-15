#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <boost/asio/io_context.hpp>
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
    explicit ClientWindow(boost::asio::io_context &context,QWidget *parent = nullptr);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;

    boost::asio::io_context &context;
    std::shared_ptr<Networker> networker;

    QStandardItemModel* model{nullptr};

    std::unordered_map<int,int> row_to_index;

private slots:
    void setTableData(std::string data);


    void run();
    void senRequest();
};

#endif // CLIENTWINDOW_H
