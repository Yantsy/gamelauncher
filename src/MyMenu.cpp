#include "MyMenu.hpp"

MyMenu::MyMenu(QWidget* parent) {
    auto mainLayout = QHBoxLayout(this);
    optionList      = new QListWidget();
    stacks          = new QStackedWidget();
    mainLayout.addWidget(optionList);
    mainLayout.addWidget(stacks);
}