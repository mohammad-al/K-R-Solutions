#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void) {

	printf("%d\n", day_of_year(2026, 7, 24));

	int month;
	int day;
	month_day(2026, 205, &month, &day);

	printf("%d %d\n", month, day);
	return 0;

}

int day_of_year(int year, int month, int day) {


	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	char *year_pointer = *(daytab + leap);

	while (month--) {
		day += *year_pointer++;
	}

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {

	int i, leap;
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	char *year_pointer = *(daytab + leap);

	while (yearday > *year_pointer) {
		yearday -= *year_pointer;
		*year_pointer++;
	}

	// Just find difference between how far yearday has moved from where it started
	*pmonth = year_pointer - *(daytab + leap);
	*pday = yearday;
}
