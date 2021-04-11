#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>

// observer - abstract class
//            update method needs to be implemented by observers

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};


class Observable {
private:
    std::vector<Observer*> observers;
public:
    virtual ~Observable() {}

    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        auto it = std::find(observers.begin(), observers.end(), obs);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notify() {
        for (auto obs : observers) {
            obs->update();
        }
    }
};

#endif // OBSERVER_H
