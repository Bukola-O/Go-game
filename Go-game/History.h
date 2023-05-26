#pragma once
#include "Board.h"

struct HistoryNode
{
  Board gameBoard;
  HistoryNode* p_next;
};

class History
{
  private:
   HistoryNode* head;
  public:
    History ();
    History (const History& history_in);
    ~History ();
    History& operator= (const History& history_in);
    bool isAtLeast1Long () const;
    bool isAtLeast2Long () const;
    bool isAtLeast3Long () const;
    const Board& getFirst () const;
    const Board& getSecond () const;
    bool isInList (const Board& board_in) const;
    void addAtHead (const Board& board_in);
    void removeAtHead ();
    void removeAll ();
};
  HistoryNode* copyLinkedList (const HistoryNode* p_old_head_in);
  void destroyLinkedList (HistoryNode* p_head_in);
