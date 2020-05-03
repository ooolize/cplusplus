### XML
> XML 被设计用来传输和存储数据。
XML 指可扩展标记语言（EXtensible Markup Language）。但它不进行实际的工作，只是用于前后端数据传输。
+ XML 标签没有被预定义。您需要自行定义标签。
### RSS
  RSS就是通过xml等格式的文件来定义的一种文件格式，并在服务器端和客户端形成一个协议，支持RSS的客户端，根据协议来解析RSS这个xml文件，然后列出xml文件中列出的文章列表，每一个文章有一个标题、简介和地址，支持RSS功能的客户端就可以将这个xml文件显示成了一个文章列表，可以直接在收藏夹栏里列出来，或者直接显示在网页里。而服务器端则要保证，提供的xml文件要根据协议的格式写，并且要将最新的文章信息写入到这个xml文件里，供客户端来读取，服务器端就提供一个RSS订阅的xml文件的地址，这个xml文件就是订阅RSS链接点击后下载的文件。
### 解析RSS文件
使用开源库tinyxml2解析XML文件，得到文章的title,link,descripet,content
```
#include "tinyxml2.h"
#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
using namespace::tinyxml2;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

struct RssItem{
    string title;
    string link;
    string description;
    string content;
};
class RssReader{
public:
    RssReader()
    {

    }
    void parseRss(const string&filename);//解析xml
    void dump(const string& filename);//写入新文件
private:
    vector<RssItem> _rss;
};
void RssReader::parseRss(const string&filename){
    XMLDocument doc;
    doc.LoadFile(filename.c_str());//加载文件
    if(doc.ErrorID()){
        cout<<"XMLDocument load file error!"<<endl;
        return;
    }
    XMLElement* itemNode=doc.FirstChildElement("rss")//获取第一个item
        ->FirstChildElement("channel")->FirstChildElement("item");
    do{
        RssItem item;
        XMLElement* titleNode=itemNode->FirstChildElement("title"); //获取title
        item.title=titleNode->GetText();
        /* cout<<titleText<<endl; */
        XMLElement* linkNode=itemNode->FirstChildElement("link");//获取link
        item.link=linkNode->GetText();
        
        XMLElement* descriptionNode=itemNode->FirstChildElement("description");
        item.description=descriptionNode->GetText();
        /* cout<<linkText<<endl; */
        XMLElement* contentNode=itemNode->FirstChildElement("content:encoded");
        const char* content=contentNode->GetText();
        /* cout<<contenTExt<<endl; */

        std::regex re("<.+?>");
        item.content=std::regex_replace(content,re,"");
        _rss.push_back(item);
    }while((itemNode=itemNode->NextSiblingElement("item")));
}
void RssReader::dump(const string&filename){
    ofstream ofs(filename);
    int i=0;
    for(auto &p:_rss){
        ofs<<"<doc>"<<endl
           <<"  <docid>"<<++i<<"</docid> "<<endl;
            
        ofs<<"  <title>"<<p.title<<"</title>"<<endl
            <<"  <link>"<<p.link<<"</link>"<<endl
            <<"  <description>"<<p.description<<"</description>"<<endl
            <<"  <content>"<<p.content<<"</content>"<<endl;    
        ofs<<"</doc>"<<endl;
    }
}

int main(int argc,char**argv)
{
    RssReader RR;
    RR.parseRss(argv[1]);
    RR.dump(argv[2]);
    return 0;
}
```
### Todo
+ 正则表达式regex
