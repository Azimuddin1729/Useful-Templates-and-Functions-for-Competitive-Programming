#include<bits/stdc++.h>
using namespace std;
#define int long long

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


