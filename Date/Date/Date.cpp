#include <iostream>
#include <fstream>
#include <string>

std::ifstream fin;
std::ofstream fout("output.txt");

class Date {
public:
	int day;
	int month;
	int year;
};

class DateArray : public Date {
private:
	Date item;
	Date* arr;
	std::string s;
	int size;

public:

	enum Months {
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULE,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	void openFile() {
		fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		try
		{
			std::cout << "Trying to open file ...\n";
			fin.open("input.txt");
			std::cout << "File was opened\n";
		}
		catch (const std::ifstream::failure ex)
		{
			std::cout << ex.what() << "\n";
			std::cout << ex.code() << "\n";
			std::cout << "Error when opening file ...\n";
		}
	}

	void init(std::string s) {
		item.day = int(s[0] - 48) * 10 + int(s[1] - 48);
		item.month = int(s[3] - 48) * 10 + int(s[4] - 48);
		item.year = int(s[6] - 48) * 1000 + int(s[7] - 48) * 100 + int(s[8] - 48) * 10 + int(s[9] - 48);
	}

	void getDataSize() {
		fin >> size;
		arr = new Date[size];
	}

	void getData() {
		fin >> s;
		init(s);
	}

	bool isLeap() {
		if (item.year % 4) {
			return false;
		}
		else {
			return true;
		}
	}

	Date nextDay() {
		if (item.month == Months::DECEMBER && item.day == 31) {
			item.year++;
			item.month = Months::JANUARY;
			item.day = 1;
		}
		else if (item.month == Months::FEBRUARY && ((isLeap() && item.day == 29) || (!isLeap() && item.day == 28))) {
			item.month++;
			item.day = 1;
		}
		else if (((!(item.month % 2) && item.month < Months::AUGUST) || (item.month % 2 && item.month > Months::JULE)) && item.day == 31) {
			item.month++;
			item.day = 1;
		}
		else if (((item.month % 2 && item.month < Months::AUGUST) || (!(item.month % 2) && item.month > Months::JULE)) && item.day == 30) {
			item.month++;
			item.day = 1;
		}
		else {
			item.day++;
		}

		correctDate();

		return item;

	}

	void correctDate() {

		if (item.day < 10) {
			fout << "0" << item.day << ".";
			std::cout << "0" << item.day << ".";
		}
		else {
			fout << item.day << ".";
			std::cout << item.day << ".";
		}

		if (item.month < 10) {
			fout << "0" << item.month << ".";
			std::cout << "0" << item.month << ".";
		}
		else {
			fout << item.month << ".";
			std::cout << item.month << ".";
		}

		if (item.year < 10) {
			fout << "000" << item.year << "\n";
			std::cout << "000" << item.year << "\n";
		}
		else if (item.year < 100) {
			fout << "00" << item.year << "\n";
			std::cout << "00" << item.year << "\n";
		}
		else if (item.year < 1000) {
			fout << "0" << item.year << "\n";
			std::cout << "0" << item.year << "\n";
		}
		else {
			fout << item.year << "\n";
			std::cout << item.year << "\n";
		}
	}

	void getNextDay() {
		openFile();
		getDataSize();
		for (int i = 0; i < size; i++) {
			getData();
			arr[i] = nextDay();
		}
		fin.close();
	}
	
	Date previousDay() {
		if (item.month == Months::JANUARY && item.day == 1) {
			item.year--;
			item.month = Months::DECEMBER;
			item.day = 31;
		}
		else if (item.month == Months::MARCH && (isLeap() && item.day == 1)) {
			item.month--;
			item.day = 29;
		}
		else if (item.month == Months::MARCH && (!isLeap() && item.day == 1)) {
			item.month--;
			item.day = 28;
		}
		else if (((!(item.month % 2) && item.month < Months::AUGUST) || (item.month % 2 && item.month > Months::JULE)) && item.day == 1) {
			item.month--;
			item.day = 30;
		}
		else if (((item.month % 2 && item.month < Months::AUGUST) || (!(item.month % 2) && item.month > Months::JULE)) && item.day == 1) {
			item.month--;
			item.day = 31;
		}
		else {
			item.day--;
		}

		correctDate();

		return item;
	}

	void getPreviousDay() {
		openFile();
		getDataSize();
		for (int i = 0; i < size; i++) {
		    getData();
			arr[i] = previousDay();
		}
		fin.close();
	}

	short weekNumber() {
		short leftDaysOfThisMonth = 0;
		short weeksOfThisMonth = 0;

		short weeks = 0;
		short days = 0;

		leftDaysOfThisMonth = item.day % 7;
		weeksOfThisMonth = (item.day - leftDaysOfThisMonth) / 7;

		if (item.month > 1) {
			for (int i = 1; i < item.month; i++) {
				if (i == Months::JANUARY) { weeks += 4; days += 3; continue; }
				if (i == Months::FEBRUARY && isLeap()) { weeks += 4; days += 1; continue; }
				if (i == Months::FEBRUARY && !isLeap()) { weeks += 4; continue; }
				if (i == Months::MARCH) { weeks += 4; days += 3; continue; }
				if (i == Months::APRIL) { weeks += 4; days += 2; continue; }
				if (i == Months::MAY) { weeks += 4; days += 3; continue; }
				if (i == Months::JUNE) { weeks += 4; days += 2; continue; }
				if (i == Months::JULE) { weeks += 4; days += 3; continue; }
				if (i == Months::AUGUST) { weeks += 4; days += 3; continue; }
				if (i == Months::SEPTEMBER) { weeks += 4; days += 2; continue; }
				if (i == Months::OCTOBER) { weeks += 4; days += 3; continue; }
				if (i == Months::NOVEMBER) { weeks += 4; days += 2; continue; }
			}
		}

		short totalDays = days + leftDaysOfThisMonth;
		weeks += weeksOfThisMonth;

		if (totalDays > 7) {
			short left = totalDays % 7;
			weeks += (totalDays - left) / 7;
		}

		std::cout << weeks << "\n";
		fout << weeks << "\n";
	
		return weeks;

	}

	void getWeeks() {
		openFile();
		getDataSize();
		for (int i = 0; i < size; i++) {
			getData();
			weekNumber();
		}
		fin.close();
	}

	int daysDiffent(Date item) {
		int days = 0;

		for (int i = 0; i < item.year; i++) {
			if (isLeap()) { days += 366; }
			else { days += 365; }
		}

		for (int i = 1; i < item.month; i++) {
			if (i < Months::AUGUST) {
				if (i == Months::FEBRUARY && isLeap()) { days += 29;  continue; }
				if (i == Months::FEBRUARY && !isLeap()) { days += 28; continue; }

				if (i % 2) { days += 31; }
				else { days += 30; }
			}
			else {
				if (i % 2) { days += 30; }
				else { days += 31; }
			}
		}

		days += item.day;

		return days;
	}

	int daysTillYourBirthday(Date birthdayDate) {
		int different = daysDiffent(birthdayDate) - daysDiffent(this->item);

		std::cout << different << "\n";
		fout << different << "\n";

		return different;
	}

	void getDaysDifferent(Date birthdayDate) {
		openFile();
		getDataSize();
		int different;
		for (int i = 0; i < size; i++) {
			getData();
			daysTillYourBirthday(birthdayDate);
		}
		fin.close();
	}

	int duration(Date date) {

	}

};


int main()
{
	DateArray A;
	A.getPreviousDay();
	A.getNextDay();
	A.getWeeks();

	Date MyBirthday;
	MyBirthday.day = 01;
	MyBirthday.month = 01;
	MyBirthday.year = 2022;

	A.getDaysDifferent(MyBirthday);

	return 0;

}