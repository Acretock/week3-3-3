#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;



class Person
{
public:
	Person(const string& first, const string& last, const int& b);
	~Person();
	void ChangeFirstName(int year, const string& name) {
		if (birth!=0)
		First.insert({ year,name });
	}
	void ChangeLastName(int year, const string& last) {
		if (birth != 0)
		Last.insert({ year,last });
	}

	int FindFirstYear(int year) {
		int firstchange = First.lower_bound(0)->first;
		if (firstchange == year)
			return year;			// if last == sought-for
		int first = 0;
		while ((firstchange < year) && (First.upper_bound(firstchange) != end(First))) {
			if (First.upper_bound(firstchange)->first > year) {
				return firstchange;	// return year before sought-for
			}
			else
				firstchange = First.upper_bound(firstchange)->first;
		}
		return firstchange;			// if ONLY 1 change has happend
	}

	int FindLastYear(int year) {
		int firstchange = Last.lower_bound(0)->first;
		if (firstchange == year)
			return year;			// if last == sought-for
		int first = 0;
		while ((firstchange < year) && (Last.upper_bound(firstchange) != end(Last))) {
			if (Last.upper_bound(firstchange)->first > year) {
				return firstchange;	// return year before sought-for
			}
			else
				firstchange = Last.upper_bound(firstchange)->first;
		}
		return firstchange;			// if ONLY 1 change has happend
	}

	string HistoryLast(int year) {
		int y = FindLastYear(year);
		string s = Last.lower_bound(y)->second + " ";
		vector<string> vec;
		for (auto i : Last) {
			if (i.first == Last.find(y)->first) {
				if (!vec.empty()) {
					s += "(";
					reverse(begin(vec), end(vec));
					for (int j = 0; j < vec.size(); j++)
						if (j == (vec.size() - 1))
							s += vec[j];
						else
							s += vec[j] + ", ";
					if (!vec.empty())
						s += ")";
					return s;
				}
				else return s;
			}
			else
				vec.push_back(i.second);
		}
	}

	string HistoryFirst(int year) {
		int y = FindFirstYear(year);
		string s = First.lower_bound(y)->second + " ";
		vector<string> vec;
		for (auto i : First) {
			if (i.first == First.find(y)->first) {
				if (!vec.empty()) {
					s += "(";
					reverse(begin(vec), end(vec));
					for (int j = 0; j < vec.size(); j++)
						if (j == (vec.size() - 1))
							s += vec[j];
						else
							s += vec[j] + ", ";
					if (!vec.empty())
						s += ")";
					return s;
				}
				else return s;
			}
			else
				vec.push_back(i.second);
		}
	}

	string GetFullName(int year) {
		if (birth <= year) {
			int firstnamechange1 = First.lower_bound(0)->first;
			int lastnamechange1 = Last.lower_bound(0)->first;
			if (((firstnamechange1 > year) && (lastnamechange1 > year)))	// if changes happend after year
				return "Incognito";
			if ((firstnamechange1 <= year) && (lastnamechange1 > year))		// if first name changed but last wasn't
				return First.lower_bound(FindFirstYear(year))->second + " with unnown last name";
			if ((lastnamechange1 <= year) && (firstnamechange1 > year))		// if last name changed but first wasn't
				return Last.lower_bound(FindLastYear(year))->second + " with unnown last name";
			if ((lastnamechange1 <= year) && (firstnamechange1 <= year))	// if all was changed
				return First.lower_bound(FindFirstYear(year))->second + ' ' + Last.lower_bound(FindLastYear(year))->second;
		}
		else return "No person";
	}

	string GetFullNameWithHistory(int year) {
		if (birth <= year) {
			int firstnamechange1 = First.lower_bound(0)->first;
			int lastnamechange1 = Last.lower_bound(0)->first;
			if (((firstnamechange1 > year) && (lastnamechange1 > year)))	// if changes happend after year
				return "Incognito";
			if ((firstnamechange1 <= year) && (lastnamechange1 > year))		// if first name changed but last wasn't
				return HistoryFirst(year) + "with unnown last name";
			if ((lastnamechange1 <= year) && (firstnamechange1 > year))		// if last name changed but first wasn't
				return HistoryLast(year) + "with unnown last name";
			if ((lastnamechange1 <= year) && (firstnamechange1 <= year))	// if all was changed
				return HistoryFirst(year) + " " + HistoryLast(year);
		}
		else return "No person";
	}


private:
	map<int, string> First;
	map<int, string> Last;
	int birth;
};

Person::Person(const string& first, const string& last, const int& b)
{
	this->First[birth] = first;
	this->Last[birth] = last;
	this->birth = b;
}

Person::~Person()
{
}


int main()
{
	Person person("Polina", "Sergeeva", 1960);;

	for (int year : { 1959,1960 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : { 1965, 1967 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}



	/*
	Incognito
	Polina with unnown last name
	Polina  Sergeeva
	Polina  Sergeeva
	Appolinaria (Polina) Sergeeva
	Polina  Volkova (Sergeeva)
	Appolinaria (Polina) Volkova (Sergeeva)
	Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)
	Pauline (Polina)with unnown last name
	Sergeeva with unnown last name
	Pauline (Polina) Sergeeva (Sergeeva)
	Pauline (Polina) Sergeeva (Ivanova, Sergeeva)

	THIS SHOULD BE PRINTED
	*/	return 0;
}
