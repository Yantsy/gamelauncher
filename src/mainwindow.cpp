#include "mainwindow.hpp"
MyWindow::MyWindow() noexcept {
    setFixedSize(1320, 720);
    setWindowFlags(Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_TranslucentBackground);
    //  parameters:0.667,0.667
}
MyWindow::~MyWindow() { }

void MyWindow::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    auto rect = QPainterPath();
    rect.addRoundedRect(this->rect(), 15, 15);
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