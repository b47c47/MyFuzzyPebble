#include "num2words.h"
#include "string.h"

static const char* const ONES[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"
};

static const char* const TEENS[] ={
  "",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen"
};

static const char* const TENS[] = {
  "",
  "ten",
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety"
};

static const char* STR_NOON = "noon";
static const char* STR_MIDNIGHT = "midnight";
//static const char* STR_OH_CLOCK = "o'clock";
//static const char* STR_QUARTER = "quarter";
//static const char* STR_TO = "to";
//static const char* STR_PAST = "past";
//static const char* STR_HALF = "half";
//static const char* STR_AFTER = "after";

static const char* STR_HALF = "half";
static const char* STR_ALMOST = "almost";
static const char* STR_PAST = "past";
static const char* STR_ISH = "ish";
static const char* STR_OR_SO = "or so";

static size_t append_number(char* words, int num) {
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 0) {
    if (tens_val == 1 && num != 10) {
      strcat(words, TEENS[ones_val]);
      return strlen(TEENS[ones_val]);
    }
    strcat(words, TENS[tens_val]);
    len += strlen(TENS[tens_val]);
    if (ones_val > 0) {
      strcat(words, " ");
      len += 1;
    }
  }

  if (ones_val > 0 || num == 0) {
    strcat(words, ONES[ones_val]);
    len += strlen(ONES[ones_val]);
  }
  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

void fuzzy_time_to_words(int hours, int minutes, char* words, size_t length) {
  int fuzzy_hours = hours;
  int fuzzy_minutes = ((minutes + 2) / 5) * 5;

  // Handle hour & minute roll-over.
  if (fuzzy_minutes >= 53) {
    fuzzy_hours += 1;
    // if it is 24 it will be reset below modulus 12
  }

  size_t remaining = length;
  memset(words, 0, length);

  if (fuzzy_minutes >= 13 && fuzzy_minutes < 23) {
      remaining -= append_string(words, remaining, STR_PAST);
      remaining -= append_string(words, remaining, " ");
  } else if (fuzzy_minutes >= 43 && fuzzy_minutes < 53) {
      remaining -= append_string(words, remaining, STR_PAST);
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, STR_HALF);
      remaining -= append_string(words, remaining, " ");
  } else if (fuzzy_minutes >= 53 && fuzzy_minutes < 58) {
      remaining -= append_string(words, remaining, STR_ALMOST);
      remaining -= append_string(words, remaining, " ");
  } else if (fuzzy_minutes >= 23 && fuzzy_minutes < 28) {
      remaining -= append_string(words, remaining, STR_ALMOST);
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, STR_HALF);
      remaining -= append_string(words, remaining, " ");
  } else if (fuzzy_minutes >= 28 && fuzzy_minutes < 43) {
      remaining -= append_string(words, remaining, STR_HALF);
      remaining -= append_string(words, remaining, " ");
  }

  fuzzy_hours = fuzzy_hours % 12;
  if (fuzzy_hours == 0) {
      fuzzy_hours = 12;
  }
  remaining -= append_number(words, fuzzy_hours);

  if (fuzzy_minutes >= 3 && fuzzy_minutes < 8) {
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, STR_ISH);
  } else if (fuzzy_minutes >= 8 && fuzzy_minutes < 13) {
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, STR_OR_SO);
  } else if (fuzzy_minutes >= 33 && fuzzy_minutes < 38) {
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, STR_ISH);
  } else if (fuzzy_minutes >= 38 && fuzzy_minutes < 43) {
      remaining -= append_string(words, remaining, " ");
      remaining -= append_string(words, remaining, STR_OR_SO);
  }
}
