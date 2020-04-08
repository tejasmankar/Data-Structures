#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//Implementation of Standard Trie

//All the input strings are assumed to be lowercase

//Structure of a node of the Standard Trie
struct Node
{
    struct Node *alphabets[26] = {nullptr};     //Array containing pointers to the next character nodes of the respective strings
    bool is_last_character;                          //Boolean variable which is set to 1 if the current node contains the last character of some input string
};

//Initializing the pointer to the root of the trie
struct Node *root = new struct Node;

struct Node* create_new_node();
bool is_leaf_node(struct Node*);
bool search_string(string, struct Node*);
void insert_string(string, struct Node*);
void delete_string(string, struct Node*);
void print_all_strings(string, struct Node*);

int main(void)
{
    int option(0);
    string input_string;
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert a new lowercase string in the trie\n"
             "2. Remove a string from the trie\n"
             "3. Check whether a string is present in the trie\n"
             "4. Print all the strings which are present in the trie\n"
             "5. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the string to be inserted in the trie: ";
                cin >> input_string;
                insert_string(input_string, root);
                break;
            case 2:
                cout << "Enter the string to be removed from the trie: ";
                cin >> input_string;
                delete_string(input_string, root);
                break;
            case 3:
                cout << "Enter the string to be searched in the trie: ";
                cin >> input_string;
                if(!search_string(input_string, root))
                {
                    cout << "The given string is not present in the trie\n";
                }
                else
                {
                    cout << "The given string is present in the trie\n";
                }
                break;
            case 4:
                print_all_strings("", root);
                break;
            case 5:
                exit(0);
                break;
            default:
                cout << "You have selected an invalid option. Please select a valid option\n";
        }
    }while(option != 5);

    return 0;
}

//Returns a pointer to the newly created node
struct Node* create_new_node()
{
    struct Node *pointer = new struct Node;
    pointer->is_last_character = false;
    return pointer;
}

//Returns true if the given node is a leaf node or false otherwise
bool is_leaf_node(struct Node *pointer)
{
    for(int index = 0; index < 26; index++)
    {
        if(pointer->alphabets[index])
        {
            return false;
        }
    }
    return true;
}

//Returns true if the given string is present in the trie rooted at the node pointed by the given pointer or false otherwise
bool search_string(string input_string, struct Node *pointer)
{
    //If the next character of the string is not present in any child node of the current node,
    //it means that the given string is not present in the trie
    if(pointer->alphabets[input_string[0] - 'a'] == nullptr)
    {
        return false;
    }
    else
    {
        //If there are no characters left to check in the given string and we have reached the node containing the
        //last word of the string, then we have found the given string in the trie
        if(input_string.size() == 1)
        {
            if(pointer->alphabets[input_string[0] - 'a']->is_last_character == true)
            {
                return true;
            }
            //If the given string is a prefix of some string in the trie but it's never inserted as an individual
            //string in the trie, return false
            return false;
        }
        //In this function, we only match the first character of the input string with the characters present
        //in the trie nodes. In each successive recursive call, we pass the input string after removing it's first
        //character which is already present in the trie. The pointer is also updated to point to the appropriate child
        //of the parent node.
        return search_string(input_string.substr(1, input_string.size() - 1), pointer->alphabets[input_string[0] - 'a']);
    }
}

//Recursively inserts the given string in the trie rooted at the node pointed by the given pointer
void insert_string(string input_string, struct Node *pointer)
{
    //If the first character of the input string is not present in the trie, create a new node and
    //insert that character in the newly created node
    if(pointer->alphabets[input_string[0] - 'a'] == nullptr)
    {
        pointer->alphabets[input_string[0] - 'a'] = create_new_node();
    }
    //Set the is_last_character flag to true if the current character being stored is the last character of the string
    if(input_string.size() == 1)
    {
        pointer->alphabets[input_string[0] - 'a']->is_last_character = true;
    }
    //Recursively insert the next character of the input string in the trie
    else
    {
        insert_string(input_string.substr(1, input_string.size() - 1), pointer->alphabets[input_string[0] - 'a']);
    }
}

//Recursively deletes the given string in the trie rooted at the node pointed by the given pointer
void delete_string(string input_string, struct Node *pointer)
{
    //If any character of the string is not present in the trie, the string is not present in the trie
    if(pointer->alphabets[input_string[0] - 'a'] == nullptr)
    {
        cout << "The given string is not present in the trie\n";
        return;
    }
    else
    {
        //If a string character is present in the trie, then recursively search for the next character of
        //the string using the same technique that is used in the search_string function above
        if(input_string.size() > 1)
        {
            delete_string(input_string.substr(1, input_string.size() - 1), pointer->alphabets[input_string[0] - 'a']);
        }
        //If any child of the node being pointed by pointer is the last character of the input string to be deleted
        if(input_string.size() == 1)
        {
            if(pointer->alphabets[input_string[0] - 'a']->is_last_character)
            {
                //If any child of the node being pointed by pointer is the last character of the input string to be deleted
                //and is also a leaf node, delete that child node containing the last character of the input_string
                if(is_leaf_node(pointer->alphabets[input_string[0] - 'a']))
                {
                    delete pointer->alphabets[input_string[0] - 'a'];
                    pointer->alphabets[input_string[0] - 'a'] = nullptr;
                }
                //If the node to be deleted is not a leaf and contains the last character of the input string to be deleted,
                //simply mark it's is_last_character flag to false. This is to ensure that we do not delete any nodes of the
                //input string to be deleted as the input string is a prefix of at least one longer string(as this last node
                //is not a leaf node) which is also inserted in the trie
                else
                {
                    pointer->alphabets[input_string[0] - 'a']->is_last_character = false;
                }
            }
            //If the input string to be deleted is a proper prefix of some string which is already inserted in the
            //trie and the prefixed string is not inserted in the trie, then the given string is not present in the trie
            else
            {
                cout << "The given string is not present in the trie\n";
                return;
            }
        }
        else
        {
            //If any child of the node being pointed by pointer is a leaf node but does not contain the last character
            //of any string which is inserted in the trie, then delete such a child node. This is to ensure that we do
            //not delete any inserted string which is a prefix of the input string being deleted during the recursive
            //bottom-up deletion of the nodes containing the characters of the string to be deleted
            if((is_leaf_node(pointer->alphabets[input_string[0] - 'a'])) && !(pointer->alphabets[input_string[0] - 'a']->is_last_character))
            {
                    delete pointer->alphabets[input_string[0] - 'a'];
                    pointer->alphabets[input_string[0] - 'a'] = nullptr;
            }
        }
    }
}

//Prints all the strings which are inserted or currently present in the trie
void print_all_strings(string concatenated_prefix, struct Node *pointer)
{
    //If the root node of the trie has no children, then the trie is empty
    if(is_leaf_node(root))
    {
        cout << "No strings are present in the trie\n";
    }
    else
    {
        //Check for the presence of every alphabet in the pointer node as the children of pointer node could
        //begin with any alphabet
        for(int index = 0; index < 26; index++)
        {
            //temporary_prefix stores the substring formed by appending all the characters present in the path
            //from the root to the to the pointer node. This is initialized on every iteration of the loop so
            //that all the children of the pointer node could append their values to a common prefix
            string temporary_prefix(concatenated_prefix);
            if(pointer->alphabets[index] != nullptr)
            {
                //Update the temporary_prefix by appending the node present in the child node
                temporary_prefix += char('a' + index);
                //If any child of the pointer node is the last character of any string which is inserted in the
                //trie, print that entire string
                if(pointer->alphabets[index]->is_last_character)
                {
                    cout << temporary_prefix << "\n";
                    //If we have reached a leaf node of the trie, then continue printing the strings present in the trie
                    //by looking for the subsequent/next children of the pointer node
                    if(is_leaf_node(pointer->alphabets[index]))
                    {
                        continue;
                    }
                }
                //Recursively print the next characters of the strings
                print_all_strings(temporary_prefix, pointer->alphabets[index]);
            }
        }
    }
}
