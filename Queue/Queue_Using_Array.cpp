#include<iostream>
#include<cstdlib>
using namespace std;

//Program to implement a queue using array

//Defines the maximum number of elements which the queue can hold
#define MAX_SIZE 5

//Array used to represent the queue
int queue_array[MAX_SIZE];

//Pointer to the front element of the queue
int queue_front_index(0);

//Pointer to the location following the rear element of the queue
int queue_rear_index(0);

//In this queue, we will insert elements at the front of the array if there is space after removal of some elements
//and no element can be added at the end of the array.
//Insertion and removal of elements from the queue will happen in a circular fashion.
//In this implementation, in a queue of size MAX_SIZE, we will add only MAX_SIZE-1 elements because
//otherwise there would be ambiguity when the queue is either full or empty, as in both the cases
//queue_front_index = queue_rear_index

void enqueue(int);
void dequeue();
void front_element();
void rear_element();
int queue_size();
void print_elements();

//Driver function
int main(void)
{
    int option(0), element(0);
    do
    {
        cout << "Select an appropriate option:\n"
        "1. Insert element in the queue\n"
        "2. Remove element from the queue\n"
        "3. Print the front element of the queue\n"
        "4. Print the rear element of the queue\n"
        "5. Size of the queue\n"
        "6. Print the elements in the queue\n"
        "7. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the element to be inserted in the queue: ";
                cin >> element;
                enqueue(element);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                front_element();
                break;
            case 4:
                rear_element();
                break;
            case 5:
                cout << "The size of the queue is: " << queue_size() << "\n";
                break;
            case 6:
                print_elements();
                break;
            case 7:
                exit(0);
                break;
            default:
                cout << "You have selected an invalid option. Please select a valid option\n";
        }
    }while(option != 7);
    return 0;
}

//Inserts the given element at the end of the queue
void enqueue(int element)
{
    if((queue_rear_index + 1) % MAX_SIZE != queue_front_index)
    {
        queue_array[(queue_rear_index) % MAX_SIZE] = element;
        queue_rear_index = (queue_rear_index + 1) % MAX_SIZE;
    }
    else
    {
        cout << "Queue is full\n";
    }
}

//Removes the front element from the queue
void dequeue()
{
    if(queue_front_index != queue_rear_index)
    {
        int temp = queue_array[queue_front_index];
        queue_front_index = (queue_front_index + 1) % MAX_SIZE;
    }
    else
    {
        cout << "Queue is empty\n";
    }
}

//Prints the front element of the queue
void front_element()
{
    if(queue_size())
    {
        cout << "The front element is: " << queue_array[queue_front_index] << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}

//Prints the rear element of the queue
void rear_element()
{
    if(queue_size())
    {
        //The rear element index is (queue_rear_index + MAX_SIZE - 1) % MAX_SIZE and not queue_rear_index - 1
        //as the index value would be negative when queue_rear_index is 0. This is to ensure that we get the
        //proper rear element after we insert elements in the front(index 0 onwards) of the array after we have
        //removed some elements from the front of a completely filled queue
        cout << "The rear element is: " << queue_array[(queue_rear_index + MAX_SIZE - 1) % MAX_SIZE] << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}

//Returns the number of elements currently present in the queue using the pointers to the
//front and rear elements of the queue
int queue_size()
{
    if(queue_front_index == queue_rear_index)
    {
        return 0;
    }
    else if(queue_rear_index > queue_front_index)
    {
        return queue_rear_index - queue_front_index;
    }
    return MAX_SIZE - queue_front_index + queue_rear_index;
}

//Prints all the elements currently present in the queue from the front to the rear
void print_elements()
{
    int index(queue_front_index), length(queue_size());
    if(length)
    {
        cout << "The elements in the queue are: ";
        while(length--)
        {
            cout << queue_array[index] << " ";
            index = (index + 1) % MAX_SIZE;
        }
        cout << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}
