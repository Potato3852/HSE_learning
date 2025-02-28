#pragma once

#include<stdio.h>
#include<stdlib.h>

typedef struct NODE
{
    int value;
    struct NODE* left;
    struct NODE* right;
}tree;

tree* Add2Tree(tree* root, int value);
tree* DeleteTree(tree* root);
void In(tree* root);
void Pre(tree* root);
void Post(tree* root);
void PrintfTreeOnSide(tree* root, int level);
tree* DeleteFromTree(tree* root, int value);
tree* DelNode(tree* root);
void Replace(tree** elem, int* value);
