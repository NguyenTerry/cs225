/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 */

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
    /* TODO Finish this function */

    size_t first_larger_idx = insertion_idx(subroot->elements, key);
    // std::cout<<first_larger_idx<<std::endl;

    /* If first_larger_idx is a valid index and the key there is the key we
     * are looking for, we are done. */

    /* Otherwise, we need to figure out which child to explore. For this we
     * can actually just use first_larger_idx directly. E.g.
     * | 1 | 5 | 7 | 8 |
     * Suppose we are looking for 6. first_larger_idx is 2. This means we want to
     * explore the child between 5 and 7. The children vector has a pointer for
     * each of the horizontal bars. The index of the horizontal bar we want is
     * 2, which is conveniently the same as first_larger_idx. If the subroot is
     * a leaf and we didn't find the key in it, then we have failed to find it
     * anywhere in the tree and return the default V.
     */

    DataPair data = (subroot->elements)[first_larger_idx];
        // std::cout<<data.key << " " << data.value<<std::endl;

    if (key == data) {
        return data.value;
    } else if (subroot->is_leaf) {
        return V();
    } else {
        subroot = (subroot->children)[first_larger_idx];
        return find(subroot, key);
    }
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if (root == nullptr) {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if (root->elements.size() >= order) {
        BTreeNode* new_root = new BTreeNode(false, order);
        if ( !(root->children).empty() )    
            root->is_leaf = false; // added
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{
    /* Assume we are splitting the 3 6 8 child.
     * We want the following to happen.
     *     | 2 |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     *
     * Insert a pointer into parent's children which will point to the
     * new right node. The new right node is empty at this point.
     *     | 2 |   |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Insert the mid element from the child into its new position in the
     * parent's elements. At this point the median is still in the child.
     *     | 2 | 6 |
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Now we want to copy over the elements (and children) to the right
     * of the child median into the new right node, and make sure the left
     * node only has the elements (and children) to the left of the child
     * median.
     *     | 2 | 6 |
     *    /   /     \
     * | 1 | | 3 | | 8 |
     *
     */

    /* E.g.
     * | 3 | 6 | 8 |
     * Mid element is at index (3 - 1) / 2 = 1 .
     * Mid child (bar) is at index 4 / 2 = 2 .
     * E.g.
     * | 2 | 4 |
     * Mid element is at index (2 - 1) / 2 = 0 .
     * Mid child (bar) is at index 2 / 2 = 1 .
     * This definition is to make this BTree act like the visualization
     * at
     * https://www.cs.usfca.edu/~galles/visualization/BTree.html
     */

    /* TODO Your code goes here! */
        /* Child of parent to be split */
    BTreeNode* child = parent->children[child_idx];
        /* Will replace the parent at the end */
    BTreeNode* new_parent = new BTreeNode(parent->is_leaf, order);    
        /* The new elem to be added to new_parent->elem*/
            // std::cout<<":biiii ";

    // DataPair new_elem = DataPair( K(),V() );
        // std::cout<<":biiii ";

        /* The new child to be added to new_parent->child (the right of child)*/
    BTreeNode* new_child = new BTreeNode(child->is_leaf, order);

    /* Fill up new_parent elements
     * 
     * mid_child_elem_idx - Index of middle of child->elements
     * mid_child_elem_itr - Iterator for middle index
     * 
     * new_elem - Iterator of element from child->elements to be inserted into new_parent->elements
     * mid_itr - Iterator marking where to insert the new element. 
     */
    size_t mid_child_elem_idx = (child->elements.size() - 1) / 2;
    auto mid_child_elem_itr = child->elements.begin() + mid_child_elem_idx;
 
    // new_elem = *mid_child_elem_itr;
    auto parse_elem_itr = (parent->elements).begin();
    auto mid_elem_itr = (parent->elements).begin() + child_idx;
    auto end__elem_itr = (parent->elements).end();
    for (; parse_elem_itr != mid_elem_itr; parse_elem_itr++)
        (new_parent->elements).push_back(*parse_elem_itr);
    (new_parent->elements).push_back(*mid_child_elem_itr);
    for (; parse_elem_itr != end__elem_itr; parse_elem_itr++)
        (new_parent->elements).push_back(*parse_elem_itr);
   /* Fill up new_child elements */
    parse_elem_itr = ++mid_child_elem_itr;
    end__elem_itr = (child->elements).end();
    for (; parse_elem_itr != end__elem_itr; parse_elem_itr++)
        (new_child->elements).push_back(*parse_elem_itr);
  /* Remove any elements taken from child->elements, from child->elements */
    int childSize = (child->elements).size();
    for (int i = mid_child_elem_idx; i < childSize; i++)
        (child->elements).pop_back();

    /* Fill up new_parent children
     *
     * mid_itr - Iterator marking where to insert the new child into new_parent->child.
     * new_child - new child to be inserted.
     */
    auto parse_child_itr = (parent->children).begin();
    auto mid_child_itr = (parent->children).begin() + child_idx + 1;
    auto end_child_itr = (parent->children).end();
    for (; parse_child_itr != mid_child_itr; parse_child_itr++)
        (new_parent->children).push_back(*parse_child_itr);
    (new_parent->children).push_back(new_child);
    for (; parse_child_itr != end_child_itr; parse_child_itr++)
        (new_parent->children).push_back(*parse_child_itr);
    /* Fill up new_child children
     *
     * mid_child_child_idx - Index of middle of child->children
     * mid_child_child_itr - Iterator for middle index
     */
    size_t mid_child_child_idx = child->children.size() / 2;
    auto mid_child_child_itr = child->children.begin() + mid_child_child_idx;
  
    parse_child_itr = mid_child_child_itr;
    end_child_itr = (child->children).end();
    for (; parse_child_itr != end_child_itr; parse_child_itr++)
        (new_child->children).push_back(*parse_child_itr);
    /* Remove any children taken from child->children, from child->children */
    childSize = (child->children).size();
    for (int i = mid_child_child_idx; i < childSize; i++)
        (child->children).pop_back();

    (parent->elements).clear();
    (parent->children).clear();
    parent->is_leaf = new_parent->is_leaf;
    for (DataPair elem : new_parent->elements)
        (parent->elements).push_back(elem);
    for (BTreeNode* child : new_parent->children)
        (parent->children).push_back(child);
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{

    /* There are two cases to consider.
     * If the subroot is a leaf node and the key doesn't exist subroot, we
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * 
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order.
     */

    size_t first_larger_idx = insertion_idx(subroot->elements, pair);

    /* TODO Your code goes here! */
    if (subroot->is_leaf) {

        BTreeNode* new_subroot = new BTreeNode(subroot->is_leaf, order);
        auto parse_iter = (subroot->elements).begin();
        auto mid_itr = (subroot->elements).begin() + first_larger_idx;
        auto end_itr = (subroot->elements).end();
        for ( ; parse_iter != mid_itr; parse_iter++)
            (new_subroot->elements).push_back(*parse_iter);
        (new_subroot->elements).push_back(pair);
        for ( ; parse_iter != end_itr; parse_iter++)
            (new_subroot->elements).push_back(*parse_iter);

        (subroot->elements).clear();
        for (DataPair elem : new_subroot->elements)
            (subroot->elements).push_back(elem);

    } else {
        BTreeNode* parent = subroot;
        subroot = (subroot->children)[first_larger_idx];
        insert(subroot, pair);

        if ( (subroot->elements).size() >= order ) {
            split_child(parent, first_larger_idx);
        }
    }
}
