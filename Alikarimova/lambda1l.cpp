#include <iostream>
#include <function>

std::function<int(int)> make_offseter(int offset)
{
 return [=](int j){return offset+j;};
}
int main()
{
 std::cout << "Hello --- Hi!" << std::endl;	
	
 std::function<int(int)> offset_42=make_offseter(42);
 std::function<int(int)> offset_123=make_offseter(123);
 std::cout<<offset_42(12)<<”,”<<offset_123(12)<<std::endl;
 std::cout<<offset_42(12)<<”,”<<offset_123(12)<<std::endl;

return 0;
}
