#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include "Broker.h"
#include "VideoPublisher.h"
#include "VideoFollower.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::onLineEditReturnPressed);

    broker = new Broker();

    videoPublisher = new VideoPublisher("VideoPublisher", broker);
    videoFollower = new VideoFollower("VideoFollower");
    broker->subscribe("topic", videoFollower);

    connect(videoFollower, &VideoFollower::messageProcessed, this, &MainWindow::onFollowerMessage);

    ui->label->setText(QString::fromStdString(videoPublisher->getName()));
    ui->label_2->setText(QString::fromStdString(videoFollower->getName()));
    ui->pushButton->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete videoPublisher;
    delete broker;
    
}

void MainWindow::onLineEditReturnPressed() {
    QString text = ui->lineEdit->text();
    videoPublisher->publish("topic", text.toStdString());
    ui->lineEdit->clear();
}

void MainWindow::onFollowerMessage(const QString &message) {
    ui->pushButton->setText(message);
}

