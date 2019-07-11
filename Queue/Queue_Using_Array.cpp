#include<iostream>
#include<cstdlib>
using namespace std;

#define MAX_SIZE 100        //Defines the maximum number of elements which the queue can hold

int stack_queue[MAX_SIZE];    //Array which will be used to implement the queue
int queue_front_index(-1);    //Pointer to the front element of the queue
int queue_rear_index(0);      //Pointer to the rear element of the queue

void push_element(int);
void pop_element();
void top_element();
void stack_size();
void print_elements();

int main(void)       //Driver function
{
    int option(0), element(0);
    do
    {
        cout << "Select an appropriate option:\n1. Push element at the top of the stack \n2. Pop element from the stack\n3. Get the top element in the stack\n4. Size of the stack\n5. Print the elements in the stack\n6. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cin >> element;
                push_element(element);
                break;
            case 2:
                pop_element();
                break;
            case 3:
                top_element();
                break;
            case 4:
                stack_size();
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

