#include "SplayTree.h"
#include <iostream>
#include <vector>

using namespace std;

inline splay* SplayTree::RR_Rotate(splay* k2) {
    splay* k1 = k2->lchild;
    k2->lchild = k1->rchild;
    k1->rchild = k2;
    return k1;
}

inline splay* SplayTree::LL_Rotate(splay* k2) {
    splay* k1 = k2->rchild;
    k2->rchild = k1->lchild;
    k1->lchild = k2;
    return k1;
}

splay* SplayTree::Splay(KEY_TYPE key, splay* root) {
    if (!root) return NULL;
    splay header;
    header.lchild = header.rchild = NULL;
    splay* LeftTreeMax = &header;
    splay* RightTreeMin = &header;

    while (1) {
        if (key < root->key) {
            if (!root->lchild) break;
            if (key < root->lchild->key) {
                root = RR_Rotate(root);
                if (!root->lchild) break;
            }
            RightTreeMin->lchild = root;
            RightTreeMin = RightTreeMin->lchild;
            root = root->lchild;
            RightTreeMin->lchild = NULL;
        }
        else if (key > root->key) {
            if (!root->rchild) break;
            if (key > root->rchild->key) {
                root = LL_Rotate(root);
                if (!root->rchild) break;
            }
            LeftTreeMax->rchild = root;
            LeftTreeMax = LeftTreeMax->rchild;
            root = root->rchild;
            LeftTreeMax->rchild = NULL;
        }
        else break;
    }

    LeftTreeMax->rchild = root->lchild;
    RightTreeMin->lchild = root->rchild;
    root->lchild = header.rchild;
    root->rchild = header.lchild;
    return root;
}

splay* SplayTree::New_Node(KEY_TYPE key, node node) {
    splay* p_node = new splay;
    if (!p_node) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    p_node->key = key;
    p_node->items.push_back(node);
    p_node->lchild = p_node->rchild = NULL;
    return p_node;
}

splay* SplayTree::Insert(KEY_TYPE key, splay* root, node node) {
    static splay* p_node = NULL;
    if (!p_node) p_node = New_Node(key, node);
    else p_node->key = key;
    if (!root) {
        root = p_node;
        p_node = NULL;
        return root;
    }
    root = Splay(key, root);
    if (key == root->key) root->items.push_back(node);
    else if (key < root->key) {
        p_node->lchild = root->lchild;
        p_node->rchild = root;
        root->lchild = NULL;
        root = p_node;
    }
    else {
        p_node->rchild = root->rchild;
        p_node->lchild = root;
        root->rchild = NULL;
        root = p_node;
    }
    p_node = NULL;
    return root;
}

splay* SplayTree::Delete(KEY_TYPE key, splay* root) {
    splay* temp;
    if (!root) return NULL;
    root = Splay(key, root);
    if (key != root->key) return root;
    else {
        if (!root->lchild) {
            temp = root;
            root = root->rchild;
        }
        else {
            temp = root;
            root = Splay(key, root->lchild);
            root->rchild = temp->rchild;
        }
        delete temp;
        return root;
    }
}

splay* SplayTree::Search(KEY_TYPE key, splay* root) {
    return Splay(key, root);
}

void SplayTree::InOrder(splay* root) {
    if (root) {
        InOrder(root->lchild);
        for (const auto& item : root->items) {
            cout << "Hash Value: " << item.hash_value;
            cout << "  Folder Name: " << item.Folder_Name;
            cout << " | Path: " << item.path << "\n";
        }
        InOrder(root->rchild);
    }
}
