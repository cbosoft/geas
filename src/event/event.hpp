#pragma once

class Event {
public:
    Event() =default;
    ~Event() =default;

    virtual bool should_run(float time) const =0;
    virtual void run() =0;

    [[nodiscard]] bool should_delete() const;
    void should_delete(bool v=true);

private:
    bool _should_delete;
};