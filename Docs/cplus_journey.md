---
tags:
  - cplus
  - c
  - class
  - struc
---
z# Resources 
- [ ] [C++ Standard Template Library (STL) - GeeksforGeeks](https://www.geeksforgeeks.org/cpp/the-c-standard-template-library-stl/)
- [ ] [STL Function Usage](https://learn.microsoft.com/es-es/troubleshoot/developer/visualstudio/cpp/libraries/use-priority-queue-stl-function)
- [ ] [Dynamic Casting C++ Implementation](https://www.learncpp.com/cpp-tutorial/dynamic-casting/)
- [ ] [LibCurl Application C++](https://dev.to/secure_daily/using-libcurl-in-c-c-application-4668)
- [ ] [Cororutines C++20](https://en.cppreference.com/w/cpp/language/coroutines.html)
- [ ] [Templates](https://www.geeksforgeeks.org/cpp/templates-cpp/)

# Statements

- Declaration statements
- Jump statements
- Expression statements
- Compound statements
- Selection statements (conditionals)
- Iteration statements (loops)
- Try blocks
---
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

- [ ] Data Members of Animals comes first in the memory layout so this enable safe upcasting Dog* --> Animal* via Pointer Reinterpretation
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
---
# *Type Castsing*

### Implicit Casting
The operation is entirely made by the compiler
```c
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double
```
![[65ce73a84554f_type_casting_in_c_3 1.webp]]


### Explicit Casting
The program must define when this is going to happen

```c
C style cast
 div = (double)a / b;

```

 ### RTTI (Run-Time Type Information) in C++
 RTTI exposes info about the object's data type at runtime and is available only for the classes which have at least one virtual function. This allows these two kind of casting
- **Upcasting**: When a pointer or a reference of a derived class object is treated as a base class pointer.
- **Downcasting**: When a base class pointer or reference is converted to a derived class pointer.

## Named cast Operators

### *static cast - Pointer Reinterpretation*
Performs compile-time type conversion used mainly for explicit conversions considered safe by the compiler
```c++
T* var_name = static_cast <new_type>(expr);
```
```c 
include <iostream>

int main(void) {
	double numd = static_cast<double>(n);
	std::cout << typeid(n).name()
}
```
Static cast uses direct initialization any explicit constructors of the target class type will be considered when initializing the temporary object to be returned
- [More Info]([14.16 — Converting constructors and the explicit keyword – Learn C++](https://www.learncpp.com/cpp-tutorial/converting-constructors-and-the-explicit-keyword/))
### *dynamic cast - Downcasting*
Converting a pointer/reference of a base class to a derived class, ensures type safety by runtime type check
```c++
	dynamic_cast <new_type> (exp);
	#return value NULL POINTER or 0 if failed
```
### *reinterpret cast - Pointer Reinterpretation*

Uncheck and dangerous pointer conversion to any type. Non portable-product. 
```c 
T* new_ptr = reinterpret_cast<T*>(old_ptr);
```
```c++
	#include <iostream>
	
	int main() {
		int* p = new(22);
		char* ch = reinterpret_cast<char*>(p);
		
		
		bool* n = reinterpret_cast<bool*>(ch);
		cout << *n << endl;
	}
```
### const_cast 

>[!warning] **Regla de oro** para usar const_cast
>- **Permitido:** quitar `const` y **modificar** si el objeto original **no** fue declarado `const`.
>- **UB (comportamiento indefinido):** modificar un objeto que **fue declarado `const`** desde el inicio, aunque le quites `const`.
```c++
struct Foo {
	int i;
	Foo(): i(3) {} 
		//Foo constructor with member initializer
		# : i(3) stands for a default value if its not override it by the call to the constructor
		# i{3} protege la variable de narrowing al intentar setear un valor no valido narrow checking	
	void f(int v) const
	{
	    const_cast<Foo*>(this)->i = v; // OK as long as the type object isn't const
	}
}    
int main() {
    Foo f; 
	f.i = 5; //❌ No se puede realizar ya es un const
    const_cast<int&>(f.i);
}
```
>[!warning] No confundir con bound checking
> Este se aplica en tiempo de ejecucion si accedo a una variable fuera del rango de un contenedor ejemplo `std::vector`
```c++
	#Ejemplo 
	std::vector<int> v = {1,2,3};
	try {
	    int x = v.at(5);
	} catch (const std::out_of_range& e) {
		// v.at(i): Comprueba si i < v.size(), size() devuelve `std::out_of_range`
	}
	int y = v[5]; ⚠️
	// OJO CUIDAO puede empezar a leer basura ya que se encuentra fuera del rango
	
```
### C-style casts
Casting done via the **operator()** *var_name*. Still used in C code
```c
std::cout << (double)x / y << '\n';
```
Casting via the **function-style** 
```c
std::cout << double(x) / y << '\n';
```
A C-style cast tries to perform the following C++ casts, in order:
- **`const_cast`** *(not recommeded to use)*
- **`static_cast`** 
- **`static_cast`**, followed by **`const_cast`**
- **`reinterpret_cast`**
- **`reinterpret_cast`**, followed by **`const_cast`**

## *class* `or` *struct* = **default** ?
This 

---
## Data Types

- Literals of data are read only 
### Types of variable Initialization
#### **Default-Initialization**
```C++
int a; //This performs no initialization
```
#### **Direct-Initialization**
```C++
int a (5); 

```
When values are `static_cast` they use direct-initialization
#### **Aggregate Initialization**
>[!tldr] Aggreate Data type
> Its consider any type that can contain multiple data members. Some types of operators allow members to have different types
```c++
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)
```
##### Designated Initializers
New way in C++20 to target select the variables to avoid assigning another value to the desired variable inside an struct
```c++
struct Foo {
	int a{};
	int b{};
	int c{};
};

int main() {
	Foo f1{.a{1}, .c{4}};  // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 4
	Foo f2{.a = 4, .c = 1} // ok: f2.a = 4, f2.b = 3,  f2.c = 1
	Foo f3{.b {2}, .a {32}} //❌ Not correct order must be respected of declaration struct
	
	return 0;
}
```
> [!error] For Clang users
>When doing designated initializers of single values using braces, Clang improperly issues warning “braces around scalar initializer”. Hopefully this will be fixed soon.

#### **Copy-Initialization**
```c++
int value = 4; //Uses assignment operator
```
- **Before C++17** could involve extra temporary objects
- **Since C++17**, usually as efficient as direct-init
When values are implicit copied ( passing arguments, try catch exeptions) they also use copy-list initialization

> [!warning] Narrowing Conversion
> It's a type of numeric conversion where the destination type may not be able to hold all the values of the source type. Leading to data loss and unsafe behaviors
> - Types of narrowing conversions
> Float point type to integral type, Floating point type to a lesser-ranked floating point type unless its `constexpr`, integral type to floating point type unless `constexpr`, integral type to another integral that cannot represent all value of the original type 
> > [!tldr] Integral Range
> > enum, char16_t, char32_t, signed char, unsigned char, char ,wchat_t, short, unsigned short, signed char, unsigned char, int_fast8_t, int_fast16_t, int_fast32_t, int_fast64_t, intmax_t, int_least*_tr

 ```c++
  int i {3.5}; // Gives compile error
  int i = 3.5; //Gives no error initialize to 3
  ```
#### List-Initialization / Uniform-Initialization / Brace-Initialization 
Modern way of initialize objects in C++
> [!success] Best practice
> Prefer direct-list-initialization or value-initialization to initialize your variables
```c++
int width {5};
//direct-list-initialization
int height = {6};
//copy-list-initialization
```
#### **Reference-Initialization**
>[!tldr] Reference **&** Definition
>A **reference** is an alias for an existing object. Once a reference has been defined, any operation on the reference is applied to the object being referenced. This means we can use a reference to read or modify the object being referenced.
```c++
int value {5};
int& ref {value}; //lvalue reference to an int object value that equals to 5

ref = 3; //Now value and ref equals 3;
```
> [!success] Best practice
When defining a reference, place the ampersand next to the type (not the reference variable’s name). 
#### Static-Inicialization, Constant-Initialization, Dynamic-Initialization
```c++

```
#### Zero/Value-Initialization
safe defaults: zero, false, or default ctor
```c++
int list_num {};
```
>[!tldr] Add-ons
> To avoid warning of unused variables tag this before declaring a variable object
```c++
[[maybe_unused]] double pi {3.14159};
```
---
# Operators

