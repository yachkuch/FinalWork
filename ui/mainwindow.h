#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataBaseWorker.h"
#include <memory>

#include <boost/asio/io_context.hpp>
namespace Ui {
class MainWindow;
}
class Networker;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(boost::asio::io_context &context,QWidget *parent = nullptr);
    ~MainWindow();

    std::shared_ptr<DataBaseWorker> getDb();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DataBaseWorker> dbWorker;
    std::shared_ptr<Networker> net;
    boost::asio::io_context &context;

    void receiveCarState(std::vector<std::string> carState);
    private slots:
    void setTableData(std::string data);
    void run();

};

#endif // MAINWINDOW_H
