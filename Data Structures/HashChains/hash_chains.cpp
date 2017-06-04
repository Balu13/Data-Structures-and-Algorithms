#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

struct Elem {
	string record;
	Elem *next = NULL;
	Elem *prev = NULL;
};

class QueryProcessor
{
    int bucket_count;
    // store all strings in one vector
    vector<Elem*> elems;
    size_t hash_func(const string& s) const
	{
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
		{
			hash = ((hash * multiplier + s[i]) % prime + prime) % prime;
		}
        return (hash % bucket_count + bucket_count) % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count)
	{
		elems.resize(bucket_count);
	}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
			Elem *found = elems[query.ind];
			while (found != NULL)
			{
				std::cout << found->record << " ";
				found = found->next;
			}
            std::cout << "\n";
        } else {
			int hash = hash_func(query.s);
			Elem *elem = find(query.s, hash);
			if (query.type == "find")
			{
				writeSearchResult(elem != NULL);
			}
            else if (query.type == "add")
			{
				if (elem == NULL)
				{
					elem = new Elem();
					elem->record = query.s;
					if (elems[hash] != NULL)
					{
						elem->next = elems[hash];
						elems[hash]->prev = elem;
					}
					elems[hash] = elem;
				}
            }
			else if (query.type == "del")
			{
				if (elem != NULL)
				{
					if (elem->prev != NULL)
					{
						elem->prev->next = elem->next;
					}
					else
					{
						elems[hash] = elem->next;
					}
					if (elem->next != NULL)
					{
						elem->next->prev = elem->prev;
					}
					delete elem;
				}
            }
        }
    }

	Elem * find(string s, int hash)
	{
		Elem *elem = elems[hash];
		while (elem != NULL)
		{
			if (elem->record == s)
			{
				break;
			}
			elem = elem->next;
		}
		return elem;
	}

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
