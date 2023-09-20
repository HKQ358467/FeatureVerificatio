#pragma once
#include "MathOperation.h"

class DivisionOperation : public MathOperation {
public:
    double execute(double a, double b) override {
        if (b != 0) {
            return a / b;
        }
        else {
            throw std::invalid_argument("Division by zero");
        }
    }
};
