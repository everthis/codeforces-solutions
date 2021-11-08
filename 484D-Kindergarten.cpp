#include <bits/stdc++.h>
using namespace std;
#define abs(x) ((x >= 0) ? (x) : -(x))
typedef long long int LL;

const int N = 1e6 + 7;
LL a[N], dp[N];

int main() {
  int n;
  scanf("%d", &n);
  dp[0] = 0ll;
  for (int i = 1; i <= n; i++) {
    scanf("%I64d", &a[i]);
    dp[i] = 0ll;
  }
  int pre = 1;
  for (int i = 2; i <= n; i++) {
    dp[i] =
        max(dp[pre - 1] + abs(a[i] - a[pre]), dp[pre] + abs(a[i] - a[pre + 1]));
    if (a[i - 1] <= a[i] && a[i] >= a[i + 1]) pre = i;
    if (a[i - 1] >= a[i] && a[i] <= a[i + 1]) pre = i;
  }
  printf("%I64d\n", dp[n]);
  return 0;
}
