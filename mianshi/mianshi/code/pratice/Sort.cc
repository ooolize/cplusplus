#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Sort{
public:
    Sort(vector<int>&v)
    :v(v)
    {
        
    }
    void quicksort(int l,int r){
        if(l<r){
            int pivot=partition(l,r);
            quicksort(l,pivot-1);
            quicksort(pivot+1,r);
        }
    }
    int partition(int l,int r){
        int k=l;
        for(int i=0;i<r;++i){
            if(v[i]<v[r]){
                swap(v[i],v[k]);
                ++k;    
            }
        }
        swap(v[r-1],v[k]);
        return k;
    }
    void swap(int &a,int &b){
        int tmp=a;
        a=b;
        b=tmp;
    }
    void heapsort(int l,int len){
        for(int i=len/2;i>=0;--i){
            adjustheap(i,len);
        }
        swap(v[0],v[len-1]);
        for(int i=len-1;i>0;--i){
            adjustheap(0,i);
            swap(v[0],v[i-1]);
        }
    }
    void adjustheap(int pos,int len){
        int dad=pos;
        int son=dad*2+1;
        if(son+1<len&&v[son]<v[son+1])++son;
        while(son<len){
            if(v[dad]<v[son]){
                swap(v[dad],v[son]);
                dad=son;
                son=dad*2+1;
            }
            else break;
        }
    }
    void display()const{
        for(auto &p:v){
            cout<<p<<" ";
        }
        cout<<endl;
    }
    int size()const{return v.size();}
private:
    vector<int> v;
};
int main()
{
    vector<int> v={4,3,2};
    Sort s(v);
    
    s.display();
    /* s.quicksort(0,s.size()-1); */
    s.heapsort(0,s.size());
    s.display();
    return 0;
}

