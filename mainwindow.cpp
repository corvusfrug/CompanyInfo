#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(TabActiveSwitcher(int)));
    QObject::connect(ui->listWidgetPosition, SIGNAL(currentRowChanged(int)), this, SLOT(CurrentPositionSwitch(int)));
    QObject::connect(ui->listWidgetPerson, SIGNAL(currentRowChanged(int)), this, SLOT(CurrentPersonSwitch(int)));

    ui->textEditPositions->setReadOnly(true);
    ui->textEditSub->setReadOnly(true);
}

void MainWindow::SetCompany(std::shared_ptr<Company> company)
{
    this->company=company;

    emit ui->tabWidget->currentChanged(ui->tabWidget->currentIndex());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TabActiveSwitcher(int arg)
{
    switch (arg)
    {
        case 0:
            CompanyTabActive();
        break;
        case 1:
            PersonTabActive();
        break;
        case 2:
            PositionTabActive();
        break;
    }
}

void MainWindow::CurrentPositionSwitch(int arg)
{
    if(arg<0 || arg>=(int)company->GetPositions().size())
        return;
    std::shared_ptr<Position> currPosition = company->GetPositions()[arg];
    ui->LNamePosition->setText(currPosition->GetName());
    ui->LCountInCompany->setText(QString::number(currPosition->GetCount()));
    QString str = currPosition->GetName();
    if(str == "Employee")
    {
            ui->LNamePositionComent->setText("Простой сотрудник");
            ui->LPrecentFS->setText("Не может быть");
            ui->LPrecentFSType->setText("");
    } else if(str == "Sales")
    {
            ui->LNamePositionComent->setText("Специалист по продажам");
            ui->LPrecentFS->setText(QString::number((currPosition->GetPremiumForSubordinate())*100) + " %");
            ui->LPrecentFSType->setText("За подчиненных любого уровня");

    } else if(str == "Manager")
    {
            ui->LNamePositionComent->setText("Специалист по управлению персоналом");
            ui->LPrecentFS->setText(QString::number((currPosition->GetPremiumForSubordinate())*100) + " %");
            ui->LPrecentFSType->setText("Только за подчиненных первого уровня");
    } else if(str == "CEO")
    {
            ui->LNamePositionComent->setText("Генеральный директор");
            ui->LPrecentFS->setText(QString::number((currPosition->GetPremiumForSubordinate())*100) + " %");
            ui->LPrecentFSType->setText("Только за подчиненных первого уровня");
    }

    ui->LRate->setText(QString::number(currPosition->GetRate()) + " рубли");
    ui->LPrecentFY->setText(QString::number((currPosition->GetLengthOfServicePrecent()-1)*100) + " %");
    ui->LPrecentFYMAX->setText(QString::number((currPosition->GetMaxLengthOfServicePrecent()-1)*100) + " %");
}

void MainWindow::CurrentPersonSwitch(int arg)
{
    if(arg<0 || arg>=(int)company->GetPersons().size())
        return;
    std::shared_ptr<Employee> currPosition = company->GetPersons()[arg];
    ui->LPersName->setText(currPosition->GetFullName());
    ui->LPersPosition->setText(currPosition->GetCurrentPosition()->GetConcretPosition()->GetName());
    ui->LPersPositionDate->setText(currPosition->GetCurrentPosition()->GetBeginDate().toString("yyyy-M-d"));
    ui->LPersSalary->setText(QString::number(currPosition->GetSalary(),'f',2));
    ui->LPersSayaryLOS->setText(QString::number(currPosition->GetSalaryForLOS(),'f',2));
    ui->textEditPositions->clear();
    ui->textEditPositions->setText(currPosition->GetPositionsInfoString());

    ui->LPersSalarySub->setVisible(true);
    ui->label_15->setVisible(true);
    ui->LPersSubLab->setVisible(true);
    ui->LPersSubCount->setVisible(true);
    ui->LPersSubCountFLevel->setVisible(true);
    ui->LPersSubLab->setVisible(true);
    ui->LPersSubLab_2->setVisible(true);
    ui->LPersSubLab_3->setVisible(true);
    ui->LPersSubLab_4->setVisible(true);
    ui->textEditSub->setVisible(true);

    switch(currPosition->GetType())
    {
        case PersonType::Employee:
            ui->LPersSalarySub->setVisible(false);
            ui->label_15->setVisible(false);
            ui->LPersSubLab->setVisible(false);
            ui->LPersSubCount->setVisible(false);
            ui->LPersSubCountFLevel->setVisible(false);
            ui->LPersSubLab->setVisible(false);
            ui->LPersSubLab_2->setVisible(false);
            ui->LPersSubLab_3->setVisible(false);
            ui->LPersSubLab_4->setVisible(false);
            ui->textEditSub->setVisible(false);
        break;
        case PersonType::Manager:
        case PersonType::CEO:
        {
            auto tmpptr = std::dynamic_pointer_cast<Manager>(currPosition);
            ui->LPersSayaryLOS->setText(QString::number(tmpptr->GetSalaryForLOS(),'f',2));
            ui->LPersSalarySub->setText(QString::number(tmpptr->GetSalaryForSub(),'f',2));
            ui->LPersSubCount->setText(QString::number(tmpptr->GetSubCount()));
            ui->LPersSubCountFLevel->setText(QString::number(tmpptr->GetSubFLCount()));
            ui->textEditSub->setText(tmpptr->GetSubordinatesInfoString());
        break;
        }
        case PersonType::Sales:
        {
            auto tmpptr = std::dynamic_pointer_cast<Sales>(currPosition);
            ui->LPersSayaryLOS->setText(QString::number(tmpptr->GetSalaryForLOS(),'f',2));
            ui->LPersSalarySub->setText(QString::number(tmpptr->GetSalaryForSub(),'f',2));
            ui->LPersSubCount->setText(QString::number(tmpptr->GetSubCount()));
            ui->LPersSubCountFLevel->setText(QString::number(tmpptr->GetSubFLCount()));
            ui->textEditSub->setText(tmpptr->GetSubordinatesInfoString());
        break;
        } 
    }
}

void MainWindow::CompanyTabActive()
{
    ui->LCEOPerson->setText(company->GetCEO()->GetFullName());
    ui->LCountEmplPerson->setText(QString::number(company->GetCountEmployee())+ " сотрудников");
    ui->LSumSalary->setText(QString::number(company->GetTotalMoney(),'f',2)+ " рублей");
}

void MainWindow::PositionTabActive()
{
    int currentRow = ui->listWidgetPosition->currentRow();
    ui->listWidgetPosition->clear();
    for(auto ptr : company->GetPositions())
    {
        ui->listWidgetPosition->addItem(ptr->GetName());
    }
    if(currentRow>=0 && currentRow<ui->listWidgetPosition->count())
        ui->listWidgetPosition->setCurrentRow(currentRow);
    else
        ui->listWidgetPosition->setCurrentRow(0);
}

void MainWindow::PersonTabActive()
{
    int currentRow = ui->listWidgetPerson->currentRow();
    ui->listWidgetPerson->clear();
    for(auto ptr : company->GetPersons())
    {
        ui->listWidgetPerson->addItem(ptr->GetSmallName());
    }
    if(currentRow>=0 && currentRow<ui->listWidgetPerson->count())
        ui->listWidgetPerson->setCurrentRow(currentRow);
    else
        ui->listWidgetPerson->setCurrentRow(0);
}


