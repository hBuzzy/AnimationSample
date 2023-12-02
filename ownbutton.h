#ifndef OWNBUTTON_H
#define OWNBUTTON_H

#include <QPushButton>

class OwnButton : public QPushButton {
    Q_OBJECT

    /*Создаем свойство для того, чтобы потом его использовать в QPropertyAnimation*/
    Q_PROPERTY(QColor color READ GetColor WRITE SetColor NOTIFY ColorChanged FINAL)
public:
    OwnButton(QWidget *parent = nullptr);
    QColor GetColor() const;
    void SetColor(const QColor &newColor);

signals:
    void ColorChanged();

private:
    QColor color_;
};

#endif // OWNBUTTON_H
