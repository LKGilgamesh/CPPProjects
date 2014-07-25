#include <iostream>

class DynamicArray{
public:
	DynamicArray();
	DynamicArray(int capacity);
	~DynamicArray();
	bool insert(std::string str);
	std::string remove();
	std::string remove(int index);
	void remove(std::string str);
	int index_of(std::string str);
	std::string item_at(int index);
	int size();
	int capacity();
	void clear();
	DynamicArray & operator=(const DynamicArray & rhs);
	const DynamicArray operator+(const DynamicArray & rhs) const;
	std::string &operator[](const int index);
	friend std::ostream &operator<<(std::ostream &os, const DynamicArray rhs);
private:
	void grow();
	std::string *DA;
	int SIZE;
	int CAPACITY;
	int get_size() const;
	int get_capacity() const;
	std::string get_item(int index) const;

};