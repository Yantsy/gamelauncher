#pragma once
#include "../MyPictureWidget/audioWidget_sdl2.h"
#include "../MyPictureWidget/demuxer.h"
#include "../MyPictureWidget/videoWidget_gl.h"
#include <QAudioOutput>
#include <QEvent>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>
class MyWindow : public QWidget {
    Q_OBJECT
public:
    explicit MyWindow() noexcept;
    ~MyWindow();
    void setPictureOutput(MyGLWidget* glWidget);
    void setAudioOutput(MyAudioWidget* audioWidget);
    QVBoxLayout mainLayout;
    void start();

private:
    QThread* thread             = nullptr;
    DemuxerPlusDecoder* demuxer = nullptr;
    // 修改圆角弧度
    qreal xr { 10 }, yr { 10 };
    bool m_isDraging { false };
    QPoint last, latest, offset;

    void drawBoarder(QPainter& painter);
    void addContents(const std::string& source, int index);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* press) override;
    void mouseMoveEvent(QMouseEvent* move) override;
    void mouseReleaseEvent(QMouseEvent* release) override;
    void paintEvent(QPaintEvent* paint) override;
};