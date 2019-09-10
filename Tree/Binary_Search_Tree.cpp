#include<iostream>
#include<cstdlib>

using namespace std;

//Implementation of Binary Search Tree(BST)

//Structure of a node of the BST
struct Node
{
    int key;                     //Key value stored in the node
    struct Node *parent;         //Pointer to the parent of the node
    struct Node *left_child;     //Pointer to the left child of the node
    struct Node *right_child;    //Pointer to the right child of the node
};

//Pointer to the root of the binary search tree
struct Node *root = nullptr;

//Pointer to traverse the BST
struct Node *pointer = nullptr;

//Temporary pointer
struct Node *temp = nullptr;

//Pointer to the would-be parent of a new key to be inserted in the BST
struct Node *new_key_parent = nullptr;

//Stores the number of elements or keys currently present in the BST
int key_count(0);

struct Node* initialize_node(int, struct Node*, struct Node*, struct Node*);
void insert_key(int);
void remove_key(int);
void update_parent_node(struct Node*, struct Node*);
struct Node* search_key(int, struct Node*);
struct Node* minimum_key(struct Node*);
struct Node* maximum_key(struct Node*);
struct Node* predecessor(int);
struct Node* first_right_ancestor(struct Node*);
struct Node* successor(int);
struct Node* first_left_ancestor(struct Node*);
void preorder_traversal(struct Node*);
void inorder_traversal(struct Node*);
void postorder_traversal(struct Node*);

//Driver function
int main(void)
{
    int option(0), element_key(0);
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert a new key in the binary search tree\n"
             "2. Remove a key from the binary search tree\n"
             "3. Check whether a key is present in the binary search tree\n"
             "4. Minimum key value present in the binary search tree\n"
             "5. Maximum key value present in the binary search tree\n"
             "6. Find the predecessor of a given key\n"
             "7. Find the successor of a given key\n"
             "8. Preorder traversal of all the keys present in the binary search tree\n"
             "9. Inorder traversal of all the keys present in the binary search tree\n"
             "10. Postorder traversal of all the keys present in the binary search tree\n"
             "11. Number of keys currently present in the binary search tree\n"
             "12. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the key to be inserted in the binary search tree: ";
                cin >> element_key;
                insert_key(element_key);
                break;
            case 2:
                cout << "Enter the key to be removed from the binary search tree: ";
                cin >> element_key;
                remove_key(element_key);
                break;
            case 3:
                cout << "Enter the key to be searched in the binary search tree: ";
                cin >> element_key;
                if(!search_key(element_key, root))
                {
                    cout << "The given key is not present in the binary search tree\n";
                }
                else
                {
                    cout << "The given key is present in the binary search tree\n";
                }
                break;
            case 4:
                if(!minimum_key(root))
                {
                    cout << "The binary search tree is empty\n";
                }
                else
                {
                    cout << "The minimum key value present in the binary search tree is " << minimum_key(root)->key << "\n";
                }
                break;
            case 5:
                if(!maximum_key(root))
                {
                    cout << "The binary search tree is empty\n";
                }
                else
                {
                    cout << "The maximum key value present in the binary search tree is " << maximum_key(root)->key << "\n";
                }
                break;
            case 6:
                cout << "Enter the key whose predecessor is to be found: ";
                cin >> element_key;
                if(!predecessor(element_key))
                {
                    cout << "The binary search tree is empty or the given key is not present in the BST\n";
                }
                else if(element_key == minimum_key(root)->key)
                {
                    cout << "The given key has no predecessor as it has the minimum value\n";
                }
                else
                {
                    cout << "The predecessor of key " << element_key << " is " << predecessor(element_key)->key << "\n";
                }
                break;
            case 7:
                cout << "Enter the key whose successor is to be found: ";
                cin >> element_key;
                if(!successor(element_key))
                {
                    cout << "The binary search tree is empty or the given key is not present in the BST\n";
                }
                else if(element_key == maximum_key(root)->key)
                {
                    cout << "The given key has no successor as it has the maximum value\n";
                }
                else
                {
                    cout << "The successor of key " << element_key << " is " << successor(element_key)->key << "\n";
                }
                break;
            case 8:
                if(!key_count)
                {
                    cout << "The binary search tree is empty\n";
                }
                else
                {
                    cout << "Preorder traversal of all the keys in the binary search tree:\n";
                    preorder_traversal(root);
                    cout << "\n";
                }
                break;
            case 9:
                if(!key_count)
                {
                    cout << "The binary search tree is empty\n";
                }
                else
                {
                    cout << "Inorder traversal of all the keys in the binary search tree:\n";
                    inorder_traversal(root);
                    cout << "\n";
                }
                break;
            case 10:
                if(!key_count)
                {
                    cout << "The binary search tree is empty\n";
                }
                else
                {
                    cout << "Postorder traversal of all the keys in the binary search tree:\n";
                    postorder_traversal(root);
                    cout << "\n";
                }
                break;
            case 11:
                cout << "The number of keys currently present in the binary search tree is " << key_count << "\n";
                break;
            case 12:
                exit(0);
                break;
            default:
                cout << "You have selected an invalid option. Please select a valid option\n";
        }
    }while(option != 12);
    return 0;
}

//Returns the pointer to a newly created BST node after plugging in the desired values for
//key, parent, left_child and right_child pointer
struct Node* initialize_node(int element_key, struct Node *parent, struct Node *left_child, struct Node *right_child)
{
    temp = new struct Node;
    temp->key = element_key;
    temp->parent = parent;
    temp->left_child = left_child;
    temp->right_child = right_child;

    //Increment the number of keys in the BST by 1
    key_count++;

    return temp;
}

//Inserts the given key in the BST
void insert_key(int element_key)
{
    //If the BST is empty
    if(!key_count)
    {
        root = initialize_node(element_key, nullptr, nullptr, nullptr);
    }
    else
    {
        //Search function is called so as to get the new_key_parent point to the
        //parent of the new key to be inserted
        //dont use search function. due to this, 1,3,4 are insetted as 1-3-4 and not 1-4-3
        temp = search_key(element_key, root);
        //The only time the search_key function won't return null value while inserting a node is
        //when the BST already contains a node having the same key value as the one to be inserted
        //Even if the search_key function returns null value, we store it in temp as in the next step,
        //we are making temp point to the newly inserted node in the BST

        //Make the new node's parent pointer point to the node referred by new_key_parent
        temp = initialize_node(element_key, new_key_parent, nullptr, nullptr);

        //If the key value is less than or equal to it's parent node's,the new node becomes the left child
        //of the parent
        if(element_key <= new_key_parent->key)
        {
            new_key_parent->left_child = temp;
        }

        //Else, it becomes the right child of the parent
        else
        {
            new_key_parent->right_child = temp;
        }
    }
}

//Removes the given key from the BST
void remove_key(int element_key)
{
    //Get the pointer pointing to the key to be removed
    struct Node *removed_node = search_key(element_key, root);

    //If the given key is not present in the BST
    if(!removed_node)
    {
        cout << "The given key is not present in the binary search tree\n";
    }
    else
    {
        //Calculate the number of children of the key to be removed
        int number_of_children = (removed_node->left_child != nullptr) + (removed_node->right_child != nullptr);

        //Update the parent and children pointers of the node to be deleted
        if(number_of_children == 0)
        {
            update_parent_node(removed_node, nullptr);
        }
        else if(number_of_children == 1)
        {
            struct Node *child_pointer = (removed_node->left_child == nullptr) ? removed_node->right_child : removed_node->left_child;
            update_parent_node(removed_node, child_pointer);
            child_pointer->parent = removed_node->parent;
        }
        else
        {
            //In the case when the key/node to be deleted has 2 children, update the parent and child pointers
            //of the key/node which will replace the removed key. We can replace the node having 2 children with
            //either its inorder successor or predecessor
            struct Node *replacement = predecessor(element_key);

            //Here, we are updating the key value of the node to be removed with its replacement and in doing so,
            //we also do away with the need to update the parent and children pointers of the key to be deleted
            //Instead, we update the parent and children pointers of the replacement node
            //Also, in this case, if the node to be deleted is the root, we don't need to update the root pointer
            //as in the previous two cases, since we are updating the replacement key pointers and putting in its
            //value in place of the key to be deleted already
            removed_node->key = replacement->key;
            update_parent_node(replacement, replacement->left_child);
            if(replacement->left_child)
            {
                (replacement->left_child)->parent = replacement->parent;
            }
            //We have not included a similar condition for the right child of the replacement node, because
            //if the replacement node had a right child, then it would have been the predecessor of the node
            //to be deleted and hence, the replacement

            //Updating removed_node to maintain uniformity in the common memory deallocation step,
            //so that we can use the same pointer as input to the free() function
            removed_node = replacement;
        }

        /*For the case when the node to be removed has 2 children, in place of the above block of code, we
        can also use the following block in which we update the parent and child pointers of the node to be
        removed instead of merely copying the replacement key's value:

        struct Node *replacement = predecessor(element_key);
        update_parent_node(replacement, replacement->left_child);
        if(replacement->left_child)
        {
            (replacement->left_child)->parent = replacement->parent;
        }
        if(removed_node != root)
        {
            replacement->parent = removed_node->parent;
        }
        //The following line will update the root pointer if the node to be deleted is the root
        //Else, it will make the parent of the removed node point to the replacement node
        update_parent_node(removed_node, replacement);
        replacement->left_child = removed_node->left_child;
        replacement->right_child = removed_node->right_child;
        if(removed_node->left_child)
        {
            (removed_node->left_child)->parent = replacement;
        }
        if(removed_node->right_child)
        {
            (removed_node->right_child)->parent = replacement;
        }
        */

        //Deallocate the memory pointed to by removed_node
        free(removed_node);

        //Decrement the number of keys in the BST by 1
        key_count--;
    }
}

//Updates the appropriate child of the parent node of the first argument by assigning it as value the second argument
void update_parent_node(struct Node *removed_node, struct Node *new_child_pointer)
{
    //Update root if the deleted node is the root and the deleted node has 0 or 1 child
    //This is necessary as otherwise removed_parent would be NULL in the else block when removed_parent = root
    //as the root does not have any parent
    if(removed_node == root)
    {
        root = new_child_pointer;
    }
    else
    {
        //If the node to be deleted is the left child of its parent, update the left_child of the parent
        if((removed_node->parent)->left_child == removed_node)
        {
            (removed_node->parent)->left_child = new_child_pointer;
        }
        //Else, update the right_child of the parent of the node to be deleted
        else
        {
            (removed_node->parent)->right_child = new_child_pointer;
        }
    }
}

//Returns a pointer to the given key or nullptr if the given key is not present in the BST
struct Node* search_key(int element_key, struct Node *pointer)
{
    //If the tree having its root pointed by pointer is empty
    if(!pointer)
    {
        //This will also return the pointer corresponding to the location where a new key
        //should be inserted
        return nullptr;
    }
    else
    {
        //If the key to be searched is less than the one pointed by pointer,
        //search recursively in the left subtree of the current node
        if(element_key < pointer->key)
        {
            if(!pointer->left_child)
            {
                new_key_parent = pointer;
            }
            return search_key(element_key, pointer->left_child);
        }

        //If the key to be searched is more than the one pointed by pointer,
        //search recursively in the right subtree of the current node
        else if(element_key > pointer->key)
        {
            if(!pointer->right_child)
            {
                new_key_parent = pointer;
            }
            return search_key(element_key, pointer->right_child);
        }

        //If the pointer points to the key to be searched, return the current pointer
        else
        {
            return pointer;
        }
    }
}

//Returns a pointer to the minimum key value present in the BST
struct Node* minimum_key(struct Node *pointer)
{
    //If the tree is empty
    if(!pointer)
    {
        return nullptr;
    }
    else
    {
        //Traverse every left child starting from the root until we reach the final left child
        while(pointer->left_child != nullptr)
        {
            pointer = pointer->left_child;
        }
        return pointer;
    }
}

//Returns a pointer to the maximum key value present in the BST
struct Node* maximum_key(struct Node *pointer)
{
    //If the tree is empty
    if(!pointer)
    {
        return nullptr;
    }
    else
    {
        //Traverse every right child starting from the root until we reach the final right child
        while(pointer->right_child != nullptr)
        {
            pointer = pointer->right_child;
        }
        return pointer;
    }
}

//Returns a pointer to the inorder predecessor of the given key
struct Node* predecessor(int element_key)
{

    //Search for the key whose predecessor is to be found in the BST
    pointer = search_key(element_key, root);

    //If the given key is not present in the BST or if the BST is empty
    if(!pointer)
    {
        return nullptr;
    }

    //If the given key is already the key having the minimum value in the BST, then
    //it does not have any predecessor
    else if(pointer->key == minimum_key(root)->key)
    {
        return pointer;
    }

    else
    {
        temp = pointer;
        pointer = pointer->left_child;

        //If the given node has no left child, then find the first ancestor of this given
        //node such that the given node lies in the right subtree of the ancestor
        if(!pointer)
        {
            return first_right_ancestor(temp);
        }

        //Search for the rightmost key in the left subtree of the given node
        else
        {
            return maximum_key(pointer);
        }
    }
}

//Returns the pointer to the first ancestor node of the given node, such that the
//given node lies in the right subtree of the ancestor
struct Node* first_right_ancestor(struct Node *pointer)
{
    //error here if pointer is null
    struct Node *ancestor = pointer->parent;

    //If the desired ancestor is found
    if(ancestor->right_child == pointer)
    {
        return ancestor;
    }

    //Else, move up the tree in search of the desired ancestor
    else
    {
        return first_right_ancestor(ancestor);
    }
}

//Returns a pointer to the inorder successor of the given key
struct Node* successor(int element_key)
{

    //Search for the key whose successor is to be found in the BST
    pointer = search_key(element_key, root);

    //If the given key is not present in the BST or if the BST is empty
    if(!pointer)
    {
        return nullptr;
    }

    //If the given key is already the key having the maximum value in the BST, then
    //it does not have any successor
    else if(pointer->key == maximum_key(root)->key)
    {
        return pointer;
    }

    else
    {
        temp = pointer;
        pointer = pointer->right_child;

        //If the given node has no right child, then find the first ancestor of this given
        //node such that the given node lies in the left subtree of the ancestor
        if(!pointer)
        {
            return first_left_ancestor(temp);
        }

        //Search for the leftmost key in the right subtree of the given node
        else
        {
            return minimum_key(pointer);
        }
    }
}

//Returns the pointer to the first ancestor node of the given node, such that the
//given node lies in the left subtree of the ancestor
struct Node* first_left_ancestor(struct Node *pointer)
{
    struct Node *ancestor = pointer->parent;

    //If the desired ancestor is found
    if(ancestor->left_child == pointer)
    {
        return ancestor;
    }

    //Else, move up the tree in search of the desired ancestor
    else
    {
        ancestor = first_left_ancestor(ancestor);
    }
}

//Prints all the keys present in the BST by first printing the key value of the node pointed by the
//temp and then recursively printing the key values in the left and right subtree of the temp node respectively
void preorder_traversal(struct Node *temp)
{
    if(!temp)
    {
        return;
    }
    else
    {
        cout << temp->key << " ";
        preorder_traversal(temp->left_child);
        preorder_traversal(temp->right_child);
    }
}

//Prints all the keys present in the BST by first recursively printing the key values in the left subtree
//of the node pointed by the temp and then printing the key value of the temp node and finally
//recursively printing the key values in the right subtree of the temp node
void inorder_traversal(struct Node *temp)
{
    if(!temp)
    {
        return;
    }
    else
    {
        inorder_traversal(temp->left_child);
        cout << temp->key << " ";
        inorder_traversal(temp->right_child);
    }
}

//Prints all the keys present in the BST by first recursively printing the key values in the left and right
//subtrees of the node pointed by the temp respectively and then printing the key value of the temp node
void postorder_traversal(struct Node *temp)
{
    if(!temp)
    {
        return;
    }
    else
    {
        postorder_traversal(temp->left_child);
        postorder_traversal(temp->right_child);
        cout << temp->key << " ";
    }
}
