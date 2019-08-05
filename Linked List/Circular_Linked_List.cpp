#include<iostream>
#include<cstdlib>
using namespace std;

struct Node        //Structure of a node of the circular linked list
{
    int data;             //Data stored in the node
    struct Node *next;    //Pointer to the next element in the circular linked list
};

struct Node *last_node = nullptr;        //Pointer to the head of the linked list
struct Node *pointer = nullptr;          //Pointer to traverse the linked list
struct Node *temp = nullptr;             //Temporary pointer

int circular_linked_list_size(0);                //Stores the current size of the circular linked list

struct Node* get_pointer(int);
struct Node* initialize_node(int, struct Node*);
void insert_begin(int);
void insert_end(int);
void insert_after(int,int);
void remove_element(int);
void print_first_and_last_elements();
void print_elements();

//Driver function
int main(void)
{
    int option(0), element(0), previous_element(0);
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert new element at the beginning of the linked list\n"
             "2. Insert new element at the end of the linked list\n"
             "3. Insert new element after a particular element\n"
             "4. Remove an element from the linked list\n"
             "5. Print the first and last elements of the linked list\n"
             "6. Print all the elements in the linked list\n"
             "7. Size of the linked list\n"
             "8. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the element to be inserted at the beginning of the linked list: ";
                cin >> element;
                insert_begin(element);
                break;
            case 2:
                cout << "Enter the element to be inserted at the end of the linked list: ";
                cin >> element;
                insert_end(element);
                break;
            case 3:
                cout << "Enter the element to be inserted in the linked list: ";
                cin >> element;
                cout << "Enter the element after which you want to insert the new element: ";
                cin >> previous_element;
                insert_after(element, previous_element);
                break;
            case 4:
                cout << "Enter the element to be removed from the linked list: ";
                cin >> element;
                remove_element(element);
                break;
            case 5:
                print_first_and_last_elements();
                break;
            case 6:
                print_elements();
                break;
            case 7:
                cout << "The size of the linked list is: " << circular_linked_list_size << "\n";
                break;
            case 8:
                exit(0);
                break;
            default:
                cout << "You have selected an invalid option. Please select a valid option\n";
        }
    }while(option != 8);
    return 0;
}

//Returns a pointer to the desired element
struct Node* get_pointer(int element)
{
    if(last_node != nullptr)
    {
        pointer = last_node;
        //Used a do-while loop as a while loop would not execute even once when the circular linked list
        //contains only a single node
        do
        {
            if(pointer->data == element)
            {
                return pointer;
            }
            pointer = pointer->next;
        }while(pointer != last_node);
    }
    return nullptr;
}

//Returns the pointer to a newly created node after plugging in the desired values for data and next element pointer
struct Node* initialize_node(int element, struct Node *next_pointer_value)
{
    temp = new struct Node;
    temp->data = element;
    temp->next = next_pointer_value;
    //Increment the size of the circular linked list by 1
    circular_linked_list_size++;
    return temp;
}

//Inserts an element at the beginning of the circular linked list
void insert_begin(int element)
{
    if(last_node == nullptr)
    {
        last_node = initialize_node(element, nullptr);
        //The next section of a single node points to itself
        last_node->next = last_node;
    }
    else
    {
        temp = initialize_node(element, last_node->next);
        last_node->next = temp;
    }
}

//Inserts an element at the end of the circular linked list
void insert_end(int element)
{
    if(last_node == nullptr)
    {
        last_node = initialize_node(element, nullptr);
        //The next section of a single node points to itself
        last_node->next = last_node;
    }
    else
    {
        temp = initialize_node(element, last_node->next);
        //Update the next section of the element pointed by last_node to point to the
        //newly added last node
        last_node->next = temp;
        //Update last_node to point it to the newly added last node of the circular linked list
        last_node = last_node->next;
    }
}

//Inserts an element after any particular element
void insert_after(int element, int previous_element)
{
    if(last_node == nullptr)
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        //Getting the pointer of the element after which the new element is to be inserted
        pointer = get_pointer(previous_element);
        if(!pointer)
        {
            cout << "The selected element is not present in the linked list\n";
        }
        else
        {
            temp = initialize_node(element, pointer->next);
            //Update the next section of the previous element to point to the newly added node
            pointer->next = temp;
        }
    }
}

//Removes an element from the circular linked list
void remove_element(int element)
{
    if(!circular_linked_list_size)
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        //Get the pointer pointing to the element to be deleted
        pointer = get_pointer(element);
        if(pointer == nullptr)
        {
            cout << "The element is not present in the linked list\n";
        }
        else
        {
            //The following code block finds the pointer to the element present just before the element to
            //be deleted and updates its next element pointer to point to the element following the element
            //to be deleted
            struct Node *previous_element_pointer = last_node;
            do
            {
                previous_element_pointer = previous_element_pointer->next;
            }while(previous_element_pointer->next != pointer);
            //Update the next section of the previous element to point to the element following
            //the element to be removed
            previous_element_pointer->next = pointer->next;
            if(pointer == last_node)
            {
                //Update the last_node pointer if the last node points to the element to be deleted
                last_node = previous_element_pointer;
            }
            free(pointer);
            //Decrement the size of the circular linked list by 1
            circular_linked_list_size--;
        }
    }
}

//Prints the first and last elements of the circular linked list
void print_first_and_last_elements()
{
    if(!circular_linked_list_size)
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        //temp here holds the pointer to the first node in the circular linked list,
        //which is the node following the last node
        temp = last_node->next;
        cout << "The first element is: " << temp->data << "\n";
        cout << "The last element is: " << last_node->data << "\n";
    }
}

//Prints all the elements present in the circular linked list starting from the last node
void print_elements()
{
    if(!circular_linked_list_size)
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        cout << "The elements in the linked list are: ";
        pointer = last_node;
        do
        {
            cout << pointer->data << " ";
            pointer = pointer->next;
        }while(pointer != last_node);
        cout << "\n";
    }
}
