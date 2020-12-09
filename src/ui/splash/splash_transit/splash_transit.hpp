#pragma once

#include <string>
#include "../../../event/event.hpp"

class SplashTransit : public Event {
public:
    SplashTransit(const std::string &dest, float delay);

    bool should_run(float time) override;
    void run() override;

private:
    std::string _dest;
    float _trigger_time;
};