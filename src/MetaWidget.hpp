#pragma once
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
class MetaWidget : public QWidget {
    Q_OBJECT

public:
    MetaWidget() {
        setWindowFlags(Qt::FramelessWindowHint);
        setContentsMargins(0, 0, 0, 0);
    }
    ~MetaWidget() { }

private:
    qreal xr { 10 }, yr { 10 };
    bool m_isDraging { false };
    QPoint last, latest, offset;
    QColor borderColor { QColor(234, 130, 22).rgb() };
    qreal border_left { 0.8 }, border_top { 0.8 }, border_right { -0.8 }, border_bottom { -0.8 };

protected:
    void setRadius(qreal xr = 10, qreal yr = 10) {
        this->xr = xr;
        this->yr = yr;
    }
    void setBorderColor(int r, int g, int b) { borderColor = QColor(r, g, b).rgb(); }
    void setBoardAdjust(qreal left, qreal top, qreal right, qreal bottom) {
        border_left   = left;
        border_top    = top;
        border_right  = right;
        border_bottom = bottom;
    }
    void resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);
        auto rect = QPainterPath();
        rect.addRoundedRect(this->rect(), xr, yr);
        setMask(rect.toFillPolygon().toPolygon());
    }
    void drawBoarder(QPainter& painter) {
        painter.setRenderHint(QPainter::Antialiasing);
        // 修改颜色
        painter.setPen(borderColor);
        painter.setBrush(Qt::NoBrush);
        auto rect = QRectF(this->rect());
        // 修改边框绘制范围
        painter.drawRoundedRect(
            rect.adjusted(border_left, border_top, border_right, border_bottom), xr, yr);
    }
    void mousePressEvent(QMouseEvent* press) {
        QWidget::mousePressEvent(press);
        m_isDraging = true;
        if (press->buttons() == Qt::LeftButton) {
            offset = press->globalPosition().toPoint() - frameGeometry().topLeft();
        }
    }

    void mouseMoveEvent(QMouseEvent* move) {
        QWidget::mouseMoveEvent(move);
        if (m_isDraging && (move->buttons() & Qt::LeftButton)) {
            this->move(move->globalPosition().toPoint() - offset);
        }
    }
    void mouseReleaseEvent(QMouseEvent* release) { m_isDraging = false; }

    void paintEvent(QPaintEvent* paint) {
        QWidget::paintEvent(paint);
        QPainter painter(this);
        drawBoarder(painter);
    }
};