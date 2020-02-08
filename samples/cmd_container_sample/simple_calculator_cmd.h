#pragma once
#include "command_container.h"

class simple_calculator_cmd : public  cmd
{
public:
	string get_query() override
	{
        return "calc";
	}
	
	void execute() override
	{
        char operation;
        cout << "Enter operator (+, -, *, /): ";
        cin >> operation;
		
        double operand1, operand2;
        cout << "Enter two operands: ";
        cin >> operand1 >> operand2;
        switch (operation)
        {
        case '+':
            cout << operand1 + operand2;
            break;
        case '-':
            cout << operand1 - operand2;
            break;
        case '*':
            cout << operand1 * operand2;
            break;
        case '/':
            cout << operand1 / operand2;
            break;
        default:
            cout << "Error! operator is not correct";
            break;
        }
        cout << endl;
	}
	
	string get_description() override
	{
        return "Simple calculator";
	}
};

