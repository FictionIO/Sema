
###Boost Sema 

Sema is a set of tools for adding semantical methods to boost variant types.

For example let's say we have a variant type : `variant<int, double, string, recursive_wrapper<object>>` and we want to implement methods
`isInt, isDouble, ... asObject, asInt, asDouble, ... asObject` we can define a meta function object :

```
struct MyInterface
{
  template<typename ImplT, std::size_t Index, typename T>
  struct get{ using type = unspecified; }; 
  
  template<typename ImplT, std::size_t Index>
  struct get<ImplT, Index, int> // notice specialization for int
  { 
    using type  = intInterface;
  }; 
  
  template<typename ImplT, std::size_t Index>
  struct get<ImplT, Index, std::string> // notice specialization for std::string
  { 
    using type  = intInterface;
  }; 
};
```

By default it returns `sema::unspecified`, no interface type. Otherwise if template specialization satisfies it returns the interface. If desired this allows grouping interfaces for similar types, for example you can have one interface for all integer types.

Then we can then define our interface and storage (boost variant) in one go like :

```
using MyType = sema<MyInterface, int, double, std::string, sema::container<std::map,std::string, sema::_1>>;
```
Here we used `sema::container and sema::_1` to define a recursive type `std::map<std::string, MyType>`

Now we can use our composed interface methods like :

```
MyType value;

value = 10;

if( value.isInt() )
{
  std::cout << value.asInt() << std::endl;
}
```
