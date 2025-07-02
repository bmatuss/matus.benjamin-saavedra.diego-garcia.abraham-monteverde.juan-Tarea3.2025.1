#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QSlider>
#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <QString>
#include <QGridLayout>
#include <QLabel>

class VideoWindow;

class Broker;
class VideoPublisher;
class VideoFollower;
class GPSCarPublisher;
class GPSCarFollower;
class GPSMovementView;
class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onLineEditReturnPressed();
    void onFollowerMessage(const QString &message);
    void onGPSMessage(const QString &message);
    void sendNextGPSData();
    void on_pushButton_pressed();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_actionVideo_triggered(); 
    void on_actionVideo_2_triggered();
    void on_actionCarGPS_triggered();
    void LeerArchivo(const QString &fileName);

private:
    struct GPSData {
        int segundos;
        int x;
        int y;
    };
    
    void ocultarTodo();
    
    QList<QString> listaVideos;
    QList<GPSData> datosGPS;
    QTimer *gpsTimer;
    int currentGPSIndex;
    QWidget *botonesWidget = nullptr;
    QGridLayout *gridLayout = nullptr;
    QLabel *labelVideos = nullptr;
    Ui::MainWindow *ui;
    Broker *broker;
    Broker *broker2;
    VideoPublisher *videoPublisher;
    VideoFollower *videoFollower;
    GPSCarPublisher *gpsCarPublisher;
    GPSCarFollower *gpsCarFollower;
    GPSMovementView *gpsView;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;
    QSlider *volumeSlider;
};
