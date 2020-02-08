#pragma once
#include "command_container.h"

class pyramid_cmd : public cmd
{
public:
	string get_query() override
	{
		return "pyramid";
	}
	
	void execute() override
	{
        int rows;
        cout << "Please enter # of rows: ";
        cin >> rows;
		
        for (int i = 1; i <= rows; i++)
        {
            const int spaces_count = (rows - i) * 2;
            string spaces (spaces_count, ' ');
            cout << spaces;
        	
            int k = 0;
            while (k != (2 * i) - 1)
            {
                cout << "* ";
                k++;
            }
            cout << endl;
        }
	}
	
	string get_description() override
	{
		return "pyramid generator";
	}
};

