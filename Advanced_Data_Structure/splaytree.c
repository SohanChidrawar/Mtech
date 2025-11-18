#include<stdio.h>
#include<stdlib.h>

struct splay
{
    int key;
    struct splay *left,*right,*parent;
};

struct splay* newnode(int key)
{
    struct splay* temp = (struct splay*)malloc(sizeof(struct splay));
    temp->key = key;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

void RR(struct splay **root, struct splay *x)
{
    struct splay* y = x->left;
    if(y==NULL)
        return ;

    //move y right subtree to x left
    x->left = y->right;
    if(y->right!=NULL)
        y->right->parent = x;
    // update y parent to x parent
    y->parent = x->parent;

    //update root or child pointer
    if(x->parent == NULL)
        (*root) = y;
    else if(x == x->parent->left)
        x->parent->left = y;           // x as a left child
    else
        x->parent->right = y;          // x as a right child
    // make x as right child of y
    y->right = x;
    x->parent = y;
}

void LL(struct splay **root, struct splay *x)
{
    struct splay* y = x->right;
    if(y==NULL)
        return ;
    
    //move y left subtree to x right
    x->right = y->left;
    if(y->left!=NULL)
        y->left->parent = x;
    // update y parent to x parent
    y->parent = x->parent;

    if(x->parent == NULL)
        (*root) = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    //make x as left child of y
    y->left = x;
    x->parent = y;
}

void splaying(struct splay **root, struct splay* temp)
{
    while(temp->parent != NULL)
    {
        struct splay *p = temp->parent;
        struct splay *g = p->parent;

        // zig and zag case with p is root and g is null
        if(g==NULL)
        {
            if(temp == p->left)
                RR(root,p);
            else
                LL(root,p);
        }

        //zig-zig,zag-zag,zig-zag,zag-zig
        else
        {
            if(temp == p->left && p == g->left)
            {
                RR(root,g);
                RR(root,p);
            }
            else if(temp == p->right && p == g->right)
            {
                LL(root,g);
                LL(root,p);
            }
            else if(temp == p->right && p == g->left)
            {
                LL(root,p);
                RR(root,g);
            }
            else // temp = p->left && p = g->right
            {
                RR(root,p);
                LL(root,g);
            }
        }
    }
}

struct splay* insert(struct splay *root, int key)
{
    struct splay *z = root;
    struct splay *p = NULL;

    //Standard BST insertion
    while(z!=NULL)
    {
        p = z;
        if(key < z->key)
            z = z->left;
        else if(key > z->key)
            z = z->right;
        else
            return root;
    }
    struct splay* node = newnode(key);
    node->parent = p;

    // node is toward left or  right of parent
    if(p==NULL)
        root = node;
    else if(key < p->key)
        p->left = node;
    else
        p->right = node;  
    
    // splay operation on newly inserted node
    splaying(&root, node);
    return root;
}

struct splay *search(struct splay *root, int key)
{
    struct splay* z = root;
    while(z!=NULL)
    {
        if(key < z->key)
            z = z->left;
        else if(key > z->key)
            z = z->right;
        else
        {
            splaying(&root,z);
            return root;
        }
    }
    return root;
}

// deletion in top down approach
struct splay* deletenode(struct splay *root, int key)
{
    if(root==NULL || root!=key)
        return root;              // if tree is empty or key not found
    // search the node and splay it
    root = search(root,key);

    struct splay* temp;

    // if left subtree is not there
    if(root->left==NULL)
    {
        temp = root;
        root = root->right;
        free(temp);
    }
    else
    {
        temp = root;
        //left subtree is present
        struct splay* rightsubtree = root->right;

        root = root->left;
        root->parent = NULL;

        struct splay* max = root;
        while(max->right!=NULL)
            max = max->right;
        
        splaying(&root,max);
        root->right = rightsubtree;

        if(rightsubtree!=NULL)
            rightsubtree->parent = root;

        free(temp);
    }
}

void inorder(struct splay* ptr)
{
    if(ptr!=NULL)
    {
        inorder(ptr->left);
        printf("%d ",ptr->key);
        inorder(ptr->right);
    }
    // //printf("\n");
    // if(ptr==NULL)
    //     return;
    // inorder(ptr->left);
    // printf("%d ",ptr->key);
    // inorder(ptr->right);
}

int main()
{
    struct splay *root = NULL;

    root = insert(root,10);
    root = insert(root,6);
    root = insert(root,12);
    root = insert(root,1);
    root = insert(root,20);

    printf("Inorder of traversal of tree is: ");
    inorder(root);

    // root = search(root,12);
    // printf("Root of tree after search operation is %d",root->key);
    // inorder(root);
}
