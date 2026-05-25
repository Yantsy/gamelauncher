#pragma once

#include "MetaWidget.hpp"
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>

class MyMenu : public MetaWidget {
    Q_OBJECT
public:
    MyMenu(QWidget* parent = nullptr);
    ~MyMenu();
public slots:
private:
    QListWidget* optionList { nullptr };
    QStackedWidget* stacks { nullptr };
};