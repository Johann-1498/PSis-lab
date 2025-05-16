#ifndef PUNTO_H
#define PUNTO_H

struct Punto {
    double x;
    double y;
    Punto(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}
};

#endif