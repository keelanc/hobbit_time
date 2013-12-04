#include "hobbit_meals.h"

static const char* const MEALS[] = {
	"almost\nbreak\nfast",
	"break\nfast",
	"seven\nish",
	"almost\nsecond\nbkft",
	"second\nbreak\nfast",
	"almost\neleven\nses",
	"eleven\nses",
	"lunch\neon",
	"after\nlunch\nnap",
	"after\nnoon\ntea",
	"three\nish",
	"almost\ndinner",
	"dinner",
	"almost\nsupper",
	"supper",
	"eight\nish",
	"nine\nish"
};

void hobbit_time(int int_hour, char* str_hour) {
	strcpy(str_hour, "");
	if (int_hour > 4 && int_hour < 22) {
		strcat(str_hour, MEALS[int_hour - 5]);
	}
    else if (int_hour == 0) {
        strcat(str_hour, "mid\nnight\nsnack");
    }
	else {
		strcat(str_hour, "sleep");
	}

}