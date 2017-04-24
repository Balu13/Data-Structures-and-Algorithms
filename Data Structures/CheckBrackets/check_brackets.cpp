#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
			Bracket opening(next, position);
			opening_brackets_stack.push(opening);
        }
		else if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
			if (opening_brackets_stack.empty())
			{
				std::cout << position + 1 << "\n";
				return 0;
			}
			Bracket opening = opening_brackets_stack.top();
			if (!opening.Matchc(next))
			{
				std::cout << position + 1 << "\n";
				return 0;
			}
			opening_brackets_stack.pop();
        }
    }

	if (opening_brackets_stack.empty())
	{
		std::cout << "Success" << "\n";
	}
	else
	{
		Bracket *first { nullptr };
		while (!opening_brackets_stack.empty())
		{
			first = &opening_brackets_stack.top();
			opening_brackets_stack.pop();
		}
		std::cout << (*first).position + 1 << "\n";
	}

    // Printing answer, write your code here


    return 0;
}
