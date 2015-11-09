#pragma once

#include "timer.hpp"
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "timer_listener.hpp"

namespace cpptimer {
    
    class TimerImpl : public Timer {
        
    public:
        
        /** constructor */
        TimerImpl(const std::shared_ptr<TimerListener> & listener);
    
        void StartTimer(int32_t seconds);
        
    private:
        
        void TimerTick();
        
        std::shared_ptr<TimerListener> listener_;
        
        boost::asio::io_service io_service_;
        std::shared_ptr<boost::asio::io_service> io_service_ptr_;
        boost::asio::deadline_timer timer_;
        boost::thread io_thread_;
        int time_remaining_;
        
    };
    
}