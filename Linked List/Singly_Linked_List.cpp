#include<iostream>
#include<cstdlib>
using namespace std;

struct Node        //Structure of a node of the linked list
{
    int data;             //Data stored in the node
    struct Node* next;    //Pointer to the next element in the linked list
};

struct Node* head = nullptr;        //Pointer to the head of the linked list
struct Node* pointer = nullptr;     //Pointer to traverse the linked list
struct Node* temp = nullptr;        //Temporary pointer

struct Node* get_pointer(int);
void initialize_node(struct Node*, struct Node*, int);
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

//Initializes a newly created node by plugging in the desired values for data and next element pointer
void initialize_node(struct Node* temp, int element, struct Node* next_pointer_value)
{
    temp->data = element;
    temp->next = next_pointer_value;
}

//Inserts an element at the beginning of the linked list
void insert_begin(int element)
{
    if(head == nullptr)
    {
        head = new struct Node;
        initialize_node(head, element, nullptr);
    }
    else
    {
        temp = new struct Node;
        initialize_node(temp, element, head);
        head = temp;
    }
}

//Inserts an element at the end of the linked list
void insert_end(int element)
{
    if(head == nullptr)
    {
        head = new struct Node;
        initialize_node(head, element, nullptr);
    }
    else
    {
        pointer = head;
        while(pointer->next != nullptr)
        {
            pointer = pointer->next;
        }
        temp = new struct Node;
        initialize_node(temp, element, nullptr);
        pointer->next = temp;
    }
}

//Inserts an element after any particular element
void insert_after(int element, int previous_element)
{
    //Getting the pointer of the element after which the new element is to be inserted
    pointer = get_pointer(previous_element);
    if(pointer == nullptr)
    {
        if(!linked_list_size())
        {
            cout << "Linked list is empty\n";
        }
        else
        {
            cout << "The selected element is not present in the linked list\n";
        }
    }
    else
    {
        temp = new struct Node;
        initialize_node(temp, element, pointer->next);
        pointer->next = temp;
    }
}

//Removes an element from the linked list
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
        head = head->next;
        free(temp);
    }
    else
    {
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
            struct Node* previous_element_pointer = head;
            while(previous_element_pointer->next != pointer)
            {
                previous_element_pointer = previous_element_pointer->next;
            }
            previous_element_pointer->next = pointer->next;
            free(pointer);
        }
    }
}

//Prints the elements present at the head and tail of the linked list
void print_first_and_last_elements()
{
    if(linked_list_size())
    {
        cout << "The first element is: " << head->data << "\n";
        pointer = head;
        while(pointer->next != nullptr)
        {
            pointer = pointer->next;
        }
        cout << "The last element is: " << pointer->data << "\n";
    }
    else
    {
        cout << "Linked list is empty\n";
    }
}

//Prints all the elements present in the linked list
void print_elements()
{
    if(linked_list_size())
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
    else
    {
        cout << "Linked list is empty\n";
    }
}

//Returns the number of elements currently present in the linked list
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
