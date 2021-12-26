#include <iostream>
using namespace std;

template <typename T>
struct Element
{
	T number;
	Element* next;
	Element* prev;
};

template <typename T>
class STACK
{
	Element<T>* head;
	Element<T>* tail;
public:
	STACK();
	STACK(const STACK& other);
	STACK(STACK&& other)noexcept;
	~STACK();
	
	void push(T element);
	T pop();
	T peek();
	int get_size();

	STACK& operator=(const STACK& other);
	STACK& operator=(STACK&& other)noexcept;

	friend ostream &operator<<(ostream& stream, const STACK& that)
	{
		if (that.head == NULL) return stream << "Очередь пуста";
		Element<T>* temp = that.head;
		while (temp != that.tail)
		{
			stream << temp->number << " ";
			temp = temp->prev;
		} 
		return stream << temp->number;
	}
};
