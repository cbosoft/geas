#pragma once

#include "../../physics/trigger/trigger.hpp"

class TunnelTrigger : public Trigger {
public:
    TunnelTrigger(GeasObject &owner, const Vec4 &rect, const std::string &destination,
                  const std::string &descriptor, const std::string &transition);

    void on_trigger(GeasObject &with);

private:
    std::string _destination, _descriptor, _transition;
};