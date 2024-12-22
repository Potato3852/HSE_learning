#include "bTree.h"
#include<stdio.h>
#include<stdlib.h>

tree* Add2Tree(tree* root, int value)
{
    if(!root)
    {
        root = malloc(sizeof(tree));
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if(value < root->value)
    {
        root->left = Add2Tree(root->left, value);
    }
    else if(value > root->value)
    {
        root->right = Add2Tree(root->right, value);
    }
    return root;
}

tree* DeleteTree(tree* root)
{
    if(root)
    {
        root->left = DeleteTree(root->left);
        root->right = DeleteTree(root->right);
        free(root);
    }
    return NULL;
}

void In(tree* root)
{
    if(root)
    {
        In(root->left);
        printf("%5d", root->value);
        In(root->right);
    }
}

void Pre(tree* root)
{
    if(root)
    {
        printf("%5d", root->value);
        Pre(root->left);
        Pre(root->right);
    }
}

void Post(tree* root)
{
    if(root)
    {
    Post(root->left);
    Post(root->right);
    printf("%5d", root->value);
    }
}

void PrintfTreeOnSide(tree* root, int level)
{
    if(root)
    {
        PrintfTreeOnSide(root->right, level + 1);
        for(int i = 0; i < level; i++)
            printf("\t");
        printf("%5d\n", root->value);
        PrintfTreeOnSide(root->left, level + 1);
    }
}

tree* DeleteFromTree(tree* root, int value)
{
    if(root)
    {
        if(root->value == value)
            root = DelNode(root);
    }
    else if(value < root->value)
    {
        root->left = DeleteFromTree(root->left, value);
    }
    else if(value > root->value)
    {
        root->right = DeleteFromTree(root->right, value);
    }
}

tree* DelNode(tree* root)
{
    if(root->left == NULL && root->right == NULL)
    {
        free(root);
        return NULL;
    }
    if(root->left && !root->right)
    {
        tree* temp = root;
        root = root->left;
        free(temp);
        return root;
    }
    if(!root->left && root->right)
    {
        tree* temp = root;
        root = root->right;
        free(temp);
        return root;
    }
    if(root->left && root->right)
    {
        int value;
        Replace(&root->right, &value);
        root->value = value;
    }
}

void Replace(tree** elem, int* value)
{
     if ((*elem)->left)
        Replace(&((*elem)->left), value);
    else
    {
        *value = (*elem)->value;
        tree *temp = *elem;
        *elem = (*elem)->right;
        free(temp);
    }
}