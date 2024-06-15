#include "table.h"
#include "ui_table.h"
#include <QHeaderView>
Table::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0,7);
    model->setHeaderData(0, Qt::Horizontal, "Номер");
    model->setHeaderData(1, Qt::Horizontal, "Марка");
    model->setHeaderData(2, Qt::Horizontal, "Пробег");
    model->setHeaderData(3, Qt::Horizontal, "Топливо");
    model->setHeaderData(4, Qt::Horizontal, "Состояние");
    model->setHeaderData(5, Qt::Horizontal, "Имя арендатора");
    model->setHeaderData(6, Qt::Horizontal, "Время аренды");
    ui->table->setModel(model);
    ui->table->verticalHeader()->setVisible(false);
}

Table::~Table()
{
    delete ui;
}

void Table::setRow(std::vector<std::string> row)
{
    int index = -1;
    try
    {
        index = std::stoi(row.at(1));
    }
    catch(const std::exception& e)
    {
        return;
    }
    
    auto row_number = model->rowCount();;
    auto iter = row_to_index.find(index);
    if(iter == row_to_index.end())
    {
        row_to_index[index] = row_number;
        for(int i = -1; const auto &el : row)
        {
            if(i > model->columnCount()) return;
            model->setItem(row_number,i,new QStandardItem(QString(el.data())));
            i++;
        }
        return;
    }
    for(int i = -1; const auto &el : row)
    {
        if(i > model->columnCount()) return;
        auto item = model->item(iter->second,i);
        item->setData(QVariant(el.data()));
        i++;
    }
}

void Table::setRows(std::list<std::vector<std::string>> rows)
{
    for(const auto &el : rows) setRow(el);
}

