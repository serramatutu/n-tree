#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <iterator>

#include "AVLTreeNode.hpp"
#include "useful.hpp"

template <typename T, 
          class Less = std::less<T>>
class AVLTree {

    public:
        struct const_iterator : public AVLTreeNode<T, Less>::const_iterator {
            const_iterator() : AVLTreeNode<T, Less>::const_iterator() {};

            const_iterator(const AVLTree<T, Less>& tree, bool end = false) 
                : AVLTreeNode<T, Less>::const_iterator(tree.root, end) {};
        };

        struct iterator : public AVLTreeNode<T, Less>::iterator {
            iterator() : AVLTreeNode<T, Less>::iterator() {};

            iterator(AVLTree<T, Less>& tree, bool end = false) 
                : AVLTreeNode<T, Less>::iterator(tree.root, end) {};
        };
        // typedef typename AVLTreeNode<T, Less>::const_iterator const_iterator;
        // typedef typename AVLTreeNode<T, Less>::iterator iterator;

        AVLTree();
        virtual ~AVLTree();
        AVLTree(const AVLTree& other);
        AVLTree<T, Less>& operator=(AVLTree<T, Less> other);
        AVLTree(AVLTree&& other);

        void insert(const T& data);
        bool remove(const T& data);

        bool empty() const;

        const_iterator find(const T& data) const;
        iterator find(const T& data);

        int height() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        iterator begin();
        iterator end();

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const AVLTree<U>& t);

    private:
        AVLTreeNode<T, Less>* root;

        static const_iterator downcastIterator(const typename AVLTreeNode<T, Less>::const_iterator& it);
        static iterator downcastIterator(const typename AVLTreeNode<T, Less>::iterator& it);
};

template <typename T, class Less>
AVLTree<T, Less>::AVLTree() : root(nullptr) {}

template <typename T, class Less>
AVLTree<T, Less>::~AVLTree() {
    delete root;
    root = nullptr;
}

template <typename T, class Less>
AVLTree<T, Less>::AVLTree(const AVLTree<T, Less>& other) {
    if (other.root != nullptr)
        root = new AVLTreeNode<T, Less>(*other.root);
};

template <typename T, class Less>
AVLTree<T, Less>& AVLTree<T, Less>::operator=(AVLTree<T, Less> other) {
    std::swap(root, other.root);

    return *this;
}

template <typename T, class Less>
AVLTree<T, Less>::AVLTree(AVLTree&& other) : root(std::move(other.root)) {}


template <typename T, class Less>
typename AVLTree<T, Less>::const_iterator AVLTree<T, Less>::downcastIterator(const typename AVLTreeNode<T, Less>::const_iterator& it) {
    typename AVLTreeNode<T, Less>::const_iterator tmp(it);
    return static_cast<AVLTree<T, Less>::const_iterator&>(tmp);
}

template <typename T, class Less>
typename AVLTree<T, Less>::iterator AVLTree<T, Less>::downcastIterator(const typename AVLTreeNode<T, Less>::iterator& it) {
    typename AVLTreeNode<T, Less>::iterator tmp(it);
    return static_cast<AVLTree<T, Less>::iterator&>(tmp);
}

template <typename T, class Less>
typename AVLTree<T, Less>::const_iterator AVLTree<T, Less>::cbegin() const {
    if (root != nullptr)
        return AVLTree<T, Less>::downcastIterator(root->cbegin());
    return AVLTree<T, Less>::const_iterator();
}

template <typename T, class Less>
typename AVLTree<T, Less>::const_iterator AVLTree<T, Less>::cend() const {
    if (root != nullptr)
        return AVLTree<T, Less>::downcastIterator(root->cend());
    return AVLTree<T, Less>::const_iterator();
}

template <typename T, class Less>
typename AVLTree<T, Less>::iterator AVLTree<T, Less>::begin() {
    if (root != nullptr)
        return AVLTree<T, Less>::downcastIterator(root->begin());
    return AVLTree<T, Less>::iterator();
}

template <typename T, class Less>
typename AVLTree<T, Less>::iterator AVLTree<T, Less>::end() {
    if (root != nullptr) 
        return AVLTree<T, Less>::downcastIterator(root->end());
    return AVLTree<T, Less>::iterator();
}

template <typename T, class Less>
bool AVLTree<T, Less>::empty() const {
    return root == nullptr;
}

template <typename T, class Less>
void AVLTree<T, Less>::insert(const T& data) {
    if (root == nullptr)
        root = new AVLTreeNode<T, Less>(data, root);
    else
        root->insert(data);
}

template <typename T, class Less>
bool AVLTree<T, Less>::remove(const T& data) {
    if (root == nullptr)
        return false;
    return root->remove(data);
}

template <typename T, class Less>
typename AVLTree<T, Less>::iterator AVLTree<T, Less>::find(const T& data) {
    if (root == nullptr)
        return end();
    return AVLTree<T, Less>::downcastIterator(root->find(data));
}

template <typename T, class Less>
typename AVLTree<T, Less>::const_iterator AVLTree<T, Less>::find(const T& data) const {
    if (root == nullptr)
        return cend();
    return AVLTree<T, Less>::downcastIterator(const_cast<const AVLTreeNode<T, Less>*>(root)->find(data));
}

template <typename T, class Less>
int AVLTree<T, Less>::height() const {
    if (root == nullptr)
        return 0;
    return root->height(); 
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const AVLTree<T>& t) {
    os << "[";
    if (t.root != nullptr)
        os << *t.root;
    os << "]";

    return os;
}

#endif