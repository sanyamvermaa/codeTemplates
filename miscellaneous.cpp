
============================================================
CHECKING PALLINDROMES EFFICIENTLY 
============================================================
int expand(int i, int j, int& cnt, string& s){
        int n = s.length();
        while(i>=0 && j<n && s[i]==s[j]){
            cnt++;
            i--;
            j++;
        }
        return cnt;
    }

int countSubstrings(string s) {
        int n = s.length();
        int cnt = 0;

        for(int i=0;i<n;i++){
            expand(i,i,cnt,s);    // FOR ODD LENGTH PALI
            expand(i,i+1,cnt,s);  // FOR EVEN LENGTH PALI
        }
        return cnt;
    }


PALLINDROMIC DP
vector<vector<bool>> palindromeDP(string& s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++)
        dp[i][i] = true;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = (s[i] == s[j]) && (len == 2 || dp[i + 1][j - 1]);
        }
    }

    return dp;
}


