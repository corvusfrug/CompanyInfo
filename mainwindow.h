#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Company.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void SetCompany(std::shared_ptr<Company>);
    ~MainWindow();

public slots:
    void TabActiveSwitcher(int);
    void CurrentPositionSwitch(int);
    void CurrentPersonSwitch(int);


private:
    Ui::MainWindow *ui;
    std::shared_ptr<Company> company;
    void CompanyTabActive();
    void PositionTabActive();
    void PersonTabActive();
};

#endif // MAINWINDOW_H
