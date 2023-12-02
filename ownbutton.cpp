#include "ownbutton.h"
OwnButton::OwnButton(QWidget *parent) : QPushButton(parent) {}

QColor OwnButton::GetColor() const {
    return color_;
}

void OwnButton::SetColor(const QColor &newColor) {

    if (color_ == newColor)
        return;

    color_ = newColor;

    /*Задаем цвет кнопки*/
    setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                      .arg(color_.red())
                      .arg(color_.green())
                      .arg(color_.blue()));

    emit ColorChanged();
}
