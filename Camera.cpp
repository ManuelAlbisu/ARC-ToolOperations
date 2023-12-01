#include "Camera.h"

#include <QVideoFrame>
#include <QImage>

Camera::Camera(QWidget *parent) : QMainWindow(parent), m_camera(new QCamera) {
    m_videoLabel = new QLabel(this);

    m_videoSink = new QVideoSink();

    QObject::connect(m_videoSink, &QVideoSink::videoFrameChanged, this, [this](const QVideoFrame &frame) {
        if (!frame.isValid()) return;

        QImage image = frame.toImage();
        m_videoLabel->setPixmap(QPixmap::fromImage(image));
    });

    captureSession.setCamera(m_camera);
    captureSession.setVideoSink(m_videoSink);

    m_camera->start();
}

Camera::~Camera() {
    m_camera->stop();
    delete m_camera;
    delete m_videoSink;
    delete m_videoLabel;
}
