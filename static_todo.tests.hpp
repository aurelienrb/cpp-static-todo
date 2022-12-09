//
// Created by Jamie Pond on 09/12/2022.
//

// Tests for the static_todo.hpp header
// These are all static assertions, so if they fail to compile, the test has failed!
namespace static_todo {
static_assert(is_whitespace(' '));
static_assert(is_whitespace('\t'));
static_assert(!is_whitespace('a'));

static_assert(year_string_to_int("2018") == 2018);
static_assert(year_string_to_int("2345") == 2345);

static_assert(get_year_from_string("Jan  1 2018") == 2018);
static_assert(get_year_from_string("Dec 1 2022") == 2022);
static_assert(get_year_from_string("December \t 1st 2022") == 2022);
static_assert(get_year_from_string("December 1st 2022") == 2022);
static_assert(get_year_from_string("1st December 2022") == 2022);
static_assert(get_year_from_string("1s t December 2022") != 2022);  // breaks! four total spaces.

static_assert(is_a_month("Jan"));
static_assert(is_a_month("Feb"));
static_assert(is_a_month("Mar"));
static_assert(!is_a_month("April"));  // Must be 3 chars
static_assert(is_a_month("May"));
static_assert(!is_a_month("jun"));  // Must be title case

static_assert(get_month_from_string("Jan  1 2018") == 1);
static_assert(get_month_from_string("Feb 1 2022") == 2);
static_assert(get_month_from_string("Mar \t 1st 2022") == 3);
static_assert(get_month_from_string("Apr 1st 2022") == 4);
static_assert(get_month_from_string("Nov 1st 2022") == 11);
static_assert(get_month_from_string("Dec 1st 2022") == 12);

static_assert(is_date_before("Jan 1 2017", 2018, 1));
static_assert(is_date_before("Jan 1 2018", 2018, 2));
static_assert(is_date_before("Mar 31 1901", 1902, 2));
static_assert(is_date_before("Feb 31 1902", 1902, 3));
}  // namespace static_todo
