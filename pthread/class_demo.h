#ifndef __CLASS_DEMO_H
#define __CLASS_DEMO_H

class Demo {
public:
    Demo() = default;
    ~Demo() = default;

    static void * thread_func(void * arg);
    void process_func();
    int value() const;

private:
    int num__;
};

#endif
