#ifndef DATE_H
#define DATE_H

#include <cstdio>

class Date
{
public:
    enum { YEAR_MIN = 1900, YEAR_MAX = 2900 };
    enum { FEBRUARY = 2, JULY = 7 };

    Date() = default;
    Date(short day, short month, short year);

    void change(short day, short month, short year);
    void print() const;
    void validate();
    short day() const;
    short month() const;
    short year() const;
    short lastDayOfMonth() const;
    bool isLeapYear() const;
    int compare(const Date& other) const;

private:
    bool validDay() const;
    bool validMonth() const;
    bool validYear() const;

    short m_day;
    short m_month;
    short m_year;
    bool  m_valid{ false };
};

#endif // DATE_H
