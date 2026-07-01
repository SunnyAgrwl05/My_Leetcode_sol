class Solution {
public: // code written by sunny
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        // ---------- STEP 1: Multi-source BFS ----------
        // dist[r][c] = us cell ki sabse nazdeek thief se Manhattan distance
        // -1 matlab abhi tak visit nahi hua
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int,int>> q;

        // Saare thieves ek saath queue mein daalo (distance 0 se start)
        // Yehi "multi-source" wala trick hai — isse O(n^2) mein hi
        // sabhi cells ki nearest-thief-distance mil jaati hai
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(grid[i][j]==1){ 
                    dist[i][j]=0; 
                    q.push({i,j}); 
                }

        // 4 directions: right, left, down, up
        int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};

        // Normal BFS — jo bhi cell pehli baar reach hoga,
        // uski distance guaranteed shortest hogi (BFS property)
        while(!q.empty()){
            auto [x,y]=q.front(); q.pop();
            for(int d=0;d<4;d++){
                int nx=x+dx[d], ny=y+dy[d];
                // boundary check + already visited check
                if(nx>=0&&nx<n&&ny>=0&&ny<n&&dist[nx][ny]==-1){
                    dist[nx][ny]=dist[x][y]+1;  // parent se +1 distance
                    q.push({nx,ny});
                }
            }
        }
        // Ab dist[][] grid ready hai — har cell ki "safety value" pata hai

        // ---------- STEP 2: Modified Dijkstra (max-heap) ----------
        // safe[r][c] = (0,0) se (r,c) tak jitne bhi paths ho sakte hain,
        // unme se best path ka "minimum dist value" (bottleneck)
        vector<vector<int>> safe(n, vector<int>(n, -1));

        // Max-heap: hamesha sabse zyada "safeness" wala cell pehle pop hoga
        // pair = {current path ka safeness so far, cell ka encoded index}
        priority_queue<pair<int,int>> pq;

        pq.push({dist[0][0], 0});   // start cell (0,0), index 0 = 0*n+0
        safe[0][0]=dist[0][0];      // starting safety = us cell ki khud ki dist value

        while(!pq.empty()){
            auto [s, code] = pq.top(); pq.pop();
            int x=code/n, y=code%n;   // decode karke row, col nikala

            // Agar yeh entry stale hai (better value already mil chuki hai)
            // toh skip karo — standard Dijkstra optimization
            if(s < safe[x][y]) continue;

            // Destination mil gaya — yehi answer hai (max-heap se sabse
            // pehle destination jo pop hoga wahi optimal hoga)
            if(x==n-1 && y==n-1) return s;

            // 4 neighbors explore karo
            for(int d=0;d<4;d++){
                int nx=x+dx[d], ny=y+dy[d];
                if(nx>=0&&nx<n&&ny>=0&&ny<n){
                    // Path ka naya safeness = purane path ka min aur 
                    // is naye cell ki dist value, dono ka minimum
                    // (kyunki path ki safety uske sabse weak/risky point se decide hoti hai)
                    int ns = min(s, dist[nx][ny]);

                    // Agar yeh naya raasta us neighbor tak pehle se better hai
                    // (zyada safe hai), tabhi update karo aur pq mein daalo
                    if(ns > safe[nx][ny]){
                        safe[nx][ny]=ns;
                        pq.push({ns, nx*n+ny});
                    }
                }
            }
        }
        // Agar loop khatam ho gaya (edge case), toh jo bhi compute hua wahi return
        return safe[n-1][n-1];
    }
};