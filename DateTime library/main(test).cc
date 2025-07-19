#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include "datetime.h"

using namespace DateTime;

void TestAll();

int main() {
	TestAll();
	return 0;
}

// Tests

void TestTime();
void TestDate();
void TestDateTime();
void TestTimediff();

void TestAll() {
	try {
		TestTime();
		TestDate();
		TestDateTime();
		TestTimediff();
	}
	catch (...) {
		assert(false); // unknown exception
	}
}

/*
	Tests for class `time`
*/
void TestTime() {
	{   // Valid time 00:01:02
		DateTime::time tm(0, 1, 2);
		assert(0 == tm.hour());
		assert(1 == tm.minute());
		assert(2 == tm.second());
		assert(std::string("00:01:02") == DateTime::to_string(tm));
	}

	{   // Valid time 00:00:00
		DateTime::time tm(0, 0, 0);
		assert(0 == tm.hour());
		assert(0 == tm.minute());
		assert(0 == tm.second());
		assert(std::string("00:00:00") == DateTime::to_string(tm));
	}

	{   // Valid time 23:59:59
		DateTime::time tm(23, 59, 59);
		assert(23 == tm.hour());
		assert(59 == tm.minute());
		assert(59 == tm.second());
		assert(std::string("23:59:59") == DateTime::to_string(tm));
	}

	{   // Invalid time
		try {
			DateTime::time tm(23, 59, 60);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time
		try {
			DateTime::time tm(23, 60, 59);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time
		try {
			DateTime::time tm(24, 10, 9);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time (negative)
		try {
			DateTime::time tm1(-11, 10, 9);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time (negative)
		try {
			DateTime::time tm1(11, -10, 9);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time (negative)
		try {
			DateTime::time tm1(11, 10, -9);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Add 10 hours
		DateTime::time tm(0, 0, 0);
		tm.add_hours(10);
		assert(10 == tm.hour());
		assert(0 == tm.minute());
		assert(0 == tm.second());
		assert(std::string("10:00:00") == DateTime::to_string(tm));
	}

	{   // Add 61 minutes
		DateTime::time tm(0, 0, 0);
		tm.add_minutes(61);
		assert(std::string("01:01:00") == DateTime::to_string(tm));
	}

	{   // Add 4321 seconds
		DateTime::time tm(0, 0, 0);
		tm.add_seconds(4321);
		assert(std::string("01:12:01") == DateTime::to_string(tm));
	}

	{   // Add -72 seconds
		DateTime::time tm(1, 1, 1);
		tm.add_seconds(-72);
		assert(std::string("00:59:49") == DateTime::to_string(tm));
	}

	{   // Add 10 seconds to 23:59:58
		DateTime::time tm(23, 59, 58);
		tm.add_seconds(10);
		assert(23 == tm.hour());
		assert(59 == tm.minute());
		assert(59 == tm.second());
		assert(std::string("23:59:59") == DateTime::to_string(tm));
	}

	{   // Add -10 seconds to 00:00:01
		DateTime::time tm(0, 0, 1);
		tm.add_seconds(-10);
		assert(0 == tm.hour());
		assert(0 == tm.minute());
		assert(0 == tm.second());
		assert(std::string("00:00:00") == DateTime::to_string(tm));
	}

	{   // Time operators
		DateTime::time tm1(12, 50, 0);
		DateTime::time tm2(13, 40, 0);
		DateTime::time tm3(tm1);
		assert(tm1 == tm3);
		assert(tm1 != tm2);
		assert(tm1 < tm2);
		assert(tm1 <= tm2);
		assert(tm1 <= tm3);
		assert(tm2 > tm1);
		assert(tm2 >= tm3);
		assert(tm1 >= tm3);
	}

	std::cout << "TestTime OK" << std::endl;
}

/*
	Tests for class `date`
*/

void TestDate() {
	{   // Valid date 2025.02.01
		DateTime::date dt(2025, 2, 1);
		assert(2025 == dt.year());
		assert(2 == dt.month());
		assert(1 == dt.day());
		assert(DateTime::weekday::saturday == dt.weekday());
		assert(false == dt.is_leapyear());
		assert(std::string("2025.02.01") == DateTime::to_string(dt));
	}

	{   // Invalid dates. Throw invalid argument exception
		try {
			DateTime::date dt1(2025, 13, 10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}


	{   // Invalid dates. Throw invalid argument exception
		try {
			DateTime::date dt2(2025, 0, 10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid dates. Throw invalid argument exception
		try {
			DateTime::date dt3(2025, -1, 10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid dates. Throw invalid argument exception
		try {
			DateTime::date dt4(2025, 1, -10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid dates. Throw invalid argument exception
		try {
			DateTime::date dt5(2025, 1, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid day 32 for months with 31 days. Throw invalid argument exception
		int month_to_check_31[] = { 1, 3, 5, 7, 8, 10, 12 };
		for (int i : month_to_check_31) {
			try {
				DateTime::date dt1(2025, i, 32);
				assert(false);
			}
			catch (const std::invalid_argument& error) {
			}
			catch (...) {
				assert(false);
			}
		}
	}

	{   // Invalid day 31 for months with 30 days. Throw invalid argument exception
		int month_to_check_30[] = { 4, 6, 9, 11 };
		for (int i : month_to_check_30) {
			try {
				DateTime::date dt1(2025, i, 31);
				assert(false);
			}
			catch (const std::invalid_argument& error) {
			}
			catch (...) {
				assert(false);
			}
		}
	}

	{   // Invalid day 30 for february. Throw invalid argument exception
		bool res{ true };
		try {
			DateTime::date dt1(2000, 2, 30);
			assert(res == false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(res == false);
		}
	}

	{   // Valid day 29 for february. Throw invalid argument exception
		DateTime::date dt(2000, 2, 29);
		assert(2000 == dt.year());
		assert(2 == dt.month());
		assert(29 == dt.day());
		assert(DateTime::weekday::tuesday == dt.weekday());
		assert(true == dt.is_leapyear());
		assert(std::string("2000.02.29") == DateTime::to_string(dt));
	}

	{   // Valid day 29 for february. Throw invalid argument exception
		DateTime::date dt(2024, 2, 29);
		assert(2024 == dt.year());
		assert(2 == dt.month());
		assert(29 == dt.day());
		assert(DateTime::weekday::thursday == dt.weekday());
		assert(true == dt.is_leapyear());
		assert(std::string("2024.02.29") == DateTime::to_string(dt));
	}

	{ // Add days
		DateTime::date dt(2019, 12, 31);
		dt.add_days(60);
		assert(std::string("2020.02.29") == DateTime::to_string(dt));
	}

	{ // Add days
		DateTime::date dt(2019, 12, 31);
		dt.add_days(61);
		assert(std::string("2020.03.01") == DateTime::to_string(dt));
	}

	{ // Add days
		DateTime::date dt(2020, 3, 1);
		dt.add_days(-61);
		assert(std::string("2019.12.31") == DateTime::to_string(dt));
	}

	{   // Next date
		DateTime::date dt1(2024, 2, 29);
		DateTime::date dt2 = dt1.next();
		assert(std::string("2024.02.29") == DateTime::to_string(dt1));
		assert(std::string("2024.03.01") == DateTime::to_string(dt2));
	}

	{   // Next date
		DateTime::date dt1(2025, 2, 28);
		DateTime::date dt2 = dt1.next();
		assert(std::string("2025.02.28") == DateTime::to_string(dt1));
		assert(std::string("2025.03.01") == DateTime::to_string(dt2));
	}

	{   // Next date
		DateTime::date dt1(2024, 3, 31);
		DateTime::date dt2 = dt1.next();
		assert(std::string("2024.03.31") == DateTime::to_string(dt1));
		assert(std::string("2024.04.01") == DateTime::to_string(dt2));
	}


	{   // Prev date
		DateTime::date dt1(2024, 3, 1);
		DateTime::date dt2 = dt1.prev();
		assert(std::string("2024.03.01") == DateTime::to_string(dt1));
		assert(std::string("2024.02.29") == DateTime::to_string(dt2));
	}

	{   // Prev date
		DateTime::date dt1(2025, 3, 1);
		DateTime::date dt2 = dt1.prev();
		assert(std::string("2025.03.01") == DateTime::to_string(dt1));
		assert(std::string("2025.02.28") == DateTime::to_string(dt2));
	}

	{   // Prev date
		DateTime::date dt1(2024, 4, 1);
		DateTime::date dt2 = dt1.prev();
		assert(std::string("2024.04.01") == DateTime::to_string(dt1));
		assert(std::string("2024.03.31") == DateTime::to_string(dt2));
	}

	{   // Next and prev dates
		DateTime::date dtp(2023, 12, 31);
		DateTime::date dt(2024, 1, 1);
		DateTime::date dtn(2024, 1, 2);
		for (int i = 0; i < 1000; ++i) {
			DateTime::date cur = dtp.next();
			assert(cur == dt);
			cur = dt.next();
			assert(cur == dtn);
			cur = dt.prev();
			assert(cur == dtp);
			cur = dtn.prev();
			assert(cur == dt);
			dtp = dtp.next();
			assert(dtp == dt);
			dt = dt.next();
			assert(dt == dtn);
			dtn = dt.next();
		}
	}

	{   // Pre-Increment test 
		DateTime::date dt(2023, 12, 31);
		DateTime::date dtn(2024, 1, 1);
		for (int i = 0; i < 1000; ++i) {
			assert(++dt == dtn);
			dtn = dtn.next();
		}
	}

	{   // Post-Increment test 
		DateTime::date dt(2023, 12, 31);
		DateTime::date dtn(2024, 1, 1);
		for (int i = 0; i < 1000; ++i) {
			dt++;
			assert(dt == dtn);
			dtn = dtn.next();
		}
	}

	{   // Post-Increment test 
		DateTime::date dt(2023, 12, 31);
		DateTime::date dtn = dt;
		for (int i = 0; i < 1000; ++i) {
			assert(dt++ == dtn);
			dtn = dtn.next();
		}
	}

	{   // Pre-decrement test 
		DateTime::date dt(2025, 1, 1);
		DateTime::date dtp(2024, 12, 31);
		for (int i = 0; i < 1000; ++i) {
			assert(--dt == dtp);
			dtp = dtp.prev();
		}
	}

	{   // Post-decrement test 
		DateTime::date dt(2025, 1, 1);
		DateTime::date dtp(2024, 12, 31);
		for (int i = 0; i < 1000; ++i) {
			dt--;
			assert(dt == dtp);
			dtp = dtp.prev();
		}
	}

	{   // Post-decrement test 
		DateTime::date dt(2023, 12, 31);
		DateTime::date dtn = dt;
		for (int i = 0; i < 1000; ++i) {
			assert(dt-- == dtn);
			dtn = dtn.prev();
		}
	}

	{   // Is leap tests
		assert(DateTime::date::is_leapyear(2025) == false);
		assert(DateTime::date::is_leapyear(2024) == true);
		assert(DateTime::date::is_leapyear(2023) == false);
		assert(DateTime::date::is_leapyear(2020) == true);
		assert(DateTime::date::is_leapyear(2019) == false);
		assert(DateTime::date::is_leapyear(2000) == true);
		assert(DateTime::date::is_leapyear(1999) == false);
		assert(DateTime::date::is_leapyear(1900) == false);
		assert(DateTime::date::is_leapyear(1800) == false);
		assert(DateTime::date::is_leapyear(1600) == true);
	}

	{
		DateTime::date dt1 = date(2025, 2, 11);
		DateTime::date dt2 = date(2025, 2, 12);
		DateTime::date dt3 = dt1;
		assert(dt1 == dt3);
		assert(dt1 != dt2);
		assert(dt1 < dt2);
		assert(dt1 <= dt2);
		assert(dt1 <= dt3);
		assert(dt2 > dt1);
		assert(dt2 >= dt3);
		assert(dt1 >= dt3);
	}

	std::cout << "TestDate OK" << std::endl;
}

/*
	Tests for class `datetime`
*/

void TestDateTime() {
	{   // Valid date 2025.02.01
		DateTime::datetime dt(2025, 2, 1);
		assert(2025 == dt.year());
		assert(2 == dt.month());
		assert(1 == dt.day());
		assert(0 == dt.hour());
		assert(0 == dt.minute());
		assert(0 == dt.second());
		assert(DateTime::weekday::saturday == dt.weekday());
		assert(false == dt.is_leapyear());
		assert(std::string("2025.02.01 00:00:00") == DateTime::to_string(dt));
	}

	{   // Valid date 2025.02.01 12:40:15
		DateTime::datetime dt(2025, 2, 1, 12, 40, 15);
		assert(2025 == dt.year());
		assert(2 == dt.month());
		assert(1 == dt.day());
		assert(12 == dt.hour());
		assert(40 == dt.minute());
		assert(15 == dt.second());
		assert(DateTime::weekday::saturday == dt.weekday());
		assert(false == dt.is_leapyear());
		assert(std::string("2025.02.01 12:40:15") == DateTime::to_string(dt));
	}

	{   // Invalid date. Throw invalid argument exception
		try {
			DateTime::datetime dt1(2025, 13, 10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid date (zero). Throw invalid argument exception
		try {
			DateTime::datetime dt2(2025, 0, 10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid date (negative). Throw invalid argument exception
		try {
			DateTime::datetime dt3(2025, -1, 10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid date (negative). Throw invalid argument exception
		try {
			DateTime::datetime dt4(2025, 1, -10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid date (zero). Throw invalid argument exception
		try {
			DateTime::datetime dt5(2025, 1, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time (negative). Throw invalid argument exception
		try {
			DateTime::datetime dt6(2025, 1, 10, -10, 0, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time (negative). Throw invalid argument exception
		try {
			DateTime::datetime dt7(2025, 1, 10, 10, -10, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time (negative). Throw invalid argument exception
		try {
			DateTime::datetime dt8(2025, 1, 10, 10, 10, -10);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time. Throw invalid argument exception
		try {
			DateTime::datetime dt9(2025, 1, 10, 24, 0, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time. Throw invalid argument exception
		try {
			DateTime::datetime dt10(2025, 1, 10, 10, 60, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid time. Throw invalid argument exception
		try {
			DateTime::datetime dt11(2025, 1, 10, 10, 10, 60);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Invalid day 32 for months with 31 days. Throw invalid argument exception
		int month_to_check_31[] = { 1, 3, 5, 7, 8, 10, 12 };
		for (int i : month_to_check_31) {
			bool res{ true };
			try {
				DateTime::datetime dt1(2025, i, 32);
				assert(res == false);
			}
			catch (const std::invalid_argument& error) {
			}
			catch (...) {
				assert(res == false);
			}
		}
	}

	{   // Invalid day 31 for months with 30 days. Throw invalid argument exception
		int month_to_check_30[] = { 4, 6, 9, 11 };
		for (int i : month_to_check_30) {
			bool res{ true };
			try {
				DateTime::datetime dt1(2025, i, 31);
				assert(res == false);
			}
			catch (const std::invalid_argument& error) {
			}
			catch (...) {
				assert(res == false);
			}
		}
	}

	{   // Invalid day 30 for february. Throw invalid argument exception
		bool res{ true };
		try {
			DateTime::datetime dt1(2000, 2, 30);
			assert(res == false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(res == false);
		}
	}


	{   // Valid day 29 for february. Throw invalid argument exception
		DateTime::datetime dt(2000, 2, 29);
		assert(2000 == dt.year());
		assert(2 == dt.month());
		assert(29 == dt.day());
		assert(DateTime::weekday::tuesday == dt.weekday());
		assert(true == dt.is_leapyear());
		assert(std::string("2000.02.29 00:00:00") == DateTime::to_string(dt));
	}

	{   // Valid day 29 for february. Throw invalid argument exception
		DateTime::datetime dt(2024, 2, 29);
		assert(2024 == dt.year());
		assert(2 == dt.month());
		assert(29 == dt.day());
		assert(DateTime::weekday::thursday == dt.weekday());
		assert(true == dt.is_leapyear());
		assert(std::string("2024.02.29 00:00:00") == DateTime::to_string(dt));
	}

	{ // Add days
		DateTime::datetime dt(2019, 12, 31, 10, 0, 0);
		dt.add_days(60);
		assert(std::string("2020.02.29 10:00:00") == DateTime::to_string(dt));
	}

	{ // Add days
		DateTime::datetime dt(2019, 12, 31, 10, 0, 0);
		dt.add_days(61);
		assert(std::string("2020.03.01 10:00:00") == DateTime::to_string(dt));
	}

	{ // Add days
		DateTime::datetime dt(2020, 3, 1, 10, 0, 0);
		dt.add_days(-61);
		assert(std::string("2019.12.31 10:00:00") == DateTime::to_string(dt));
	}

	{ // Add hours
		DateTime::datetime dt(2020, 2, 28, 23, 0, 0);
		dt.add_hours(60);
		assert(std::string("2020.03.02 11:00:00") == DateTime::to_string(dt));
	}

	{ // Add minutes
		DateTime::datetime dt(2020, 2, 28, 23, 59, 0);
		dt.add_minutes(59);
		assert(std::string("2020.02.29 00:58:00") == DateTime::to_string(dt));
	}

	{ // Add seconds
		DateTime::datetime dt(2020, 2, 28, 23, 59, 50);
		dt.add_seconds(59);
		assert(std::string("2020.02.29 00:00:49") == DateTime::to_string(dt));
	}

	{ // Add seconds
		DateTime::datetime dt(2024, 12, 31, 23, 59, 59);
		dt.add_seconds(1);
		assert(std::string("2025.01.01 00:00:00") == DateTime::to_string(dt));
	}

	{ // Add seconds
		DateTime::datetime dt(2025, 1, 1, 0, 0, 0);
		dt.add_seconds(-1);
		assert(std::string("2024.12.31 23:59:59") == DateTime::to_string(dt));
	}

	{   // Is leap tests
		assert(DateTime::datetime::is_leapyear(2025) == false);
		assert(DateTime::datetime::is_leapyear(2024) == true);
		assert(DateTime::datetime::is_leapyear(2023) == false);
		assert(DateTime::datetime::is_leapyear(2020) == true);
		assert(DateTime::datetime::is_leapyear(2019) == false);
		assert(DateTime::datetime::is_leapyear(2000) == true);
		assert(DateTime::datetime::is_leapyear(1999) == false);
		assert(DateTime::datetime::is_leapyear(1900) == false);
		assert(DateTime::datetime::is_leapyear(1800) == false);
		assert(DateTime::datetime::is_leapyear(1600) == true);
	}

	{
		DateTime::datetime dt1 = datetime(2025, 2, 11);
		DateTime::datetime dt2 = datetime(2025, 2, 12);
		DateTime::datetime dt3 = dt1;
		assert(dt1 == dt3);
		assert(dt1 != dt2);
		assert(dt1 < dt2);
		assert(dt1 <= dt2);
		assert(dt1 <= dt3);
		assert(dt2 > dt1);
		assert(dt2 >= dt3);
		assert(dt1 >= dt3);
	}

	{
		DateTime::datetime dt1 = datetime(2025, 2, 11, 23, 59, 0);
		DateTime::datetime dt2 = datetime(2025, 2, 11, 23, 59, 1);
		DateTime::datetime dt3 = dt1;
		assert(dt1 == dt3);
		assert(dt1 != dt2);
		assert(dt1 < dt2);
		assert(dt1 <= dt2);
		assert(dt1 <= dt3);
		assert(dt2 > dt1);
		assert(dt2 >= dt3);
		assert(dt1 >= dt3);
	}

	{ // Get friday
		DateTime::datetime dt = datetime(2024, 12, 27, 23, 59, 0);
		assert(dt.weekday() == DateTime::weekday::friday);
	}

	{ // Get saturday
		DateTime::datetime dt = datetime(2024, 12, 28, 23, 59, 0);
		assert(dt.weekday() == DateTime::weekday::saturday);
	}

	{ // Get sunday
		DateTime::datetime dt = datetime(2024, 12, 29, 23, 59, 0);
		assert(dt.weekday() == DateTime::weekday::sunday);
	}

	std::cout << "TestDateTime OK" << std::endl;
}


void TestTimediff() {

	{   // Throw invalid argument exception
		try {
			DateTime::timediff ts(0, -24, 0, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Throw invalid argument exception
		try {
			DateTime::timediff ts(0, 24, 0, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Throw invalid argument exception
		try {
			DateTime::timediff ts(0, -60, 0, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Throw invalid argument exception
		try {
			DateTime::timediff ts(0, 60, 0, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Throw invalid argument exception
		try {
			DateTime::timediff ts(0, 0, -60, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Throw invalid argument exception
		try {
			DateTime::timediff ts(0, 0, 60, 0);
			assert(false);
		}
		catch (const std::invalid_argument& error) {
		}
		catch (...) {
			assert(false);
		}
	}

	{   // Valid timediff
		DateTime::timediff ts(0, 0, 0, 0);
		assert(0 == ts.days());
		assert(0 == ts.hours());
		assert(0 == ts.minutes());
		assert(0 == ts.seconds());
	}

	{   // Valid timediff
		DateTime::timediff ts(1, 2, 3, 4);
		assert(1 == ts.days());
		assert(2 == ts.hours());
		assert(3 == ts.minutes());
		assert(4 == ts.seconds());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(0, 0, 0, 50);
		assert(50 == ts.total_seconds());
		assert(0 == ts.total_minutes());
		assert(0 == ts.total_hours());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(0, 0, 3, 50);
		assert(230 == ts.total_seconds());
		assert(3 == ts.total_minutes());
		assert(0 == ts.total_hours());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(0, 2, 3, 50);
		assert(7430 == ts.total_seconds());
		assert(123 == ts.total_minutes());
		assert(2 == ts.total_hours());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(1, 2, 3, 50);
		assert(93830 == ts.total_seconds());
		assert(1563 == ts.total_minutes());
		assert(26 == ts.total_hours());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(0, 0, 0, -50);
		assert(-50 == ts.total_seconds());
		assert(0 == ts.total_minutes());
		assert(0 == ts.total_hours());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(0, 0, -3, -50);
		assert(-230 == ts.total_seconds());
		assert(-3 == ts.total_minutes());
		assert(0 == ts.total_hours());
	}

	{   // Total seconds, minutes, hours
		DateTime::timediff ts(0, -2, -3, -50);
		assert(-7430 == ts.total_seconds());
		assert(-123 == ts.total_minutes());
		assert(-2 == ts.total_hours());
	}

	{   // Total seconds
		DateTime::timediff ts(-1, -2, -3, -50);
		assert(-93830 == ts.total_seconds());
		assert(-1563 == ts.total_minutes());
		assert(-26 == ts.total_hours());
	}

	{
		DateTime::timediff ts1(1, 2, 3, 10);
		DateTime::timediff ts2(1, 0, 4, 0);
		DateTime::timediff ts3 = ts1;
		DateTime::timediff ts4(-1, -2, -3, -10);
		assert(ts1 == ts3);
		assert(ts1 != ts2);
		assert(ts2 < ts1);
		assert(ts3 <= ts1);
		assert(ts4 < ts2);
		assert(ts1 > ts2);
		assert(ts1 >= ts3);
		assert(ts2 > ts4);
	}

	{
		DateTime::time tm1(10, 52, 10);
		DateTime::time tm2(11, 12, 5);
		DateTime::timediff ts1 = tm2 - tm1;
		assert(ts1.days() == 0);
		assert(ts1.hours() == 0);
		assert(ts1.minutes() == 19);
		assert(ts1.seconds() == 55);
		assert(ts1.total_hours() == 0);
		assert(ts1.total_minutes() == 19);
		assert(ts1.total_seconds() == 1195);

	}

	{
		DateTime::date date1(2024, 12, 31);
		DateTime::date date2(2024, 12, 25);
		DateTime::timediff ts1 = date1 - date2;
		assert(ts1.days() == 6);
		assert(ts1.hours() == 0);
		assert(ts1.minutes() == 0);
		assert(ts1.seconds() == 0);
		assert(ts1.total_hours() == 144);
		assert(ts1.total_minutes() == 8640);
		assert(ts1.total_seconds() == 518400);
	}

	{
		DateTime::datetime date1(2024, 12, 31);
		DateTime::datetime date2(2024, 12, 25);
		DateTime::timediff ts1 = date1 - date2;
		assert(ts1.days() == 6);
		assert(ts1.hours() == 0);
		assert(ts1.minutes() == 0);
		assert(ts1.seconds() == 0);
		assert(ts1.total_hours() == 144);
		assert(ts1.total_minutes() == 8640);
		assert(ts1.total_seconds() == 518400);
	}

	{
		DateTime::datetime date1(2024, 12, 31);
		DateTime::datetime date2(2024, 11, 25);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -36);
		assert(ts1.hours() == 0);
		assert(ts1.minutes() == 0);
		assert(ts1.seconds() == 0);
	}


	{
		DateTime::datetime date1(2024, 12, 31);
		DateTime::datetime date2(2024, 11, 25);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -36);
		assert(ts1.hours() == 0);
		assert(ts1.minutes() == 0);
		assert(ts1.seconds() == 0);
	}
	{
		DateTime::datetime date1(2024, 12, 31, 11, 0, 0);
		DateTime::datetime date2(2024, 12, 25, 13, 0, 0);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -5);
		assert(ts1.hours() == -22);
	}

	{
		DateTime::datetime date1(2024, 12, 31, 11, 55, 12);
		DateTime::datetime date2(2024, 12, 25, 13, 32, 5);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -5);
		assert(ts1.hours() == -22);
		assert(ts1.minutes() == -23);
		assert(ts1.seconds() == -7);
	}

	{
		DateTime::datetime date1(2024, 12, 31, 11, 32, 5);
		DateTime::datetime date2(2024, 12, 25, 13, 55, 12);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -5);
		assert(ts1.hours() == -21);
		assert(ts1.minutes() == -36);
		assert(ts1.seconds() == -53);
	}

	{
		DateTime::datetime date1(2024, 12, 31, 13, 32, 5);
		DateTime::datetime date2(2024, 12, 25, 11, 55, 12);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -6);
		assert(ts1.hours() == -1);
		assert(ts1.minutes() == -36);
		assert(ts1.seconds() == -53);
	}

	{
		DateTime::datetime date1(2024, 12, 31);
		DateTime::datetime date2(2023, 11, 25);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == -402);
		assert(ts1.hours() == 0);
		assert(ts1.minutes() == 0);
		assert(ts1.seconds() == 0);
	}

	{
		DateTime::datetime date1(2024, 12, 31, 7, 32, 5);
		DateTime::datetime date2(2024, 12, 31, 14, 55, 12);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == 0);
		assert(ts1.hours() == 7);
		assert(ts1.minutes() == 23);
		assert(ts1.seconds() == 7);
	}

	{
		DateTime::datetime date1(2025, 2, 27, 15, 58, 2);
		DateTime::datetime date2(2025, 3, 2, 9, 0, 0);
		DateTime::timediff ts1 = date2 - date1;
		assert(ts1.days() == 2);
		assert(ts1.hours() == 17);
		assert(ts1.minutes() == 1);
		assert(ts1.seconds() == 58);
		assert(ts1.total_seconds() == ((2 * 24 + 17) * 60 + 1) * 60 + 58);

	}

	{
		DateTime::datetime date1(2025, 2, 27, 15, 58, 2);
		DateTime::datetime date2(2025, 3, 2, 9, 0, 0);
		DateTime::timediff ts1 = date2 - date1;
		DateTime::datetime date3 = date1 + ts1;
		assert(date3 == date2);
		date3 = date2 - ts1;
		assert(date3 == date1);
	}

	{
		DateTime::datetime date1(2000, 2, 27, 15, 0, 30);
		DateTime::datetime date2(2000, 3, 2, 9, 0, 10);
		DateTime::timediff ts1 = date2 - date1;
		DateTime::datetime date3 = date1 + ts1;
		assert(date3 == date2);
		date3 = date2 - ts1;
		assert(date3 == date1);
	}

	std::cout << "TestTimeDiff OK" << std::endl;
}
