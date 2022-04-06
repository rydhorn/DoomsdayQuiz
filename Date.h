#ifndef DATE_H
#define DATE_H

struct Date
{
    
    Date() { day = 1; month = 1; year = 1970; };
    Date(int d, int m, int y) 
    {
        day = d;
        month = m; 
        year = y;
    };

    int day;
    int month;
    int year;



};

#endif