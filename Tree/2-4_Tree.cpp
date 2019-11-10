#include<iostream>
#include<cstdlib>
#include<algorithm>

//The placeholder value is selected to be a large number as otherwise it may cause errors while inserting new keys in the node
//Specifically, the conditions in the search_key function would fail if we choose a smaller value for PLACEHOLDER
//All the 3 elements/keys in each node are initialized to this value
#define PLACEHOLDER 9999

using namespace std;

//Implementation of 2-4 Tree

//Structure of a node of the 2-4 tree
struct Node
{
    int keys[3] = {PLACEHOLDER};                 //Key values stored in the node
    int current_number_of_keys = 0;     //Stores the number of keys currently presen in the node
    struct Node *parent;               //Pointer to the parent of the node
    struct Node *child1;               //Pointer to the first child of the node
    struct Node *child2;               //Pointer to the second child of the node
    struct Node *child3;               //Pointer to the third child of the node
    struct Node *child4;               //Pointer to the fourth child of the node
};

//Pointer to the root of the 2-4 tree
struct Node *root = nullptr;

//Pointer to traverse the 2-4 tree
struct Node *pointer = nullptr;

//Temporary pointer
struct Node *temp = nullptr;

//Pointer to the would-be parent of a new key to be inserted in the 2-4 tree
struct Node *new_key_parent = nullptr;

//Pointer to the 5th child after a node having 3 siblings is split after the insertion of a new key
struct Node *child5 = nullptr;

//Stores the number of nodes currently present in the 2-4 tree
int node_count(0);

struct Node* initialize_node(int, struct Node*, struct Node*, struct Node*);
void insert_key(int);
void remove_key(int);
void split_node(struct Node*, int);
void update_parent_node(struct Node*, struct Node*);
struct Node* new_key_location(int, struct Node*);
void rearrange_parent_child_pointers(struct Node*, struct Node*, struct Node*);
struct Node* minimum_key(struct Node*);
struct Node* maximum_key(struct Node*);
struct Node* predecessor(int);
struct Node* first_right_ancestor(struct Node*);
struct Node* successor(int);
struct Node* first_left_ancestor(struct Node*);
void preorder_traversal(struct Node*);

//Driver function
int main(void)
{
    int option(0), element_key(0);
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert a new key in the 2-4 tree\n"
             "2. Remove a key from the 2-4 tree\n"
             "4. Preorder traversal of all the keys present in the 2-4 tree\n"
             "5. Number of nodes currently present in the 2-4 tree\n"
             "6. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the key to be inserted in the 2-4 tree: ";
                cin >> element_key;
                insert_key(element_key);
                break;
            /*case 2:
                cout << "Enter the key to be removed from the 2-4 tree: ";
                cin >> element_key;
                remove_key(element_key);
                break;*/
            case 4:
                if(!node_count)
                {
                    cout << "The 2-4 tree is empty\n";
                }
                else
                {
                    cout << "Preorder traversal of all the keys in the 2-4 tree with their respective heights:\n";
                    //preorder_traversal(root);
                    cout << "\n";
                }
                break;
            case 5:
                cout << "The number of nodes currently present in the 2-4 tree is " << node_count << "\n";
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "You have selected an invalid option. Please select a valid option\n";
        }
    }while(option != 6);
    return 0;
}

//Returns the pointer to a newly created 2-4 tree node after plugging in the desired values for
//key, parent and all the 4 possible children of the node
struct Node* initialize_node(int element_key, struct Node *parent, struct Node *child1, struct Node *child2, struct Node *child3, struct Node *child4)
{
    struct Node *new_node = new struct Node;

    new_node->keys[new_node->current_number_of_keys++] = element_key;

    new_node->parent = parent;
    new_node->child1 = child1;
    new_node->child2 = child2;
    new_node->child3 = child3;
    new_node->child4 = child4;

    //Increment the number of keys in the 2-4 tree by 1
    node_count++;

    return new_node;
}

//Inserts a new key in the appropriate node of the 2-4 tree
void insert_key(int element_key)
{
    //If the 2-4 tree is empty
    if(!node_count)
    {
        root = initialize_node(element_key, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    else
    {
        //Find the node in which the new key is to be inserted
        temp = new_key_location(element_key, root);

        //If the given node has less than 3 keys, add the key in the node and sort all the keys
        if(temp->current_number_of_keys < 3)
        {
            temp->keys[temp->current_number_of_keys++] = element_key;
            sort(temp->keys, (temp->keys) + 3);
        }
        //Else, split the node into two different nodes
        else
        {
            split_node(temp, element_key);
        }
    }
}

//Splits the node having 3 keys into two separate nodes after we try to insert the fourth key in it
void split_node(struct Node *node_to_split, int element_key)
{
    //Store and sort the keys present in the node and the new key to be inserted in the node to be split
    int sort_keys[4] = {node_to_split->keys[0], node_to_split->keys[1], node_to_split->keys[2], element_key};
    sort(sort_keys, sort_keys + 4);

    struct Node *new_node1 = new struct Node;
    new_node1->keys[0] = sort_keys[0];
    new_node1->keys[1] = sort_keys[1];
    new_node1->current_number_of_keys = 2;

    struct Node *new_node2 = new struct Node;
    new_node2->keys[0] = sort_keys[2];
    new_node2->keys[1] = sort_keys[3];
    new_node2->current_number_of_keys = 2;

    node_count++;

    //Rearrange the parent and child pointers accordingly after the split
    rearrange_parent_child_pointers(node_to_split, new_node1, new_node2);

    //If the node to split is a root, then create a new root node
    if(node_to_split == root)
    {
        struct Node *new_root = initialize_node(new_node1->keys[1], nullptr, new_node1, new_node2, nullptr, nullptr);
        node_count++;
        new_node1->keys[--new_node1->current_number_of_keys] = PLACEHOLDER;
        new_node1->parent = new_root;
        new_node2->parent = new_root;
        root = new_root;
    }
    else
    {
        new_node1->parent = node_to_split->parent;
        new_node2->parent = node_to_split->parent;

        //If the parent of the node which has been split has 3 keys, then split the parent
        //and continue this process recursively
        if(node_to_split->parent->current_number_of_keys == 3)
        {
            split_node(node_to_split->parent, new_node1->keys[1]);
        }
        //Else, insert the middle of the 4 keys in the parent node
        else
        {
            node_to_split->parent->keys[node_to_split->parent->current_number_of_keys++] = element_key;
            sort(node_to_split->parent->keys, (node_to_split->parent->keys) + 3);
            new_node1->keys[--new_node1->current_number_of_keys] = PLACEHOLDER;
        }
    }
}

//Returns the pointer to the node in which the new key should be inserted
struct Node* new_key_location(int element_key, struct Node *subtree_root)
{
    //New keys will only be inserted in the appropriate leaf nodes
    if((!subtree_root->child1) && (!subtree_root->child2) && (!subtree_root->child3) && (!subtree_root->child4))
    {
        return subtree_root;
    }
    //Find the appropriate node to insert into based on the search property
    else
    {
        //new_key_parent = subtree_root;
        if(element_key <= subtree_root->keys[0])
        {
            return new_key_location(element_key, subtree_root->child1);
        }
        else if((element_key > subtree_root->keys[0]) && (element_key <= subtree_root->keys[1]))
        {
            return new_key_location(element_key, subtree_root->child2);
        }
        else if((element_key > subtree_root->keys[1]) && (element_key <= subtree_root->keys[2]))
        {
            return new_key_location(element_key, subtree_root->child3);
        }
        else if(element_key > subtree_root->keys[2])
        {
            return new_key_location(element_key, subtree_root->child4);
        }
    }
}

//Rearranges the parent and child pointers of the node which is split
void rearrange_parent_child_pointers(struct Node *node_to_split, struct Node *new_node1, struct Node *new_node2)
{
    if(node_to_split->parent->child1 == node_to_split)
    {
        node_to_split->parent->child1 = new_node1;
        child5 = node_to_split->parent->child4;
        node_to_split->parent->child4 = node_to_split->parent->child3;
        node_to_split->parent->child3 = node_to_split->parent->child2;
        node_to_split->parent->child2 = new_node2;
    }
    else if(node_to_split->parent->child2 == node_to_split)
    {
        node_to_split->parent->child2 = new_node1;
        child5 = node_to_split->parent->child4;
        node_to_split->parent->child4 = node_to_split->parent->child3;
        node_to_split->parent->child3 = new_node2;
    }
    else if(node_to_split->parent->child3 == node_to_split)
    {
        node_to_split->parent->child3 = new_node1;
        child5 = node_to_split->parent->child4;
        node_to_split->parent->child4 = new_node2;
    }
    else if(node_to_split->parent->child4 == node_to_split)
    {
        node_to_split->parent->child4 = new_node1;
        child5 = new_node2;
    }

    new_node1->child1 = node_to_split->child1;
    new_node1->child2 = node_to_split->child2;
    new_node2->child1 = node_to_split->child3;
    new_node2->child2 = node_to_split->child4;
    new_node2->child3 = child5;
}
