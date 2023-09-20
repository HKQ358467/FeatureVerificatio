#include <iostream>
#include "AdditionOperation.h"
#include "SubtractionOperation.h"
#include "MultiplicationOperation.h"
#include "DivisionOperation.h"
#include "Calculator.h"

int main() {
    AdditionOperation add;
    SubtractionOperation subtract;
    MultiplicationOperation multiply;
    DivisionOperation divide;

    Calculator calculator(&add);
    std::cout << "Addition: " << calculator.calculate(5.0, 3.0) << std::endl;

    calculator.setOperation(&subtract);
    std::cout << "Subtraction: " << calculator.calculate(5.0, 3.0) << std::endl;

    calculator.setOperation(&multiply);
    std::cout << "Multiplication: " << calculator.calculate(5.0, 3.0) << std::endl;

    calculator.setOperation(&divide);
    try {
        std::cout << "Division: " << calculator.calculate(5.0, 1.0) << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
