#include<iostream>
#include<cstdlib>
using namespace std;

#define MAX_SIZE 100        //Defines the maximum number of elements which the stack can hold

int stack_array[MAX_SIZE];    //Array which will be used to implement the stack
int stack_top_index(-1);     //Pointer to the topmost element of the stack

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

void push_element(int element)     //Pushes an element on the top of the stack
{
    if(stack_top_index < MAX_SIZE - 1)
    {
        stack_array[++stack_top_index] = element;
    }
    else
    {
        cout << "Stack Overflow\n";
    }
}

void pop_element()      //Pops out(removes) the topmost element from the stack
{
    if(stack_top_index >= 0)
    {
        int temp = stack_array[stack_top_index];
        stack_top_index--;
    }
    else
    {
        cout << "Stack Underflow\n";
    }
}

void top_element()       //Prints the topmost element of the stack
{
    if(stack_top_index >= 0)
    {
        cout << stack_array[stack_top_index] << "\n";
    }
    else
    {
        cout << "Stack is empty\n";
    }
}

void stack_size()         //Prints the current size of the stack using the pointer to the topmost elemnt of the stack
{
    cout << stack_top_index + 1 << "\n";
}

void print_elements()      //Prints all the elements currently present in the stack starting from the bottom of the stack
{
    int index(0);
    if(stack_top_index >= 0)
    {
        while(index <= stack_top_index)
        {
            cout << stack_array[index++] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "Stack is empty\n";
    }
}
