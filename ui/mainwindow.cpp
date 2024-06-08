#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),dbWorker(std::make_shared<DataBaseWorker>()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbWorker->start_db();
}

MainWindow::~MainWindow()
{
    delete ui;
}
