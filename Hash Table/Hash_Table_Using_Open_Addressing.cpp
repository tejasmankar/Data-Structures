#include<iostream>
#include<cstdlib>

using namespace std;

//Implementation of open addressing using double hashing method

//Defines the maximum number of keys which the hash table can hold
#define MAX_SIZE 5

//Array used to represent the hash table
int hash_table[MAX_SIZE];

//Stores the number of elements or keys currently present in the hash table
int key_count(0);

void initialize_hash_table();
int compute_initial_hash_value(int);
int compute_offset_hash_value(int);
int element_index(int);
void insert_key(int);
void remove_key(int);
void search_key(int);
void print_keys();

//Driver function
int main(void)
{
    int option(0), element_key(0);
    initialize_hash_table();
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert a new key in the hash table\n"
             "2. Remove a key from the hash table\n"
             "3. Search a key in the hash table\n"
             "4. Print all the keys present in the hash table\n"
             "5. Number of keys currently present in the hash table\n"
             "6. Load factor of the hash table\n"
             "7. Exit\n";
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
                cout << "Enter the key corresponding to the element to be searched in the hash table: ";
                cin >> element_key;
                search_key(element_key);
            case 4:
                print_keys();
                break;
            case 5:
                cout << "The number of keys currently present in the hash table is " << key_count << "\n";
                break;
            case 6:
                cout << "The load factor of the hash table is: " << (double)key_count / MAX_SIZE << "\n";
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

//Initializes all the locations in the hash table
void initialize_hash_table()
{
    //Initializing the hash table, all array elements initially contain -1, which tells that
    //all the locations are initially empty
    for(int index = 0; index < MAX_SIZE; index++)
    {
        hash_table[index] = -1;
    }
}

//Returns the hash value obtained as output after passing the key value to the hash function
//In this case, the modulo function is used as the hash function
//This function gives us the initial location in the hash table to probe for the keys
int compute_initial_hash_value(int element_key)
{
    return element_key % MAX_SIZE;
}

//Returns the offset value to be added to the initial hash value if the location indicated
//by the initial hash value is already occupied
//In case of linear probing, the offset value is 1
int compute_offset_hash_value(int element_key)
{
    int offset = MAX_SIZE - (element_key % MAX_SIZE);
    if(offset % MAX_SIZE == 0)
    {
        //Incrementing the offset value by 1 if it is divisible by the size of the hash table(MAX_SIZE),
        //because if offset is divisible by MAX_SIZE, we will probe the location denoted by the
        //initial hash value repeatedly
        offset++;
    }
    return offset;
}

//Returns the index of the given element key in the hash table
int element_index(int element_key)
{
    //Compute the initial location where we search for the given key
    int initial_location = compute_initial_hash_value(element_key);

    //Initialize the variable that will be used to iterate through the hash table to the initial hash value
    int index = initial_location;

    //Boolean variable to check if we have visited the location indicated by the initial hash value twice
    bool flag = 0;

    //Offset to be added to the current location if it does not contain the given key
    int offset = compute_offset_hash_value(element_key);

    while(hash_table[index] != element_key)
    {
        //Adding offset to the index of the hash table
        index = ((index + offset) % MAX_SIZE);

        if(index == initial_location)
        {
            //Set the flag to 1 if we have visited the initial hash location twice
            //This means that the given key is not present in the hash table as we have checked
            //all the locations in the hash table at least once
            //The fact that every location in the hash table is checked at least once is true
            //as our hash table size is a prime number
            flag = 1;
            break;
        }
    }

    //If the key is not present in the hash table, return the size of the hash table(MAX_SIZE)
    if(flag)
    {
        return MAX_SIZE;
    }

    //Otherwise, return the index corresponding to the given key
    return index;
}

//Inserts the given key in the hash table
void insert_key(int element_key)
{
    //If the hash table is already full of keys(values other than -1 or -2)
    if(key_count == MAX_SIZE)
    {
        cout << "No keys/elements can be added in the hash table as it is full\n";
    }
    else
    {
        int initial_location = compute_initial_hash_value(element_key);
        int index = initial_location;
        int offset = compute_offset_hash_value(element_key);

        //Iterate through the hash table until we find an empty location(a location having value -1) or
        //a location where a key was deleted(a location having value -2)
        while(hash_table[index] >= 0)
        {
            index = ((index + offset) % MAX_SIZE);
        }

        //Insert the key value in the required location
        hash_table[index] = element_key;

        //Increment the number of keys in the hash table by 1
        key_count++;
    }
}

//Removes the given key from the hash table
void remove_key(int element_key)
{
    //If the hash table is empty
    if(!key_count)
    {
        cout << "No keys/elements can be removed from the hash table as it is empty\n";
    }
    else
    {
        //Get the index of the key to be deleted in the hash table
        int index = element_index(element_key);

        //Delete the key by placing a tombstone marker
        //A tombstone marker indicates that a key has been deleted from that location
        hash_table[index] = -2;

        //Decrement the number of keys in the hash table by 1
        key_count--;
    }
}

//Returns the index of the given key in the hash table
void search_key(int element_key)
{
    //If the hash table is empty
    if(!key_count)
    {
        cout << "The hash table is empty\n";
    }
    else
    {
        //Get the index of the key to be searched in the hash table
        int index = element_index(element_key);

        //If the given key is not present in the hash table
        if(index == MAX_SIZE)
        {
            cout << "The given key is not present in the hash table\n";
        }

        //Else print the index of the given key in the hash table
        else
        {
            cout << "The given key is present at location " << index << " in the hash table\n";
        }
    }
}

//Prints all the keys present in the hash table
void print_keys()
{
    //If the hash table is empty
    if(!key_count)
    {
        cout << "The hash table is empty\n";
    }
    else
    {
        cout << "The keys present in the hash table are: ";
        for(int index = 0; index < MAX_SIZE; index++)
        {
            if(hash_table[index])
            {
                cout << hash_table[index] << " ";
            }
        }
        cout << "\n";
    }
}
