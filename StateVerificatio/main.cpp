#include <iostream>

// 抽象状态基类
class TVState {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void nextChannel() = 0;
    virtual void prevChannel() = 0;
};

// 具体状态类：关机状态
class OffState : public TVState {
public:
    void turnOn() override;
    void turnOff() override {
        std::cout << "TV is already off." << std::endl;
    }
    void nextChannel() override {
        std::cout << "Can't change channel when TV is off." << std::endl;
    }
    void prevChannel() override {
        std::cout << "Can't change channel when TV is off." << std::endl;
    }
};

// 具体状态类：开机状态
class OnState : public TVState {
public:
    void turnOn() override {
        std::cout << "TV is already on." << std::endl;
    }
    void turnOff() override;
    void nextChannel() override;
    void prevChannel() override;
};

// 具体状态类：播放状态
class PlayingState : public TVState {
public:
    void turnOn() override {
        std::cout << "TV is already on." << std::endl;
    }
    void turnOff() override;
    void nextChannel() override;
    void prevChannel() override;
};

// 电视类，包含状态对象
class TV {
private:
    TVState* state;

public:
    TV() {
        state = new OffState(); // 初始状态为关机
    }

    void setState(TVState* newState) {
        delete state; // 释放旧状态
        state = newState;
    }

    void turnOn() {
        state->turnOn();
        setState(new OnState());
    }

    void turnOff() {
        state->turnOff();
        setState(new OffState());
    }

    void nextChannel() {
        state->nextChannel();
    }

    void prevChannel() {
        state->prevChannel();
    }
};

// 实现具体状态类的方法
void OffState::turnOn() {
    std::cout << "Turning on the TV." << std::endl;
}
void OnState::turnOff() {
    std::cout << "Turning off the TV." << std::endl;
}
void OnState::nextChannel() {
    std::cout << "Changing to the next channel." << std::endl;
}
void OnState::prevChannel() {
    std::cout << "Changing to the previous channel." << std::endl;
}
void PlayingState::turnOff() {
    std::cout << "Stopping the TV playback and turning off." << std::endl;
}
void PlayingState::nextChannel() {
    std::cout << "Changing to the next channel while playing." << std::endl;
}
void PlayingState::prevChannel() {
    std::cout << "Changing to the previous channel while playing." << std::endl;
}

int main() {
    TV tv;

    tv.turnOn();
    tv.nextChannel();
    tv.prevChannel();
    tv.turnOff();

    tv.turnOff(); // 试图关机，但已经关机
    tv.turnOn();
    tv.nextChannel();
    tv.turnOff(); // 关机
    tv.nextChannel(); // 试图切换频道，但已经关机

    return 0;
}
