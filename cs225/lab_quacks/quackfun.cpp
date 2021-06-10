/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.size() == 0) {return 0;}
    else if (s.size() == 1) {return s.top();}

    T top = s.top();
    s.pop();
    T ss = sum(s);
    s.push(top);

    return ( s.top() + ss );

    // Your code here
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    // @TODO: Make less optimistic

    if (input.empty()) {return true;}
    else if (input.size() == 1) {
        if ( input.back() != ']' && input.front() != '[' ) 
            return true; }

    if (input.front() == ']') {return false;}

    stack<char> tempStack;

    /*
        First set of '['
    */
    
    // remove letters, and separate the front ']'
    while (input.size() != 0 && input.front() != ']') {
        if (input.front() == '[')
            tempStack.push('[');
        input.pop();
    }

    if (input.size() == 0) { 
        // if only letters, return true
        if (tempStack.size() == 0) {return true;}
        // if no '[' but some ']', return false
        else {return false;}
    }

    // remove the letters and delete the '[' and it's corresponding ']'
    while (input.size() != 0 && input.front() != '[') {
        if (input.front() == ']') {
            if (tempStack.size() != 0) 
                tempStack.pop(); 
            else {return false;}
        }
        input.pop();
    }

    /*
        Second set of '['
    */

    // Remake the queue
    for (unsigned i = 0; i < tempStack.size(); i++)
        input.push('[');
    for (unsigned i = 0; i < (input.size()-tempStack.size()); i++) {
        input.push(input.front());
        input.pop(); }

    return isBalanced(input);
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{

    
    //stack<T> s;
    // optional: queue<T> q2;

    // Your code here
    q = scramble2(q, 1, false);
}

template <typename T>
queue<T> scramble2(queue<T> q, unsigned n, bool flip) {
    queue<T> qFront;
    bool lastQueue;

    // Isolate the front portion of the list
    if (n < q.size()) {
        for (unsigned i = 0; i < n; i++) {
            qFront.push(q.front());
            q.pop();  
        }
        lastQueue = false;  
    } else {
        qFront = q;
        lastQueue = true;  
    }
    
    // Flip the list if necessary
    if (flip) {
        stack<T> tempStack;
        unsigned size = qFront.size();
        for (unsigned i = 0; i < size; i++) {
            tempStack.push(qFront.front());
            qFront.pop(); }
        for (unsigned i = 0; i < size; i++) {
            qFront.push(tempStack.top());
            tempStack.pop();  }
    }

    if (lastQueue) {return qFront;}
    else {
        unsigned size = q.size();
        queue<T> newQueue = scramble2(q, n+1, !flip);
        for (unsigned i = 0; i < size; i++) {
            qFront.push(newQueue.front());
            newQueue.pop();
        }
        return qFront;
    }
}

}
