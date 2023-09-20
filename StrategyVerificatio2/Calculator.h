#pragma once
#include "MathOperation.h"

class Calculator {
public:
    Calculator(MathOperation* operation) : operation_(operation) {}

    void setOperation(MathOperation* operation) {
        operation_ = operation;
    }

    double calculate(double a, double b) {
        return operation_->execute(a, b);
    }

private:
    MathOperation* operation_;
};
