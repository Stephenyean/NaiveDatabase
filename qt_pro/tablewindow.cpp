#include "tablewindow.h"
#include "ui_tablewindow.h"
#include "QStandardItemModel"
#include "string.h"

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);

}

void TableWindow::outputTable(std::vector<std::vector<std::string> > tableList){
    QStandardItemModel *myTableModel = new QStandardItemModel();
    int row = tableList.size();
    int column = tableList[0].size();
    for(int i=0; i<column; i++){
        myTableModel->setHorizontalHeaderItem(i, new QStandardItem(QString::fromStdString(tableList[0][i])));
    }
    for(int i=1; i<row; i++){
        for(int j=0; j<column; j++){
            myTableModel->setItem(i-1, j, new QStandardItem(QString::fromStdString(tableList[i][j])));
        }
    }

    //利用setModel()方法将数据模型与QTableView绑定
    ui->myTableView->setModel(myTableModel);
}

TableWindow::~TableWindow()
{
    delete ui;
}
