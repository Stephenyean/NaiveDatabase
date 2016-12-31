#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void outputTable(std::vector<std::vector<std::string> >);
    void getInfo(QString);

private:
    Ui::MainWindow *ui;
    TableWindow *myTableWindow;

public slots:
    void getCommand();

    void chooseFile();
    void LoadFile();
};

#endif // MAINWINDOW_H
