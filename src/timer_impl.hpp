#pragma once

#include <boost/asio.hpp>

#include "timer.hpp"
#include "timer_listener.hpp"

namespace cpptimer {
    
    class TimerImpl : public Timer {
        
    public:
        
        /** constructor */
        TimerImpl(const std::shared_ptr<TimerListener> & listener);
    
        void StartTimer(int32_t seconds);
        
    private:
        
        void TimerTick(const boost::system::error_code& e);
        
        std::shared_ptr<TimerListener> listener_;
        
        boost::asio::io_service io_service_;
        boost::asio::deadline_timer timer_;
        int time_remaining_;
        
    };
    
}