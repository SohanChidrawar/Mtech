#include <stdio.h>
#include <stdlib.h>

struct avl
{
    int data;
    struct avl* left;
    struct avl* right;
    int ht;
};

int height(struct avl* node)
{
    if(node == NULL)
        return 0;
    return node->ht;
}

int max(int a, int b)
{
    return a>b?a:b;
}

int balfactor(struct avl* node)
{
    if(node==NULL)
        return 0;
    else
        return height(node->left) - height(node->right);
}

struct avl* LL(struct avl* node)
{
    struct avl* x = node->left;
    struct avl* z = x->right;
    x->right = node;
    node->left = z;
    node->ht = max(height(node->left),height(node->right))+1;
    x->ht = max(height(x->left),height(x->right))+1;
    return x;
}

struct avl* RR(struct avl* y)
{
    struct avl* x = y->right;
    struct avl* z = x->left;
    x->left = y;
    y->right = z;
    y->ht = max(height(y->left),height(y->right))+1;
    x->ht = max(height(x->left),height(x->right))+1;
    return x;
}

struct avl* insert(struct avl* ptr, int key)
{
    if(ptr==NULL)
    {
        ptr = (struct avl*)malloc(sizeof(struct avl));
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->data = key;
        ptr->ht = 1;
        return ptr;
    }
    if(key < ptr->data)
        ptr->left = insert(ptr->left, key);
    else if(key > ptr->data)
        ptr->right = insert(ptr->right, key);

    ptr->ht = max(height(ptr->left),height(ptr->right))+1;

    int bf = balfactor(ptr);

    //LL rotation
    if(bf>1 && key < ptr->left->data)
        return LL(ptr);
    //RR rotation
    if(bf<-1 && key > ptr->right->data)
        return RR(ptr);
    // LR rotation
    if(bf>1 && key > ptr->left->data)
    {
        ptr->left = RR(ptr->left);
        return LL(ptr);
    }
    //RL rotation
    if(bf<-1 && key < ptr->right->data)
    {
        ptr->right = LL(ptr->right);
        return RR(ptr);
    }
    return ptr;
}

struct avl* minnnode(struct avl* ptr)
{
    struct avl* curr = ptr;
    while(curr->left!=NULL)
        curr = curr->left;
    return curr;
}

struct avl* deletenode(struct avl* ptr, int key)
{
    // Performing standard bst deletion on avl tree
    if(ptr==NULL)
        return ptr;
    
    if(key < ptr->data)
        ptr->left = deletenode(ptr->left,key);
    else if(key > ptr->data)
        ptr->right = deletenode(ptr->right,key);
    else
    {
        // node with 0 or 1 child
        if(ptr->left == NULL || ptr->right == NULL)
        {
            struct avl* temp = ptr->left ? ptr->left : ptr->right;
            
            //no child case
            if(temp==NULL)
            {
                temp = ptr;
                ptr = NULL;
            }
            else
            {
                // one child
                *ptr = *temp;      //copy content
            }
        }
        else
        {
            //Node with two side: get smallest in right subtree
            struct avl* temp = minnode(ptr->right);
            //copy the successor data to root node
            ptr->data = temp->data;
            //delete inorder successor
            ptr->right = deletenode(ptr->right,temp->data);
        }
    }
    // if tree has only one node
    if(ptr==NULL)
        return ptr;
    //calculate height after deleting a node
    int ht = max(height(ptr->left),height(ptr->right));

    //calculate balance factor
    int bf = balfactor(ptr);

    if(bf>1 && balfactor(ptr->left)>=0)
        return LL(ptr);
    if(bf<-1 && balfactor(ptr->right)<0)
        return RR(ptr);
    if(bf>1 && balfactor(ptr->left)<0)
    {
        ptr->left = RR(ptr->left);
        return LL(ptr);
    }
    if(bf<1 && balfactor(ptr->right)>0)
    {
        ptr->right = LL(ptr->right);
        return RR(ptr);
    }
    return ptr;
}

void inorder(struct avl* ptr)
{
    if(ptr!=NULL)
    {
        inorder(ptr->left);
        printf("%d ",ptr->data);
        inorder(ptr->right);
    }
}

int search(struct avl* ptr, int key)
{
    if(ptr==NULL)
        return 0;
    if(ptr->data == key)
        return 1;
    if(key < ptr->data)
        return search(ptr->left,key);
    else
        return search(ptr->right,key);
}

int main()
{
    struct avl* node = NULL;
    node = insert(node,5);
    node = insert(node,3);
    node = insert(node,7);

    inorder(node);

    node = deletenode(node,7);
    inorder(node);

    int key = 5;
    if(search(node, key))
        printf("Key found\n");
    else
        printf("Key not found\n");
}
