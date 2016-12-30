#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include "string.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTableWindow = new TableWindow();
    myTableWindow->hide();

    connect(ui->myOkButton, SIGNAL(clicked()), this, SLOT(getCommand()));
    connect(ui->myChooseFileButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(ui->myLoadButton, SIGNAL(clicked()), this, SLOT(loadFile()));

    /* test for tableview
    std::vector<std::vector<std::string> > myVectorList;
    std::vector<std::string> v0, v1, v2;
    v0.push_back("name");   v0.push_back("sex");    v0.push_back("age");
    v1.push_back("John");   v1.push_back("male");    v1.push_back("19");
    v2.push_back("Jenny");   v2.push_back("female");    v2.push_back("18");
    myVectorList.push_back(v0);
    myVectorList.push_back(v1);
    myVectorList.push_back(v2);
    outputTable(myVectorList);
    */
}

void MainWindow::outputTable(std::vector<std::vector<std::string> > tableList){
    myTableWindow->outputTable(tableList);
    myTableWindow->show();
}

void MainWindow::getCommand(){
    QString Command = ui->myTextEdit->toPlainText();
    std::string stringCommand = Command.toStdString();
    //传给Parse.parse(stringCommand);
}

void MainWindow::getInfo(QString text){
    ui->myTextBrowser->append(text);
    this->update();
}

void MainWindow::chooseFile(){
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("*.sql *.SQL"));
    if(path.length() == 0){
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else{
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }
    ui->myFileTextEdit->setText(path);
}

void MainWindow::LoadFile(){
    QString filePath = ui->myFileTextEdit->toPlainText();
    std::string stringFilePath = filePath.toStdString();
    //stringFilePath传给Parse
}

MainWindow::~MainWindow()
{
    delete ui;
}
