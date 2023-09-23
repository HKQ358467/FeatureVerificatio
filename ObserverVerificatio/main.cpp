#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // 添加这行以使用 std::find

class Observer {
public:
    virtual void update(const std::string& stockSymbol, float price) = 0;
};

class StockObserver : public Observer {
private:
    std::string name;

public:
    StockObserver(const std::string& observerName) : name(observerName) {}

    void update(const std::string& stockSymbol, float price) override {
        std::cout << "Observer " << name << " - Stock " << stockSymbol << " price updated to: " << price << std::endl;
    }
};

class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class StockMarket : public Subject {
private:
    std::string stockSymbol;
    float stockPrice;
    std::vector<Observer*> observers;

public:
    StockMarket(const std::string& symbol, float initialPrice) : stockSymbol(symbol), stockPrice(initialPrice) {}

    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers() override {
        for (auto observer : observers) {
            observer->update(stockSymbol, stockPrice);
        }
    }

    void setStockPrice(float newPrice) {
        stockPrice = newPrice;
        notifyObservers();
    }
};

int main() {
    StockMarket stockMarket("AAPL", 150.0);
    StockObserver investor1("Investor 1");
    StockObserver investor2("Investor 2");

    stockMarket.registerObserver(&investor1);
    stockMarket.registerObserver(&investor2);

    stockMarket.setStockPrice(155.0);
    stockMarket.setStockPrice(160.0);

    stockMarket.removeObserver(&investor1);

    stockMarket.setStockPrice(165.0);

    return 0;
}
