#define BOOST_TIMER_ENABLE_DEPRECATED 
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <boost/date_time/gregorian/gregorian.hpp> // 处理日期的组件
#include <boost/date_time/posix_time/posix_time.hpp>  // 处理时间的组件
using namespace std;
using namespace boost;
using namespace boost::gregorian;

// day-2025-6-11 
// 第二章-日期和时间

// 日期
//int main()
//{
	//date d1;
	//date d2(2010, 1, 1);
	//date d3(2000, Jan, 1);
	//date d4(d2);
	//assert(d1 == date(not_a_date_time));
	//assert(d2 == d4);
	//assert(d3 < d4);

	//cout << day_clock::local_day() << endl;
	//cout << day_clock::universal_day() << endl;
	//date d5(neg_infin);
	//cout << d5 << endl;
	//date d6(pos_infin);
	//cout << d6 << endl;
	//cout << date(not_a_date_time) << endl;
	//cout << date(max_date_time) << endl;
	//cout << date(min_date_time) << endl;

	//cout << date(1399, 12, 1) << endl;

	//date::ymd_type ymd = d3.year_month_day();
	//assert(ymd.year == 2000);
	//assert(ymd.month == 1);
	//assert(ymd.day == 1);

	//cout << d3.day_of_week() << endl;
	//cout << d3.day_of_year() << endl;

	//cout << date(2025, 6, 11).week_number() << endl;

	//date d(2025, 6, 11);
	//cout << to_simple_string(d) << endl;
	//cout << to_iso_string(d) << endl;
	//cout << to_iso_extended_string(d) << endl;
	//cout << d << endl;

	//date d(2017, 5, 20);
	//tm t = to_tm(d);
	//assert(t.tm_hour == 0 && t.tm_min == 0);
	//assert(t.tm_year == 117 && t.tm_mday == 20);

	//date d2 = date_from_tm(t);
	//assert(d == d2);
//}


/*
class progress_timer : public timer
{
private:

	progress_timer(progress_timer const&);
	progress_timer& operator=(progress_timer const&);

public:
	explicit progress_timer(std::ostream& os = std::cout)
		// os is hint; implementation may ignore, particularly in embedded systems
		: timer(), m_os(os) {
	}
	~progress_timer()
	{
		//  A) Throwing an exception from a destructor is a Bad Thing.
		//  B) The progress_timer destructor does output which may throw.
		//  C) A progress_timer is usually not critical to the application.
		//  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
		try
		{
			// use istream instead of ios_base to workaround GNU problem (Greg Chicares)
			std::istream::fmtflags old_flags = m_os.setf(std::istream::fixed,
				std::istream::floatfield);
			std::streamsize old_prec = m_os.precision(2);
			m_os << elapsed() << " s\n" // "s" is System International d'Unites std
				<< std::endl;
			m_os.flags(old_flags);
			m_os.precision(old_prec);
		}

		catch (...) {} // eat any exceptions
	} // ~progress_timer

private:
	std::ostream& m_os;
};
*/

//int main()
//{
//	{	//第一个计时
//		boost::progress_timer t;
//	}
//	{	//第二个计时
//		boost::progress_timer t;
//	}
//}

/*
class timer
{
public:
	timer() { _start_time = std::clock(); } 
	//         timer( const timer& src );     
	//        ~timer(){}
	//  timer& operator=( const timer& src );  
	void   restart() { _start_time = std::clock(); } 
	double elapsed() const                 
	{
		return  double(std::clock() - _start_time) / CLOCKS_PER_SEC;
	}

	double elapsed_max() const  
	{
		return (double((std::numeric_limits<std::clock_t>::max)())
			- double(_start_time)) / double(CLOCKS_PER_SEC);
	}

	double elapsed_min() const           
	{
		return double(1) / double(CLOCKS_PER_SEC);
	}

private:
	std::clock_t _start_time;
};	// timer
*/

//int main()
//{
//	timer t;
//
//	cout << "max timespan: "					// 可度量的最大时间, 以 小时为单位
//		<< t.elapsed_max() / 3600 << "h" << endl;
//
//	cout << "min timespan: "
//		<< t.elapsed_min() << "s" << endl;
//
//	cout << "now time elapsed: "
//		<< t.elapsed() << "s" << endl;
//
//}