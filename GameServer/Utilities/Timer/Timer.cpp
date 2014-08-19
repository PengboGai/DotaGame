#include "Timer.h"

namespace Utilities {

Timer::Timer(TIMER_CALLBACK callback, time_t interval)
: m_callback(callback)
, m_interval(interval)
, m_repeat(Timer::NO_REPEAT)
, m_elapsed(0)
{
}

Timer::Timer(TIMER_CALLBACK callback, time_t interval, int repeat)
: m_callback(callback)
, m_interval(interval)
, m_repeat(repeat)
, m_elapsed(0)
{
}

Timer::~Timer()
{
}

bool Timer::Update(time_t dt)
{
	if (m_repeat <= 0 && m_repeat != Timer::REPEAT_FOREVER) {
		return false;
	}

	m_elapsed += dt;
	if (m_elapsed >= m_interval) {
		m_callback(m_elapsed);
		m_elapsed = 0;
		
		if (m_repeat != Timer::REPEAT_FOREVER) {
			--m_repeat;
		}
	}
	return true;
}

} // namespace Utilities