# ifndef HASHTABLE_H
# define HASHTABLE_H

# include <iostream>
# define TABLESIZE 100
using namespace std;

struct patient{
    string key = "";
    string gender = "";
    int height = 0;
    int weight = 0;
    patient *next = NULL;
};

class HashTable{
public:
    HashTable();
    HashTable(HashTable &);
    ~HashTable();
    void addItem(string, string, int, int);
    HashTable &operator[](const string);
    string getGender() const;
    int getHeight() const;
    int getWeight() const;
    int hash_function(string);
    void checktable();

private:
    patient data[TABLESIZE];
    patient *ptr;
};


# endif
