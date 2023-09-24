#include <iostream>
#include <string>

class Request {
public:
    Request(const std::string& type, const std::string& content)
            : type_(type), content_(content) {}

    std::string GetType() const {
        return type_;
    }

    std::string GetContent() const {
        return content_;
    }

private:
    std::string type_;
    std::string content_;
};

class Handler {
public:
    virtual ~Handler() {}
    virtual void HandleRequest(Request& request) = 0;
    void SetSuccessor(Handler* successor) {
        successor_ = successor;
    }

protected:
    Handler* successor_;
};

class ConcreteHandlerA : public Handler {
public:
    void HandleRequest(Request& request) override {
        if (request.GetType() == "TypeA") {
            std::cout << "ConcreteHandlerA is handling the request: " << request.GetContent() << std::endl;
        } else if (successor_) {
            successor_->HandleRequest(request);
        } else {
            std::cout << "No handler can process the request." << std::endl;
        }
    }
};

class ConcreteHandlerB : public Handler {
public:
    void HandleRequest(Request& request) override {
        if (request.GetType() == "TypeB") {
            std::cout << "ConcreteHandlerB is handling the request: " << request.GetContent() << std::endl;
        } else if (successor_) {
            successor_->HandleRequest(request);
        } else {
            std::cout << "No handler can process the request." << std::endl;
        }
    }
};

class ConcreteHandlerC : public Handler {
public:
    void HandleRequest(Request& request) override {
        if (request.GetType() == "TypeC") {
            std::cout << "ConcreteHandlerC is handling the request: " << request.GetContent() << std::endl;
        } else if (successor_) {
            successor_->HandleRequest(request);
        } else {
            std::cout << "No handler can process the request." << std::endl;
        }
    }
};

int main() {
    Handler* handlerA = new ConcreteHandlerA();
    Handler* handlerB = new ConcreteHandlerB();
    Handler* handlerC = new ConcreteHandlerC();

    handlerA->SetSuccessor(handlerB);
    handlerB->SetSuccessor(handlerC);

    Request request1("TypeA", "Request 1");
    Request request2("TypeB", "Request 2");
    Request request3("TypeD", "Request 3"); // This type is not handled

    handlerA->HandleRequest(request1);
    handlerA->HandleRequest(request2);
    handlerA->HandleRequest(request3);

    delete handlerA;
    delete handlerB;
    delete handlerC;

    return 0;
}
