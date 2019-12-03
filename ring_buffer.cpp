#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
using namespace std;

#define FORWARD 1
#define REWIND  0

class Node {
  public:
  int data = 0;
  Node *prev, *next;
};

class LList {
  public:
  string name;
  Node head, tail; 
  LList(string argname) {
    head.next = head.prev = &tail;
    tail.next = tail.prev = &head;
    name = argname;
  };
  ~LList();
  void add(int ldata);
  void print(bool dir);
  void dcopy(const LList& other);  
  LList(const LList& other); 
  LList& operator=(const LList& other);
};

void LList::dcopy(const LList& other) {
  Node *scurr = other.tail.next;
  bool head_copied = false;

  while(scurr) {
    if (scurr == &other.head && head_copied) {
      return;
    } else if (scurr == &other.head && !head_copied) {
      head_copied = true, this->add(scurr->data), scurr = scurr->next;
    } else {
      this->add(scurr->data), scurr = scurr->next;
    }
  }
}

LList::LList(const LList& other) {
  dcopy(other);
}

LList& LList::operator=(const LList& other) {
  if (this == &other) return *this;
  dcopy(other);
  return *this;
}

LList::~LList() {
  Node *curr = head.next, *tmp;
  while(curr->next && (curr != &tail))
    tmp = curr, curr = curr->next, delete tmp;
  cout << "[FREE] (" << name << ") elements" << endl;
}

void LList::print(bool dir) {
  if (dir == FORWARD) {
    Node *tmp = &head;
    cout << "[FORWARD] (" << name << ") ";
    while (tmp) {
      cout << tmp->data << " ";
      if (tmp->data == tail.data) {
        cout << endl;
        return;
      }
      tmp = tmp->next;
    }
  } else if (dir == REWIND) {
    Node *tmp = &tail;
    cout << "[REVERSE] (" << name << ") ";
    while (tmp) {
      cout << tmp->data << " ";
      if (tmp->data == head.data) {
        cout << endl;
        return;
      }
      tmp = tmp->prev;
    }
  }
}

void LList::add(int ldata) {
  if (head.data == 0) {
    head.data = ldata;
    return;
  }
  if (tail.data == 0) {
    tail.data = ldata;
    return;
  }
  Node *nnode = new Node();
  nnode->data = tail.data;
  tail.data = ldata;
  (tail.prev)->next = nnode;
  nnode->prev = tail.prev;
  nnode->next = &tail;
  tail.prev = nnode;
}

int main()
{
  LList nlist("nlist"), clist("clist"), plist("plist"), blist("blist");
  nlist.add(4); // goes into head
  nlist.add(5); // the rest go in between
  nlist.add(6);
  nlist.add(7);
  nlist.add(8);
  nlist.add(9); // goes into tail
 
  nlist.print(FORWARD);
  nlist.print(REWIND);

  clist = nlist;
  clist.print(FORWARD);
  plist = clist;
  plist.print(FORWARD);
  blist = plist;
  blist.print(FORWARD);

  cout << "[END]" << endl;
  return 0;
}
