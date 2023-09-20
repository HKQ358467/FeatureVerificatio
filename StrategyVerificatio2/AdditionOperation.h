#pragma once
#include "MathOperation.h"

class AdditionOperation : public MathOperation {
public:
    double execute(double a, double b) override {
        return a + b;
    }
};
