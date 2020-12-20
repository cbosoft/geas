#include "tunnel.hpp"
#include "tunnel_trigger/tunnel_trigger.hpp"

Tunnel::Tunnel(Transform *parent,
               const std::string &destination,
               const std::string &descriptor,
               const std::string &transition)
    :   GeasObject(parent)
{
    this->physics = new TunnelTrigger(*this, Vec4({0.0,0.0, 32, 32}), destination, descriptor, transition);
}