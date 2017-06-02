#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
	{
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries)
{
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
	string *contacts1 = new string[10000000];
	for (size_t i = 0; i < queries.size(); ++i)
	{
		if (queries[i].type == "add")
		{
			contacts1[queries[i].number] = queries[i].name;
		}
		else if (queries[i].type == "del")
		{
			contacts1[queries[i].number] = "";
		}
		else
		{
			string response = "not found";
			string storedName = contacts1[queries[i].number];
			if (storedName.length() > 0)
			{
				response = storedName;
			}
			result.push_back(response);
		}
	}
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}
