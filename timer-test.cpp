#include "timer.hpp"

void tick() {
    std::cout<<"tick"<<std::endl;
}

int main() {
    Timer t(tick, 2);
    t.run();
    std::this_thread::sleep_for(1s);
    t.set_fps(8);
    std::this_thread::sleep_for(1s);
    t.set_fps(0);
    std::this_thread::sleep_for(1s);
    t.set_fps(2);
    std::this_thread::sleep_for(1s);
}
