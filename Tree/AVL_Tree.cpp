#include<iostream>
#include<cstdlib>
#include<algorithm>

using namespace std;

//Implementation of AVL Tree

//Structure of a node of the AVL tree
struct Node
{
    int key;                     //Key value stored in the node
    int height;                  //Height of the node
    struct Node *parent;         //Pointer to the parent of the node
    struct Node *left_child;     //Pointer to the left child of the node
    struct Node *right_child;    //Pointer to the right child of the node
};

//Pointer to the root of the AVL tree
struct Node *root = nullptr;

//Pointer to traverse the AVL tree
struct Node *pointer = nullptr;

//Temporary pointer
struct Node *temp = nullptr;

//Pointer to the would-be parent of a new key to be inserted in the AVL tree
struct Node *new_key_parent = nullptr;

//Stores the original height of the first_unbalanced_ancestor before any rebalancing is performed
int first_unbalanced_ancestor_original_height(0);

//Stores the number of elements or keys currently present in the AVL tree
int key_count(0);

struct Node* initialize_node(int, struct Node*, struct Node*, struct Node*);
void set_height(struct Node*);
bool check_height_balance(struct Node*);
struct Node* first_unbalanced_ancestor(struct Node*);
void ancestor_rebalance(struct Node*, void (*)(struct Node*, int));
void height_balancer_insert(struct Node*, int);
void height_balancer_remove(struct Node*, int);
void select_rotation_direction(struct Node*, struct Node*, struct Node*);
void rotate_left(struct Node*, struct Node*);
void rotate_right(struct Node*, struct Node*);
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

//Driver function
int main(void)
{
    int option(0), element_key(0);
    do
    {
        cout << "Select an appropriate option:\n"
             "1. Insert a new key in the AVL tree\n"
             "2. Remove a key from the AVL tree\n"
             "3. Check whether a key is present in the AVL tree\n"
             "4. Preorder traversal of all the keys present in the AVL tree\n"
             "5. Number of keys currently present in the AVL tree\n"
             "6. Exit\n";
        cin >> option;
        switch(option)
        {
            case 1:
                cout << "Enter the key to be inserted in the AVL tree: ";
                cin >> element_key;
                insert_key(element_key);
                break;
            case 2:
                cout << "Enter the key to be removed from the AVL tree: ";
                cin >> element_key;
                remove_key(element_key);
                break;
            case 3:
                cout << "Enter the key to be searched in the AVL tree: ";
                cin >> element_key;
                if(!search_key(element_key, root))
                {
                    cout << "The given key is not present in the AVL tree\n";
                }
                else
                {
                    cout << "The given key is present in the AVL tree\n";
                }
                break;
            case 4:
                if(!key_count)
                {
                    cout << "The AVL tree is empty\n";
                }
                else
                {
                    cout << "Preorder traversal of all the keys in the AVL tree with their respective heights:\n";
                    preorder_traversal(root);
                    cout << "\n";
                }
                break;
            case 5:
                cout << "The number of keys currently present in the AVL tree is " << key_count << "\n";
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

//Returns the pointer to a newly created AVL tree node after plugging in the desired values for
//key, parent, left_child and right_child pointer
struct Node* initialize_node(int element_key, struct Node *parent, struct Node *left_child, struct Node *right_child)
{
    struct Node *new_node = new struct Node;
    new_node->key = element_key;
    new_node->height = 1;
    new_node->parent = parent;
    new_node->left_child = left_child;
    new_node->right_child = right_child;

    //Increment the number of keys in the AVL tree by 1
    key_count++;

    return new_node;
}

//Sets the height of each node of the tree having the given node as root
void set_height(struct Node *pointer)
{
    //If the given node is a leaf, set its height to 1
    if((!pointer->left_child) && (!pointer->right_child))
    {
        pointer->height = 1;
    }
    //If the given node has two children, then the height of the given node is 1 + height of child with greater height
    else if((pointer->left_child) && (pointer->right_child))
    {
        set_height(pointer->left_child);
        set_height(pointer->right_child);
        pointer->height = max(pointer->left_child->height, pointer->right_child->height) + 1;
    }
    //If the given node has only one child, then the height of the given node is 1 + height of child
    else
    {
        struct Node *child_pointer = (pointer->left_child == nullptr) ? (pointer->right_child) : (pointer->left_child);
        set_height(child_pointer);
        pointer->height = child_pointer->height + 1;
    }
}

//Checks if the subtrees of the given node are height balanced i.e the difference in the heights
//of the left and right subtree of the given node is at most 1
bool check_height_balance(struct Node *pointer)
{
    //If the given node is a leaf, then it is height balanced
    if((!pointer->left_child) && (!pointer->right_child))
    {
        return true;
    }
    //Else if the given node has two children, check whether the difference in their heights lie
    //between -1 and 1
    else if((pointer->left_child) && (pointer->right_child))
    {
        int absolute_height_difference = pointer->left_child->height - pointer->right_child->height;
        if((absolute_height_difference >= -1) && (absolute_height_difference <= 1))
        {
            return true;
        }
        return false;
    }
    //Else if the given node has only one child, then the height of that child node should be 1
    else
    {
        if(pointer->left_child)
        {
            return pointer->left_child->height == 1;
        }
        else if(pointer->right_child)
        {
            return pointer->right_child->height == 1;
        }
    }
}

//Returns the first ancestor of the newly inserted node which is not height-balanced
struct Node* first_unbalanced_ancestor(struct Node *pointer)
{
    pointer = pointer->parent;
    if(!pointer)
    {
        return nullptr;
    }
    else
    {
        if(check_height_balance(pointer))
        {
            return first_unbalanced_ancestor(pointer);
        }
        return pointer;
    }
}

//Checks if any ancestor node of temp need to be rebalanced after insertion or deletion in the AVL tree
//A function is passed as the second argument here as height_balancer_insert will be called if the insertion of
//a new key causes height imbalance height_balancer_remove will be called if some deletion causes height imbalance
void ancestor_rebalance(struct Node *removed_node, void (*height_balancer)(struct Node*, int))
{
    set_height(root);
    if(removed_node)
    {
        pointer = first_unbalanced_ancestor(removed_node);

        //Store the parent of the first unbalanced ancestor to compare the height of its child
        //before and after the rebalancing of nodes so as to decide whether to rebalance further ancestors
        //when the height of its child reduces
        if(pointer)
        {
            struct Node *balanced_ancestor = pointer->parent;


            //Rebalance the nodes if a height imbalanced ancestor is present
            (*height_balancer)(pointer, removed_node->key);

            if(balanced_ancestor)
            {
                //Recursively check for height imbalance of the ancestors if the height of the appropriate
                //child of the first unbalanced ancestor's parent decreases
                if((balanced_ancestor->left_child == pointer ? balanced_ancestor->left_child->height : balanced_ancestor->right_child->height) < first_unbalanced_ancestor_original_height)
                {
                    ancestor_rebalance(balanced_ancestor, height_balancer);
                }
            }

        }
    }
}

//Rebalances the given node after the insertion of element_key causes height imbalance at that node
void height_balancer_insert(struct Node *unbalanced_node, int element_key)
{
    struct Node *unbalanced_node_child = nullptr;
    struct Node *unbalanced_node_grandchild = nullptr;

    //Sets the pointers to the appropriate child and grandchild of the unbalanced node
    if(element_key <= unbalanced_node->key)
    {
        unbalanced_node_child = unbalanced_node->left_child;
    }
    else
    {
        unbalanced_node_child = unbalanced_node->right_child;
    }
    if(element_key <= unbalanced_node_child->key)
    {
        unbalanced_node_grandchild = unbalanced_node_child->left_child;
    }
    else
    {
        unbalanced_node_grandchild = unbalanced_node_child->right_child;
    }

    //Select the direction in which to rotate the unbalanced_node and it's successors to maintain height balance
    select_rotation_direction(unbalanced_node, unbalanced_node_child, unbalanced_node_grandchild);
}

//Rebalances the given node after the deletion of element_key causes height imbalance at that node
void height_balancer_remove(struct Node *unbalanced_node, int element_key)
{
    struct Node *unbalanced_node_child = nullptr;
    struct Node *unbalanced_node_grandchild = nullptr;

    //Sets the pointers to the appropriate child and grandchild of the unbalanced node
    if(!unbalanced_node->left_child)
    {
        unbalanced_node_child = unbalanced_node->right_child;
    }
    else if(!unbalanced_node->right_child)
    {
        unbalanced_node_child = unbalanced_node->left_child;
    }
    //The condition when both the children are not present is not added because then the given node
    //is a leaf and leaf nodes are always height balanced
    else
    {
        if(unbalanced_node->left_child->height <= unbalanced_node->right_child->height)
        {
            unbalanced_node_child = unbalanced_node->right_child;
        }
        else
        {
            unbalanced_node_child = unbalanced_node->left_child;
        }
    }
    if(!unbalanced_node_child->left_child)
    {
        unbalanced_node_grandchild = unbalanced_node_child->right_child;
    }
    else if(!unbalanced_node_child->right_child)
    {
        unbalanced_node_grandchild = unbalanced_node_child->left_child;
    }
    else
    {
        if(unbalanced_node_child->left_child->height < unbalanced_node_child->right_child->height)
        {
            unbalanced_node_grandchild = unbalanced_node_child->right_child;
        }
        else if(unbalanced_node_child->left_child->height > unbalanced_node_child->right_child->height)
        {
            unbalanced_node_grandchild = unbalanced_node_child->left_child;
        }
        else
        {
            if(unbalanced_node_child == unbalanced_node->left_child)
            {
                unbalanced_node_grandchild = unbalanced_node_child->left_child;
            }
            else
            {
                unbalanced_node_grandchild = unbalanced_node_child->right_child;
            }
        }
    }

    //Select the direction in which to rotate the unbalanced_node and it's successors to maintain height balance
    select_rotation_direction(unbalanced_node, unbalanced_node_child, unbalanced_node_grandchild);
}

//Selects the direction in which to rotate the given nodes to maintain height balance in the AVL tree
void select_rotation_direction(struct Node *unbalanced_node, struct Node *unbalanced_node_child, struct Node *unbalanced_node_grandchild)
{
    //Left-Left case
    if((unbalanced_node->left_child == unbalanced_node_child) && (unbalanced_node_child->left_child == unbalanced_node_grandchild))
    {
        rotate_left(unbalanced_node, unbalanced_node_child);
    }
    //Left-Right case
    else if((unbalanced_node->left_child == unbalanced_node_child) && (unbalanced_node_child->right_child == unbalanced_node_grandchild))
    {
        rotate_right(unbalanced_node_child, unbalanced_node_grandchild);
        unbalanced_node_child = unbalanced_node_grandchild;
        rotate_left(unbalanced_node, unbalanced_node_child);
    }
    //Right-Left case
    else if((unbalanced_node->right_child == unbalanced_node_child) && (unbalanced_node_child->left_child == unbalanced_node_grandchild))
    {
        rotate_left(unbalanced_node_child, unbalanced_node_grandchild);
        unbalanced_node_child = unbalanced_node_grandchild;
        rotate_right(unbalanced_node, unbalanced_node_child);
    }
    //Right-Right case
    else if((unbalanced_node->right_child == unbalanced_node_child) && (unbalanced_node_child->right_child == unbalanced_node_grandchild))
    {
        rotate_right(unbalanced_node, unbalanced_node_child);
    }
}


//Rotates the branch to maintain height balance when the unbalanced_node_child is the left child of the unbalanced_node
void rotate_left(struct Node *unbalanced_node, struct Node *unbalanced_node_child)
{
    unbalanced_node->left_child = unbalanced_node_child->right_child;
    if(unbalanced_node_child->right_child)
    {
        (unbalanced_node_child->right_child)->parent = unbalanced_node;
    }
    unbalanced_node_child->right_child = unbalanced_node;
    unbalanced_node_child->parent = unbalanced_node->parent;

    //Updates the root if the current root is not height-balanced
    if(!unbalanced_node->parent)
    {
        root = unbalanced_node_child;
    }
    else
    {
        if(unbalanced_node->key <= (unbalanced_node->parent)->key)
        {
            (unbalanced_node->parent)->left_child = unbalanced_node_child;
        }
        else
        {
            (unbalanced_node->parent)->right_child = unbalanced_node_child;
        }
    }
    unbalanced_node->parent = unbalanced_node_child;
}

//Rotates the branch to maintain height balance when the unbalanced_node_child is the right child of the unbalanced_node
void rotate_right(struct Node *unbalanced_node, struct Node *unbalanced_node_child)
{
    unbalanced_node->right_child = unbalanced_node_child->left_child;
    if(unbalanced_node_child->left_child)
    {
        (unbalanced_node_child->left_child)->parent = unbalanced_node;
    }
    unbalanced_node_child->left_child = unbalanced_node;
    unbalanced_node_child->parent = unbalanced_node->parent;

    //Updates the root if the current root is not height-balanced
    if(!unbalanced_node->parent)
    {
        root = unbalanced_node_child;
    }
    else
    {
        if(unbalanced_node->key <= (unbalanced_node->parent)->key)
        {
            (unbalanced_node->parent)->left_child = unbalanced_node_child;
        }
        else
        {
            (unbalanced_node->parent)->right_child = unbalanced_node_child;
        }
    }
    unbalanced_node->parent = unbalanced_node_child;
}


//Inserts the given key in the AVL tree
void insert_key(int element_key)
{
    //If the AVL tree is empty
    if(!key_count)
    {
        temp = initialize_node(element_key, nullptr, nullptr, nullptr);
        root = temp;
    }
    else
    {
        //Search function is called so as to get the new_key_parent point to the
        //parent of the new key to be inserted
        temp = search_key(element_key, root);
        //The only time the search_key function won't return null value while inserting a node is
        //when the AVL tree already contains a node having the same key value as the one to be inserted
        //Even if the search_key function returns null value, we store it in temp as in the next step,
        //we are making temp point to the newly inserted node in the AVL tree

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

    //Rebalance the ancestors if they become height imbalanced after insertion
    ancestor_rebalance(temp, height_balancer_insert);

    //Update the heights of the nodes after the AVL tree has been rebalanced
    set_height(root);
}

//Removes the given key from the AVL tree
void remove_key(int element_key)
{
    //Get the pointer pointing to the key to be removed
    struct Node *removed_node = search_key(element_key, root);

    //If the given key is not present in the AVL tree
    if(!removed_node)
    {
        cout << "The given key is not present in the AVL tree\n";
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

        if(root)
        {
            set_height(root);
        }

        //Find the first ancestor of the removed_node which maybe imbalanced
        //If no ancestors are imbalanced, then first_unbalanced_ancestor method returns nullptr
        temp = first_unbalanced_ancestor(removed_node);

        //Appropriately rebalance the tree in case of height imbalance at some ancestor node
        if(temp)
        {
            first_unbalanced_ancestor_original_height = temp->height;
            ancestor_rebalance(removed_node, height_balancer_remove);
        }

        //Update the heights of the nodes after the AVL tree has been rebalanced
        if(root)
        {
            set_height(root);
        }

        //Deallocate the memory pointed to by removed_node
        free(removed_node);

        //Decrement the number of keys in the AVL tree by 1
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

//Returns a pointer to the given key or nullptr if the given key is not present in the AVL tree
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

//Returns a pointer to the minimum key value present in the AVL tree
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

//Returns a pointer to the maximum key value present in the AVL tree
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

    //Search for the key whose predecessor is to be found in the AVL tree
    pointer = search_key(element_key, root);

    //If the given key is not present in the AVL tree or if the AVL tree is empty
    if(!pointer)
    {
        return nullptr;
    }

    //If the given key is already the key having the minimum value in the AVL tree, then
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

    //Search for the key whose successor is to be found in the AVL tree
    pointer = search_key(element_key, root);

    //If the given key is not present in the AVL tree or if the AVL tree is empty
    if(!pointer)
    {
        return nullptr;
    }

    //If the given key is already the key having the maximum value in the AVL tree, then
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

//Prints all the nodes and their heights present in the AVL tree by first printing the key value of the node pointed by the
//temp and then recursively printing the key values in the left and right subtree of the temp node respectively
void preorder_traversal(struct Node *temp)
{
    if(!temp)
    {
        return;
    }
    else
    {
        cout << temp->key << " " << temp->height << "\n";
        preorder_traversal(temp->left_child);
        preorder_traversal(temp->right_child);
    }
}
