// We have the condition here that we can visit a node any number of times but we shall add its value only once for that path for the calculation of its quality.
// A valid path in the graph is any path that starts at node 0, ends at node 0, and takes at most maxTime seconds to complete
using p=pair<int,int>;//{neigh,time}
class Solution {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n=values.size();
        int res=values[0];//starting w 0
        vector<vector<p>> adj(n);//{u:{v,wt}}
        for(auto e:edges){
            int u=e[0]; int v=e[1]; int wt=e[2];
            adj[u].push_back({v,wt});
            adj[v].push_back({u,wt});
        }
        vector<int> vis(n,0);//vis[i]=no of times node i has been vis;
        dfs(adj,values,vis,res,0,0,0,maxTime);
        return res;
    }
    void dfs(vector<vector<p>>&adj,vector<int>&values,vector<int>&vis,int &res,int node,int score,int time,int maxtime){
        //if time exceeds max allowed, stop exploring this path
        if(time>maxtime) return;
        if(!vis[node]){
            score+=values[node];
        }
        vis[node]++;//store the times v has been vis since we can visit a ndoe multiple times
        if(node==0){//update max score if at ndoe 0-valid path
            res=max(res,score);
        }
        for(auto&it:adj[node]){
            int neigh=it.first;
            int newtime=time+it.second;//time to get to neigh
            int newscore=score;
            if(vis[neigh]==0){//if 1s time visitng this neigh, add its val
                newscore+=values[neigh];
            }
            dfs(adj,values,vis,res,neigh,score,newtime,maxtime);
        }
        vis[node]--;//backtrack
    }
};