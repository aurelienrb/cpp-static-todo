#pragma once

namespace details {
    constexpr const char *find_next(const char *s, const char c) {
        return (*s == c) ? s : find_next(s + 1, c);
    }

    constexpr const char *find_prev(const char *s, const char c) {
        return (*s == c) ? s : find_prev(s - 1, c);
    }

    constexpr int to_int(const char *year) {
        return (year[0] - '0') * 1000 + (year[1] - '0') * 100 + (year[2] - '0') * 10 + (year[3] - '0');
    }

    constexpr bool strncmp(const char *a, const char *b, const int n) {
        return (n > 0 && *a == *b) ? strncmp(a + 1, b + 1, n - 1) : (n == 0);
    }

    constexpr int find_month(const char (&l)[12][4], const int index, const char *s) {
        return (index < 0 || strncmp(l[index], s, 3)) ? index : find_month(l, index - 1, s);
    }

    constexpr const char months[12][4]{
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
}

// Returns the year from the current build date
constexpr int current_build_year() {
    return details::to_int(details::find_prev(details::find_next(__DATE__, '\0'), ' ') + 1);
}

// Returns the month number (1..12) from the current build date
constexpr int current_build_month() {
    return details::find_month(details::months, 11, __DATE__) + 1;
}

/// TODO_BEFORE() inserts a compilation "time bomb" that will trigger a "TODO" build error a soon as
/// the given date is reached.
///
/// This is useful to force attention on a specific piece of code that should not been forgotten
/// among a growing list of many other "TODO" comments...
///
/// Example:
///     TODO_BEFORE(01, 2019, "refactor to use std::optional<> once we compile in C++17 mode");
#define TODO_BEFORE(month, year, msg)                                                              \
    static_assert((year >= 2018 && month > 0 && month <= 12) &&                                    \
                      (current_build_year() < year ||                                              \
                          (current_build_year() == year && current_build_month() < month)),        \
        "TODO: " msg)

/// FIXME_BEFORE() works the same way than TODO_BEFORE() but triggers a "FIXME" error instead
#define FIXME_BEFORE(month, year, msg)                                                             \
    static_assert((year >= 2018 && month > 0 && month <= 12) &&                                    \
                      (current_build_year() < year ||                                              \
                          (current_build_year() == year && current_build_month() < month)),        \
        "FIXME: " msg)
