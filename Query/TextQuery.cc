#include "TextQuery.h"

namespace wd{
QueryResult::QueryResult(string word,shared_ptr<set<int>> wordLine,
                         shared_ptr<vector<string>>files)
    :_word(word)
     ,_wordLine(wordLine)
     ,_files(files)
{ 

}
void QueryResult::print()const{
    cout<<"queryword: "<<_word<<endl
        <<"total: "<<_wordLine->size();
    cout<<"---------------------------------"<<endl;
    for(auto &p:*_wordLine){
        cout<<"Line: "<<p<<" "<<(*_files)[p-1]<<endl;
    }
    cout<<"---------------------------------"<<endl;
}
TextQuery::TextQuery(ifstream&ifs)
    :_files(new vector<string>())
{
    string row,word;
    int n;
    while(getline(ifs,row)){
        _files->push_back(row);
        n=_files->size();

        istringstream iss(row);
        while(iss>>word){
            if(_wordLine.find(word)==_wordLine.end()){
                _wordLine[word]=std::make_shared<set<int>>();
            }
            _wordLine[word]->insert(n);
        }
    }
    
 }
QueryResult TextQuery::query(const string&word)const{
    auto p=_wordLine.find(word);
    static shared_ptr<set<int>> nodata=std::make_shared<set<int>>();
    if(p==_wordLine.end()){
        return QueryResult(word,nodata,_files);
    }
    else{
        return QueryResult(word,p->second,_files);
    }
}
}//end of namespace
