#pragma once
#include "MathOperation.h"

class MultiplicationOperation : public MathOperation {
public:
    double execute(double a, double b) override {
        return a * b;
    }
};
