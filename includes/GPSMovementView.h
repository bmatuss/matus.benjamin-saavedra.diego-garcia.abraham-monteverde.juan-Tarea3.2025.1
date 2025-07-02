#ifndef GPSMOVEMENTVIEW_H
#define GPSMOVEMENTVIEW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QList>

class GPSMovementView : public QDialog
{
    Q_OBJECT

public:
    explicit GPSMovementView(QWidget *parent = nullptr);
    ~GPSMovementView();
    
    void addGPSData(int tiempo, int x, int y);
    void clearGPSData();
    void updateCarPosition(int x, int y);
    void finalizePath();

signals:
    void positionUpdated(int tiempo, int x, int y);

private slots:
    void updatePosition();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsEllipseItem *car;
    QTimer *timer;
    
    struct GPSPoint {
        int tiempo;
        int x;
        int y;
    };
    
    QList<GPSPoint> gpsPoints;
    int currentPointIndex;
};

#endif // GPSMOVEMENTVIEW_H
