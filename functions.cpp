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


struct trie{
    trie* child[26];
    int cnt;
    trie(){
        for(int i=0;i<26;i++){
            child[i]=NULL;
        }
        cnt=0;
    }
};
void insert(trie* root, string &s){
    trie* temp=root;
    for(int i=0;i<s.size();i++){
        int x=s[i]-'a';
        if(temp->child[x]==NULL){
            temp->child[x]=new trie();
        }
        temp=temp->child[x];
        temp->cnt++;
    }
}
int search(trie* root, string &s){
    trie* temp=root;
    for(int i=0;i<s.size();i++){
        int x=s[i]-'a';
        if(temp->child[x]==NULL){
            return 0;
        }
        temp=temp->child[x];
    }
    return temp->cnt;
}
void erase(trie* root, string &s){
    trie* temp=root;
    for(int i=0;i<s.size();i++){
        int x=s[i]-'a';
        if(temp->child[x]==NULL){
            return;
        }
        temp=temp->child[x];
        temp->cnt--;
    }
}



int kruskals(vvp &adj,vector<pair<int,pair<int,int>>>&spanningpath,int size){//edge based approach   
   //TC: //O(ElogE+V^2)==O(ElogV+V^2) as E<=V^2
     int n=size;
    //with union find to detect cycles
    vi index(n,0);// index[i] indicates the tree to which this vertex belongs 
    //sort the edges first part ElogE time which is ElogV too
    for(int i=0;i<n;i++){
        index[i]=i;//initially all are itself small tree with one node
    }
    int sum=0;
    vector<pair<int,pair<int,int>>>edges;
    for(int i=0;i<adj.size();i++){    //E
    for(auto j:adj[i]){
        edges.push_back({j.second,{i,j.first}});
    }
    } // this contains (a,b),(b,a)(undirected graph) both pairs we can avoid that from start without using the adjacent list 
    sort(edges.begin(),edges.end()); //ElogV
    for(int i=0;i<edges.size();i++){ //asymptotic complexity be  V^2 as thus loop overall for n-1 connections there the merging will take place with O(V)complexity
    // n-1 times among the edges.size() there will this if condition becomes valid 
    // so this loop executes like E+(V-1)*V=E+V^2==O(V^2)
        int from=edges[i].second.first;
        int to=edges[i].second.second;
        int weight=edges[i].first;
        if(index[from]!=index[to]){//belong to different trees
            sum+=weight;
            spanningpath.push_back(edges[i]);
        }
        int old=index[from];
        int nw=index[to];
        for(int i=0;i<n;i++){
           if(index[i]==old){
            index[i]=nw;
           }
        }
    }
    return sum;
}


int prims(vvp &adj,vi &visited){ //vertex based approach
       //O(ElogV) a solution for sparse graphs as E<<V^2 but for dense this becomes V^2logV
       //actually its ElogV +VlogV=ElogV
       int sum=0;
       int n=visited.size();
       vi cuts(n,INT_MAX);
       vi incomingv(n,-1);
       set<pair<int,pair<int,int>>> edges;
       for(auto i:adj[0]){
        edges.insert({i.second,{0,i.first}});
        cuts[i.first]=i.second;
        incomingv[i.first]=0;
       }
       visited[0]=1;
       for(int i=0;i<n-1;i++){
          if(edges.empty()){
            cout<<"No MCST"<<endl;
            return -1;
          }
          else{
             auto it=edges.begin(); //O(log V)operation at max only V can reside in this set 
             int from =it->second.first;
             int to=it->second.second;
             int weight=it->first;
             visited[to]=1;
             sum+=weight;
             cout<<from+1<<" "<<to+1<<endl;
             edges.erase(edges.begin());
             //contains the minimum edge value at beginning in the
             // set take it
             //update part
             for(auto i:adj[to]){
                if(!visited[i.first]&&cuts[i.first]>i.second){
                    edges.erase({cuts[i.first],{incomingv[i.first],i.first}});
                    cuts[i.first]=i.second;
                    incomingv[i.first]=to;
                    edges.insert({cuts[i.first],{to,i.first}});

                }
             }
          }
       }
       return sum;
} 

void dijkstra(vvp &adj,vi &dis,vi &visit,int start,vi &path){ //TC: O(V^2+E) by implementation using priority queue it can be improved also their exits one algo where TC is O(E) only in cp-algorithms site
    int n=visit.size();
    
    for(int i=0;i<n;i++){ // all the vertices are visited starting with least dis[x] and then its made to be not used later by marking it
        int mini=INT_MAX;
        int pos=-1;
        for(int j=0;j<n;j++){
            if(mini>dis[j]&&visit[j]==0){
                 mini=dis[j];
                 pos=j;
            }
        }
        if(mini==INT_MAX){ //break as there is no distance which is less than infinity given initially to all vertices
            break;
        }
        visit[pos]=1;//else mark it visited and now we do the relaxations

        for(auto j:adj[pos]){ //do the relaxations for the unvisited vertex
        //    if(visit[j.first]==1){
        //      continue;
        //    }
            int to =j.first;
            int weight =j.second;
            if(dis[pos]+weight<dis[to]){
                path[to]=pos; //path[v] is the penultimate vertex in the shortest path from  start to v;
            }
            dis[to]=min(dis[pos]+weight,dis[to]);//relaxations performed
        }
    }
    
}
void restore_path(int start, int end,vi &path){//zero based indexing 
    vi temp;
       if(path[end]==-1){
        cout<<"No path"<<endl;
        return;
       }
       for(int i=end;i!=start;i=path[i]){
           temp.push_back(i);
       }
       temp.push_back(start);
       for(int i=temp.size()-1;i>=0;i--){
          cout<<temp[i]+1<<"->";
       }
       cout<<"Null"<<endl;
       return;
} 

void modifieddijkstra(vvp &adj,vvi &dis,vvi &visit,int k){ //for two state transition 
    int n=visit.size();
    
    for(int i=0;i<n*k+2*n;i++){

        int mini=INT_MAX;
        pair<int,int> pos={-1,-1};
    for(int i=0;i<n;i++){ //
      
        for(int j=0;j<k+1;j++){//should be k+1 instead of k+2 as pos.secod+1 then might get run time error
            if(dis[i][j]<mini&&visit[i][j]==0){
                mini=dis[i][j];
                pos={i,j};
            }
        }
    }
    if(mini==INT_MAX){
        return;
    }
    // cout<<pos.first<<" "<<pos.second<<endl;
    visit[pos.first][pos.second]=1;
    for(auto i:adj[pos.first]){//u,steps->v,steps+1 v =adj(u)
        if(dis[i.first][pos.second+1]>dis[pos.first][pos.second]+i.second){
            dis[i.first][pos.second+1]=dis[pos.first][pos.second]+i.second;
            // pathtotalverticesneededtoreachvertexi[i.first]=pathtotalverticesneededtoreachvertexi[pos.first]+1;
        }
    }
    }
    return;
}