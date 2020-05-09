#include "TextQuery.h"
#include <memory>
#include <algorithm>
using std::shared_ptr;
using namespace::wd;

class QueryBase{
    friend class Query;
private:
    virtual QueryResult eval(const TextQuery&t)const=0;
    virtual string rep()const=0;
};
class WordQuery
:public QueryBase
{
    friend class Query;
    //能不能放到共有呢
private:
    WordQuery(const string&word)
        :_word(word)
    {

    }
    QueryResult eval(const TextQuery&t)const{return t.query(_word);}
    string rep()const{return _word;}
    string _word;
};
class Query
{   
    friend Query operator~(const Query&q);
    friend Query operator&(const Query&lsh,const Query&rhs);
    friend Query operator|(const Query&lhs,const Query&rhs);
public:
    Query(const string& s) 
    :_q(new WordQuery(s))
    {

    }
    QueryResult eval(const TextQuery&t)const{return _q->eval(t);} 
    string rep()const{return _q->rep();}
private:
    Query(shared_ptr<QueryBase>q):_q(q){}//不能加引用!!
    shared_ptr<QueryBase> _q;
};

class NotQuery
:public QueryBase
{   
    friend Query operator~(const Query&);
public:
    NotQuery(const Query&q)
        :_q(q)
    {

    }
private:
    QueryResult eval(const TextQuery&t)const;
    string rep()const{return "~("+_q.rep()+")";}
    Query _q;
};
Query operator~(const Query&q){
    return shared_ptr<QueryBase>(new NotQuery(q));
}
QueryResult NotQuery::eval(const TextQuery&t)const{
    auto notEle=_q.eval(t);
    shared_ptr<set<int>> p(new set<int>());
    int n=notEle.getFile()->size(),pred=1;
    for(auto iter=notEle.begin();iter!=notEle.end();iter++){
        for(int i=pred;i<*iter;i++){
            p->insert(i);
        }
        pred=*iter+1;
    }
    for(int i=pred;i<=n;i++){
        p->insert(i);
    }

    return QueryResult(rep(),p,notEle.getFile());
}
class BinaryQuery
:public QueryBase
{
protected:
    BinaryQuery(const Query&lhs,const Query&rhs,const string&ope)
        :_lhs(lhs)
         ,_rhs(rhs)
         ,_operation(ope)
    {

    }
    Query _lhs,_rhs;
    string _operation;
    /* private: */
    string rep()const{
        return  "("+_lhs.rep()+")"
            +_operation+
            "("+_rhs.rep()+")";
    }
};
class AndQuery
:public BinaryQuery
{
    friend Query operator&(const Query&lhs,const Query&rhs);
private:
    AndQuery(const Query&lhs,const Query&rhs)
        :BinaryQuery(lhs,rhs,"&")
    {

    }
    QueryResult eval(const TextQuery&)const;
};
Query operator&(const Query&lhs,const Query&rhs){
    return shared_ptr<QueryBase>(new AndQuery(lhs,rhs));
}
QueryResult AndQuery::eval(const TextQuery&t)const{
    auto left=_lhs.eval(t),right=_rhs.eval(t);
    /* cout<<"AndQuery::eval(const TextQuery&t)"<<endl; */
    shared_ptr<set<int>> p(new set<int>());
    //插入器第一元素是容器，第二个元素是插入的位置
    set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*p,p->begin())) ;
    return QueryResult(rep(),p,left.getFile());
    /* return QueryResult("",nullptr,nullptr); */
}
class OrQuery
:public BinaryQuery
{
    friend Query operator|(const Query&lhs,const Query&rhs);
private:
    OrQuery(const Query&lhs,const Query&rhs)
        :BinaryQuery(lhs,rhs,"|")
    {

    }
    QueryResult eval(const TextQuery&)const;
};
Query operator|(const Query&lhs,const Query&rhs){
    return shared_ptr<QueryBase>(new OrQuery(lhs,rhs));
}
QueryResult OrQuery::eval(const TextQuery&t)const{
    auto left=_lhs.eval(t),right=_rhs.eval(t);
    shared_ptr<set<int>> p(new set<int>());
    //插入器第一元素是容器，第二个元素是插入的位置
    set_union(left.begin(),left.end(),right.begin(),right.end(),inserter(*p,p->begin())); 
    return QueryResult(rep(),p,left.getFile());
    /* auto left=_lhs.eval(t),right=_rhs.eval(t); */
    /* shared_ptr<set<int>> p(new set<int>(left.begin(),left.end())); */
    /* /1* set<int> tmp(left.begin(),left.end()); *1/ */
    /* for(auto iter=right.begin();iter!=right.end();iter++){ */
    /*     p->insert(*iter); */
    /* } */
    /* return QueryResult(rep(),p,left.getFile()); */
}

int main(int argc,char** argv){
    ifstream ifs(argv[1]);
    TextQuery text(ifs);

    Query q1(argv[2]),q2(argv[3]),q3(argv[4]);
    Query q4=q1&q2&q3;
    QueryResult ans=q4.eval(text);
    ans.print();
}
