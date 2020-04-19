#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Implementation of Binary Min Heap

//Array used to represent the binary min heap
vector<int> heap_array;

void create_initial_heap();
void heapify(int);
void insert_priority_value(int);
void remove_minimum_priority_value();
int get_minimum_priority_value();

//Driver function
int main(void)
{
    int option(0), priority_value(0);
    create_initial_heap();
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert a new priority value in the binary heap\n"
             "2. Remove the the minimum priority value from the binary heap\n"
             "3. Get the minimum priority value present in the binary heap\n"
             "4. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the priority value to be inserted in the binary search tree: ";
                cin >> priority_value;
                insert_priority_value(priority_value);
                break;
            case 2:
                remove_minimum_priority_value();
                break;
            case 3:
                {
                    int minimum_priority_value(get_minimum_priority_value());
                    if(minimum_priority_value == -1)
                    {
                        cout << "The binary heap is empty\n";
                    }
                    else
                    {
                        cout << "The minimum priority value present in the heap is " << minimum_priority_value << "\n";
                    }
                }
                break;
            case 4:
                exit(0);
                break;
            default:
                cout << "You have selected an invalid option. Please select a valid option\n";
        }
    }while(option != 4);
    return 0;
}

//Creates the initial binary heap from the given priority values
void create_initial_heap()
{
    int priority_value_count(0), index(0), input(0);

    cout << "Enter the number of priority values to be added to the initial heap:\n";
    cin >> priority_value_count;

    if(priority_value_count > 0)
    {
        cout << "Enter the priority values to be added to the initial heap:\n";
        for(index = 0; index < priority_value_count; index++)
        {
            cin >> input;
            heap_array.push_back(input);
        }
        //Perform the heapify procedure on all the non-leaf nodes of the binary heap so that it satisfies
        //the heap property i.e. the priority value of a parent node is less than or equal to the
        //priority values of its children
        for(index = heap_array.size() / 2 - 1; index >= 0; index--)
        {
            heapify(index);
        }
    }
}

//Heapifies the subtree rooted at the given input index so that the heap property is satisfied for that subtree
//Note that the structure property of the binary heap is not being checked as the priority values which are inputted
//are assumed to follow/represent the level order traversal of the tree
void heapify(int index)
{
    int child_priority_value_to_swap(0), child_priority_value_to_swap_index(0);

    //If the binary heap contains 0 or 1 priority values, then it already satisfies the heap property
    if(heap_array.size() < 2)
    {
        return;
    }
    else
    {
        //If the priority value/node corresponding to the given index is a leaf or already satisfies the heap property,
        //then we do not need to heapify that priority value/node
        if((index * 2 + 1 > heap_array.size() - 1) || ((heap_array[index] <= heap_array[index * 2 + 1]) && (heap_array[index] <= heap_array[index * 2 + 2])))
        {
            return;
        }
        //If the priority value/node corresponding to the given index has a single child(which is its left child according
        //to the structure property of binary heap) and its value is lesser than the node corresponding to the given index,
        //we store the priority value and index of the child so that the its value and that of its parent node can be swapped
        else if((index * 2 + 2 > heap_array.size() - 1) && (heap_array[index] > heap_array[index * 2 + 1]))
        {
            child_priority_value_to_swap = heap_array[index * 2 + 1];
            child_priority_value_to_swap_index = index * 2 + 1;
        }
        //Else, if the priority value/node corresponding to the given index is greater than at least one of its two children,
        //we store the priority value of the child having the minimum priority value and its index so that the its value and
        //that of its parent node can be swapped
        else
        {
            child_priority_value_to_swap = min(heap_array[index * 2 + 1], heap_array[index * 2 + 2]);
            child_priority_value_to_swap_index = index * 2 + 1;
            if(heap_array[index * 2 + 1] > heap_array[index * 2 + 2])
            {
                child_priority_value_to_swap_index = index * 2 + 2;
            }
        }

        //Swapping the priority values at the given index/node and its child having the minimum priority value
        swap(heap_array[index], heap_array[child_priority_value_to_swap_index]);

        //Recursively heapify the binary heap rooted at the child of the given index/node having the minimum priority value
        //with the child node now containing the priority value of its parent i.e. the priority value at the index given as input
        heapify(child_priority_value_to_swap_index);
    }
}

//Inserts the given priority value in the binary heap
void insert_priority_value(int priority_value)
{
    //Initially insert the input priority value at the end of the binary heap array
    heap_array.push_back(priority_value);
    int new_priority_value_index(heap_array.size() - 1);

    //If the number of priority values in the heap is 1, then we do not need to process any further
    if(new_priority_value_index == 0)
    {
        return;
    }
    else
    {
        //Move the newly inserted priority value/node up the binary heap by successively swapping it with its
        //parent node having a larger priority value than itself
        while((heap_array[new_priority_value_index] < heap_array[(new_priority_value_index - 1) / 2]) && (new_priority_value_index >= 1))
        {
            swap(heap_array[new_priority_value_index], heap_array[(new_priority_value_index - 1) / 2]);
            //Update the index of the newly inserted priority value by setting it to the index of its current parent
            new_priority_value_index = (new_priority_value_index - 1) / 2;
        }
    }
}

//removes the minimum priority value from the binary heap
void remove_minimum_priority_value()
{
    //Replace the minimum priority value with the last priority value in the heap_array(Typically, its a swap)
    //This is because in the tree representation of binary heap, the last value is present at the rightmost node
    //of the bottom-most level and can be deleted easily
    heap_array[0] = heap_array[heap_array.size() - 1];

    //If the binary heap is not empty
    if(heap_array.size() > 0)
    {
        //Delete the minimum priority value which is now present at the end of the heap_array
        heap_array.erase(heap_array.end() - 1);
        //Heapify the binary heap rooted at the first location of the heap_array so that the minimum
        //priority value in the binary heap is present at that location
        heapify(0);
    }
    else
    {
        cout << "The binary heap is empty\n";
    }
}

 //Returns the minimum priority value present in the binary heap and -1 if the binary heap is empty
int get_minimum_priority_value()
{
    //Returns the first element of the heap_array which stores the minimum element of the binary min heap
    //(which represents the root of the binary heap)
    if(heap_array.size() > 0)
    {
        return heap_array[0];
    }
    //If the binary heap is empty
    else
    {
        return -1;
    }
}
