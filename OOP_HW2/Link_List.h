#ifndef LINK_LIST
#define LINK_LIST

#include <iostream>
using namespace std;

template <typename T>
struct Int_Node
{
	T value;
	Int_Node<T> *pre, *next;
};

template <typename T>
class Link_List
{
	template <typename U>
	friend ostream &operator<<(ostream &, const Link_List<U> &);  	// print all integers in the list
	template <typename U>
	friend istream &operator>>(istream &, Link_List<U> &);			// input a value at the back of the list, like insert_node(val);

public:
	Link_List();										// default constructor
	Link_List(const Link_List &);						// copy constructor
	~Link_List();
	int getSize() const;

	const Link_List &operator=(const Link_List &);		// assignment operator
	bool operator==(const Link_List &) const;			// equality operator
	bool operator!=(const Link_List &right) const		// inequality operator
	{
		return !(*this == right);
	}

	T &operator[](int index);							// subscript operator for non-const objects
	T operator[](int index) const;						// subscript operator for const objects

	bool insert_node(T value);							// insert an integer at the back of link list
	bool delete_node();									// delete the last node
	bool insert_node(int index, T value);				// insert an integer after the i_th position
	bool delete_node(int index);						// delete the i_th node

private:
	int size;
	Int_Node<T> *head, *tail;								// pointer to the first and the last element of Link_List
};





///////////////////////////// implementation /////////////////////////////

template <typename U>
ostream &operator<<(ostream &output, const Link_List<U> &ll){
    Int_Node<U> *node = ll.head;
    while (node){
        output << node -> value << " ";
        node = node -> next;
    }
    return output;
}

template <typename U>
istream &operator>>(istream &input, Link_List<U> &ll){
    Int_Node<U> *node = new Int_Node<U>;
    input >> node -> value;
    node -> next = NULL;
    if (ll.size == 0){
        ll.head = ll.tail = node;
        node -> pre = NULL;
    }
    else{
        node -> pre = ll.tail;
        ll.tail -> next = node;
        ll.tail = node;
    }
    ++ll.size;
    return input;
}

template <typename T>
Link_List<T>::Link_List(){
    head = tail = NULL;
    size = 0;
}

template <typename T>
Link_List<T>::Link_List(const Link_List &ll){
    size = ll.size;
    if (size == 0){
        head = tail = NULL;
    }
    else{
        Int_Node<T> *cpnode = ll.head;
        for (int i = 0; i < size; i++){
            Int_Node<T> *node = new Int_Node<T>;
            node -> value = cpnode -> value;
            node -> next = NULL;
            if (i == 0){
                head = tail = node;
                node -> pre = NULL;
            }
            else{
                node -> pre = tail;
                tail -> next = node;
                tail = node;
            }
            cpnode = cpnode -> next;
        }
    }
}

template <typename T>
Link_List<T>::~Link_List(){
    while (head){
        if (head -> next){
            head = head -> next;
            delete head -> pre;
        }
        else{
            delete head;
            head = NULL;
        }
    }
    cout << "Link_List of size " << size << " has been deleted.\n";
}

template <typename T>
int Link_List<T>::getSize() const{
    return size;
}

template <typename T>
const Link_List<T> &Link_List<T>::operator=(const Link_List &ll){
    size = ll.size;
    if (size == 0){
        head = tail = NULL;
    }
    else{
        Int_Node<T> *cpnode = ll.head;
        for (int i = 0; i < size; i++){
            Int_Node<T> *node = new Int_Node<T>;
            node -> value = cpnode -> value;
            node -> next = NULL;
            if (i == 0){
                head = tail = node;
                node -> pre = NULL;
            }
            else{
                node -> pre = tail;
                tail -> next = node;
                tail = node;
            }
            cpnode = cpnode -> next;
        }
    }
    return *this;
}

template <typename T>
bool Link_List<T>::operator==(const Link_List &ll) const{
    Int_Node<T> *nodeptr = head;
    Int_Node<T> *cmpptr = ll.head;
    if (size != ll.size) return false;
    else{
        for (int i = 0; i < size; i++){
            if (nodeptr -> value != cmpptr -> value) return false;
            else{
                nodeptr = nodeptr -> next;
                cmpptr = cmpptr -> next;
            }
        }
        return true;
    }
}

template <typename T>
T &Link_List<T>::operator[](int index){
    try {
        if (index >= size || index < 0 || size == 0) throw "index out of bound,";
    }
    catch (const char * msg){
        cerr << "\nError: " << msg << " reset index to 0.\n";
        index = 0;
        if (size == 0){
            cerr << "\nError: linked list is empty, auto insert one node value = 0.\n\n";
            this -> insert_node(0);
        }
    }
    Int_Node<T> *nodeptr = head;
    for (int i = 0; i < index; i++){
        nodeptr = nodeptr -> next;
    }
    return nodeptr -> value;
}

template <typename T>
T Link_List<T>::operator[](int index) const{
    try {
        if (index >= size || index < 0 || size == 0) throw "index out of bound,";
    }
    catch (const char * msg){
        cerr << "\nError: " << msg << " reset index to 0.\n";
        index = 0;
        if (size == 0){
            cout << "\nError: linked list is empty, return value 0.\n\n";
            return 0;
        }
    }
    Int_Node<T> *nodeptr = head;
    for (int i = 0; i < index; i++){
        nodeptr = nodeptr -> next;
    }
    return nodeptr -> value;
}

template <typename T>
bool Link_List<T>::insert_node(T value){
    Int_Node<T> *node = new Int_Node<T>;
    if (!node) return false;
    node -> value = value;
    node -> next = NULL;
    if (size == 0){
        head = tail = node;
        node -> pre = NULL;
    }
    else{
        node -> pre = tail;
        tail -> next = node;
        tail = node;
    }
    ++size;
    return true;
}

template <typename T>
bool Link_List<T>::delete_node(){
    if (size == 0) return false;
    else if (size == 1){
        delete head;
        head = tail = NULL;
        --size;
    }
    else{
        tail = tail -> pre;
        delete tail -> next;
        tail -> next = NULL;
        --size;
    }
    return true;
}

template <typename T>
bool Link_List<T>::insert_node(int index, T value){
    if ((index > size && size != 0) || index < 0) return false; // avoid invalid index.
    if (size == 0){              // special case 0
        if (index == 0) insert_node(value);
        else return false;
    }
    else{
        Int_Node<T> *node = new Int_Node<T>;
        if (!node) return false;
        node -> value = value;
        Int_Node<T> *nodeptr = head;
        for (int i = 0; i < index; i++){
            nodeptr = nodeptr -> next; //switch to node that users want to insert.
        }
        if (nodeptr){            // case that node is not tail.
            node -> next = nodeptr;
            if (nodeptr -> pre){ // case that node is not head.
                node -> pre = nodeptr -> pre;
                nodeptr = nodeptr -> pre;
                nodeptr -> next = node;
            }
            else{                // cast that node is head.
                node -> pre = NULL;
                head = node;
            }
        }
        else {                   // case that node is tail.
            node -> next = NULL;
            node -> pre = tail;
            tail -> next = node;
            tail = node;
        }
        ++size;
        return true;
    }
}

template <typename T>
bool Link_List<T>::delete_node(int index){
    if (index >= size || index < 0 || size == 0) return false;
    if (index == 0){             // case that node is head.
        if (head -> next){       // size > 1.
            head = head -> next;
            delete head -> pre;
            head -> pre = NULL;
            --size;
        }
        else {                   // size == 1.
            delete head;
            head = tail = NULL;
            --size;
        }
        return true;
    }
    else{                        // other case (including tail).
        Int_Node<T> *nodeptr = head;
        Int_Node<T> *copyptr;
        for (int i = 0; i < index-1; i++){ // switch to the node's previous one.
            nodeptr = nodeptr -> next;
        }
        copyptr = nodeptr;
        if (!nodeptr -> next -> next){  // case that node is tail.
            delete nodeptr -> next;
            nodeptr -> next = NULL;
            tail = nodeptr;
        }
        else{                           // case that node is others.
            nodeptr -> next = nodeptr -> next -> next;
            nodeptr = nodeptr -> next;
            delete nodeptr -> pre;
            nodeptr -> pre = copyptr;
        }
        --size;
        return true;
    }

}


#endif // LINK_LIST
