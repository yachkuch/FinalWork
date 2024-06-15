#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QStandardItemModel>
#include <unordered_map>

namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();

    void setRow(std::vector<std::string> row);
    void setRows(std::list<std::vector<std::string>> rows);
    
    QStandardItemModel* model{nullptr};

private:
    Ui::Table *ui;

    std::unordered_map<int,int> row_to_index;
};

#endif // TABLE_H
