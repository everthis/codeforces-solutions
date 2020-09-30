/*  
You are given a string 𝑠 consisting of lowercase Latin letters
"a", "b" and "c" and question marks "?".

Let the number of question marks in the string 𝑠 be 𝑘. Let's replace each
question mark with one of the letters "a", "b" and "c". Here we can obtain
all 3𝑘 possible strings consisting only of letters "a", "b" and "c".
For example, if 𝑠="ac?b?c" then we can obtain the following strings:
["acabac", "acabbc", "acabcc", "acbbac", "acbbbc", "acbbcc",
"accbac", "accbbc", "accbcc"].

Your task is to count the total number of subsequences "abc" in all resulting
strings. Since the answer can be very large, print it modulo 109+7.

A subsequence of the string 𝑡 is such a sequence that can be derived from the
string 𝑡 after removing some (possibly, zero) number of letters without
changing the order of remaining letters. For example, the string "baacbc"
contains two subsequences "abc" — a subsequence consisting of letters at
positions (2,5,6) and a subsequence consisting of letters at positions (3,5,6).

Input
The first line of the input contains one integer 𝑛 (3≤𝑛≤200000) — the
length of 𝑠.

The second line of the input contains the string 𝑠 of length 𝑛 consisting
of lowercase Latin letters "a", "b" and "c" and question marks"?".

Output
Print the total number of subsequences "abc" in all strings you can obtain
if you replace all question marks with letters "a", "b" and "c", modulo 109+7.
/**/

#include <bits/stdc++.h>

using namespace std;

const int MOD = int(1e9) + 7;
const int N = 200043;
const int K = 4;

int add(int x, int y) {
  x += y;
  while (x >= MOD) x -= MOD;
  while (x < 0) x += MOD;
  return x;
}

int mul(int x, int y) { return (x * 1ll * y) % MOD; }

int n;
string s;
int dp[N][K][K];
char buf[N];
int pow3[N];

int main() {
  scanf("%d", &n);
  scanf("%s", buf);
  s = buf;
  int cntQ = 0;
  for (auto c : s)
    if (c == '?') cntQ++;
  pow3[0] = 1;
  for (int i = 1; i < N; i++) pow3[i] = mul(pow3[i - 1], 3);
  dp[0][0][0] = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= 3; j++)
      for (int k = 0; k <= 3; k++) {
        if (!dp[i][j][k]) continue;
        dp[i + 1][j][k] = add(dp[i + 1][j][k], dp[i][j][k]);
        if (j < 3 && (s[i] == '?' || s[i] - 'a' == j)) {
          int nk = (s[i] == '?' ? k + 1 : k);
          dp[i + 1][j + 1][nk] = add(dp[i + 1][j + 1][nk], dp[i][j][k]);
        }
      }
  int ans = 0;
  for (int i = 0; i <= 3; i++)
    if (cntQ >= i) ans = add(ans, mul(dp[n][3][i], pow3[cntQ - i]));
  printf("%d\n", ans);
}

// another

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
  int n;
  string s;
  cin >> n >> s;
  int a = 0, ab = 0, abc = 0, m = 1; // m is total number of different strings so far.
  for (char c : s) {
    if (c == 'a') {
      a = (a + m) % mod;
    } else if (c == 'b') {
      ab = (ab + a) % mod;
    } else if (c == 'c') {
      abc = (abc + ab) % mod;
    } else {  // '?'
      abc = (3ll * abc + ab) % mod;
      ab = (3ll * ab + a) % mod;
      a = (3ll * a + m) % mod;
      m = (3ll * m) % mod;
    }
  }
  cout << abc << endl;
  return 0;
}
