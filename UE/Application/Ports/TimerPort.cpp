#include "TimerPort.hpp"

namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{}

void TimerPort::start(ITimerEventsHandler &handler)
{
    logger.logDebug("Started");
    this->handler = &handler;
}

void TimerPort::stop()
{
    m_started = false;
    handler = nullptr;
    logger.logDebug("Stopped");
}

void TimerPort::startTimer(Duration duration)
{
    uint64_t my_counter = duration.count();
    m_started = true;
    logger.logDebug("Start timer: ", duration.count(), "ms");

     m_thread = std::thread([this, my_counter]()
    {
        uint64_t counter = my_counter;
        while (counter && m_started) {
            counter--;
            std::this_thread::sleep_for(std::chrono::milliseconds{1} );
        }

        if(handler != nullptr && m_started)
        {
            handler->handleTimeout();
        }
        m_started = false;
    });
    m_thread.detach();

}

void TimerPort::stopTimer()
{
    m_started = false;
    logger.logDebug("Stop timer");
}

}
