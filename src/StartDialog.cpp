#include "StartDialog.h"
#include "ui_StartDialog.h"
#include "simulador/mainwindow.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::on_startButton_clicked()
{
    MainWindow *mainWin = new MainWindow();
    mainWin->show();
    this->close();
}
