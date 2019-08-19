#include<iostream>
#include<cstdlib>
using namespace std;

//Defines the maximum number of unique hash values which the hash table can hold
#define MAX_SIZE 5

//The hash function used here is the modulo function(a%b) whose output ranges from 0 to b-1 for any positive a and b

struct Node        //Structure of a node of the linked list
{
    int key;             //Key value of the inserted element
    struct Node *next;    //Pointer to the next element in the linked list
};

struct Node *pointer = nullptr;     //Pointer to traverse the linked list
struct Node *temp = nullptr;        //Temporary pointer

//Array used to represent the hash table
struct Node* hash_table[MAX_SIZE];

int key_count(0);     //Stores the number of elements or keys currently present in the hash table

void initialize_hash_table();
struct Node* initialize_node(int, struct Node*, struct Node*);
int compute_hash_value(int);
void insert_key(int);
void remove_key(int);
void remove_keys_with_hash_value(int);
void print_keys_with_hash_value(int);
void print_keys();

//Driver function
int main(void)
{
    int option(0), element_key(0), hash_value(0);
    initialize_hash_table();
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert new key in the hash table\n"
             "2. Remove a key from the hash table\n"
             "3. Remove all keys having a particular hash value\n"
             "4. Print all the keys having a particular hash value\n"
             "5. Print all the keys present in the hash table\n"
             "6. Number of keys currently present in the hash table\n"
             "7. Load factor of the hash table\n"
             "8. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the key corresponding to the element to be inserted in the hash table: ";
                cin >> element_key;
                if(element_key >= 0)
                {
                    insert_key(element_key);
                }
                else
                {
                    cout << "Please enter a positive key value\n";
                }
                break;
            case 2:
                cout << "Enter the key corresponding to the element to be removed from the hash table: ";
                cin >> element_key;
                remove_key(element_key);
                break;
            case 3:
                cout << "Enter the desired hash value: ";
                cin >> hash_value;
                remove_keys_with_hash_value(hash_value);
                break;
            case 4:
                cout << "Enter the desired hash value: ";
                cin >> hash_value;
                print_keys_with_hash_value(hash_value);
                break;
            case 5:
                print_keys();
                break;
            case 6:
                cout << "The number of keys currently present in the hash table is " << key_count << "\n";
                break;
            case 7:
                cout << "The load factor of the hash table is: " << (double)key_count / MAX_SIZE << "\n";
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

//Initializes all the locations in the hash table
void initialize_hash_table()
{
    //Initially, all the locations point to nullptr
    for(int index = 0; index < MAX_SIZE; index++)
    {
        hash_table[index] = nullptr;
    }
    //When the hash table elements are added, these array elements will point to the heads of the linked lists
    //which contain the keys that are mapped to the same hash value, which will be equal to the corresponding
    //array index
}

//Returns the pointer to a newly created node after plugging in the desired values for data and next element pointer
struct Node* initialize_node(int element_key, struct Node *next_pointer_value)
{
    temp = new struct Node;
    temp->key = element_key;
    temp->next = next_pointer_value;

    //Increment the number of keys in the hash table by 1
    key_count++;

    return temp;
}

//Returns the hash value obtained as output after passing the key value to the hash function
//In this case, the modulo function is used as the hash function
int compute_hash_value(int element_key)
{
    return element_key % MAX_SIZE;
}

//Inserts the given key in the hash table, specifically in the linked list associated with the hash value of the key
void insert_key(int element_key)
{
    int hash_value = compute_hash_value(element_key);

    //In case of a collision, the new key is inserted at the head of the linked list associated with
    //the appropriate hash value
    hash_table[hash_value] = initialize_node(element_key, hash_table[hash_value]);
}

//Removes the given key from the hash table
void remove_key(int element_key)
{
    int hash_value = compute_hash_value(element_key);

    //If no key is mapped to the same hash value as that of the given key
    if(!hash_table[hash_value])
    {
        cout << "The given key is not present in the hash table as no key is mapped to the same hash value as it\n";
    }
    else
    {
        //The following code block finds the pointer to the element present just before the element to
        //be deleted and updates its next element pointer to point to the element following the element
        //to be deleted
        pointer = hash_table[hash_value];
        struct Node *previous_element_pointer = pointer;

        //Iterate through the linked list to find the key to be removed
        while((pointer != nullptr) && (pointer->key != element_key))
        {
            previous_element_pointer = pointer;
            pointer = pointer->next;
        }

        //If the key is not present in the linked list associated with a particular hash value
        if(pointer == nullptr)
        {
            cout << "The given key is not present in the hash table\n";
        }
        else if(pointer == hash_table[hash_value])
        {
            hash_table[hash_value] = pointer->next;
            free(pointer);

            //Decrement the number of keys in the hash table by 1
            key_count--;
        }
        else
        {
            //Update the next section of the previous element to point to the element following
            //the element to be removed
            previous_element_pointer->next = pointer->next;
            free(pointer);

            //Decrement the number of keys in the hash table by 1
            key_count--;
        }
    }
}

//Removes all the keys present in the hash table with the given hash value
void remove_keys_with_hash_value(int hash_value)
{
    //Checks the validity of the given hash value, since the output of the modulo function is
    //between 0 and MAX_SIZE - 1
    if((hash_value < 0) || (hash_value > MAX_SIZE - 1))
    {
        cout << "The given hash value is invalid\n";
    }
    else
    {
        if(hash_table[hash_value] == nullptr)
        {
            cout << "No keys are present in the hash table with the given hash value\n";
        }
        else
        {
            pointer = hash_table[hash_value];

            //Loop to deallocate the memory associated with each key
            while(pointer != nullptr)
            {
                temp = pointer->next;
                free(pointer);

                //Decrement the number of keys in the hash table by 1
                key_count--;

                pointer = temp;
            }
            hash_table[hash_value] = nullptr;
        }
    }
}

//Prints all the keys present in the hash table with the given hash value
void print_keys_with_hash_value(int hash_value)
{
    //Checks the validity of the given hash value, since the output of the modulo function is
    //between 0 and MAX_SIZE - 1
    if((hash_value < 0) || (hash_value > MAX_SIZE - 1))
    {
        cout << "The given hash value is invalid\n";
    }
    else
    {
        if(hash_table[hash_value] == nullptr)
        {
            cout << "No keys are present in the hash table with the hash value " << hash_value << "\n";
        }
        else
        {
            pointer = hash_table[hash_value];
            cout << "The keys with hash value " << hash_value << " are: ";
            while(pointer != nullptr)
            {
                cout << pointer->key << " ";
                pointer = pointer->next;
            }
            cout << "\n";
        }
    }
}

//Prints all the keys present in the hash table
void print_keys()
{
    for(int hash_value = 0; hash_value < MAX_SIZE; hash_value++)
    {
        print_keys_with_hash_value(hash_value);
    }
}
