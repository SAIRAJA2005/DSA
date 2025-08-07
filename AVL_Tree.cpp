#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    int height;
    TreeNode *left, *right;
    TreeNode(int val) {
        data = val;
        height = 1;
        left = right = NULL;
    }
};

struct AVLTree {
    TreeNode *root;

    AVLTree() {
        root = NULL;
    }
    int Height(TreeNode *node) {
        return node ? node->height : 0;
    }
    int GetBalance(TreeNode *node) {
        return node ? Height(node->left) - Height(node->right) : 0;
    }

    TreeNode* LeftRotate(TreeNode *P) {
        TreeNode *X = P->right;
        TreeNode *Y = X->left;

        X->left = P;
        P->right = Y;

        P->height = max(Height(P->left), Height(P->right)) + 1;
        X->height = max(Height(X->left), Height(X->right)) + 1;

        return X;
    }

    TreeNode* RightRotate(TreeNode *P) {
        TreeNode *X = P->left;
        TreeNode *Y = X->right;

        X->right = P;
        P->left = Y;

        P->height = max(Height(P->left), Height(P->right)) + 1;
        X->height = max(Height(X->left), Height(X->right)) + 1;

        return X;
    }

    TreeNode* ADD(TreeNode *node, int val) {
        if (!node)
            return new TreeNode(val);

        if (val < node->data)
            node->left = ADD(node->left, val);
        else if (val > node->data)
            node->right = ADD(node->right, val);
        else
            return node; // No duplicates

        node->height = 1 + max(Height(node->left), Height(node->right));
        int balance = GetBalance(node);

        // LL Case
        if (balance > 1 && val < node->left->data)
            return RightRotate(node);

        // RR Case
        if (balance < -1 && val > node->right->data)
            return LeftRotate(node);

        // LR Case
        if (balance > 1 && val > node->left->data) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // RL Case
        if (balance < -1 && val < node->right->data) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }

    void Insert(int val) {
        root = ADD(root, val);
    }

    TreeNode* Delete(TreeNode *node, int val) {
        if (!node) return node;

        if (val < node->data)
            node->left = Delete(node->left, val);
        else if (val > node->data)
            node->right = Delete(node->right, val);
        else {
            if (!node->left || !node->right) {
                TreeNode *temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                TreeNode *temp = node->right;
                while (temp->left)
                    temp = temp->left;
                node->data = temp->data;
                node->right = Delete(node->right, temp->data);
            }
        }

        if (!node)
            return node;

        node->height = 1 + max(Height(node->left), Height(node->right));
        int balance = GetBalance(node);

        // LL
        if (balance > 1 && GetBalance(node->left) >= 0)
            return RightRotate(node);

        // LR
        if (balance > 1 && GetBalance(node->left) < 0) {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }

        // RR
        if (balance < -1 && GetBalance(node->right) <= 0)
            return LeftRotate(node);

        // RL
        if (balance < -1 && GetBalance(node->right) > 0) {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }

    void DeleteNode(int val) {
        root = Delete(root, val);
    }

    void Inorder(TreeNode *node) {
        if (!node) return;
        Inorder(node->left);
        cout << node->data << " ";
        Inorder(node->right);
    }

    void Display() {
        Inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter values: ";
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        tree.Insert(A[i]);
    }

    cout << "Inorder after insertion: ";
    tree.Display();

    int del;
    cout << "Enter value to delete: ";
    cin >> del;
    tree.DeleteNode(del);

    cout << "Inorder after deletion: ";
    tree.Display();

    return 0;
}
