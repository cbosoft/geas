#pragma once

#include "../geas_object/geas_object.hpp"
#include "../physics/trigger/trigger.hpp"

class Tunnel : public GeasObject {
public:
    Tunnel(Transform *t, const std::string &destination, const std::string &description, const std::string &transition);
};