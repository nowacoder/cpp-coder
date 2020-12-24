#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

string treeNodeToString(TreeNode* root) {
    if (root == nullptr) {
      return "[]";
    }

    string output = "";
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

void prettyPrintTree(TreeNode* node, string prefix = "", bool isLeft = true) {
    if (node == nullptr) {
        cout << "Empty tree";
        return;
    }

    if(node->right) {
        prettyPrintTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

    if (node->left) {
        prettyPrintTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> rst;
    if (root==NULL) return rst;
    queue<TreeNode*> v1;
    bool flag = true;
    TreeNode *node = NULL;
    v1.push(root);
    while (flag) {
        flag = false;
        vector<int> row;
        queue<TreeNode*> v2;
        while(!v1.empty()) {
            node = v1.front();
            row.push_back(node->val);
            v1.pop();
            if (node->left != NULL) {
                v2.push(node->left);
                flag = true;
            }
            if (node->right != NULL) {
                v2.push(node->right);
                flag = true;
            }
        }
        rst.push_back(row);
        v1 = v2;
    }
    return rst;
}

bool isSymSub(TreeNode* left, TreeNode* right) {
    if (left!=nullptr and right!=nullptr) {
        if (left->val==right->val) {
            if (isSymSub(left->left, right->right) and 
                isSymSub(left->right, right->left)) 
                return true;
            else return false;
        } else return false;
    } else if (left==nullptr and right==nullptr)
        return true;
    else return false;
}

bool isSymmetric(TreeNode* root) {
    if (root==nullptr) return true;
    return isSymSub(root->left, root->right);
}

int main() {
    string line;
    while (getline(cin, line)) {
        TreeNode* root = stringToTreeNode(line);
        prettyPrintTree(root);

        cout << isSymmetric(root) << endl;

        /*
        auto rst = levelOrder(root);
        for (auto row : rst) {
            for (int v : row) {
                cout << v << ' ';
            }
            cout << endl;
        } */
    }
    return 0;
}