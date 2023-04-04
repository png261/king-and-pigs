#pragma once

class Callback
{
public:
    virtual void call() = 0;
};

class StaticCallback : public Callback
{
public:
    StaticCallback(void (*func)())
        : m_func(func)
    {}

    virtual void call() { m_func(); }

private:
    void (*m_func)();
};
