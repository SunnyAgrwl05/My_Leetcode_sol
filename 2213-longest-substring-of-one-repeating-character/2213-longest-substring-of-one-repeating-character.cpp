class Solution {
public: // code written by sunny
    struct Node {
        int len, pref, suff, best;
        char left, right;

        Node() : len(0), pref(0), suff(0), best(0), left(0), right(0) {}

        Node(char c) {
            len = pref = suff = best = 1;
            left = right = c;
        }
    };

    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node res;

        res.len = a.len + b.len;
        res.left = a.left;
        res.right = b.right;

        res.pref = a.pref;
        if (a.pref == a.len && a.right == b.left)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.right == b.left)
            res.suff = b.len + a.suff;

        res.best = max(a.best, b.best);

        if (a.right == b.left)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int node, int l, int r, string &s) {
        if (l == r) {
            tree[node] = Node(s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        int n = s.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(
                1,
                0,
                n - 1,
                queryIndices[i],
                queryCharacters[i]
            );

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};