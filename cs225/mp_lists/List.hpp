/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  length_ = 0;

  ListNode* currNode = head_;
  ListNode* nextNode = head_;
  while (currNode != NULL) {
    nextNode = currNode->next;
    delete currNode;
    currNode = nextNode;
  }

  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);

  newNode -> prev = NULL;
  newNode -> next = head_;

  if (head_ != NULL) 
    head_ -> prev = newNode;

  head_ = newNode;
  if (tail_ == NULL) { tail_ = newNode;} 
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  // /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);


  newNode -> prev = tail_;
  newNode -> next = NULL;                         

  if (tail_ != NULL)
    tail_ -> next = newNode; 
  

  tail_ = newNode;
  if (head_ == NULL) { head_ = newNode; }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode* curr = start;

  if (curr != NULL) {
    for (int i = 0; i < splitPoint && curr->next != NULL; i++) {
      curr = curr->next;
    }
  }

  // curr->prev = NULL;

  return curr;


  // if (curr != NULL) {
  //     curr->prev->next = NULL;
  //     curr->prev = NULL;
  // }

  // return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1

  ListNode* currNode = head_;
  bool first = true;

  bool hasThree = true;
  ListNode* lastNode = NULL;
  while (hasThree) {

    if (currNode!= NULL) {
      if (currNode->next != NULL) {
        if (currNode->next->next != NULL) {

          ListNode* node3 = currNode ;
          ListNode* node1 = currNode->next;
          ListNode* node2 = currNode->next->next;
          ListNode* node4 = NULL;
          if (currNode->next->next->next != NULL) {
            node4 = currNode->next->next->next;
          }

          node1->prev = NULL;
          node2->prev = NULL;
          node3->prev = NULL;
          node1->next = NULL;
          node2->next = NULL;
          node3->next = NULL;

          if (lastNode != NULL) { lastNode-> next = node1; }
          node1->prev = lastNode;

          node1->next = node2;
          node2->prev = node1;

          node2->next = node3;
          node3->prev = node2;

          if (node4 != NULL) {
            currNode = node4;
            lastNode = node3;
          } else {
            tail_ = node3;
            hasThree = false;
          }

          if (first) {
            head_ = node1;
            first = false;
          }

        } else {
          hasThree = false;
        }
      } else {
        hasThree = false;
      }
    } else {
      hasThree = false;
    }
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
  tail_->next = NULL;
}

/**new ListNode(
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  ListNode* startOuter = NULL;
  ListNode* endOuter = NULL;

  if (startPoint != NULL) 
    startOuter = startPoint->prev;
  if (endPoint != NULL) 
    endOuter = endPoint->next;

  ListNode* start = startPoint;
  ListNode* end = endPoint;
  start->prev = NULL;
  end->next = NULL;

  ListNode* lastNode = NULL;
  ListNode* nextNode = NULL;

  while (start->next != NULL) {
    lastNode = start->prev;
    if (lastNode == NULL) { end = start;}
    nextNode = start->next;

    start->next = lastNode;
    start->prev = nextNode;
    start = nextNode;
  }
  
  lastNode = start->prev;
  nextNode = start->next;

  start->next = lastNode;
  start->prev = nextNode;

  startPoint = start;
  endPoint = end;

  if (startOuter != NULL) {
    startOuter->next = startPoint;
    startPoint->prev = startOuter;
  }
  if (endOuter != NULL) {
    endOuter->prev = endPoint;
    endPoint->next = endOuter;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  ListNode* top = NULL;
  ListNode* bottom = head_;

  bool firstRun = true;

  while (bottom != NULL) {
    top = bottom;
    for (int i = 0; i < n-1; i++) {
      if (bottom->next != NULL) 
        bottom = bottom->next;
      else 
        break;
    }

    ListNode* bottomHolder = NULL;
    if (bottom->next != NULL)
      bottomHolder = bottom->next;

    reverse(top, bottom);

    if (firstRun) {
      head_ = top;
      firstRun = false;
    }

    if (bottomHolder == NULL)
      tail_ = bottom;

    bottom = bottomHolder;
  }

  tail_->next = NULL;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    int a = 0;
    if (tail_ != NULL) {
        while (tail_->next != NULL){
            tail_ = tail_->next;
        }
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2



  if (first == NULL) { 
    return second;
  } else if (second == NULL) {
    return first;
  }


  ListNode* aaa = first;
  ListNode* bbb = second;
  int x = 1;
  int y = 1;
  while (aaa->next != NULL){
      aaa = aaa->next;
      x++;
  }
  while (bbb->next != NULL){
    bbb = bbb->next;
    y++;
  }

  if (x < y) {
    return merge(second, first);
  }



  ListNode* firstNode = first;
  ListNode* firstNext = NULL;

  if (firstNode->next != NULL) {
    firstNext = firstNode->next;
  }

  ListNode* secondNode = second;
  ListNode* secondNext = NULL;

  firstNode->prev = NULL;
  secondNode->prev = NULL;



  int a = 0;
  int c = 0;
  while (secondNode != NULL) {

    secondNode->prev = NULL;
    secondNext = secondNode->next;

    if (secondNext != NULL)
      secondNext->prev = NULL;

    if (false) {
      if (firstNode != NULL) {
        std::cout << "f1 ";
        if (firstNode->prev != NULL) {
          std::cout << firstNode->prev->data << " "; 
          // std::cout << "b  ";
        } else {
          std::cout << "a  ";
        }
        std::cout << firstNode->data << " ";
          // std::cout << "b  ";

        if (firstNode->next != NULL) {
          std::cout << firstNode->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOFIRST"<< std::endl;
      }

      if (firstNext != NULL) {
        std::cout << "f2 ";
        if (firstNext->prev != NULL) {
          std::cout << firstNext->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << firstNext->data << " ";
                  // std::cout << "b  ";

        if (firstNext->next != NULL) {
          std::cout << firstNext->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOFIRSTNEXT" << std::endl;
      }

      if (secondNode != NULL) {
        std::cout << "s1 ";
        if (secondNode->prev != NULL) {
          std::cout << secondNode->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << secondNode->data << " ";
                  // std::cout << "b  ";

        if (secondNode->next != NULL) {
          std::cout << secondNode->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOSECOND" << std::endl;
      }
      
      if (secondNext != NULL) {
        std::cout << "s2 ";
        if (secondNext->prev != NULL) {
          std::cout << secondNext->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << secondNext->data << " ";
                  // std::cout << "b  ";

        if (secondNext->next != NULL) {
          std::cout << secondNext->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOSECONDNEXT"<<  std::endl;
      }
    }

    if ( secondNode->data < firstNode->data ) {
      // std::cout << "secondNode < firstNode ";
      secondNode->next = firstNode;
      firstNode->prev = secondNode;

      firstNode = secondNode;
      firstNext = firstNode->next;

      secondNode = secondNext;

      a++;
    } 
    else if (firstNext == NULL) {
      // std::cout << "secondNode > firstNode and firstnode is at the end ";

      secondNode->prev = firstNode;
      firstNode->next = secondNode;

      secondNode->next = NULL;

      firstNext = secondNode;

      secondNode = secondNext;

      a++;
    }
    else if (secondNode->data < firstNext->data) {
      // std::cout << " firstNode <secondNode <firstNext ";

      secondNode->prev = firstNode;
      firstNode->next = secondNode;

      secondNode->next = firstNext;
      firstNext->prev = secondNode;

      firstNext = secondNode;

      secondNode = secondNext;

      a++;
    }
    else if (firstNext->next == NULL) {
      // std::cout << " firstNext <secondNode and firstNext at wall ";

      secondNode->prev = firstNext;
      firstNext->next = secondNode;

      secondNode->next = NULL;

      firstNode = firstNext;
      firstNext = secondNode;

      secondNode = secondNext;
      a++;
    }
    else {
      // std::cout << " firstNext <secondNode so shift firstNode and firstNext up ";
      firstNode = firstNext;
      firstNext = firstNext->next;
    }

    c++;
    if (false) {
      // std::cout << std::endl;
      // std::cout << "emptry"<< std::endl;

      std::cout <<"a:"<< a << " c:"<< c <<std::endl;        

      if (firstNode != NULL) {      
        std::cout << "f1 ";
        if (firstNode->prev != NULL) {
          std::cout << firstNode->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << firstNode->data << " ";
                  // std::cout << "b  ";

        if (firstNode->next != NULL) {
          std::cout << firstNode->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOFIRST"<< std::endl;
      }

      if (firstNext != NULL) {
        std::cout << "f2 ";
        if (firstNext->prev != NULL) {
          std::cout << firstNext->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << firstNext->data << " ";
                  // std::cout << "b  ";

        if (firstNext->next != NULL) {
          std::cout << firstNext->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOFIRSTNEXT" << std::endl;
      }

      if (secondNode != NULL) {
        std::cout << "s1 ";
        if (secondNode->prev != NULL) {
          std::cout << secondNode->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << secondNode->data << " ";
                  // std::cout << "b  ";

        if (secondNode->next != NULL) {
          std::cout << secondNode->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOSECOND" << std::endl;
      }

      if (secondNext != NULL) {
        std::cout << "s2 ";
        if (secondNext->prev != NULL) {
          std::cout << secondNext->prev->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << secondNext->data << " ";
        if (secondNext->next != NULL) {
          std::cout << secondNext->next->data << " ";
                    // std::cout << "b  ";

        } else {
          std::cout << "a  ";
        }
        std::cout << " "<<std::endl;
      } else {
        std::cout << "NOSECONDNEXT"<<  std::endl;
      }

      std::cout << " "<<  std::endl;

    }
  }

  


  if (false) {
    ListNode* a1 = firstNode;
    ListNode* b1 = secondNode;
    int xx = 1;
    int yy = 1;
    while (a1->prev != NULL){
        a1 = a1->prev;
    }
    while (a1->next != NULL){
        a1 = a1->next;
        xx++;
    }
    if (b1 != NULL) {
      while (b1->prev != NULL){
        b1 = b1->prev;
      }
      while (b1->next != NULL){
        b1 = b1->next;
        y++;
      }
    }
    std::cout <<"x "<< x << " y "<< y <<std::endl;
  }

  if (firstNode == NULL) {
      // std::cout<<"end4"<<std::endl;
  }
  while (firstNode->prev != NULL){
    firstNode = firstNode->prev;
  }
  return firstNode;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  // std::cout << "chainlength: " <<chainLength <<std::endl;

  if (chainLength == 0) {
    return NULL;
  } else if (chainLength == 1) {
    return start;
  } else if (chainLength == 2) {

    ListNode* second = start->next;
    start->next = NULL;
    second->prev = NULL;


    return merge(start, second);
  }

  int length1 = chainLength/2;
  int length2 = chainLength - length1;

  ListNode* secondHead = start;

  int n = 0;   
  for (int i = 0; i < length1; i++){
    secondHead = secondHead->next;
  }   
  secondHead->prev ->next = NULL;
  secondHead->prev = NULL;

  return merge( mergesort(start, length1), mergesort(secondHead, length2) );
  

}

