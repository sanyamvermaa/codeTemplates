class DisjointSet{
    private:
        vector<int> parent;
        vector<int> size;

    public:
        DisjointSet(int n){
            parent.resize(n);
            for(int i=0;i<n;i++) parent[i]=i;
            size.resize(n,1);
        }

        int findUpar(int u){
            if(parent[u]==u) return u;
            return parent[u] = findUpar(parent[u]);
        }

        void unionBySize(int u , int v){
            int pv = findUpar(v);
            int pu = findUpar(u);

            if(pv==pu) return ;

            else if(size[pv]<size[pu]){
                parent[pv] = pu;
                size[pu]+=size[pv];
            }
            else{
                parent[pu] = pv;
                size[pv]+=size[pu];
            }
        }

};
