#include<iostream>
#include<unistd.h>
using namespace std;
int main(){
      int i=10;
      while(i--){
            cout<<"1\n";
            sleep(1);
      }
      return 0;
}