#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#define vvi vector<vector<int>>

vector<int> manacher (string &s){   //manacher Algorithm O(n) to find the longest palindromic substring
      string t;
      int x=s.size();
      for(int i=0;i<x;i++){
        t+="#";
        t+=s[i];
      }
      t+="#"; 
      t= "$"+t+"^";
      int n=t.size();
      vector<int> dp(n); 
      int centre=1; 
      int right=1;
      for(int i=1;i<=n-2;i++){ 
            int mirror= (centre)-(i-centre) ;    
            dp[i]=max(0ll,min(right-i,dp[mirror]));
            while(t[i+dp[i]]==t[i-dp[i]]){
            dp[i]++;
            }
            if(i+dp[i]>right){ 
            centre=i;
            right=i+dp[i];
            }
      }
      return vector<int>(begin(dp)+1,end(dp)-1); 
}

 vector<int>lpf(200006,0); //lpf means least prime factor for each  number seems like its needed for optimisation
 vector<int>primes(200006,1);
 void init(){
        //first find the sieve to get which are primes
        primes[0]=0;
        primes[1]=0;
        for(int i=2;i*i<=200005;i++){
            if(primes[i]){
                for(int j=i*i;j<=200005;j+=i){
                    if(primes[j]){
                        primes[j]=0;
                        lpf[j]=i;
                    }
                }
            }
        }
        //for the primes we will have lpf as the number itself
        for(int i=2;i<=200005;i++){
            if(primes[i]){
                lpf[i]=i;
            }
        }
 }



int setBit (int n, int bitpos){ //from 1 to n how many have "bitpos" set  
//formula derived from just pattern noticing for each bit periodicity like for 2nd bit (0 based), the pattern repeats after every 8 numbers from there i got the formula of for ith bit = (2^(i))*(n/(2^(i+1)))+max(0,n%(2^(i+1))-2^(i)+1)   
    if(n==0ll){
        return 0ll;
    }
    int x=(n/(1ll<<(bitpos+1ll)));
    int y=max(0ll,(n%(1ll<<(bitpos+1ll)))-(1ll<<(bitpos))+1ll);
    x*=(1ll<<bitpos);
    return x+y;
}

vvi lcsubsequence( string &s,string &t){
    int n=s.size();
    int m=t.size();
    vvi dp(n+1,vi(m+1,0));
    //dp[i][j] denotes the longest common subsequence comsidering from 1 to ith character of s and considering from 1 to jth character of t
    //transition : dp[i][j]=dp[i-1][j-1]+1 if s[i]==t[j] else dp[i][j]=max(dp[i-1][j],dp[i][j-1])
    //base case : dp[0][j]=0 and dp[i][0]=0
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1]==t[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }else{
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    return dp;
}
vvi lcsubstring(string &s, string &t){
    int n=s.size();
    int m=t.size();
    vvi dp(n+1,vi(m+1,0));
    //dp[i][j] denotes the longest common substring ending at ith character of s and jth character of t
    //transition : dp[i][j]=dp[i-1][j-1]+1 if s[i]==t[j] else dp[i][j]=0
    //base case : dp[0][j]=0 and dp[i][0]=0
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1]==t[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }else{
                dp[i][j]=0;
            }
            ans=max(ans,dp[i][j]);
        }
    }
    return dp;
}
vvi lsubstringsubsequence(string &s, string &t){//(longest substring in t which is a subsequence in a)
        int n=s.size();
        int m=t.size();
        vvi dp(n+1,vi(m+1,0));
        //we need to find the longest subsequence in p which is a substring in q
          //let dp[i][j] ddenotes the answer ending at jth character of q and comsidering string from 1 to ith character of p
          //transition : dp[i][j]=dp[i-1][j-1]+1 if p[i]==q[j] else dp[i][j]=dp[i-1][j]
            //base case : dp[0][j]=0 and dp[i][0]=0 
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s[i-1]==t[j-1]){
                    dp[i][j]=dp[i-1][j-1]+1;
                }else{
                    dp[i][j]=dp[i-1][j];
                }
            }
        }
        return dp;
}


