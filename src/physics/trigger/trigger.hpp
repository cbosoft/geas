#pragma once

#include "../physics.hpp"
#include "../collision/rectcollider.hpp"

class Trigger : public Physics {
public:
    Trigger(GeasObject &owner, const Vec4 &rect);
    ~Trigger() override =default;

    virtual void on_trigger(GeasObject &with) =0;

    [[nodiscard]] bool is_trigger() const override {return true;}

    void trigger(GeasObject &with);
    bool is_newly_triggered() const;
    void cache_value();

private:
    bool triggered, triggered_cache;
};