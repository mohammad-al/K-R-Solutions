#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void) {

	return 0;

}

int day_of_year(int year, int month, int day) {

	if (year < 0) {
		return -1;
	}

	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 != 0;

	if (month < 1 || month > 12) {
		return -1;
	}
	if (day < 1 || day > daytab[leap][month]) {
		return -1;
	}

	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {

	if (year < 0) {
		*pmonth = -1;
		*pday = -1;
		return;
	}

	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 != 0;

	int max_yearday = 366 ? leap : 365;

	if (yearday > max_yearday) {
		*pmonth = -1;
		*pday = -1;
		return;
	}

	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}
