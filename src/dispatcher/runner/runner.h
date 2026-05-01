#ifndef RUNNER_H
#define RUNNER_H

class Runner {
    virtual void run() = 0;
};

template <typename OBJECT, typename FUNCTION, typename... ARGS>
class RunnerImpl : public Runner {
public:
    RunnerImpl(OBJECT *object, OBJECT::FUNCTION function, ARGS... args)
        : m_object(object), m_function(function), m_args(args...) {}

    void run() override { (m_object->*m_function)(m_args...); }

private:
    OBJECT *m_object;
    OBJECT::FUNCTION m_function;
    std::tuple<ARGS...> m_args;
};

#endif  // RUNNER_H