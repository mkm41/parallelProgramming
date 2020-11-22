#include <iostream>
#include <function>

std::function<int(int)> make_offseter(int offset)
{
 return [=](int j){return offset+j;};
}

int main()
{

 int offset=42; 
 std::function<int(int)> offset_a=[&](int j){return offset+j;};
 
 offset=123; 
 std::function<int(int)> offset_b=[&](int j){return offset+j;};
 
 std::cout<<offset_a(12)<<”,”<<offset_b(12)<<std::endl; 
 offset=99; 
 std::cout<<offset_a(12)<<”,”<<offset_b(12)<<std::endl; 
}
