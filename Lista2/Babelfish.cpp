#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

template<typename V>
class HashTable {
private:
    struct Entry {
        string key;
        V value;
    };

    typedef vector<Entry> Bucket;

    Bucket *table;
    size_t tableSize;

    size_t hashKey(const std::string &key) {
        size_t hash = 0;
        for (const auto &c: key) {
            hash += c;
        }
        return hash % tableSize;
    }

    void Add(const string &key, V value) {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                bucket[i].value = value;
                return;
            }
        }
        Entry newEntry;
        newEntry.key = key;
        newEntry.value = value;
        bucket.push_back(newEntry);
    }

public:
    HashTable() {
        tableSize = 10000;
        table = new Bucket[tableSize];
    }

    ~HashTable() {
        delete[] table;
    }

    V &operator[](string key) {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                return bucket[i].value;
            }
        }
        Add(key, V());
        return operator[](key);
    }

    void remove(string key) {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                bucket.erase(i);
            }
        }
    }
};

int main() {
    HashTable<string> dict;
    string line, a, b;
    while (getline(cin, line)) {
        if (line.empty())
            break;
        istringstream sin(line);
        sin >> a >> b;
        dict[b] = a;
    }
    while (cin >> a) {
        string word = dict[a];
        if (!word.empty())
            cout << word << endl;
        else
            cout << "eh" << endl;
    }
    return 0;
}
