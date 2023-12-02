#ifndef EASINGFUNCTIONS_H
#define EASINGFUNCTIONS_H

#include <QObject>

class EasingFunctions : public QObject {
    Q_OBJECT
public:
    static qreal CountLinear(qreal x);
    static qreal CountSquared(qreal x);
    static qreal CountSmoothSquared(qreal x);
};

#endif // EASINGFUNCTIONS_H
