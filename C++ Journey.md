---
tags:
  - cplus
  - c
  - class
  - struc
---
# Resources 
- [ ] [C++ Standard Template Library (STL) - GeeksforGeeks](https://www.geeksforgeeks.org/cpp/the-c-standard-template-library-stl/)

# 
# Understand a Class Implementation


```c++
class Animal
{
	public:
		virtual void speak(){ 
			std::cout << "BARK OING QUACK";
			
		}
}

class Dog :public Animal {
	# Access specifier -> public, private, protected
	public: 
			void speak() override {
			std::cout << "Only BARK BARK";
		}
}

```
### Memory Layout
```c
  Animal Object                         Dog Object
+-------------------+               +-------------------+
|   vptr --------+  |               |   vptr --------+  |
|                |  |               |                |  |
+----------------+  |               +----------------+  |
                   |                                  |
                   |                                  |
                   v                                  v
            +----------------+               +----------------+
            |  Animal vtable |               |    Dog vtable  |
            +----------------+               +----------------+
            | speak ---------+-------------->| speak ---------+----> Dog::speak()
            +----------------+               +----------------+
                   |
                   +-----------------------------> Animal::speak()

```


To undestanding purposes we simulate a class behabiour in C but in reality these key point are the one followed by c++ to create a class
>[!done] Memory Layout  
>- [ ] Data Members of Animals comes first in the memory layout so this enable safe upcasting Dog* --> Animal* via Pointer Reinterpretation

>[!tldr] Pointer Reinterpretation
```c++
	#include <iostream>
	
	int main() {
		int* p = new(22);
	# T* new_ptr = reinterpret_cast<T*>(old_ptr);
		char* ch = reinterpret_cast<char*>(p);
	}
```  
>- [ ] Data Members of Animals comes first in the memory layout so this enable safe upcasting Dog* --> Animal* via Pointer Reinterpretation

- [x] A pointer to a derived object (Dog*) cast to a pointer to its (Animal*)  
- [x] Each object has a hidden vptr
- [x] For the base part Dog* and Animal* points to the same memory address for the core part
- [x] sizeof(Dog) == sizeof(Animal) + sizeof(Dog members)

```c
typedef struct Dog Dog;

# Function pointer declaration

SPEAK is a pointer to a function:
	 PointerFunction def: is a variable that stores the address of a funcion
	 void (*speak)(Animal*); could be expressed like void 0x7fffaabbccdd (Animal*); Animal* its the argument
	 
typedef struct {
    void (*speak)(Animal*);
} DogVTable;


struct Animal {
    DogVTable* vptr;
};

// Dog is a subclass: includes Animal
struct Dog {
	# Base its just a name to identify the instance of Animal that is going to inherit the "class" Dog
    Animal base;  // Inheritance via composition
};
```
Definition Structure of the Class based on vtables

```c
void Animal_speak(Animal* this) {
    printf("Animal speaks\n");
}

void Dog_speak(Animal* this) {
    printf("Dog barks\n");
}

// Vtable Instances 
DogVTable animal_vtable = {
    .speak = Animal_speak
};

DogVTable dog_vtable = {
    .speak = Dog_speak
};

void Dog_init(Dog* d) {
    d->base.vptr = &dog_vtable;
}
```