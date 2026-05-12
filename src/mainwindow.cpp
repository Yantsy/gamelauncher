#include "mainwindow.hpp"
MyWindow::MyWindow() noexcept {
    setFixedSize(1320, 720);
    setWindowFlags(Qt::FramelessWindowHint);
    setContentsMargins(0, 0, 0, 0);
    // setAttribute(Qt::WA_TranslucentBackground);
    //  parameters:0.667,0.667
    this->setLayout(&mainLayout);
    demuxer = new DemuxerPlusDecoder();
    demuxer->loopOn();
    thread = new QThread(this);
    mainLayout.setContentsMargins(0, 0, 0, 0);
    demuxer->moveToThread(thread);
    QObject::connect(thread, &QThread::started, demuxer, &DemuxerPlusDecoder::processStart);
    std::string contents = "/home/yantsy/workspace/mine/mihoyolauncher/resources/"
                           "【京吹_秀久】她的睫毛.mp4";
    addContents(contents, 1);
    /// "home/yantsy/Videos/tests/【京吹_秀久】她的睫毛.mp4"
    //"/home/yantsy/workspace/mine/mihoyolauncher/resources/examplevideo.webm"
}
MyWindow::~MyWindow() {
    demuxer->quit();
    if (demuxer != nullptr) demuxer->deleteLater();
    if (thread && thread->isRunning()) {
        if (thread != nullptr) thread->quit();
        thread->wait();
    }
}
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

void MyWindow::setPictureOutput(MyGLWidget* glWidget) {
    QObject::connect(demuxer, &DemuxerPlusDecoder::sendVideoInfo, glWidget, &MyGLWidget::getInfo);
    QObject::connect(demuxer, &DemuxerPlusDecoder::frameReady, glWidget, &MyGLWidget::frameIn);
}
void MyWindow::setAudioOutput(MyAudioWidget* audioWidget) {
    QObject::connect(
        demuxer, &DemuxerPlusDecoder::sendAudioInfo, audioWidget, &MyAudioWidget::getInfo);
}

void MyWindow::start() { thread->start(); }
void MyWindow::addContents(const std::string& source, int index) { demuxer->open(source); }
