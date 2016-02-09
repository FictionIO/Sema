
#define BOOST_TEST_MODULE SemaTests

#include <boost/test/included/unit_test.hpp>
#include <wv/wv.hpp>

using namespace wv;

BOOST_AUTO_TEST_CASE( SIMPLE_TEST )
{
	using ValueT	= wrapped_variant<default_interfaces, boost::blank, int, bool>;
	
	ValueT	val;
	BOOST_TEST( val.isBlank() );

	val	= 10;
	BOOST_TEST( val.isInt() );
	BOOST_TEST( val.asInt() == 10 );

	val	= true;
	BOOST_TEST( val.isBool() );
	BOOST_TEST( val.asBool() == true );
}

BOOST_AUTO_TEST_CASE( TEST_WITH_VECTOR )
{
	using ValueT	= wrapped_variant<default_interfaces, boost::blank, int, double, std::vector<boost::recursive_variant_>>;

	ValueT val		= std::vector<ValueT>{ 10, 20.0 };

	BOOST_TEST( val.isVector() );
	BOOST_TEST( val.asVector().size() == 2 );
	BOOST_TEST( val[ 0 ].isInt() );
	BOOST_TEST( val[ 0 ].asInt() == 10 );
	BOOST_TEST( val[ 1 ].isDouble() );
	BOOST_TEST( val[ 1 ].asDouble() == 20.0 );
}

BOOST_AUTO_TEST_CASE( TEST_WITH_MAP )
{
	using ValueT	= wrapped_variant<default_interfaces, boost::blank, int, std::string, std::map<std::string, boost::recursive_variant_>>;

	ValueT val		= std::map<std::string, ValueT>{};

	val[ "intVal" ]	= 10;
	val[ "strVal" ]	= "string";

	BOOST_TEST( val.isMap() );
	BOOST_TEST( val.asMap().size() == 2 );
	BOOST_TEST( val[ "intVal" ].isInt() );
	BOOST_TEST( val[ "intVal" ].asInt() == 10 );
	BOOST_TEST( val[ "strVal" ].isString() );
	BOOST_TEST( val[ "strVal" ].asString() == "string" );
}

struct MyType{};

struct MyInterfaces
{
	// According to this all will get no interface except MyType.

	template<typename ImplT, std::size_t TypeIndexT, typename T>
	struct get { using type	= wv::unspecified; };

	template<typename ImplT, std::size_t TypeIndexT>
	struct get<ImplT, TypeIndexT, MyType>
	{
		struct type
		{
			const bool isMyType() const
			{
				return ( (ImplT*)this )->which() == TypeIndexT;
			};

			const MyType & asMyType() const
			{
					return boost::get<MyType>( *((ImplT*)this) );
			};
		};
	};
};

BOOST_AUTO_TEST_CASE( TEST_WITH_CUSTOM_INTERFACE )
{
	using ValueT	= wrapped_variant<MyInterfaces, int, MyType>;

	ValueT v;

	v	= MyType{};

	BOOST_TEST( v.isMyType() );
}
