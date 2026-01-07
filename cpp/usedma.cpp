#include<iostream>
#include"dma.h"

int main(){
    using std::cout;
    using std::endl;

    baseDMA shirt("Portland", 8);
    lacksDMA balloon("red", "Bilp", 4);
    cout << shirt << endl;
    cout << balloon << endl;
    return 0;
}