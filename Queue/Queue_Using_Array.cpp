#include<iostream>
#include<cstdlib>
using namespace std;

#define MAX_SIZE 100        //Defines the maximum number of elements which the queue can hold

int queue_array[MAX_SIZE];    //Array which will be used to implement the queue
int queue_front_index(-1);    //Pointer to the front element of the queue
int queue_rear_index(-1);      //Pointer to the rear element of the queue
//Initially, both the front and rear pointers are equal as the queue is empty.

void insert_element(int);
void remove_element();
void front_element();
void queue_size();
void print_elements();

int main(void)       //Driver function
{
    int option(0), element(0);
    do
    {
        cout << "Select an appropriate option:\n1. Insert element in the queue \n2. Remove element from the queue\n3. Get the front element in the queue\n4. Size of the queue\n5. Print the elements in the queue\n6. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cin >> element;
                insert_element(element);
                break;
            case 2:
                remove_element();
                break;
            case 3:
                front_element();
                break;
            case 4:
                queue_size();
                break;
            case 5:
                print_elements();
                break;
            case 6:
                exit(0);
                break;
        }
    }while(option != 6);
    return 0;
}

void insert_element(int element)       //Inserts the element at the end of the queue
{
    if(queue_rear_index < MAX_SIZE - 1)
    {
        queue_array[++queue_rear_index] = element;
    }
    else
    {
        cout << "Queue is full\n";
    }
}

void remove_element()      //Removes the front element from the queue
{
    if(queue_rear_index - queue_front_index >= 1)
    {
        int temp = queue_array[queue_front_index];
        queue_front_index++;
    }
    else
    {
        cout << "Queue is empty\n";
    }
}

void front_element()       //Prints the front element of the queue
{
    if(queue_rear_index - queue_front_index >= 1)
    {
        cout << queue_array[queue_front_index] << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}

void queue_size()         //Prints the current size of the queue using the pointers to the front and rear elements of the queue
{
    cout << queue_rear_index - queue_front_index + 1 << "\n";
}

void print_elements()      //Prints all the elements currently present in the queue from the front to the rear
{
    int index(queue_front_index);
    if(queue_rear_index - queue_front_index >= 1)
    {
        while(index <= queue_rear_index)
        {
            cout << queue_array[index++] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "Queue is empty\n";
    }
}
