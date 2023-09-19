#include <iostream>
#include <vector>

// 定义一个策略接口
class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
};

// 具体的支付策略类
class CreditCardPayment : public PaymentStrategy {
public:
    CreditCardPayment(const std::string& cardNumber, const std::string& name, const std::string& date)
        : cardNumber(cardNumber), name(name), date(date) {}

    void pay(double amount) override {
        std::cout << "Paid $" << amount << " with credit card ending in " << cardNumber << std::endl;
    }

private:
    std::string cardNumber;
    std::string name;
    std::string date;
};

class PayPalPayment : public PaymentStrategy {
public:
    PayPalPayment(const std::string& email) : email(email) {}

    void pay(double amount) override {
        std::cout << "Paid $" << amount << " via PayPal to " << email << std::endl;
    }

private:
    std::string email;
};

// 客户类，使用策略对象支付
class Customer {
public:
    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    void checkout(double amount) {
        if (paymentStrategy) {
            paymentStrategy->pay(amount);
        } else {
            std::cout << "No payment strategy set." << std::endl;
        }
    }

private:
    PaymentStrategy* paymentStrategy;
};

int main() {
    // 创建客户对象
    Customer customer;

    // 选择支付策略并进行支付
    CreditCardPayment creditCard("1234-5678-9012-3456", "John Doe", "12/25");
    PayPalPayment paypal("john.doe@example.com");

    customer.setPaymentStrategy(&creditCard);
    customer.checkout(100.0);

    customer.setPaymentStrategy(&paypal);
    customer.checkout(50.0);

    return 0;
}
