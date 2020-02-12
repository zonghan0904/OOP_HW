# include "HashTable.h"
# include <cstdlib>

HashTable::HashTable(){
    ptr = NULL;
}

HashTable::HashTable(HashTable &old){
    for (int i = 0; i < TABLESIZE; i++){
        patient *patptr = &old.data[i];
        patient *newnode = new patient;
        newnode -> key = patptr -> key;
        newnode -> gender = patptr -> gender;
        newnode -> height = patptr -> height;
        newnode -> weight = patptr -> weight;
        newnode -> next = NULL;
        data[i] = *newnode;
        patient *newptr = &data[i];

        patptr = patptr -> next;
        while (patptr){
            patient *nextnode = new patient;
            nextnode -> key = patptr -> key;
            nextnode -> gender = patptr -> gender;
            nextnode -> height = patptr -> height;
            nextnode -> weight = patptr -> weight;
            nextnode -> next = NULL;
            newptr -> next = nextnode;
            newptr = newptr -> next;
            patptr = patptr -> next;
        }
    }
}

HashTable::~HashTable(){
    patient *current;
    patient *temp;

    for (int i = 0; i < TABLESIZE; i++){
        current = &data[i];
        temp = current;
        while (current){
            current = current -> next;
            delete temp;
            temp = current;
        }
    }
}

void HashTable::addItem(string keyvalue, string gendertype, int heightvalue, int weightvalue){
    patient *newpatient = new patient;
    newpatient -> key = keyvalue;
    newpatient -> gender = gendertype;
    newpatient -> height = heightvalue;
    newpatient -> weight = weightvalue;

    int index = hash_function(keyvalue);

    if (data[index].key == ""){
        data[index] = *newpatient;
    }
    else {
        newpatient -> next = data[index].next;
        data[index].next = newpatient;
    }
}

HashTable &HashTable::operator[](const string keyvalue){
    int index = hash_function(keyvalue);

    ptr = &data[index];
    while (ptr != NULL && ptr -> key != keyvalue){
        ptr = ptr -> next;
    }
    return *this;
}

string HashTable::getGender() const{
    return ptr -> gender;
}

int HashTable::getHeight() const{
    return ptr -> height;
}

int HashTable::getWeight() const{
    return ptr -> weight;
}

int HashTable::hash_function(string keyvalue){
    int value = 0;
    for (int i = 8; i <= 9; i++){
        value *= 10;
        value += (int)keyvalue[i] - 48;
    }
    return value;
}

void HashTable::checktable(){
    int sum = 0;
    for (int i = 0; i < TABLESIZE; i++){
        int counter = 0;
        patient *p = &data[i];
        while (p){
            counter++;
            p = p -> next;
        }
        cout << "data box[" << i << "] have " << counter << " data" << endl;
        sum += counter;
    }
    cout << "sum: " << sum << endl;
}
