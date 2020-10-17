#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;

struct node {
  int ans = 0;
  int o = 0;
  int c = 0;
  node() { ans = o = c = 0; }
};
string s;
node tree[2 * N];
int n;
node merge(node x, node y) {
  node temp;
  int val = min(x.o, y.c);
  temp.ans = x.ans + y.ans + (2 * val);
  temp.o = x.o + y.o - val;
  temp.c = x.c + y.c - val;
  return temp;
}
void build(string s) {
  for (int i = 0; i < n; i++) {
    tree[i + n].ans = 0;
    tree[i + n].o = (s[i] == '(');
    tree[i + n].c = (s[i] == ')');
  }
  for (int i = n - 1; i > 0; i--) {
    tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }
}
int query(int l, int r) {
  node al, ar;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) al = merge(al, tree[l++]);
    if (r & 1) ar = merge(tree[--r], ar);
  }
  node a = merge(al, ar);
  return a.ans;
}

int main() {
  cin >> s;
  n = s.length();
  build(s);
  int t;
  cin >> t;
  while (t--) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    cout << query(l, r + 1) << endl;
  }
  return 0;
}
