#pragma once

#include "timer.hpp"

namespace cpptimer {
    
    class TimerImpl : public Timer {
        
    public:
        
        /** constructor */
        TimerImpl(const std::shared_ptr<TimerListener> & listener);
    
        void StartTimer(int32_t seconds);
        
    private:
        
        std::shared_ptr<TimerListener> listener_;
        
    };
    
}