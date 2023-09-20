#pragma once
#include "MathOperation.h"

class SubtractionOperation : public MathOperation {
public:
    double execute(double a, double b) override {
        return a - b;
    }
};
