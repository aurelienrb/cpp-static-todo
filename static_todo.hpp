#pragma once

#ifndef __DATE__
#error "__DATE__ is not defined, which is required for TODO_BEFORE"
#endif

namespace static_todo {
constexpr const char months[12][4]{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

consteval bool is_whitespace(char c) { return c == ' ' || c == '\t'; }
consteval bool is_null(char c) { return c == '\0'; }

consteval int year_string_to_int(const char *year) {
    return (year[0] - '0') * 1000 + (year[1] - '0') * 100 + (year[2] - '0') * 10 + (year[3] - '0');
}

consteval int get_year_from_string(const char *date) {
    const char *year = date;

    // Walk over the first two words and point at the start of the year
    // NB There could be multiple spaces between the words!
    int num_words = 0;
    bool was_prev_char_space = false;
    while (num_words < 2) {
        if (is_whitespace(*year)) {
            if (!was_prev_char_space) {
                num_words++;
            }
            was_prev_char_space = true;
        } else {
            was_prev_char_space = false;
        }
        year++;
    }

    return year_string_to_int(year);
}

consteval bool is_a_month(const char *month) {
    for (int i = 0; i < 12; i++) {
        if (month[0] == months[i][0] && month[1] == months[i][1] && month[2] == months[i][2] &&
            is_null(month[3])) {
            return true;
        }
    }
    return false;
}

// Returns the month number (1..12) from an input string
consteval int get_month_from_string(const char *date) {
    // find matching month
    for (int i = 0; i < 12; i++) {
        const char *m = months[i];
        if (m[0] == date[0] && m[1] == date[1] && m[2] == date[2]) {
            return i + 1;
        }
    }
    return 0;
}

consteval bool is_date_before(const char *date, int year, int month) {
    return get_year_from_string(date) < year ||
           (get_year_from_string(date) == year && get_month_from_string(date) < month);
}

} // namespace static_todo

/// TODO_BEFORE() inserts a compilation "time bomb" that will trigger a "TODO" build error a soon as
/// the given date is reached.
///
/// This is useful to force attention on a specific piece of code that should not been forgotten
/// among a growing list of many other "TODO" comments...
///
/// Example:
///     TODO_BEFORE(01, 2019, "refactor to use std::optional<> once we compile in C++17 mode");
#define TODO_BEFORE(month, year, msg)                                                              \
    static_assert(                                                                                 \
        static_todo::is_a_month(#month), "Enter a month in the format Jan, Feb, Dec, etc.");       \
    static_assert(                                                                                 \
        static_todo::is_date_before(__DATE__, year, static_todo::get_month_from_string(#month)),   \
        "TODO: " msg)

/// FIXME_BEFORE() works the same way than TODO_BEFORE() but triggers a "FIXME" error
/// instead
#define FIXME_BEFORE(month, year, msg)                                                             \
    static_assert(                                                                                 \
        static_todo::is_a_month(#month), "Enter a month in the format Jan, Feb, Dec, etc.");       \
    static_assert(                                                                                 \
        static_todo::is_date_before(__DATE__, year, static_todo::get_month_from_string(#month)),   \
        "TODO: " msg)

// Include tests here, so they are compiled with the rest of the code
#include "static_todo.tests.hpp"