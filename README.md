
###WrappedVariant 

WrappedVariant is a convenient Boost.Variant wrapper for adding type interfaces.

### Example
``` 
struct MyInterfaces
{
	template<typename ImplT, std::size_t TypeIndexT, typename T>
	struct get { using type	= wv::unspecified; };

	template<typename ImplT, std::size_t TypeIndexT>
	struct get<ImplT, TypeIndexT, int>
	{
		struct type
		{
			const bool isInt() const
			{
				return ( (ImplT*)this )->which() == TypeIndexT;
			};

			const MyType & asInt() const
			{
					return boost::get<int>( *((ImplT*)this) );
			};
		};
	};
};

using MyVariant = wv::wrapped_variant<MyInterfaces, int, bool>;

MyVariant var = 10;

assert( var.isInt() ); //true
assert( var.asInt() == 10 ); //true

// You can also use default interfaces
// using MyVariant = wv::wrapped_variant<wv::default_interfaces, int, bool>;

// Or no interface, Will declare a boost::variant<...> without any additional methods
// using MyVariant = wv::wrapped_variant<wv::no_interface, int, bool>; 

```

##Dependencies

Boost
