#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0

typedef struct AVL_node
{
    int bf;
    char name[21],phoneNb[11];
    struct AVL_node *left, *right;
} treeNd;
int ck = 0;
void countBF(treeNd *root);
void L_Rotation(treeNd **parent);
void R_Rotation(treeNd **parent);
treeNd* BuildTree(treeNd *root, char *nm,char *nb){
    treeNd *new_node;
    if (!root){
       root = (treeNd *)malloc(sizeof(treeNd));
       strcpy(root->name,nm);
       strcpy(root->phoneNb,nb);
       root->left = NULL;
       root->right = NULL; 
    }
    else if(strcmp(root->name,nm) > 0)
    {
       root->left = BuildTree(root->left,nm,nb);
       countBF(root);
       if(abs(root->bf )> 1){
            L_Rotation(&root);
        }
    }
    else if(strcmp(root->name,nm)< 0){
        root->right = BuildTree(root->right,nm,nb);
        countBF(root);
        if(abs(root->bf)>1){
            R_Rotation(&root);
        }
    }
    return root;
}
void L_Rotation(treeNd **parent){
    treeNd* child , *gr_child;
    child = (*parent)->left;
    if(child->bf == 1){ /*LL rotation*/                            
        (*parent)->left = child->right;
        child->right = (*parent);
        *parent = child;
    }
    else{ /*LR rotation*/
        gr_child = child ->right;               
        child->right = gr_child->left;
        (*parent)->left = gr_child->right;
        gr_child->left = child;
        gr_child->right = (*parent);
        *parent = gr_child;
    }
}
void R_Rotation(treeNd **parent){
    treeNd* child , *gr_child;
    child = (*parent)->right;
    if(child->bf == -1){/*RR rotation*/
        (*parent)->right = child->left;
        child->left = (*parent);
        *parent = child;
    }
    else{/*RL rotation*/
        gr_child = child->left;
        child->left = gr_child->right;
        (*parent)->right = gr_child->left;
        gr_child->left = (*parent);
        gr_child->right = child;
        *parent = gr_child;
    }   
}
int tree_height(treeNd *nd)
{
    if (!nd)
        return 0;
    int ldep = tree_height(nd->left);
    int rdep = tree_height(nd->right);
    if (ldep > rdep)  //select larger one
        return ldep + 1;
    else
        return rdep + 1;
}
int BF(treeNd *nd){
    int hL = tree_height(nd->left);
    int hR = tree_height(nd->right);
    return hL - hR;   
}
void countBF(treeNd *root){
    if(!root)
        return;
    countBF(root->left);
    countBF(root->right);
    root->bf = BF(root);
}

void printVLR(treeNd *root){
    if(root){
        if(!ck){
            printf("%s",root->name);
            ck = 1;
        }
        else
            printf(" %s",root->name);
        printVLR(root->left);
        printVLR(root->right);
    }
}
int search(treeNd *root,char *tar){
    int res = FALSE;
    if(!root)
        return res;
    if(strcmp(root->name, tar) < 0){
        res =search(root->right,tar);
    }
    else if(strcmp(root->name, tar)>0)
    {
        res = search(root->left,tar);
    }
    else
    {
        if(!strcmp(root->name,tar)){
            printf("\n%s %s",root->name,root->phoneNb);
            return TRUE;
        }
    }
    return res;
}
int main(){
    treeNd *AVLroot = NULL;
    int *balanced ;
    char nm[30], pnb[11];
    char ch,st;
    scanf("%c%c", &st,&ch);
    while(1)
    {
        scanf("%s%c",nm,&ch);
        if(!strcmp(nm,"S"))
            break;
        scanf("%s\n",pnb);
        //printf("name = %s  phone =%s\n",nm,pnb);
        AVLroot = BuildTree(AVLroot,nm,pnb);
    }
    //countBF(AVLroot);
    printVLR(AVLroot);
    while(1)
    {
        scanf("%s%c",nm,&ch);
        if(!strcmp(nm,"E"))
            break;
        //printf("name = %s\n",nm);
        if(!search(AVLroot,nm))
            printf("\n%s null",nm);
    }
}