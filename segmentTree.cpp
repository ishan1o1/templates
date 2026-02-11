class SGTree{
  vector<int> seg;
  public:
  SGTree(int n){
    seg.resize(4*n+1);
  }
void build(int ind,int low,int high,vector<int>& arr){
    if(low==high){
        seg[ind] = arr[low];
        return;
    }
    int mid = (low+high)/2;
    build(2*ind+1,low,mid,arr);
    build(2*ind+2,mid+1,high,arr);
    seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);
}

int query(int ind,int low,int high,int l,int r){
    //check no overlap
    if(r<low||l>high) return INT_MAX;
    //complete overlap
    if(l<=low&&r>=high) return seg[ind];
    //partial overlap
    int mid=(low+high)>>1;
    return min(query(2*ind+1,low,mid,l,r),query(2*ind+2,mid+1,high,l,r));
}
void update(int ind,int low,int high,int i,int val){
  if(low==high){
    seg[ind]=val;
    return;
  }
  int mid = (low+high)>>1;
  if(i<=mid) update(2*ind+1,low,mid,i,val);
  else update(2*ind+2,mid+1,high,i,val);
  seg[ind] = min(seg[ind*2+1],seg[2*ind+2]);
}
};