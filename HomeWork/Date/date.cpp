#include "date.h"

Date::Date(short day, short month, short year)
{
    change(day, month, year);
}

void Date::change(short day, short month, short year)
{
    m_day = day;
    m_month = month;
    m_year = year;

    validate();
}

void Date::print() const
{
    if (m_valid) {
        printf("%02d/%02d/%d\n", m_day, m_month, m_year);
    } else {
        printf("Invalid date!\n");
    }
}

short Date::day() const
{
    return m_day;
}

short Date::month() const
{
    return m_month;
}

short Date::year() const
{
    return m_year;
}

short Date::lastDayOfMonth() const
{
    return m_month != FEBRUARY
        ? (30 + (m_month & 1) ^ (m_month > JULY))
        : (28 + isLeapYear());
}

inline bool Date::isLeapYear() const
{
    return (!(m_year & 3) && (m_year % 100)) || !(m_year % 400);
}

int Date::compare(const Date &other) const
{
    return m_year != other.m_year
           ? m_year - other.m_year
           : m_month != other.m_month
                ? m_month - other.m_month
                : m_day - other.m_day;
}

inline bool Date::validDay() const
{
    return m_day > 0 && m_day <= lastDayOfMonth();
}

inline bool Date::validMonth() const
{
    return m_month > 0 && m_month < 13;
}

inline bool Date::validYear() const
{
    return m_year >= YEAR_MIN && m_year <= YEAR_MAX;
}

void Date::validate()
{
    m_valid = validDay() && validMonth() && validYear();
}
