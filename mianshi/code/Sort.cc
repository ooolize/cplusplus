#include <iostream>
#include <vector>
#define SWAP(a,b){int c=a;a=b;b=c;}
using namespace::std;
class Sort{
public:
    Sort(vector<int>& _v)
    :v(_v)
    {

    }
    void swap(int& a,int &b){
        int tmp=a;
        a=b;
        b=tmp;
        /* 不能使用 因为对自己不能成功交换 */
        /* a=a^b; */
        /* b=a^b; */
        /* a=a^b; */
    }
    int partition(int l,int r){
        int k=l;
        for(int i=l;i<r;++i){
            if(v[i]<v[r]){
                SWAP(v[k],v[i]);
                ++k;
            }
        }
        SWAP(v[k],v[r]);
        return k;
    }
    void quicksort(int l,int r){
        if(l<r){
            int piovt=partition(l,r);
            quicksort(l,piovt-1);
            quicksort(piovt+1,r);
        }
    }
    void adjustheap(int pos,int len){
        int dad=pos;
        int son=pos*2+1;
        if(son+1<len&&v[son]<v[son+1])++son;
        while(son<len){
            if(v[son]>v[dad]){
                swap(v[son],v[dad]);
                dad=son;
                son=dad*2+1;
            }
            else break;
        }
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
    
    int size(){return v.size();}
    void display(){
        for(auto p:v)
            cout<<p<<" ";
        cout<<endl;
    }
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

