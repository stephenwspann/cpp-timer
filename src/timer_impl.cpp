#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "timer_impl.hpp"

namespace cpptimer {
    
    std::shared_ptr<Timer> Timer::CreateWithListener(const std::shared_ptr<TimerListener> & listener) {
        return std::make_shared<TimerImpl>(listener);
    }
    
    TimerImpl::TimerImpl(const std::shared_ptr<TimerListener> & listener):
            io_service_(),
            timer_(io_service_, boost::posix_time::seconds(1)) {
        listener_ = listener;
    }
    
    void TimerImpl::StartTimer(int32_t seconds) {
        time_remaining_ = seconds;
        io_service_.reset();
        timer_.async_wait(boost::bind(&TimerImpl::TimerTick, this, boost::asio::placeholders::error));
        boost::thread th([&] { io_service_.run(); });
    }
    
    void TimerImpl::TimerTick(const boost::system::error_code& e) {
        if(e != boost::asio::error::operation_aborted) {
            time_remaining_--;
            std:: cout << "C++: TimerTick() with " << std::to_string(time_remaining_) << " seconds remaining.\n";
            if (time_remaining_ > 0) {
                timer_.expires_from_now(boost::posix_time::seconds(1));
                timer_.async_wait(boost::bind(&TimerImpl::TimerTick, this, boost::asio::placeholders::error));
                listener_->TimerTicked(time_remaining_);
            } else {
                listener_->TimerEnded();
            }
        }
    }
    
}