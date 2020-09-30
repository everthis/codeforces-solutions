/*
Hurricane came to Berland and to suburbs Stringsvill. You are going to it to
check if it's all right with you favorite string. Hurrinace broke it a bit by
reversing some of its non-intersecting substrings. You have a photo of this
string before hurricane and you want to restore it to original state using
reversing minimum possible number of its substrings and find out which
substrings you should reverse.

You are given a string s — original state of your string and string t — state
of the string after hurricane. You should select k non-intersecting
substrings of t in such a way that after reverse of these substrings
string will be equal s and k is minimum possible.

Input
First line of input contains string s and second line contains string t.
Both strings have same length and consist of lowercase English
letters. 1 ≤ |s| = |t| ≤ 5·105

Output
In first line print k — minimum number of substrings you should reverse.
Next output k lines. Each line should contain two integers li, ri meaning
that you should reverse substring from symbol number li to symbol
ri (strings are 1-indexed). These substrings shouldn't intersect.
If there are multiple answers print any. If it's impossible to restore string output -1.
/**/

#include <bits/stdc++.h>
#define min(a, b) (a < b ? a : b)
using namespace std;
const int N = 1000050;
char a[N], b[N], s[N];
int tr[N][26], l[N], fa[N], f[N], ans[N], fr[N], anc[N], dif[N], tot = 1, las;
void add(int c, int n) {
  int v = las;
  while (s[n - l[v] - 1] != s[n]) v = fa[v];
  if (!tr[v][c]) {
    int u = fa[v], p = ++tot;
    l[p] = l[v] + 2;
    while (s[n - l[u] - 1] != s[n]) u = fa[u];
    fa[p] = tr[u][c], tr[v][c] = p;
    dif[p] = l[p] - l[fa[p]],
    anc[p] = dif[p] == dif[fa[p]] ? anc[fa[p]] : fa[p];
  }
  las = tr[v][c];
  return;
}
int main() {
  scanf("%s%s", a + 1, b + 1);
  int n = strlen(a + 1);
  for (int i = 1; i <= n; ++i) s[i * 2 - 1] = a[i], s[i * 2] = b[i];
  n <<= 1, s[0] = 'a' - 1, s[n + 1] = 'a' - 2;
  memset(ans, 100, sizeof(ans));
  fa[0] = 1, l[1] = -1, ans[0] = 0;
  for (int i = 1; i <= n; ++i) {
    add(s[i] - 'a', i);
    for (int k = las; k; k = anc[k]) {
      f[k] = i - l[anc[k]] - dif[k];
      if (anc[k] != fa[k] && ans[f[fa[k]]] < ans[f[k]]) f[k] = f[fa[k]];
      if (!(i & 1) && ans[i] > ans[f[k]] + 1)
        fr[i] = f[k], ans[i] = ans[f[k]] + 1;
    }
    if (s[i] == s[i - 1] && ans[i - 2] < ans[i])
      ans[i] = ans[i - 2], fr[i] = i - 2;
  }
  if (ans[n] <= n) {
    cout << ans[n] << endl;
    for (int i = n; i >= 1;) {
      if (fr[i] + 2 < i)
        printf("%d %d\n", fr[i] / 2 + 1, i / 2), i = fr[i];
      else
        i -= 2;
    }
  } else
    puts("-1");
  return 0;
}
