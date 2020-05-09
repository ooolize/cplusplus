#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__ 

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
using std::string;
using std::istringstream;
using std::cout;
using std::endl;
using std::map;
using std::fstream;
using std::vector;
using std::set;
using std::shared_ptr;
using std::ifstream;

namespace wd{
class QueryResult{
public:
    QueryResult(string ,shared_ptr<set<int>>,
                shared_ptr<vector<string>>);
    void print()const;
    shared_ptr<vector<string>> getFile()const{return _files;}
    set<int>::iterator begin()const {return _wordLine->begin();}
    set<int>::iterator end()const {return _wordLine->end();}

private:
    string _word;
    shared_ptr<set<int>> _wordLine;
    shared_ptr<vector<string>> _files;
};
class TextQuery
{
public:
    TextQuery(ifstream&);
    QueryResult query(const string& word)const;
    ~TextQuery() {}
    
private:
    shared_ptr<vector<string>> _files;
    map<string,shared_ptr<set<int>>> _wordLine;
};
}//end of namespace
#endif
