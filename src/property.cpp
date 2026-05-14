#pragma once
#include <QSize>
#include <QStyle>
#include <QWidget>

struct Property {
    virtual void apply(QWidget& widget) const = 0;
};

template <typename T>
concept property_concept = std::is_base_of_v<Property, T>;
class Widget : public QWidget {
public:
    template <property_concept... Props>
    explicit Widget(QWidget* parent, Props&&... props)
        : QWidget(parent) {
        (props.apply(*this), ...); // 折叠表达式，依次调用每个 property 的 apply
    }

    // 或者无 parent 版本
    template <property_concept... Props>
    explicit Widget(Props&&... props)
        : QWidget(nullptr) {
        (props.apply(*this), ...);
    }
};
namespace pro {
struct MinimumSize final : public QSize, Property {
    using QSize::QSize;
    void apply(QWidget& widget) const override { widget.setMinimumSize(*this); }
};

struct MaximumSize final : public QSize, Property {
    using QSize::QSize;
    void apply(QWidget& widget) const override { widget.setMaximumSize(*this); }
};
struct SizeIncrement final : public QSize, Property {
    using QSize::QSize;
    void apply(QWidget& widget) const override { widget.setSizeIncrement(*this); }
};

}

// pro为 property 的简写，保留 Widget 默认构造的同时，拓展构造的功能性，在构造的同时配置属性
int main() {
    //...
    auto widget0 = new Widget {
        pro::MinimumSize { 100, 100 },
        pro::MaximumSize { 200, 200 },
    };
    //...
}