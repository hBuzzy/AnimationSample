#include "easingfunctions.h"

qreal EasingFunctions::CountLinear(qreal x) {
    return x;
}

qreal EasingFunctions::CountSquared(qreal x) {
    return x * x;
}

qreal EasingFunctions::CountSmoothSquared(qreal x) {
    qreal threshold = 0.5;
    int multiplier = 2;

    return x < threshold ? x * x * multiplier : (1 - (1 - x) * (1 - x) * multiplier);
}
