#ifndef Profiler_H
#define Profiler_H
#include <chrono>
#include <stdexcept>
#include <functional>
#include <string>
//#include <thread>
#include <mutex>

//Just so we can treat ProfilerVariable<T> equally
class ProfilerVariableInterface
{
public:
    virtual std::string getSampleString(){return "";};
    virtual ~ProfilerVariableInterface(){};
};

/*
    This class represents a variable that can be profiled. That is,
    we can snapshot its value every `interval` seconds and then
    we can read it in a thread-safe way through getSampleString() or
    getSample if you know the type. 
    To use this, simply create an instance and call `profile` on this 
    instance every time you run your loop. You pass two funcions: one
    that will increase your `counter` every iteration, and one that will
    tell to what value to reset it.
    Example of a simple fps counter in a thread that renders things in a loop:

    ProfilerVariable<int> fps;
    while (...) {
        //render things here
        fps.profile([](int &counter){counter++;}, [](int& counter){counter=0;});
    }
    
*/
template <typename T>
class ProfilerVariable : public ProfilerVariableInterface
{
public:
    ProfilerVariable(int interval) : interval(interval)
    {
    }
    void profile(std::function<void(T &)> const &increaseFunction,
                 std::function<void(T &)> const &resetFunction)
    {
        auto now = std::chrono::system_clock::now();
        auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(now - before).count();
        if (difference >= interval)
        {
            snapshot();
            resetFunction(counter);
            before = std::chrono::system_clock::now();
        }
        increaseFunction(counter);
    }

    //To be executed at the end of the profiling period, takes a snapshot of counter
    void snapshot()
    {
        std::unique_lock<std::mutex> lock{mutex};
        sample = counter;
    }
    //TODO: return is safe????
    T getSample()
    {
        std::unique_lock<std::mutex> lock{mutex};
        return sample;
    }
    //To be shown as string, converts the generic T type to string
    std::string getSampleString() {
        return std::to_string(sample);
    }

    //Value to be increased at every profile call. `counter` can only be modified from one thread, not thread-safe
    T counter = 0;

private:
    //Value to store the result of the accumulated counter at the end of profile period
    T sample = 0;
    //Mutex for setting and reading sample.
    std::mutex mutex;
    //Stores the last profiler call time
    std::chrono::system_clock::time_point before;
    //Interval in milliseconds
    int interval;
};

#endif //Profiler_H