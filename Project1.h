// Project1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行unstring及結束執行。
//gh

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

struct Book {
	string name;
	string author;
	unsigned int date;
	string homeland;
	unsigned int ID;


};

void printBook(Book book) {
	cout << "Name : " << book.name << endl;
	cout << "Author : " << book.author << endl;
	cout << "date : " << book.date << endl;
	cout << "homeland : " << book.homeland << endl;
	cout << "ID : " << book.ID << endl;
}

struct SearchResult {
	unsigned int ID = -1;

	unsigned int percentage;
};

class DataBase {
private:
	const int SearchReturnMax = 10;

	std::vector<SearchResult> name;
	std::vector<SearchResult> author;
	std::vector<SearchResult> homeland;

public:
	std::vector<SearchResult> result;

	std::vector<Book> Rec;
	void search(std::string keyword);
	void searchforName(std::string keyword);
	void searchforAuthor(std::string keyword);
	void searchforHameland(std::string keyword);
	Book getBook(unsigned int ID);
	void addBook(Book book);

	unsigned int edit_distance(const std::string& s1, const std::string& s2)
	{
		const std::size_t len1 = s1.size(), len2 = s2.size();
		std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

		d[0][0] = 0;
		for (unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
		for (unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

		for (unsigned int i = 1; i <= len1; ++i)
			for (unsigned int j = 1; j <= len2; ++j)
				// note that std::min({arg1, arg2, arg3}) works only in C++11,
				// for C++98 use std::min(std::min(arg1, arg2), arg3)
				d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
		return d[len1][len2];
	}

	int levenshtein_distance(const std::string &s1, const std::string &s2)
	{
		// To change the type this function manipulates and returns, change
		// the return type and the types of the two variables below.
		int s1len = s1.size();
		int s2len = s2.size();

		auto column_start = (decltype(s1len))1;

		auto column = new decltype(s1len)[s1len + 1];
		std::iota(column + column_start - 1, column + s1len + 1, column_start - 1);

		for (auto x = column_start; x <= s2len; x++) {
			column[0] = x;
			auto last_diagonal = x - column_start;
			for (auto y = column_start; y <= s1len; y++) {
				auto old_diagonal = column[y];
				auto possibilities = {
					column[y] + 1,
					column[y - 1] + 1,
					last_diagonal + (s1[y - 1] == s2[x - 1] ? 0 : 1)
				};
				column[y] = std::min(possibilities);
				last_diagonal = old_diagonal;
			}
		}
		auto result = column[s1len];
		delete[] column;
		return result;
	}
};

void DataBase::search(std::string keyword)
{
	searchforName(keyword);
	searchforAuthor(keyword);
	searchforHameland(keyword);

	for (int i = 0; i < name.size(); i++)
	{
		result.push_back({ name.at(i).ID, name.at(i).percentage  + author.at(i).percentage  + homeland.at(i).percentage });
	}

	std::qsort(result.data(), result.size(), sizeof(SearchResult),
		[](const void * a, const void * b) -> int {if (((SearchResult*)a)->percentage < ((SearchResult*)b)->percentage)
			return -1;if (((SearchResult*)a)->percentage > ((SearchResult*)b)->percentage)
			return 1;return 0;});

	result.resize(SearchReturnMax);

	std::cout << "HAHAHA" << endl;

}

void DataBase::searchforName(std::string keyword)
{
	name.clear();

	unsigned int similarCharacters;

	for (int i = 0; i < Rec.size(); ++i) {
		//name.push_back({(unsigned int)rand(), (double)RAND_MAX / rand()});

		similarCharacters = levenshtein_distance(keyword, Rec.at(i).name);
		name.push_back({ Rec.at(i).ID, similarCharacters });
	}

}

void DataBase::searchforAuthor(std::string keyword)
{
	author.clear();

	unsigned int similarCharacters;

	for (int i = 0; i < Rec.size(); ++i) {
		//name.push_back({(unsigned int)rand(), (double)RAND_MAX / rand()});

		similarCharacters = levenshtein_distance(keyword, Rec.at(i).name);
		author.push_back({ Rec.at(i).ID, similarCharacters });
	}

}

void DataBase::searchforHameland(std::string keyword)
{
	homeland.clear();

	unsigned int similarCharacters;

	for (int i = 0; i < Rec.size(); ++i) {
		//name.push_back({(unsigned int)rand(), (double)RAND_MAX / rand()});

		similarCharacters = levenshtein_distance(keyword, Rec.at(i).name);
		homeland.push_back({ Rec.at(i).ID, similarCharacters });
	}

}

Book DataBase::getBook(unsigned int ID)
{
	for (int i = 0; i < Rec.size(); ++i) {
		if (ID == Rec[i].ID) {
			return Rec[i];
		}
	}

	return Book();
}

void DataBase::addBook(Book book)

{
	Rec.push_back(book);
}


