#pragma once
#include "../src/background.hpp"
#include <QEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
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
    void addContents(const std::string_view source, int index);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* press) override;
    void mouseMoveEvent(QMouseEvent* move) override;
    void mouseReleaseEvent(QMouseEvent* release) override;
    void paintEvent(QPaintEvent* paint) override;
};