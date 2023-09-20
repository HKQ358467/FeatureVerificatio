#pragma once

class MathOperation {
public:
    virtual double execute(double a, double b) = 0;
    virtual ~MathOperation() {}
};