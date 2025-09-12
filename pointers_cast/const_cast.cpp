#include <iostream>

struct Foo {
	int i;
	Foo(): i(3) {} 

	void override_const(int v) const
	{
	    const_cast<Foo*>(this)->i = v; 
        //❌ Bad practice callers belive f() won't mutate observable state
        //❌ Always UB if the member itself is const
	}
};

int main () {

    Foo f;
    Foo n;
    std::cout << "i before const_cast : " << f.i << std::endl;


    const_cast<int&>(f.i) = 5;
    
    std::cout << "i after const_cast : " << f.i << std::endl;
    
    f.override_const(7);
    std::cout << "i override of intance of Foo f : " << f.i << std::endl;

    std::cout << "i before override : " << n.i << std::endl;
    n.override_const(7);
    std::cout << "i override of intance of Foo n : " << n.i << std::endl;
}
