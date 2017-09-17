#include "mainwindow.h"
#include <QApplication>
#include "Company.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::shared_ptr<Company> company( new Company() );
    w.SetCompany(company);
    w.show();

    return a.exec();
}
