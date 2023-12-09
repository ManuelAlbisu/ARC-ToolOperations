#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QLabel>

class Camera : public QWidget {
    Q_OBJECT

public:
    Camera(QWidget *parent = nullptr);
    ~Camera();

private:
    QCamera *m_camera;
    QMediaCaptureSession captureSession;
    QVideoSink *m_videoSink;
    QLabel *m_videoLabel;
};

#endif // CAMERA_H
