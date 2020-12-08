#pragma once

class Ability {
public:
    Ability() =default;
    virtual ~Ability() =default;

    virtual void acquire() =0;
    virtual void lose() =0;

    virtual void use() =0;
};