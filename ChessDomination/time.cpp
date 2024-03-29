#include <ctime>
#include <cassert>

class Time
{
	public:
   	Time(int hour, int min, int sec);
		Time();

		int get_hours() const;
		int get_minutes() const;
		int get_seconds() const;

	   long seconds_from(Time t) const;
 	   void add_seconds(long s);

	private:
   	long time_in_secs;
};

static long remainder(long a, long n)
{  
	if (a >= 0)
      return a % n;
   else
      return n - 1 - (-a - 1) % n;
}

Time::Time(int hour, int min, int sec)
{  
	assert(0 <= hour);
   assert(hour < 24);
   assert(0 <= min);
   assert(min < 60);
   assert(0 <= sec);
   assert(sec < 60);

   time_in_secs = 60L * 60 * hour + 60 * min + sec;
}

Time::Time()
{  
	time_t now = time(0);
   struct tm& t = *localtime(&now);
   time_in_secs = 60L * 60 * t.tm_hour + 60 * t.tm_min + t.tm_sec;
}

int Time::get_hours() const
{  
	return time_in_secs / (60 * 60);
}

int Time::get_minutes() const
{  
	return (time_in_secs / 60) % 60;
}

int Time::get_seconds() const
{  
	return time_in_secs % 60;
}

long Time::seconds_from(Time t) const
{  
	return time_in_secs - t.time_in_secs;
}

void Time::add_seconds(long s)
{  
	const long SECONDS_PER_DAY = 60L * 60 * 24;
   time_in_secs = remainder(time_in_secs + s, SECONDS_PER_DAY);
}
