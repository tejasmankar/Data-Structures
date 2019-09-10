#include<iostream>
#include<cstdlib>
using namespace std;

//Structure of a node of the singly linked list
struct Node
{
    int data;             //Data stored in the node
    struct Node *next;    //Pointer to the next element in the singly linked list
};

//Pointer to the head of the singly linked list
struct Node *head = nullptr;

//Pointer to traverse the singly linked list
struct Node *pointer = nullptr;

//Temporary pointer
struct Node *temp = nullptr;

struct Node* get_pointer(int);
struct Node* initialize_node(int, struct Node*);
void insert_begin(int);
void insert_end(int);
void insert_after(int,int);
void remove_element(int);
void print_first_and_last_elements();
void print_elements();
int linked_list_size();

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
                cout << "The size of the linked list is: " << linked_list_size() << "\n";
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
    pointer = head;
    while(pointer != nullptr)
    {
        if(pointer->data == element)
        {
            return pointer;
        }
        pointer = pointer->next;
    }
    return nullptr;
}

//Returns the pointer to a newly created node after plugging in the desired values for data and next element pointer
struct Node* initialize_node(int element, struct Node *next_pointer_value)
{
    temp = new struct Node;
    temp->data = element;
    temp->next = next_pointer_value;
    return temp;
}

//Inserts the given element at the beginning of the singly linked list
void insert_begin(int element)
{
    if(head == nullptr)
    {
        head = initialize_node(element, nullptr);
    }
    else
    {
        temp = initialize_node(element, head);

        //Update head pointer to point to the newly added first node
        head = temp;
    }
}

//Inserts the given element at the end of the singly linked list
void insert_end(int element)
{
    if(head == nullptr)
    {
        head = initialize_node(element, nullptr);
    }
    else
    {
        pointer = head;
        while(pointer->next != nullptr)
        {
            pointer = pointer->next;
        }
        temp = initialize_node(element, nullptr);

        //Update the next section of the previous last node to point to the newly added last node
        pointer->next = temp;
    }
}

//Inserts the given element after any desired element
void insert_after(int element, int previous_element)
{
    if(head == nullptr)
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

//Removes the given element from the singly linked list
void remove_element(int element)
{
    if(!linked_list_size())
    {
        cout << "Linked list is empty\n";
    }
    else if(element == head->data)
    {
        //When the element to be deleted is present at the head of the linked list
        temp = head;

        //Update the head pointer to point to the new head node which is the one following the
        //previous head node
        head = head->next;
        free(temp);
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
            struct Node *previous_element_pointer = head;
            while(previous_element_pointer->next != pointer)
            {
                previous_element_pointer = previous_element_pointer->next;
            }

            //Update the next section of the previous element to point to the element following
            //the element to be removed
            previous_element_pointer->next = pointer->next;
            free(pointer);
        }
    }
}

//Prints the elements present at the head and tail of the singly linked list
void print_first_and_last_elements()
{
    if(!linked_list_size())
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        cout << "The first element is: " << head->data << "\n";
        pointer = head;
        while(pointer->next != nullptr)
        {
            pointer = pointer->next;
        }
        cout << "The last element is: " << pointer->data << "\n";
    }
}

//Prints all the elements present in the singly linked list
void print_elements()
{
    if(!linked_list_size())
    {
        cout << "Linked list is empty\n";
    }
    else
    {
        cout << "The elements in the linked list are: ";
        pointer = head;
        while(pointer != nullptr)
        {
            cout << pointer->data << " ";
            pointer = pointer->next;
        }
        cout << "\n";
    }
}

//Returns the number of elements currently present in the singly linked list
int linked_list_size()
{
    int counter(0);
    pointer = head;
    if(pointer == nullptr)
    {
        return 0;
    }
    else
    {
        while(pointer != nullptr)
        {
            counter++;
            pointer = pointer->next;
        }
        return counter;
    }
}
