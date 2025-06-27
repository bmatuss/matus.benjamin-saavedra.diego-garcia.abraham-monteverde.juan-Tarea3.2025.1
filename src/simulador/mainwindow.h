

#include <QMainWindow>

class Broker;
class VideoPublisher;
class VideoFollower;

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

private:
    Ui::MainWindow *ui;
    Broker *broker;
    VideoPublisher *videoPublisher;
    VideoFollower *videoFollower;
};
