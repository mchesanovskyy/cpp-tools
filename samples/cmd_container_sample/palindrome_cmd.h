#pragma once
#include "command_container.h"

class palindrome_cmd : public cmd
{
public:
	string get_query() override
	{
		return "palindrome";
	}

	void execute() override
	{
		cout << "Please enter a string: ";
		string str;
		cin >> str;
		string reversed_str = reverse_str(str);
		if (compare(reversed_str, str))
		{
			cout << "Entered string is palindrome" << endl;
		}
		else
		{
			cout << "Entered string is NOT palindrome" << endl;
		}
		cout << str << endl;
		cout << reversed_str << endl;
	}

	string get_description() override
	{
		return "The command checks whether an entered string is palindrome";
	}

private:
	string reverse_str(string str) const
	{
		int n = str.length();
		for (auto i = 0; i < n / 2; i++)
			swap(str[i], str[n - i - 1]);
		return str;
	}

	bool compare(string s1, string s2) const
	{
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		return s1 == s2;
	}
};
