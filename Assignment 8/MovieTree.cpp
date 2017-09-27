#include <iostream>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree() {}

MovieTree::~MovieTree() {

  DeleteAll(root);

}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity) {

  MovieNode *n1;
  MovieNode *tmp;
  MovieNode *parent;

  if (root==NULL) {

    n1=new MovieNode(ranking, title, releaseYear, quantity);
    root=n1;

  }

  tmp=root;
  n1=new MovieNode(ranking, title, releaseYear, quantity);

  while(tmp!=NULL) {

    parent=tmp;

    if (n1->title>tmp->title) {
      tmp=tmp->rightChild;
    }

    else {
      tmp=tmp->leftChild;
    }

  }

  if (n1->title>parent->title) {
    n1->parent=parent;
    parent->rightChild=n1;
  }

  if (n1->title<parent->title) {
    n1->parent=parent;
    parent->leftChild=n1;
  }

}

MovieNode *MovieTree::searchRecursive(MovieNode *node, string value) {

  if(node==NULL) return NULL;

  MovieNode *current=node;

  if (value<current->title) {
    current=searchRecursive(current->leftChild, value);
    return current;
  }

  if (current->title==value) return current;

  if (value>current->title) {
    current=searchRecursive(current->rightChild, value);
    return current;
  }

  return NULL;

}

void MovieTree::findMovie(string title) {

  MovieNode *foundMovie=searchRecursive(root, title);

  if (foundMovie!=NULL) {
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;

    //cout << foundMovie->leftChild->title << " " << foundMovie->rightChild->title << " " << foundMovie->parent->title << endl;
  }

  else cout << "Movie not found." << endl;

}

void MovieTree::rentMovie(string title) {

  MovieNode *foundMovie=searchRecursive(root, title);

  if (foundMovie!=NULL) {
    foundMovie->quantity=foundMovie->quantity-1;

    cout << "Movie has been rented." << endl;
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;

    if (foundMovie->quantity==0) {
      deleteMovieNode(title);
    }

  }

  else cout << "Movie not found." << endl;

}

MovieNode *MovieTree::treeMinimum(MovieNode *node) {
  
  while (node->leftChild!=NULL) node=node->leftChild;

  return node;

}

void MovieTree::deleteMovieNode(string title) {

  MovieNode *found=searchRecursive(root,title);

  if (found==NULL) {
    cout << "Movie not found." << endl;
    return;
  }

  MovieNode *tmp;

  if (found->rightChild!=NULL && found->leftChild!=NULL) {
    tmp=treeMinimum(found->rightChild);

    found->ranking=tmp->ranking;
    found->title=tmp->title;
    found->year=tmp->year;
    found->quantity=tmp->quantity;

    if (tmp->parent->leftChild==tmp) tmp->parent->leftChild=tmp->rightChild;

    else tmp->parent->rightChild=tmp->rightChild;

    delete tmp;
  }

  else if (found->rightChild!=NULL) {
    if (found->parent->leftChild==found) found->parent->leftChild=found->rightChild;

    else found->parent->rightChild=found->rightChild;

    delete found;
  }

  else if (found->leftChild!=NULL) {
    if (found->parent->leftChild==found) found->parent->leftChild=found->leftChild;

    else found->parent->rightChild=found->leftChild;

    delete found;
  }

  else {
    if (found->parent->leftChild==found) found->parent->leftChild=NULL;

    else found->parent->rightChild=NULL;

    delete found;
  }

}

void MovieTree::printMovieInventory() {

  printMovieInventory(root);

}

void MovieTree::printMovieInventory(MovieNode *node) {

  if(node==NULL){
     return;
  }

  printMovieInventory(node->leftChild);
  cout << "Movie: " << node->title << " " << node->quantity << endl;
  printMovieInventory(node->rightChild);


}

void MovieTree::countMovieNodes(MovieNode *node, int *c) {

  if(node==NULL){
     return;
  }

  countMovieNodes(node->leftChild, c);
  (*c)++;
  countMovieNodes(node->rightChild, c);

}

int MovieTree::countMovieNodes() {

  int c=0;
  int *count=&c;

  countMovieNodes(root, count);

  return *count;

}

void MovieTree::DeleteAll(MovieNode *node) {

  if(node==NULL) return;

  MovieNode *current=node;

  if (current->leftChild!=NULL) {
    DeleteAll(current->leftChild);
  }

  if (current->rightChild!=NULL) {
    DeleteAll(current->rightChild);
  }

  cout << "Deleting: " << current->title << endl;
  delete current;

}
