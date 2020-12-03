#pragma once

#include "../../physics/trigger/trigger.hpp"

class TunnelTrigger : public Trigger {
public:
    TunnelTrigger(GeasObject &owner, const Vec4 &rect, const std::string &destination, const std::string &descriptor);

    void on_trigger(GeasObject &with);

private:
    std::string destination, descriptor;
};