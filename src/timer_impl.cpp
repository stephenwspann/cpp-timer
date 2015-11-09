#include "timer_impl.hpp"

namespace cpptimer {
    
    std::shared_ptr<Timer> Timer::CreateWithListener(const std::shared_ptr<TimerListener> & listener) {
        return std::make_shared<TimerImpl>(listener);
    }
    
    TimerImpl::TimerImpl(const std::shared_ptr<TimerListener> & listener) {
        listener_ = listener;
    }
    
    void TimerImpl::StartTimer(int32_t seconds) {
        
    }
    
}