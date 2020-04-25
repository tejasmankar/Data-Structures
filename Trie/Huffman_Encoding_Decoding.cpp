#include<iostream>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

//Implementation of Huffman Encoding/Decoding

//Structure of a node of the Huffman trie in whose leaf nodes the characters present in the given string would be stored
struct Node
{
    char character = 0;          //Character stored in the node. The internal nodes will not store any character
    int frequency = 0;           //Frequency of the character stored in the node in the input string. Internal nodes would store the sum of the frequencies of the characters present in the leaf nodes of the subtrees rooted at those nodes.
    struct Node *left_child;     //Pointer to the left child of the node
    struct Node *right_child;    //Pointer to the right child of the node
};

//Pointer to the root of the Huffman trie
struct Node *root = nullptr;

//Initialize the frequency of all letters in the alphabet to zero
int character_frequency_array[26] = {0};

//Declare a priority queue which will return an element containing the character in the priority queue having
//the minimum frequency at that time
priority_queue<pair<int, pair<char, struct Node*> >, vector< pair< int, pair<char, struct Node*> > >, greater< pair<int, pair<char, struct Node*> > > > frequency_priority_queue;

void encode_string(string);
void reset_character_frequency_array();
void calculate_character_frequency(string);
void insert_characters_in_priority_queue();
void build_huffman_trie();
struct Node* initialize_node(pair<int, pair<char, struct Node*> >, struct Node*, struct Node*);
pair<int, pair<char, struct Node*> > remove_minimum_heap_frequency();
struct Node* create_huffman_trie_node(pair<int, pair<char, struct Node*> >);
void print_encoded_strings(string, struct Node*);
string decode_string(string, struct Node*);

//Driver function
int main(void)
{
    int option(0);
    string input_string(""), encoded_string("");
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Encode a string\n"
             "2. Decode an encoded string(Any appropriate substring of this string should be equal to the encoded codeword of any character present in the originally inserted string)\n"
             "3. Print encoded strings corresponding to all characters in the input string\n"
             "4. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the string to be encoded: ";
                cin >> input_string;
                if(input_string.size() <= 1)
                {
                    cout << "The size of the string to be encoded should be at least 2\n";
                    continue;
                }
                encode_string(input_string);
                break;
            case 2:
                {
                    cout << "Enter a valid encoded string to be decoded: ";
                    cin >> encoded_string;
                    string decoded_string = decode_string(encoded_string, root);
                    if(decoded_string == "invalid")
                    {
                        cout << "The given encoded string is invalid\n";
                    }
                    else
                    {
                        cout << "The decoded string is " << decoded_string << "\n";
                    }
                    break;
                }
            case 3:
                cout << "The encoded strings corresponding to all characters in the input string are:\n";
                print_encoded_strings("", root);
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

//Encodes the given string by building a Huffman trie
void encode_string(string input_string)
{
    reset_character_frequency_array();
    calculate_character_frequency(input_string);
    insert_characters_in_priority_queue();
    build_huffman_trie();
}

//Resets all the elements of the character_frequency_array to 0
void reset_character_frequency_array()
{
    for(int index = 0; index < 26; index++)
    {
        character_frequency_array[index] = 0;
    }
}

//Sets each character_frequency_array element to the frequency of the corresponding character in the given string
//This function creates a character-frequency map for all the characters present in the given string
void calculate_character_frequency(string input_string)
{
    for(int index = 0; index < input_string.size(); index++)
    {
        character_frequency_array[input_string[index] - 'a']++;
    }
}

//Inserts the characters and their frequencies stored in the input character-frequency map in a priority queue
void insert_characters_in_priority_queue()
{
    for(int index = 0; index < 26; index++)
    {
        //Insert the characters of the string having a non-zero frequency into the priority queue
        if(character_frequency_array[index])
        {
            frequency_priority_queue.push(make_pair(character_frequency_array[index], make_pair(index + 'a', nullptr)));
        }
    }
}

//Builds a Huffman trie by recursively adding the priority queue nodes storing the minimum character frequency values
void build_huffman_trie()
{
    //If the priority queue contains only one element, then that element is the root of the Huffman trie
    //It stores the sum of frequencies of all the characters present in the string. In this case, we
    if(frequency_priority_queue.size() == 1)
    {
        root = create_huffman_trie_node(frequency_priority_queue.top());
        frequency_priority_queue.pop();
    }
    else
    {
        //Get the priority queue node containing the smallest frequency value
        pair<int, pair<char, struct Node*> > smallest_element = remove_minimum_heap_frequency();

        //Get the priority queue node containing the second smallest frequency value
        pair<int, pair<char, struct Node*> > second_smallest_element = remove_minimum_heap_frequency();

        //Add the smallest frequency value to a Huffman trie node
        struct Node *first_child = create_huffman_trie_node(smallest_element);

        //Add the second smallest frequency value to a Huffman trie node
        struct Node *second_child = create_huffman_trie_node(second_smallest_element);

        //Add the parent node containing the sum of frequencies of the characters present in the above two nodes
        //to the Huffman trie. Its left child will be the node containing the smaller of the above two frequency values
        //and the right child will be the other node
        struct Node *parent_node = initialize_node(make_pair(smallest_element.first + second_smallest_element.first, make_pair('0', nullptr)), first_child, second_child);

        //Add the above parent node in the priority queue so that its frequency will be considered in future steps. The
        //priority queue node also stores the pointer to this parent node so that the Huffman trie is constructed properly
        //in further steps
        frequency_priority_queue.push(make_pair(smallest_element.first + second_smallest_element.first, make_pair('0', parent_node)));

        //Recursively call the function
        build_huffman_trie();
    }
}

//Returns a pointer to a newly created node to be inserted in the Huffman trie after initializing it with the given values
struct Node* initialize_node(pair<int, pair<char, struct Node*> > element, struct Node *left_child, struct Node *right_child)
{
    struct Node *new_node = new struct Node();
    new_node->character = element.second.first;
    new_node->frequency = element.first;
    new_node->left_child = left_child;
    new_node->right_child = right_child;

    return new_node;
}

//Removes and returns the heap node containing the minimum frequency
pair<int, pair<char, struct Node*> > remove_minimum_heap_frequency()
{
    pair<int, pair<char, struct Node*> > minimum_frequency_node = frequency_priority_queue.top();
    frequency_priority_queue.pop();
    return minimum_frequency_node;
}

//Returns the pointer to a newly created node to be added to the Huffman trie
struct Node* create_huffman_trie_node(pair<int, pair<char, struct Node*> > priority_queue_element)
{
    //If the priority queue node contains any character other than the empty character, create a new node and return its pointer
    //This creates the leaf nodes of the Huffman trie which store the characters present in the input string
    if(priority_queue_element.second.first != '0')
    {
        return initialize_node(priority_queue_element, nullptr, nullptr);
    }
    //If the priority queue node contains the empty character, then that node contains the sum of frequencies of the characters
    //present in the leaf nodes of the subtree of which it is the root. In this case, just return the pointer to this parent node
    //(which is stored in the priority queue element) as there is no need to create a new node since its already present in the Huffman trie
    //Also, this condition will only be satisfied by the internal nodes of the Huffman trie
    else
    {
        return priority_queue_element.second.second;
    }
}

//Prints the encoded codewords corresponding to all the characters present in the given encoded string
void print_encoded_strings(string encoded_string, struct Node *pointer)
{
    //If the pointer points to an internal node of the trie
    if(pointer->character == '0')
    {
        //Recursively traverse the left and right subtrees of the given node, appending 0 to the given
        //encoded string every time we follow the left_child pointer and 1 every time we follow the
        //right_child pointer
        print_encoded_strings(encoded_string + "0", pointer->left_child);
        print_encoded_strings(encoded_string + "1", pointer->right_child);
    }
    //If the pointer points to a leaf node, print the character present in that node and the encoded
    //string generated by appending 0s and 1s till then
    else
    {
        cout << pointer->character << " - " << encoded_string << "\n";
    }
}

//Returns the original string corresponding to the given encoded string
string decode_string(string encoded_string, struct Node *pointer)
{
    //Decoded string to be returned. It is initialized to null and appended with appropriate characters in
    //successive recursive calls
    string decoded_string("");
    //If the node pointed by pointer does not contain an empty character
    if(pointer->character != '0')
    {
        //Set decoded_string to the character present in the leaf node
        decoded_string = pointer->character;
        //If there are still more characters to process after decoding the original encoded string till the first
        //position of the given encoded_string, recursively decode the remaining substring by starting the traversal
        //from the root again
        if(encoded_string.size() >= 1)
        {
            //next_decoded_substring stores the decoded version of the substring from the character at index 1 to
            //index encoded_string.size() - 1 of encoded_string
            string next_decoded_substring = decode_string(encoded_string, root);
            //If the decoded substring is invalid, return "-1"
            if(next_decoded_substring == "invalid")
            {
                return next_decoded_substring;
            }
            return decoded_string + next_decoded_substring;
        }
        //Else if there are no further characters to process, return the decoded string
        else
        {
            return decoded_string;
        }
    }
    else
    {
        string next_step_input("");
        //If the input string has length greater than 1, then we can process the substring from the
        //second character of the string to the end of the string
        if(encoded_string.size() > 1)
        {
            next_step_input = encoded_string.substr(1, encoded_string.size() - 1);
        }
        //If the input string is empty, that means our original encoded string which is provided as an input
        //terminates at an internal node of the Huffman trie and therefore, does not correspond to any character
        //of the input string which is originally encoded in the Huffman trie. Hence, the given encoded string is invalid
        else if(encoded_string.size() == 0)
        {
            return "invalid";
        }
        //If the input string has length equal to 1, then we have reached the last character of the original
        //input string which is being decoded. So, to ensure no further processing after this step as processing
        //the last character means that we have reached a leaf node, we pass an empty string to the next recursive
        //call which is handled appropriately
        else if(encoded_string.size() == 1)
        {
            next_step_input = "";
        }
        //If the first character of the given decoded substring is 0, search for the original character recursively
        //in the left subtree of pointer
        if(encoded_string[0] == '0')
        {
            return decoded_string + decode_string(next_step_input, pointer->left_child);
        }
        //If the first character of the given decoded substring is 1, search for the original character recursively
        //in the right subtree of pointer
        else
        {
            return decoded_string + decode_string(next_step_input, pointer->right_child);
        }
        //In both the above cases, we append the string returned from the recursive call to the function's version of
        //decoded_string. This is done to account for all the characters present in the encoded string if the given
        //encoded string contains the codewords of more than one character
    }
}
