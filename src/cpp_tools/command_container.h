// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class cmd
{
public:
	virtual string get_query() = 0;
	virtual void execute() = 0;

	virtual string get_description()
	{
		return get_query();
	}
};

class cmd_not_found_exception : public exception { };

class cmd_exit_exception : public exception { };

class exit_cmd : public cmd
{
public:
	string get_query() override
	{
		return "exit";
	}

	string get_description() override
	{
		return "Exit";
	}

	void execute() override
	{
		throw cmd_exit_exception();
	}
};

class help_cmd : public cmd
{
	vector<cmd*>* _commands;
public:
	help_cmd(vector<cmd*>& commands)
	{
		_commands = &commands;
	}

	string get_query() override
	{
		return "help";
	}

	string get_description() override
	{
		return get_query();
	}

	void execute() override
	{
		const string cmd_title = "Command";
		const string desc_title = "Description";
		int longest_query_size = get_longest_query_size(cmd_title.size());
		cout << setw(longest_query_size) << left << cmd_title << " - " << desc_title << endl;
		for (size_t i = 0; i < _commands->size(); i++)
		{
			cout << setw(longest_query_size) << left << _commands->at(i)->get_query();
			cout << " - " << _commands->at(i)->get_description() << endl;
		}
	}

private:
	int get_longest_query_size(const int initial_size = 0) 
	{
		int size = initial_size;
		for (size_t i = 0; i < _commands->size(); i++)
		{
			int querySize = _commands->at(i)->get_query().size();
			if (querySize > size) {
				size = querySize;
			}
		}
		return size;
	}
};

class cmd_container
{
	vector<cmd*> _commands;
public:
	cmd_container(bool include_help = true, bool include_exit = true)
	{
		if (include_help)
			_commands.push_back(new help_cmd(_commands));

		if (include_exit)
			_commands.push_back(new exit_cmd);
	}

	void add(cmd* cmd)
	{
		_commands.push_back(cmd);
	}

	cmd& find(string query)
	{
		for (size_t i = 0; i < _commands.size(); i++)
		{
			if (compare_ignore_case(_commands[i]->get_query(), query))
			{
				return *_commands[i];
			}
		}
		throw cmd_not_found_exception();
	}

	void find_and_exec(string query)
	{
		cmd& cmd = find(query);
		cmd.execute();
	}

private:
	bool compare_ignore_case(string s1, string s2) const
	{
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		return s1 == s2;
	}
};

class cmd_env
{
public:
	static void start(cmd_container& container)
	{
		while (true)
		{
			try
			{
				string query;
				cout << endl << "CMD:> ";
				cin >> query;
				container.find_and_exec(query);
			}
			catch (cmd_exit_exception)
			{
				//
				return;
			}
			catch (cmd_not_found_exception)
			{
				cout << "Sorry, command not found. Try to type 'help' to see the list of available commands" << endl;
			}
			cin.clear();
		}
	}
};
