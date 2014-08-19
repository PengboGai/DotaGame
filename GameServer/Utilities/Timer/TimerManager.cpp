#include <algorithm>
#include "TimerManager.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace Utilities {

TimerManager::TimerManager()
: m_last_ttime(TickTime())
{
}

TimerManager::~TimerManager()
{
	Clear();
}

void TimerManager::Tick()
{
	if (m_timers.empty()) {
		return;
	}

	time_t tnow = TickTime();
	time_t dt = (tnow - m_last_ttime) / 1000;
	m_last_ttime = tnow;
	auto iter = m_timers.begin();
	for (; iter < m_timers.end();) {
		if (!(*iter)->Update(dt)) {
			iter = m_timers.erase(iter);
		}
		else {
			++iter;
		}
	}
}

void TimerManager::AddTimer(Timer* timer)
{
	auto iter = std::find(m_timers.begin(), m_timers.end(), timer);
	if (iter == m_timers.end()) {
		m_timers.push_back(timer);
	}
}

time_t TimerManager::TickTime()
{
	time_t t;
#ifdef _WIN32
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	t = ft.dwHighDateTime;
	t = t << 32;
	t += ft.dwLowDateTime;
	t /= 10;
#else
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	t = tv.tv_sec;
	t *= 1000000;
	t += tv.tv_usec;
#endif
	return t;
}

void TimerManager::Clear()
{
	auto iter = m_timers.begin();
	for (; iter != m_timers.end(); ++iter) {
		delete (*iter);
		(*iter) = nullptr;
	}
	m_timers.clear();
}

} // namespace Utilities