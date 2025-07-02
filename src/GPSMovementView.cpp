#include "GPSMovementView.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QBrush>
#include <QPen>

GPSMovementView::GPSMovementView(QWidget *parent)
    : QDialog(parent), currentPointIndex(0)
{
    setWindowTitle("GPS Car Tracker");
    resize(800, 600);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    scene = new QGraphicsScene(this);
    if (!scene) {
        return;
    }
    
    scene->setSceneRect(0, 0, 600, 400);
    scene->setBackgroundBrush(QBrush(Qt::lightGray));
    
    view = new QGraphicsView(scene, this);
    if (!view) {
        return;
    }
    
    view->setFixedSize(620, 420);
    layout->addWidget(view);
    
    car = new QGraphicsEllipseItem(0, 0, 30, 30);
    if (!car) {
        return;
    }
    
    car->setBrush(QBrush(Qt::red));
    car->setPen(QPen(Qt::black, 2));
    scene->addItem(car);
    
    timer = new QTimer(this);
    if (!timer) {
        return;
    }
    
    connect(timer, &QTimer::timeout, this, &GPSMovementView::updatePosition);
}

GPSMovementView::~GPSMovementView()
{
    if (timer && timer->isActive()) {
        timer->stop();
    }
}

void GPSMovementView::addGPSData(int tiempo, int x, int y)
{
    GPSPoint point;
    point.tiempo = tiempo;
    point.x = x;
    point.y = y;
    gpsPoints.append(point);
}

void GPSMovementView::clearGPSData()
{
    gpsPoints.clear();
    currentPointIndex = 0;
    
    if (timer) {
        timer->stop();
    }
    
    if (car) {
        car->setPos(0, 0);
    }
}

void GPSMovementView::finalizePath()
{
    if (!gpsPoints.isEmpty() && timer) {
        currentPointIndex = 0;
        timer->start(1000);
    }
}

void GPSMovementView::updateCarPosition(int x, int y)
{
    if (!car || !view) {
        return;
    }
    
    car->setPos(x, y);
    view->ensureVisible(car);
}

void GPSMovementView::updatePosition()
{
    if (currentPointIndex >= gpsPoints.size()) {
        if (timer) {
            timer->stop();
        }
        return;
    }
    
    if (!car || !view) {
        return;
    }
    
    GPSPoint currentPoint = gpsPoints[currentPointIndex];
    car->setPos(currentPoint.x * 2, currentPoint.y * 2);
    view->ensureVisible(car);
    
    emit positionUpdated(currentPoint.tiempo, currentPoint.x, currentPoint.y);
    currentPointIndex++;
}
