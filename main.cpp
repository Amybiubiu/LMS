#include <string>
#include <iostream>
#include <map>
using namespace std;

class Item{
private:
   string name;
   long id;
public:
   Item(string name, long id){
      this->name = name;
      this->id = id;
   }
   void setId(long id){
      this->id = id;
   }
   long getId(){
      return id;
   }
};

int main() {
   // string str = "abc";
   // MD5 md5(str);
   // string result = md5.md5();
   // cout << "abc md5 is " << result << endl;

   //test map will auto change
   map<int, Item> m;
   
   Item i = Item("amy",123);
   m[0] = i;
   i.setId(456);
   cout<<i.getId();
   cout<<m[0].getId();

   return 0;
}
