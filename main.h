#include "Date.h"

int GetRandomNumber(int min, int max);
bool IsLeapYear(const int &year);
void SetMaxDays(Date &inputDate);
void PopulateMap(std::map<int, std::string> &map);
void PopulateDoomsdays(std::map<int, Date> &doomsmap, const int &year);
Date GetClosestDoomsday(const Date &inputDate);
std::string GetWeekday(const Date &inputDate);


