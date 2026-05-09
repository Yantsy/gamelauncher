#include "mainwindow.hpp"
MyWindow::MyWindow() noexcept {
    setFixedSize(1320, 720);
    setWindowFlags(Qt::FramelessWindowHint);
    setContentsMargins(0, 0, 0, 0);
    // setAttribute(Qt::WA_TranslucentBackground);
    //  parameters:0.667,0.667
}
MyWindow::~MyWindow() { }
// 修改边框
void MyWindow::drawBoarder(QPainter& painter) {
    painter.setRenderHint(QPainter::Antialiasing);
    // 修改颜色
    painter.setPen(QColor(234, 130, 22).rgb());
    painter.setBrush(Qt::NoBrush);
    auto rect = QRectF(this->rect());
    // 修改边框绘制范围
    painter.drawRoundedRect(rect.adjusted(0.8, 0.8, -0.8, -0.8), xr, yr);
}

void MyWindow::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    auto rect = QPainterPath();
    rect.addRoundedRect(this->rect(), xr, yr);
    setMask(rect.toFillPolygon().toPolygon());
}

void MyWindow::mousePressEvent(QMouseEvent* press) {
    QWidget::mousePressEvent(press);
    m_isDraging = true;
    if (press->buttons() == Qt::LeftButton) {
        offset = press->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void MyWindow::mouseMoveEvent(QMouseEvent* move) {
    QWidget::mouseMoveEvent(move);
    if (m_isDraging && (move->buttons() & Qt::LeftButton)) {
        this->move(move->globalPosition().toPoint() - offset);
    }
}
void MyWindow::mouseReleaseEvent(QMouseEvent* release) { m_isDraging = false; }

void MyWindow::paintEvent(QPaintEvent* paint) {
    QWidget::paintEvent(paint);
    QPainter painter(this);
    drawBoarder(painter);
}