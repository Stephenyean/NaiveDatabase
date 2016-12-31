#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = 0);
    ~TableWindow();

private:
    Ui::TableWindow *ui;

public slots:
    void outputTable(std::vector<std::vector<std::string> >);
};

#endif // TABLEWINDOW_H
