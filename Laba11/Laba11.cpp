#include "Header.h"
template <typename T>
STACK<T>::STACK()
{
    head = tail = NULL;
}
template <typename T>
STACK<T>::STACK(const STACK& other)
{
    if (other.head == NULL)
    {
        head = tail = NULL;
        return;
    }
    Element<T>* temp = other.head;
    while (temp != other.tail)
    {
        this->push(temp->number);
        temp = temp->prev;
    }
    this->push(temp->number);
}
template <typename T>
STACK<T>::STACK(STACK&& other)noexcept
{
    if (other.head == NULL)
    {
        head = tail = NULL;
        return;
    }
    head = other.head;
    tail = other.tail;
    other.head = other.tail = NULL;
}
template <typename T>
STACK<T>::~STACK()
{
    if (head == NULL) return;
    while (this->get_size() > 0)
    {
        this->pop();
    }
    head = tail = NULL;
}
template <typename T>
void STACK<T>::push(T element)
{
    Element<T>* temp = new Element<int>;
    temp->number = element;
    if (head != NULL)
    {
        temp->next = tail;
        temp->prev = head;
        tail->prev = temp;
        head->next = temp;
        tail = temp;
    }
    else temp->next = temp->prev = head = tail = temp;
}
template <typename T>
T STACK<T>::pop()
{
    if (head == tail)
    {
        if (head == NULL) return 0;
        int res = head->number;
        delete head;
        head = tail = NULL;
        return res;
    }
    int res = head->number;
    head = head->prev;
    delete head->next;
    head->next = tail;
    tail->prev = head;
    return res;
}
template <typename T>
T STACK<T>::peek()
{
    if (head == NULL) return 0;
    return head->number;
}
template <typename T>
int STACK<T>::get_size()
{
    int i = 0;
    Element<T>* temp = tail;
    if (head == NULL) return 0;
    while (temp != head)
    {
        i++;
        temp = temp->next;
    }
    return i + 1;
}
template <typename T>
STACK<T>& STACK<T>::operator=(const STACK& other)
{
    if (this == &other || other.head == NULL) return *this;
    Element<T>* temp = other.head;
    while (temp != other.tail)
    {
        this->push(temp->number);
        temp = temp->prev;
    }
    this->push(temp->number);
    return *this;
}
template <typename T>
STACK<T>& STACK<T>::operator=(STACK&& other)noexcept
{
    if (this == &other || other.head == NULL) return *this;
    head = other.head;
    tail = other.tail;
    other.head = other.tail = NULL;
    return *this;
}

class Exception
{
public:
    virtual const string GetError() const = 0;
};

inline const string Exception::GetError() const
{
    return "\n Ошибка ";
}

class OverflowException : public Exception
{
public:
    virtual const string GetError() const override
    {
        return Exception::GetError() + "Не достаточно свободного места ";
    }
};

class NoElementsException : public Exception
{
public:
    virtual const string GetError() const override
    {
        return Exception::GetError() + "Нет элементов";
    }
};


int main()
{
    setlocale(LC_ALL, "ru");
    STACK<int> STCK;
    int opt;
    cout << "Выберите действие:" << endl;
    cout << "1. Вставить элемент в конец" << endl;
    cout << "2. Удалить и вывести головной элемент" << endl;
    cout << "3. Вывести головной элемент" << endl;
    cout << "4. Вывести длину очереди" << endl;
    cout << "5. Вывести все элементы очереди" << endl;
    cout << "6. Создать новый массив с копированием и вывести ее элементы" << endl;
    cout << "7. Создать новый массив с перемещением и вывести ее элементы" << endl;
    cout << "8. Копировать 1 очередь во 2 и вывести ее элементы" << endl;
    cout << "9. Копировать 1 очередь во 2 с перемещением и вывести ее элементы" << endl;
    cout << "0. Выйти из программы" << endl;


    try {

        cin >> opt;
        while (opt != 0 && STCK.get_size() < 10)
        {
            switch (opt)
            {
            case 1:
            {
                int a;
                cout << "Введите число для вставки: ";
                cin >> a;
                STCK.push(a);
                break;
            }
            case 2:
            {
                cout << "Значение удаленного головного элемента: " << STCK.pop() << endl;
                break;
            }
            case 3:
            {
                cout << "Значение головного элемента: " << STCK.peek() << endl;
                break;
            }

            case 4:
            {
                cout << "Длина очереди: " << STCK.get_size() << endl;
                break;
            }
            case 5:
            {
                cout << STCK << endl;
                break;
            }
            case 6:
            {
                STACK<int> STCK2 = STCK;
                cout << STCK2 << endl;
                break;
            }
            case 7:
            {
                STACK<int> STCK3 = move(STCK);
                cout << STCK3 << endl;
                break;
            }
            case 8:
            {
                STACK<int> STCK2;
                STCK2 = STCK;
                cout << STCK2 << endl;
                break;
            }
            case 9:
            {
                STACK<int> queue3;
                queue3 = move(STCK);
                cout << queue3 << endl;
                break;
            }
            default:
                cout << "Введено недопустимое значение" << endl;
            }
            cin >> opt;
        }

        return 0;
    }
    catch (Exception& exception)
    {
        exception.GetError();
    }
    cout << endl;
    cout << STCK;
}
