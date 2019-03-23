#ifndef CPP_STATIC_TODO
#define CPP_STATIC_TODO

// Returns the year from the current build date
constexpr int current_build_year() {
    // exemple: "Nov 27 2018"
    const char *year = __DATE__;

    // skip the 2 first spaces
    int nbSpaces = 0;
    while (nbSpaces < 2) {
        if (*year == ' ') {
            nbSpaces++;
        }
        year++;
    }

    return (year[0] - '0') * 1000 + (year[1] - '0') * 100 + (year[2] - '0') * 10 + (year[3] - '0');
}

// Returns the month number (1..12) from the current build date
constexpr int current_build_month() {
    constexpr const char months[12][4]{
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // exemple: "Nov 27 2018"
    constexpr const char date[] = __DATE__;

    // find matching month
    for (int i = 0; i < 12; i++) {
        const char *m = months[i];
        if (m[0] == date[0] && m[1] == date[1] && m[2] == date[2]) {
            return i + 1;
        }
    }

    return 0; // will be caught by the static_assert() check on month value
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

#endif