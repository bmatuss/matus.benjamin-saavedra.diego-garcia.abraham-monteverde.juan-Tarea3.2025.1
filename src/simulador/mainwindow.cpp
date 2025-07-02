#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QString>
#include <QUrl>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Broker.h"
#include "VideoPublisher.h"
#include "VideoFollower.h"
#include "GPSCarPublisher.h"
#include "GPSCarFollower.h"
#include "GPSMovementView.h"
class VideoWindow : public QWidget {
public:
    VideoWindow(const QString &url, QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Video Player");
        resize(700, 500);
        QVBoxLayout *layout = new QVBoxLayout(this);
        QVideoWidget *vw = new QVideoWidget(this);
        QMediaPlayer *mp = new QMediaPlayer(this);
        QAudioOutput *ao = new QAudioOutput(this);
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(0, 100);
        slider->setValue(80);
        ao->setVolume(0.8);
        mp->setAudioOutput(ao);
        mp->setVideoOutput(vw);
        QUrl videoUrl(url);
        if (!videoUrl.isValid() || videoUrl.scheme().isEmpty()) {
            videoUrl = QUrl::fromLocalFile(url);
        }
        mp->setSource(videoUrl);
        layout->addWidget(vw);
        layout->addWidget(slider);
        connect(slider, &QSlider::valueChanged, ao, [ao](int value){ ao->setVolume(value/100.0); });
        mp->play();
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    botonesWidget = new QWidget(this);
    gridLayout = new QGridLayout(botonesWidget);
    labelVideos = new QLabel(botonesWidget);
    labelVideos->setText("");
    labelVideos->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    QFont font = labelVideos->font();
    font.setPointSize(12);
    font.setBold(true);
    labelVideos->setFont(font);
    gridLayout->addWidget(labelVideos, 0, 0, 1, 3, Qt::AlignHCenter | Qt::AlignTop);
    botonesWidget->setLayout(gridLayout);
    botonesWidget->setGeometry(100, 30, 600, 200);
    botonesWidget->hide();

    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::onLineEditReturnPressed);

    broker = new Broker("topic");
    videoPublisher = new VideoPublisher("VideoPublisher", broker);
    videoFollower = new VideoFollower("VideoFollower");
    broker->subscribe("topic", videoFollower);
    connect(videoFollower, &VideoFollower::messageProcessed, this, &MainWindow::onFollowerMessage);
    ui->pushButton->setText("");

    videoWidget = new QVideoWidget(this);
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.8);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setVideoOutput(videoWidget);
    videoWidget->setGeometry(50, 100, 650, 400);
    videoWidget->setStyleSheet("border: 2px solid gray; background-color: black;");
    videoWidget->hide();
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
    videoWidget->raise();

    volumeSlider = new QSlider(Qt::Vertical, this);
    volumeSlider->setGeometry(710, 100, 30, 400);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(80);
    volumeSlider->hide();
    connect(volumeSlider, &QSlider::valueChanged, this, [this](int value) {
        audioOutput->setVolume(value / 100.0);
    });

    broker2 = new Broker("GPSCarTopic");
    gpsCarPublisher = new GPSCarPublisher("GPSCarPublisher", broker2);
    gpsCarFollower = new GPSCarFollower("GPSCarFollower");
    broker2->subscribe("GPSCarTopic", gpsCarFollower);
    connect(gpsCarFollower, &GPSCarFollower::messageProcessed, this, &MainWindow::onGPSMessage);

    gpsView = nullptr;

    gpsTimer = new QTimer(this);
    gpsTimer->setSingleShot(false);
    currentGPSIndex = 0;
    connect(gpsTimer, &QTimer::timeout, this, &MainWindow::sendNextGPSData);

    ocultarTodo();
}

void MainWindow::ocultarTodo() {
    ui->lineEdit->hide();
    ui->pushButton->hide();
    videoWidget->hide();
    volumeSlider->hide();
    if (botonesWidget) botonesWidget->hide();
}

void MainWindow::on_actionVideo_triggered() {
    ocultarTodo();
    ui->lineEdit->show();
}

void MainWindow::on_actionVideo_2_triggered() {
    ocultarTodo();
    if (botonesWidget && gridLayout) {
        QLayoutItem *child;
        while ((child = gridLayout->takeAt(1)) != nullptr) {
            if (child->widget()) delete child->widget();
            delete child;
        }
        QString topicName = QString::fromStdString(broker->getDefaultTopic());
        QString followerName = QString::fromStdString(videoFollower->getName());
        labelVideos->setText(topicName + " -> " + followerName);
        
        int col = 0, row = 1, maxCols = 3;
        for (const QString &url : listaVideos) {
            QPushButton *btn = new QPushButton(url, nullptr);
            gridLayout->addWidget(btn, row, col);
            connect(btn, &QPushButton::clicked, this, [url]() {
                VideoWindow *vw = new VideoWindow(url);
                vw->setAttribute(Qt::WA_DeleteOnClose);
                vw->show();
            });
            col++;
            if (col >= maxCols) { col = 0; row++; }
        }
        botonesWidget->show();
        botonesWidget->raise();
    }
}

MainWindow::~MainWindow()
{
    if (gpsTimer && gpsTimer->isActive()) {
        gpsTimer->stop();
    }
    
    if (gpsView) {
        gpsView->close();
        delete gpsView;
        gpsView = nullptr;
    }
    
    delete ui;
    delete videoPublisher;
    delete videoFollower;
    delete gpsCarPublisher;
    delete gpsCarFollower;
    delete broker;
    delete broker2;
}

void MainWindow::onLineEditReturnPressed() {
    QString text = ui->lineEdit->text();
    if (!text.isEmpty()) {
        videoPublisher->publish(QString::fromStdString(broker->getDefaultTopic()).toStdString(), text.toStdString());
        listaVideos.append(text);        
        ui->lineEdit->clear();
    }
}

void MainWindow::onFollowerMessage(const QString &message) {
    ui->pushButton->setText(message);
}

void MainWindow::onGPSMessage(const QString &message) {
    if (!gpsView) {
        return;
    }
    
    QStringList parts = message.split(',');
    if (parts.size() == 3) {
        bool okX, okY;
        int x = parts[1].toInt(&okX);
        int y = parts[2].toInt(&okY);
        
        if (okX && okY) {
            gpsView->updateCarPosition(x, y);
        }
    }
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
void MainWindow::on_actionCarGPS_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo CarGPS", "", "Archivos de texto (*.txt);;Todos los archivos (*)");
    if (!fileName.isEmpty()) {
        LeerArchivo(fileName);
    }
}
void MainWindow::LeerArchivo(const QString &fileName) {
    if (gpsTimer && gpsTimer->isActive()) {
        gpsTimer->stop();
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    
    datosGPS.clear();
    
    QTextStream in(&file);
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        
        if (line.isEmpty()) {
            continue;
        }
        
        QStringList parts = line.split(QRegularExpression("\\s+|,"), Qt::SkipEmptyParts);
        if (parts.size() != 3) {
            continue;
        }
        
        bool okSegundos, okX, okY;
        int segundos = parts[0].trimmed().toInt(&okSegundos);
        int x = parts[1].trimmed().toInt(&okX);
        int y = parts[2].trimmed().toInt(&okY);
        
        if (!okSegundos || !okX || !okY) {
            continue;
        }
        
        GPSData gpsData;
        gpsData.segundos = segundos;
        gpsData.x = x;
        gpsData.y = y;
        
        if (!datosGPS.isEmpty()) {
            GPSData ultimoDato = datosGPS.last();
            int diferenciaTiempo = segundos - ultimoDato.segundos;
            
            if (diferenciaTiempo > 1) {
                int diferenciaX = x - ultimoDato.x;
                int diferenciaY = y - ultimoDato.y;
                
                for (int t = 1; t < diferenciaTiempo; t++) {
                    GPSData datoInterpolado;
                    datoInterpolado.segundos = ultimoDato.segundos + t;
                    
                    datoInterpolado.x = ultimoDato.x + ((diferenciaX * t + diferenciaTiempo/2) / diferenciaTiempo);
                    datoInterpolado.y = ultimoDato.y + ((diferenciaY * t + diferenciaTiempo/2) / diferenciaTiempo);
                    
                    datosGPS.append(datoInterpolado);
                }
            }
        }
        
        datosGPS.append(gpsData);
    }
    
    file.close();
    
    if (!datosGPS.isEmpty()) {
        currentGPSIndex = 0;
        
        if (gpsView) {
            gpsView->close();
            gpsView->deleteLater();
            gpsView = nullptr;
        }
        
        gpsView = new GPSMovementView(this);
        if (!gpsView) {
            return;
        }
        
        gpsView->clearGPSData();
        
        for (const GPSData& dato : datosGPS) {
            gpsView->addGPSData(dato.segundos, dato.x, dato.y);
        }
        
        gpsView->show();
        gpsView->raise();
        gpsView->activateWindow();
        
        gpsView->finalizePath();
        
        if (gpsTimer) {
            gpsTimer->start(1000);
        }
    }
}

void MainWindow::sendNextGPSData() {
    if (currentGPSIndex >= datosGPS.size()) {
        gpsTimer->stop();
        return;
    }
    
    const GPSData& dato = datosGPS[currentGPSIndex];
    
    QString mensajeGPS = QString("%1,%2,%3")
                        .arg(dato.segundos)
                        .arg(dato.x)
                        .arg(dato.y);
    
    gpsCarPublisher->publish(QString::fromStdString(broker2->getDefaultTopic()).toStdString(), 
                           mensajeGPS.toStdString());
    
    currentGPSIndex++;
}

