#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;
enum TrafficLightPhase {
    red,
    green,
};

// FP.3 
template <class T>
class MessageQueue
{
public:
    // typical behaviour methods
    void send(T &&msg);
    T receive(); 
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::deque<T> _queue;
};

// FP.1

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    // getters / setters
    TrafficLightPhase getCurrentPhase();
    void togglePhase();
    // typical behaviour methods
    void waitForGreen();
    void simulate();
private:
    // typical behaviour methods
    void cycleThroughPhases();
    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

    MessageQueue<TrafficLightPhase> _queue;
    std::condition_variable _condition;
    std::mutex _mutex;
    TrafficLightPhase _currentPhase;
};

#endif