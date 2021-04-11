#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>


class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};


class Subject {
private:
    std::vector<Observer*> observers;
public:
    virtual ~Subject() {}
    void add_observer(Observer* obs) {
        this->observers.push_back(obs);
    }
    void remove_observer(Observer* obs) {
        auto it = std::find(this->observers.begin(), this->observers.end(), obs);
        if (it != this->observers.end()) {
            this->observers.erase(it);
        }
    }
    void notify() {
        for (auto obs : this->observers) {
            obs->update();
        }
    }
};


#endif // OBSERVER_H
