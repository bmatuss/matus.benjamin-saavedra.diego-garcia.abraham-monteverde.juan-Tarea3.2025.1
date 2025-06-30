#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QUrl>
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
    
    videoWidget = new QVideoWidget(this);
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    
    audioOutput->setVolume(0.8);
    
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setVideoOutput(videoWidget);
    
    videoWidget->setGeometry(50, 100, 700, 400);
    videoWidget->setStyleSheet("border: 2px solid gray; background-color: black;");
    videoWidget->hide();
    
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
    
    videoWidget->raise();
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


void MainWindow::on_pushButton_pressed()
{
    QString urlText = ui->pushButton->text().trimmed();
    
    if (urlText.isEmpty()) {
        return;
    }
    
    QUrl videoUrl(urlText);
    
    if (!videoUrl.isValid() || videoUrl.scheme().isEmpty()) {
        videoUrl = QUrl::fromLocalFile(urlText);
    }
    
    mediaPlayer->setSource(videoUrl);
    videoWidget->show();
    mediaPlayer->play();
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        videoWidget->hide();
    }
}

