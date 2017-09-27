#include <iostream>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree() {

  nil=new MovieNode();
  nil->isRed=false;
  nil->leftChild=nil->rightChild=nil->parent=nil;
  root=nil;

}

MovieTree::~MovieTree() {

  DeleteAll(root);

}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity) {

  MovieNode *n1;
  MovieNode *tmp;
  MovieNode *parent;

  n1=new MovieNode(ranking, title, releaseYear, quantity);
  n1->leftChild=n1->rightChild=nil;

  if (root==nil) {
    root=n1;
    root->leftChild=root->rightChild=root->parent=nil;
    root->isRed=false;
    return;
  }

  tmp=root;

  while(tmp!=nil) {
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

  rbAddFixup(n1);


}

void MovieTree::rbAddFixup(MovieNode *node) {

  MovieNode *uncle;

  while ((node!=root) && (node->parent->isRed) && (node->parent!=nil)) {
    if (node->parent==node->parent->parent->leftChild) {
      uncle=node->parent->parent->rightChild;

      if (uncle->isRed) {
        node->parent->isRed=false;
        uncle->isRed=false;
        node->parent->parent->isRed=true;
        node=node->parent->parent;
      }

      else {
        if (node==node->parent->rightChild) {
          node=node->parent;
          leftRotate(node);
        }
        node->parent->isRed=false;
        node->parent->parent->isRed=true;
        rightRotate(node->parent->parent);
      }
    }

    else {
      uncle=node->parent->parent->leftChild;

      if (uncle->isRed) {
        node->parent->isRed=false;
        uncle->isRed=false;
        node->parent->parent->isRed=true;
        node=node->parent->parent;
      }

      else {
        if (node==node->parent->leftChild) {
          node=node->parent;
          rightRotate(node);
        }
        node->parent->isRed=false;
        node->parent->parent->isRed=true;
        leftRotate(node->parent->parent);
      }
    }
  }

  root->isRed=false;

}

void MovieTree::leftRotate(MovieNode *x) {

  MovieNode *y=x->rightChild;
  x->rightChild=y->leftChild;

  if (y->leftChild!=nil) {
    y->leftChild->parent=x;
  }

  y->parent=x->parent;

  if (x->parent==nil) {
    root=y;
  }

  else {
    if (x==x->parent->leftChild) {
      x->parent->leftChild=y;
    }

    else {
      x->parent->rightChild=y;
    }
  }

  y->leftChild=x;
  x->parent=y;

}

void MovieTree::rightRotate(MovieNode *x) {

  MovieNode *y=x->leftChild;
  x->leftChild=y->rightChild;

  if (y->rightChild!=nil) {
    y->rightChild->parent=x;
  }

  y->parent=x->parent;

  if (x->parent==nil) {
    root=y;
  }

  else {
    if (x==x->parent->leftChild) {
      x->parent->leftChild=y;
    }

    else {
      x->parent->rightChild=y;
    }
  }

  y->rightChild=x;
  x->parent=y;

}

MovieNode *MovieTree::searchMovieTree(MovieNode *node, string title) {

  if(node==nil) return nil;

  MovieNode *current=node;

  if (title<current->title) {
    current=searchMovieTree(current->leftChild, title);
    return current;
  }

  if (current->title==title) return current;

  if (title>current->title) {
    current=searchMovieTree(current->rightChild, title);
    return current;
  }

  return nil;

}

void MovieTree::findMovie(string title) {

  MovieNode *foundMovie=searchMovieTree(root, title);

  if (foundMovie!=nil) {
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title:" << foundMovie->title << endl;
    cout << "Year:" << foundMovie->year << endl;
    cout << "Quantity:" << foundMovie->quantity << endl;
  }

  else cout << "Movie not found." << endl;

}

void MovieTree::rentMovie(string title) {

  MovieNode *foundMovie=searchMovieTree(root, title);

  if (foundMovie!=nil) {
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

void MovieTree::deleteMovieNode(string title) {

  MovieNode *found=searchMovieTree(root,title);

  if (found==nil) {
    cout << "Movie not found." << endl;
    return;
  }

  rbDelete(found);

}

void MovieTree::rbDelete(MovieNode *z) {

  MovieNode *replacement;
  MovieNode *min;
  bool nodeColor=z->isRed;

  if (z->rightChild!=nil && z->leftChild!=nil) {
    min=z->rightChild;

    while (min->leftChild!=nil) min=min->leftChild;
    nodeColor=min->isRed;
    replacement=min->rightChild;

    z->ranking=min->ranking;
    z->title=min->title;
    z->year=min->year;
    z->quantity=min->quantity;

    if (min->parent->leftChild==min) min->parent->leftChild=min->rightChild;

    else min->parent->rightChild=min->rightChild;

    delete min;
  }

  else if (z->rightChild!=nil) {
    replacement=z->rightChild;

    if (z->parent->leftChild==z) z->parent->leftChild=replacement;

    else z->parent->rightChild=replacement;

    replacement->parent=z->parent;

    delete z;
  }

  else if (z->leftChild!=nil) {
    replacement=z->leftChild;

    if (z->parent->leftChild==z) z->parent->leftChild=replacement;

    else z->parent->rightChild=replacement;

    replacement->parent=z->parent;

    delete z;
  }

  else {
    if (z->parent->leftChild==z) z->parent->leftChild=nil;

    else z->parent->rightChild=nil;

    delete z;
  }

  if (!nodeColor) rbDeleteFixup(replacement);

}

// void MovieTree::rbDelete(MovieNode *z) {
//
//   bool nodeColor=z->isRed;
//   MovieNode *min;
//   MovieNode *x;
//
//   if (z!=root) {
//     if (z->leftChild==nil && z->rightChild==nil) { //No children
//       if (z==z->parent->leftChild) z->parent->leftChild=nil;
//
//       else z->parent->rightChild=nil;
//     }
//
//     else if (z->leftChild!=nil && z->rightChild!=nil) { //Two children
//       min=z->rightChild;
//       while (min->leftChild!=nil) min=min->leftChild;
//
//       nodeColor=min->isRed;
//       x=min->rightChild;
//
//       if (min==z->rightChild) {
//         z->parent->leftChild=min;
//         min->parent=z->parent;
//       }
//
//       else {
//         min->parent->leftChild=min->rightChild;
//         min->parent=z->parent;
//         min->rightChild->parent=min->parent;
//         z->parent->leftChild=min;
//         min->leftChild=z->leftChild;
//         min->rightChild=z->rightChild;
//         z->rightChild->parent=min;
//         z->leftChild->parent=min;
//         min->isRed=z->isRed;
//       }
//     }
//
//     else if (z->leftChild!=nil) { //One child left
//       if (z==z->parent->leftChild) {
//         x=z->leftChild;
//         z->parent->leftChild=x;
//         x->parent=z->parent;
//       }
//
//       else {
//         x=z->leftChild;
//         z->parent->rightChild=x;
//         x->parent=z->parent;
//       }
//     }
//
//     else if (z->rightChild!=nil) { //One child right
//       if (z==z->parent->leftChild) {
//         x=z->rightChild;
//         z->parent->leftChild=x;
//         x->parent=z->parent;
//       }
//
//       else {
//         x=z->rightChild;
//         z->parent->rightChild=x;
//         x->parent=z->parent;
//       }
//     }
//   }
//
//   if (nodeColor==false) rbDeleteFixup(x);
//
//   delete z;
//
// }

void MovieTree::rbDeleteFixup(MovieNode *node) {

  MovieNode *s;

  while (node!=root && node->isRed==false) {
    if (node==node->parent->leftChild) {
      s=node->parent->rightChild;

      if (s->isRed) {
        s->isRed=false;
        node->parent->isRed=true;
        leftRotate(node->parent);
        s=node->parent->rightChild;
      }

      if (s->leftChild->isRed==false && s->rightChild->isRed==false) {
        s->isRed=true;
        node=node->parent;
      }

      else if (s->leftChild->isRed && s->rightChild->isRed==false) {
        s->leftChild->isRed=false;
        s->isRed=true;
        rightRotate(s);
        s=node->parent->rightChild;
      }

      else {
        s->isRed=node->parent->isRed;
        node->parent->isRed=false;
        s->rightChild->isRed=false;
        leftRotate(node->parent);
        node=root;
      }
    }

    else {
      s=node->parent->leftChild;

      if (s->isRed) {
        s->isRed=false;
        node->parent->isRed=true;
        rightRotate(node->parent);
        s=node->parent->leftChild;
      }

      if (s->rightChild->isRed==false && s->leftChild->isRed==false) {
        s->isRed=true;
        node=node->parent;
      }

      else if (s->rightChild->isRed && s->leftChild->isRed==false) {
        s->rightChild->isRed=false;
        s->isRed=true;
        leftRotate(s);
        s=node->parent->leftChild;
      }

      else {
        s->isRed=node->parent->isRed;
        node->parent->isRed=false;
        s->leftChild->isRed=false;
        rightRotate(node->parent);
        node=root;
      }
    }
  }

  node->isRed=false;

}

void MovieTree::printMovieInventory() {

  printMovieInventory(root);

}

void MovieTree::printMovieInventory(MovieNode *node) {

  if(node==nil){
     return;
  }

  printMovieInventory(node->leftChild);
  cout << "Movie: " << node->title << " " << node->quantity << endl;
  printMovieInventory(node->rightChild);

}

int MovieTree::countMovieNodes(MovieNode *node) {

  if(node==nil){
     return 0;
  }

  int c=0;

  c+=countMovieNodes(node->leftChild);
  c++;
  c+=countMovieNodes(node->rightChild);

  return c;

}

int MovieTree::countMovieNodes() {

  // rbValid(root);
  // cout << root->title << endl;

  return countMovieNodes(root);

}

void MovieTree::DeleteAll(MovieNode *node) {

  if(node==nil) return;

  MovieNode *current=node;

  if (current->leftChild!=nil) {
    DeleteAll(current->leftChild);
  }

  if (current->rightChild!=nil) {
    DeleteAll(current->rightChild);
  }

  cout << "Deleting: " << current->title << endl;
  delete current;

}

int MovieTree::countLongestPath() {

  return countLongestPath(root);

}

int MovieTree::countLongestPath(MovieNode *node) {

  MovieNode *tmp=root;
  int lLength=2;
  int rLength=2;

  while (tmp!=nil) {
    tmp=tmp->leftChild;
    lLength++;
  }

  if (tmp->parent->rightChild!=nil) lLength++;

  tmp=root;

  while (tmp!=nil) {
    tmp=tmp->rightChild;
    rLength++;
  }

  if (tmp->parent->leftChild!=nil) rLength++;

  // cout << lLength << " " << rLength << endl;

  return max(lLength,rLength);

}

bool MovieTree::isValid() {

  if (rbValid(root)) return true;

  else return false;

}

int MovieTree::rbValid(MovieNode * node) {

  int lh = 0;
  int rh = 0;

  // If we are at a nil node just return 1
  if (node == nil)
    return 1;

  else {
    // First check for consecutive red links.
    if (node->isRed) {
      if(node->leftChild->isRed || node->rightChild->isRed) {
        cout << "This tree contains a red violation" << endl;
        return 0;
      }
    }

    // Check for valid binary search tree.
    if ((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0)) {
      cout << "This tree contains a binary tree violation" << endl;
      return 0;
    }

    // Deteremine the height of let and right children.
    lh = rbValid(node->leftChild);
    rh = rbValid(node->rightChild);

    // black height mismatch
    if (lh != 0 && rh != 0 && lh != rh) {
      cout << "This tree contains a black height violation" << endl;
      return 0;
    }

    // If neither height is zero, incrament if it if black.
    if (lh != 0 && rh != 0) {
      if (node->isRed)
        return lh;

      else
        return lh+1;
    }

    else
      return 0;
  }

}
