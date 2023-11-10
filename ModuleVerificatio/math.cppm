import math;

int main() {
    int x = 10, y = 5;
    int sum = add(x, y);
    int difference = subtract(x, y);
    int product = multiply(x, y);
    int quotient = divide(x, y);

    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);
    printf("Product: %d\n", product);
    printf("Quotient: %d\n", quotient);

    return 0;
}