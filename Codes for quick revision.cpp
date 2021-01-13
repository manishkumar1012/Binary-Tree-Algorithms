Binary Tree

//-------------1. LCA in a binary tree---------------

int lowestCommonAncestor(TreeNode* root, int p, int q) {
    if (root == NULL) {
        return -1;
    }
    if (root->val == p || root->val == q) {
        return root->val;
    }
    int left = lowestCommonAncestor(root->left, p, q);
    int right = lowestCommonAncestor(root->right, p, q);
    if (left != -1 && right != -1) {
        return root->val;
    }
    return (left == -1) ? right : left;
}
bool find(TreeNode* root, int temp) {
    if (root == NULL ) {
        return false;
    }
    if (root->val == temp) {
        return true;
    }
    return find(root->left, temp) || find(root->right, temp);
}
int Solution::lca(TreeNode* root, int p, int q) {
    return lowestCommonAncestor(root, p, q);
}

//--------2. Diameter of binary tree-------

int height(TreeNode* root, int &ans)
{
    if (root == NULL) {
        return 0;
    }
    int lh = height(root->left, ans);
    int rh = height(root->right, ans);
    ans  = max(ans, lh + rh);
    return 1 + max(lh, rh);
}
int diameterOfBinaryTree(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int ans = 0;
    height(root, ans);
    return ans;
}

//----------3. Postorder using one stack-----------

vector<int> Solution::postorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == NULL) {
        return ans;
    }
    stack<TreeNode*> stk;
    TreeNode *curr = root, *last = NULL;
    while (curr != NULL || !stk.empty()) {
        if (curr != NULL) {
            stk.push(curr);
            curr = curr->left;
        }
        else {
            curr = stk.top();
            if (curr->right == NULL || curr->right == last) {
                ans.push_back(curr->val);
                stk.pop();
                last = curr;
                curr = NULL;
            }
            else {
                curr = curr->right;
            }
        }
    }
    return ans;
}

//----------4. Inorder Traversal---------------

vector<int> Solution::inorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == NULL) {
        return ans;
    }
    stack<TreeNode*> stk;
    while (root != NULL || !stk.empty()) {
        while (root) {
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        ans.push_back(root->val);
        root = root->right;
    }
    return ans;
}

//-------------5. Symmetric binary tree----------

int Solution::isSymmetric(TreeNode* root) {
    if (!root) {
        return 1;
    }
    stack<pair<TreeNode*, TreeNode*>> stk;
    stk.push({root->left, root->right});
    while (!stk.empty()) {
        auto p = stk.top();
        TreeNode* left = p.first;
        TreeNode* right = p.second;
        stk.pop();
        if (!left && !right) {
            continue;
        }
        if (!left || !right) {
            return 0;
        }
        if (left->val != right->val) {
            return 0;
        }
        stk.push({left->left, right->right});
        stk.push({left->right, right->left});
    }
    return 1;
}

//------------6. Max path sum in binary tree---------------

int maxSum(TreeNode* root, int &ans) {
    if (!root) {
        return 0;
    }
    int lsum = maxSum(root->left, ans);
    int rsum = maxSum(root->right, ans);
    ans = max(ans, root->val + lsum + rsum);
    return max(0, root->val + max(lsum, rsum));
}
int Solution::maxPathSum(TreeNode* root) {
    int ans = -1000;
    maxSum(root, ans);
    return ans;
}

//-----------------7. Binary tree from inorder and postorder-----------------------

TreeNode* construct(vector<int> &in, vector<int> &post, int &rootIdx, int s, int e, unordered_map<int, int> &mp) {
    if (s > e) {
        return NULL;
    }
    int currRoot = post[rootIdx--];
    TreeNode* root = new TreeNode(currRoot);
    if (s == e) {
        return root;
    }
    root->right = construct(in, post, rootIdx, mp[currRoot] + 1, e, mp);
    root->left = construct(in, post, rootIdx, s, mp[currRoot] - 1, mp);
    return root;
}
TreeNode* Solution::buildTree(vector<int> &in, vector<int> &post) {
    int s = 0, e = in.size() - 1;
    unordered_map<int, int> mp;
    for (int i = 0; i <= e; i++) {
        mp[in[i]] = i;
    }
    return construct(in, post, e, 0, e, mp);
}

//----------------8. Populate next right pointers (perfect binary tree)--------------

void connect(TreeLinkNode *root) {
    TreeLinkNode* cur(root), *next;
    while (cur) {
        next = cur->left;
        while (cur) {
            if (cur->left) {
                cur->left->next = cur->right;
                cur->right->next = cur->next ? cur->next->left : NULL;
            }
            cur = cur->next;
        }
        cur = next;
    }
}

//---------------9. for non perfect binary tree-------------------------

TreeLinkNode* getNext(TreeLinkNode* curr) {
    curr = curr->next;
    while (curr) {
        if (curr->left) return curr->left;
        if (curr->right) return curr->right;
        curr = curr->next;
    }
    return nullptr;
}
void Solution::connect(TreeLinkNode* root) {
    if (!root) {
        return;
    }
    TreeLinkNode *curr, *next = root;
    while (next) {
        curr = next;
        while (curr) {
            if (curr->left) {
                curr->left->next = curr->right ? curr->right : getNext(curr);
            }
            if (curr->right) {
                curr->right->next = getNext(curr);
            }
            curr = curr->next;
        }
        if (next->left) next = next->left;
        else if (next->right) next = next->right;
        else next = getNext(next);
    }
    return;
}

//-------------------------10. Serialize and Deserialize a binary tree-----------------

void serialize(TreeNode* root, stringstream &str) {
    if (!root) {
        str << "# ";
    }
    else {
        str << root->val << " ";
        serialize(root->left, str);
        serialize(root->right, str);
    }
}
TreeNode* deserialize(stringstream &str) {
    string temp;
    str >> temp;
    if (temp == "#") {
        return nullptr;
    }
    TreeNode* root = new TreeNode(stoi(temp));
    root->left = deserialize(str);
    root->right = deserialize(str);
    return root;
}
public:

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    stringstream str;
    serialize(root, str);
    return str.str();
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    stringstream str(data);
    return deserialize(str);
}

//------------------11. Flatten binary tree to linked list-----------------

void flatten(TreeNode *root) {

    if (!root) return;

    TreeNode* node = root;
    while (node) {

        // Attatches the right sub-tree to the rightmost leaf of the left sub-tree:
        if (node->left) {

            TreeNode *rightMost = node->left;
            while (rightMost->right) {

                rightMost = rightMost->right;
            }
            rightMost->right = node->right;

            // Makes the left sub-tree to the right sub-tree:
            node->right = node->left;
            node->left = NULL;
        }

        // Flatten the rest of the tree:
        node = node->right;
    }
}
------------------using stack---------------------- -
TreeNode* Solution::flatten(TreeNode* root) {
    if (!root) {
        return NULL;
    }
    TreeNode* curr = root;
    stack<TreeNode*> stk;
    while (curr) {
        if (curr->right) {
            stk.push(curr->right);
        }
        curr->right = curr->left;
        curr->left = NULL;
        if (curr->right == NULL && !stk.empty()) {
            curr->right = stk.top();
            stk.pop();
        }
        curr = curr->right;
    }
    return root;
}


//-----------------12. Nodes at distance k------------------------

------------ -without using parent array------------------ -

class Solution {
    vector<int> ans;
public:
    void nodesAtLevelK(TreeNode* root, int k) {
        if (!root) {
            return;
        }
        if (k == 0) {
            ans.push_back(root->val);
        }
        nodesAtLevelK(root->left, k - 1);
        nodesAtLevelK(root->right, k - 1);
    }
    int nodesAtDistanceK(TreeNode *root, TreeNode *target, int k) {
        if (!root) {
            return -1;
        }
        if (root == target) {
            nodesAtLevelK(root, k);
            return 0;
        }
        int dl = nodesAtDistanceK(root->left, target, k);
        if (dl != -1) {
            if (dl + 1 == k) {
                ans.push_back(root->val);
            }
            else {
                nodesAtLevelK(root->right, k - 2 - dl);
            }
            return 1 + dl;
        }
        int dr = nodesAtDistanceK(root->right, target, k);
        if (dr != -1) {
            if (dr + 1 == k) {
                ans.push_back(root->val);
            }
            else {
                nodesAtLevelK(root->left, k - 2 - dr);
            }
            return 1 + dr;
        }
        return -1;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if (!root) {
            return ans;
        }
        nodesAtDistanceK(root, target, k);
        return ans;
    }

    ------------using parent------------------------

    unordered_map<TreeNode*, TreeNode*> par;
    void dfs(TreeNode* root, TreeNode* p)
    {
        if (!root) {
            return;
        }
        par[root] = p;
        if (root->left) {
            dfs(root->left, root);
        }
        if (root->right) {
            dfs(root->right, root);
        }
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> ans;
        dfs(root, root);
        unordered_map<TreeNode*, bool> mp;
        queue<pair<int, TreeNode*>> q;
        q.push({0, target});
        while (!q.empty())
        {
            auto f = q.front();
            int dist = f.first;
            TreeNode* node = f.second;
            q.pop();
            mp[node] = true;
            if (dist == K) {
                ans.push_back(node->val);
            }
            if (node->left && !mp[node->left]) {
                q.push({dist + 1, node->left});
            }
            if (node->right && !mp[node->right]) {
                q.push({dist + 1, node->right});
            }
            if (!mp[par[node]]) {
                q.push({dist + 1, par[node]});
            }
        }
        return ans;
    }
