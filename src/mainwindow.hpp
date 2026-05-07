#include <QEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>

class MyWindow : public QMainWindow {

public:
    explicit MyWindow() noexcept;
    ~MyWindow();

private:
    bool m_isDraging { false };
    QPoint last, latest, offset;

    void drawBoarder(QPainter& painter);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* press) override;
    void mouseMoveEvent(QMouseEvent* move) override;
    void mouseReleaseEvent(QMouseEvent* release) override;
    void paintEvent(QPaintEvent* paint) override;
};