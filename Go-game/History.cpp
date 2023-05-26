#include "History.h"
#include <cassert>

History::History() { head = nullptr; }

History::History(const History &history_in) {
  head = copyLinkedList(history_in.head);
}

History::~History() {
  destroyLinkedList(head);
  head = nullptr;
}

History &History::operator=(const History &history_in) {
  if (this != &history_in) {
    destroyLinkedList(head);
    head = copyLinkedList(history_in.head);
  }
  return *this;
}

bool History::isAtLeast1Long() const {
  if (head != nullptr) {
    return true;
  } else {
    return false;
  }
}

bool History::isAtLeast2Long() const {
  if (isAtLeast1Long()) {
    if (head->p_next != nullptr) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool History::isAtLeast3Long() const {
  if (isAtLeast2Long()) {
    if (head->p_next->p_next != nullptr) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

const Board &History::getFirst() const {
  assert(isAtLeast1Long());
  return head->gameBoard;
}

const Board &History::getSecond() const {
  assert(isAtLeast2Long());
  return head->p_next->gameBoard;
}

bool History::isInList(const Board &board_in) const {
  HistoryNode *currptr = head;
  while (currptr != NULL) {
    if (board_in == currptr->gameBoard) {
      return true;
    }
    currptr = currptr->p_next;
  }
  return false;
}

void History::addAtHead(const Board &board_in) {
  HistoryNode *newNode = new HistoryNode;
  newNode->gameBoard = board_in;
  newNode->p_next = head;
  head = newNode;
}

void History::removeAtHead() {
  assert(isAtLeast1Long());
  HistoryNode *deleteptr = head;
  head = head->p_next;
  delete deleteptr;
  deleteptr = NULL;
}

void History::removeAll() {
  destroyLinkedList(head);
  head = nullptr;
}

HistoryNode *copyLinkedList(const HistoryNode *p_old_head_in) {
  if (p_old_head_in == nullptr) {
    return nullptr;
  }
  HistoryNode *p_new_head = new HistoryNode;
  p_new_head->gameBoard = p_old_head_in->gameBoard;
  HistoryNode *p1 = const_cast<HistoryNode *>(p_old_head_in);
  HistoryNode *p2 = p_new_head;

  while (p1->p_next != nullptr) {
    p2->p_next = new HistoryNode;
    p1 = p1->p_next;
    p2 = p2->p_next;

    p2->gameBoard = p1->gameBoard;
  }
  p2->p_next = nullptr;
  return p_new_head;
}

void destroyLinkedList(HistoryNode *p_head_in) {
  HistoryNode *currPtr = p_head_in;
  HistoryNode *ptemp;
  while (currPtr != NULL) {
    ptemp = currPtr;
    currPtr = currPtr->p_next;
    delete ptemp;
  }
}