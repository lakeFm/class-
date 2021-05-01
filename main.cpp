#include <iostream>
#include "ClassBuilder.h"

int main(){
    // player(vec3f position,int id,long socket,array<Item> inventory)
    char data[100]; std::cin.getline(data,100);
    ClassBuilder builder(data, false);
    builder.print();
    return 0;
}
