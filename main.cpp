#include <string>
#include <iostream>
#include <map>
#include <random>
#include <math.h>
#include <unistd.h>
#include <chrono>

#include "main.h"

#define MIN_YEAR 1500
#define MAX_YEAR 2500

int main()
{
    std::map<int, std::string> months;
    PopulateMap(months);

    std::string userAnswer;
    int currentStreak = 0;
    while (userAnswer != "q")
    {
        Date randomDate;
        randomDate.day= GetRandomNumber(1, 31);
        randomDate.month = GetRandomNumber(1, 12);
        randomDate.year = GetRandomNumber(MIN_YEAR, MAX_YEAR);
        SetMaxDays(randomDate);

        std::string answer = GetWeekday(randomDate);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        
        std::cout << "Guess which day of the week on this date (type q to quit): " 
        << randomDate.day << " / " <<  months.at(randomDate.month) << " / " << randomDate.year << std::endl;
        
        std::cin >> userAnswer;
        if (userAnswer == "q") break;

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        userAnswer.resize(3);
        std::string answer_short = answer;
        answer_short.resize(3);

        if(answer_short == userAnswer)
        {
            std::cout << "\nYou got it right. It was a " << answer << "!" << std::endl;

            currentStreak++;
            std::cout << "Current streak: " << currentStreak << "\tTime spent: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s." << std::endl;
         
        }
        else
        {
            std::cout << "\nYou got it wrong. It was a " << answer << "." << std::endl;
            currentStreak = 0;
        }

        std::cout << "\nContinuing...\n" << std::endl;
        sleep(2);
    }

}

Date GetClosestDoomsday(const Date &inputDate)
{
    Date retDate(1,1,0);

    switch (inputDate.month)
    {
    case 1:{
        Date closestDate = IsLeapYear(inputDate.year) ? Date(3,1,0) : Date(2,1,0);
        return closestDate;}
    case 2:{
        Date closestDate = IsLeapYear(inputDate.year) ? Date(29,2,0) : Date(28,2,0);
        return closestDate;}
    case 3:{
        Date closestDate = Date(14,3,0);
        return closestDate;}
    case 4:{
        Date closestDate = Date(4,4,0);
        return closestDate;}
    case 5:{
        Date closestDate = Date(9,5,0);
        return closestDate;}
    case 6:{
        Date closestDate = Date(6,6,0);
        return closestDate;}
    case 7:{
        Date closestDate = Date(11,7,0);
        return closestDate;}
    case 8:{
        Date closestDate = Date(8,8,0);
        return closestDate;}
    case 9:{
        Date closestDate = Date(5,9,0);
        return closestDate;}
    case 10:{
        Date closestDate = Date(10,10,0);
        return closestDate;}
    case 11:{
        Date closestDate = Date(7,11,0);
        return closestDate;}
    case 12:{
        Date closestDate = Date(12,12,0);
        return closestDate;}

    default:
        return Date(0,0,0);
        break;
    }
}

std::string GetWeekday(const Date &inputDate)
{

    int y = inputDate.year;
    int day = 2.0 + y + floor(y/4.0) - floor(y/100.0) + floor(y/400.0);
    
    day = day % 7;

    Date doomsday = GetClosestDoomsday(inputDate);


    std::map<int, std::string> weekdays;
    weekdays.emplace(0, "Sunday");
    weekdays.emplace(1, "Monday");
    weekdays.emplace(2, "Tuesday");
    weekdays.emplace(3, "Wednesday");
    weekdays.emplace(4, "Thursday");
    weekdays.emplace(5, "Friday");
    weekdays.emplace(6, "Saturday");

//    return weekdays.at(day);
    if(doomsday.day > inputDate.day) day -= (doomsday.day - inputDate.day);
    else if (doomsday.day < inputDate.day) day += (inputDate.day - doomsday.day);

    while (day < 0) day += 7;
    while (day > 6) day -= 7;

    return weekdays.at(day);
    
}

void PopulateMap(std::map<int, std::string> &map)
{
    map.emplace(1, "January");
    map.emplace(2, "February");
    map.emplace(3, "March");
    map.emplace(4, "April");
    map.emplace(5, "May");
    map.emplace(6, "June");
    map.emplace(7, "July");
    map.emplace(8, "August");
    map.emplace(9, "September");
    map.emplace(10, "October");
    map.emplace(11, "November");
    map.emplace(12, "December");
}

void SetMaxDays(Date &inputDate)
{
    int maxDays = 31;

    inputDate.year = inputDate.year < 0 ? 0 : inputDate.year;
    inputDate.year = inputDate.year > 9999 ? 9999 : inputDate.year;

    inputDate.month = inputDate.month < 1 ? 1 : inputDate.month;
    inputDate.month = inputDate.month > 12 ? 12 : inputDate.month;

    switch(inputDate.month)
    {
        case 1:
            maxDays = 31;
            break;
        case 2:
            break;
        case 3:
            maxDays = 31;
            break;
        case 4:
            maxDays = 30;
            break;
        case 5:
            maxDays = 31;
            break;
        case 6:
            maxDays = 30;
            break;
        case 7 ... 8:
            maxDays = 31;
            break;
        case 9:
            maxDays = 30;
            break;
        case 10:
            maxDays = 31;
            break;
        case 11:
            maxDays = 30;
            break;
        case 12:
            maxDays = 31;
            break;
        default:
            maxDays = 31;
            break;
    }

    inputDate.day = inputDate.day < 1 ? 1 : inputDate.day;
    inputDate.day = inputDate.day > maxDays ? 31 : inputDate.day;

    if (inputDate.month == 2 && inputDate.day > 29)
    {
        inputDate.day = IsLeapYear(inputDate.year) ? 29 : 28;
    }
}

bool IsLeapYear(const int &year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0) return true;

            return false;
        }

        return true;
    }

    return false;
}

int GetRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    return distr(gen);
}