#include <stdio.h>
#include <stdint.h>

/**
 * mktime64 - Converts date to seconds.
 * @year0: year to convert
 * @mon0: month to convert
 * @day: day to convert
 * @hour: hour to convert
 * @min: minute to convert
 * @sec: second to convert
 *
 * Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * A leap second can be indicated by calling this function with sec as
 * 60 (allowable under ISO 8601).  The leap second is treated the same
 * as the following second since they don't exist in UNIX time.
 *
 * An encoding of midnight at the end of the day as 24:00:00 - ie. midnight
 * tomorrow - (allowable under ISO 8601) is supported.
 *
 * Return: seconds since the epoch time for the given input date
 */
 
uint64_t mktime64(const uint64_t year0, const uint64_t mon0,
		const uint64_t day, const uint64_t hour,
		const uint64_t min, const uint64_t sec)
{
	unsigned int mon = mon0, year = year0;

	/* 1..12 -> 11,12,1..10 */
	if (0 >= (int) (mon -= 2)) {
		mon += 12;	/* Puts Feb last since it has leap day */
		year -= 1;
	}

	return ((((uint64_t)
		  (year/4 - year/100 + year/400 + 367*mon/12 + day) +
		  year*365 - 719499
	    )*24 + hour /* now have hours - midnight tomorrow handled here */
	  )*60 + min /* now have minutes */
	)*60 + sec; /* finally seconds */
}

int main() {
   // printf() displays the string inside quotation
   uint64_t test = 73709551615;
   
   printf("Unix time %lld", mktime64(1970, 1, 1, 1, 1, 10));
   return 0;
}
