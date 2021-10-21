#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include "html.h"
using namespace HTML;

//implementation of the six functions

/* for reference when implementing
tag members
    string tag;
    unordered_map<string, string> attributes;
    vector<Contents*> contents;
*/
//tag contructor
//Tag(const string& str, const unordered_map<string, string>& map, const vector<Contents*>& vec);
Tag* Tag::makeTag(const string& tag, const unordered_map<string, string>& attr, const vector<Contents*>& contents){
  string tg = tag;

  if(tg.compare("style") == 0 || tg.compare("script") == 0 || tg.compare("head") == 0){
    //invisible tag
    InvisibleTag *ret = new InvisibleTag(tag, attr, contents);
    return ret;

  }else if(tg.compare("br") == 0 || tg.compare("hr") == 0){
    //line brake
    LineBreak *ret = new LineBreak(tag, attr, contents);
    return ret;

  }else if(tg.compare("p") == 0 || tg.compare("h1") == 0 || tg.compare("h2") == 0 || tg.compare("h3") == 0 ||
  tg.compare("h4") == 0 || tg.compare("h5") == 0 || tg.compare("h6") == 0 || tg.compare("div") == 0){
    //paragraph
    Paragraph *ret = new Paragraph(tag, attr, contents);
    return ret;

  }else if(tg.compare("img") == 0){
    //image
    Image *ret = new Image(tag, attr, contents);
    return ret;

  }else if(tg.compare("ul") == 0){
    //unorderedlist
    UnorderedList *ret = new UnorderedList(tag, attr, contents);
    return ret;

  }else if(tg.compare("ol") == 0){
    //orderedlist
    OrderedList *ret = new OrderedList(tag, attr, contents);
    return ret;

  }else if(tg.compare("table") == 0){
    //table
    Table *ret = new Table(tag, attr, contents);
    return ret;

  }else if(tg.compare("tr") == 0){
    //tablerow
    TableRow *ret = new TableRow(tag, attr, contents);
    return ret;

  }else if(tg.compare("td") == 0 || tg.compare("th") == 0){
    //tablecolumn
    TableColumn *ret = new TableColumn(tag, attr, contents);
    return ret;

  }else{
    //tag - emty tag?
    Tag *ret = new Tag(tag, attr, contents);
    return ret;
  }

}

//unordered_map<string, string> attributes;
string Tag::getLinkTarget() const{
auto it = this->attributes.find("href");

  if(it == this->attributes.end())
    return "";
  else
    return it->second;
}

//tag representing a paragraph.  Displays a newline ('\n') before and after its contents
void Paragraph::display(ostream& out, vector<const Tag*>& links) const{
  if (getLinkTarget() != "")
    links.push_back(this);

  out << '\n'; // new line before and after printing the contents
  for (Contents* c : contents){
    c->display(out, links);
  }
  out << '\n';
  
}
//UnorderedList: tag representing a bulleted list.  Starts by outputting a newline ('\n'), 
//then iterates through its contents, displaying the string " * " in front and a '\n' after 
//everything it contains
void UnorderedList::display(ostream& out, vector<const Tag*>& links) const{
  if (getLinkTarget() != "")
    links.push_back(this);

  out << '\n';
  int count = 0;
  int flag = contents.size();  
  for (Contents* c : contents){
    out << " * ";
    c->display(out, links);
    count++;

    if(count < flag)
      out << '\n'; 
  }

  out << '\n';
}

//distance(v.begin(),it)
//OrderedList.  tag representing a numbered list.  Starts by outputting a newline ('\n'),
// then iterates through its contents, displaying "#. " before and '\n' after everything 
//it contains, where # should 1 for the first element of contents, 2 for 
//the second, etc. ("1. ", "2. ", "3. ", etc.)
void OrderedList::display(ostream& out, vector<const Tag*>& links) const{
  if (getLinkTarget() != "")
    links.push_back(this);

  int index = 1;
  for (Contents* c : contents){
    out << index++ << ". ";
    c->display(out, links);
    out << '\n'; 
  }
  
}

//Image: tag that displays text based on its "alt" attribute, or "(Image)"
// if the alt attribute is not defined. Any contents of the tag should appear afterwards.
void Image::display(ostream& out, vector<const Tag*>& links) const{
  if (getLinkTarget() != "")
    links.push_back(this);
    
  auto it = this->attributes.find("alt");
  if(it == this->attributes.end())
    out << "(Image)";
  else
    out << it->second;  
  for (Contents* c : contents)
    c->display(out, links);
  
}
