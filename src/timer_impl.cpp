#include "timer_impl.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <thread>

namespace cpptimer {
    
    using namespace boost;
    
    std::shared_ptr<Timer> Timer::CreateWithListener(const std::shared_ptr<TimerListener> & listener) {
        return std::make_shared<TimerImpl>(listener);
    }
    
    /*
     * Attempt 1: io_.run() causes a block on the viewDidLoad() thread in Obj-C
     * example from boost docs: http://www.boost.org/doc/libs/1_40_0/doc/html/boost_asio/tutorial/tuttimer2.html
     */
    
    /*
    TimerImpl::TimerImpl(const std::shared_ptr<TimerListener> & listener):
            io_service_(), timer_(io_service_, boost::posix_time::seconds(1)) {
        listener_ = listener;
    }
    
    void TimerImpl::StartTimer(int32_t seconds) {
        
        time_remaining_ = seconds;
        
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&TimerImpl::TimerTick, this));
        
        // boost::asio::io_service::run() is a blocking call
        io_service_.run();

    }
    
    void TimerImpl::TimerTick() {
        time_remaining_--;
        std:: cout << "C++: TimerTick() with " << std::to_string(time_remaining_) << " seconds remaining.\n";
        if (time_remaining_ > 0) {
            timer_.expires_from_now(boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&TimerImpl::TimerTick, this));
            listener_->TimerTicked(time_remaining_);
        } else {
            listener_->TimerEnded();
        }
    }
    */
     
    /*
     * Attempt 2: assign boost::asio::io_service::run() to its own thread
     */
    
    TimerImpl::TimerImpl(const std::shared_ptr<TimerListener> & listener):
    io_service_(), timer_(io_service_, boost::posix_time::seconds(1)) {
        listener_ = listener;
    }
    
    void TimerImpl::StartTimer(int32_t seconds) {
        
        time_remaining_ = seconds;
        
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&TimerImpl::TimerTick, this));
        
        // boost::asio::io_service::run() on its own thread
        // th.join() still causes a block.
        std::thread th([&] { io_service_.run(); });
        th.join();
    }
    
    void TimerImpl::TimerTick() {
        time_remaining_--;
        std:: cout << "C++: TimerTick() with " << std::to_string(time_remaining_) << " seconds remaining.\n";
        if (time_remaining_ > 0) {
            timer_.expires_from_now(boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&TimerImpl::TimerTick, this));
            listener_->TimerTicked(time_remaining_);
        } else {
            listener_->TimerEnded();
        }
    }
    
    /*
     * Attempt 3 (Broken): use boost::asio::io_service::post() with io_service in another thread
     * http://stackoverflow.com/questions/17321506/c-non-blocking-asio-run
     */
    
    /*
    TimerImpl::TimerImpl(const std::shared_ptr<TimerListener> & listener):
            io_service_(), timer_(io_service_, boost::posix_time::seconds(1)) {
        listener_ = listener;
    }
    
    void TimerImpl::StartTimer(int32_t seconds) {
        
        time_remaining_ = seconds;

        shared_ptr<asio::io_service::work> work(new asio::io_service::work(io_service_));
        
        // Compiler Error: No matching constructor for initialization of 'boost::thread'
        boost::thread t(&asio::io_service::run, &io_service_);
        
        // detach from current thread
        t.detach();
        
        // Compiler Error: No matching member function for call to 'post'
        io_service_.post(TimerImpl::TimerTick());
        
    }
    
    void TimerImpl::TimerTick() {
        time_remaining_--;
        std:: cout << "C++: TimerTick() with " << std::to_string(time_remaining_) << " seconds remaining.\n";
        if (time_remaining_ > 0) {
            listener_->TimerTicked(time_remaining_);
        } else {
            listener_->TimerEnded();
        }
    }
     */
    
}