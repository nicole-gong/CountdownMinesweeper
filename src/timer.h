#ifndef TIMER_H 
#define TIMER_H

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

class Timer {
public:
    bool running;
    Timer() : timeLimit(baseTime), running(false) {}
    
    void start() {
        running = true;
        clock.restart();
    }

    void reset(int flags) {
        clock.restart();
        float decayFactor = std::pow(decay, flags);
        timeLimit = sf::seconds(baseTime.asSeconds() * decayFactor);
    }

    sf::Time getRemaining() {
        if (running)
            return timeLimit - clock.getElapsedTime();
        else
            return timeLimit;
    }

private:
    sf::Time baseTime = sf::seconds(15);
    sf::Clock clock;
    sf::Time remainingTime;
    sf::Time timeLimit;
    float decay = .9f;
};

#endif