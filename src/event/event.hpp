#pragma once

class Event {
public:
    Event();
    virtual ~Event() =default;

    virtual bool should_run(float time) =0;
    virtual void run() =0;

    [[nodiscard]] bool should_delete() const;
    void should_delete(bool v);

private:
    bool _should_delete;
};