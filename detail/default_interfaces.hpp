
#pragma once

#include <string>
#include <vector>
#include <map>

#include <boost/variant/get.hpp>
#include <boost/blank.hpp>

#include <wv/detail/types.hpp>

namespace wv {

	struct default_interfaces
	{
		template<typename ImplT, std::size_t TypeIndexT, typename T>
		struct get { using type	= unspecified; };

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, boost::blank>
		{
			struct type
			{
				enum { WHICH_BLANK	= TypeIndexT };

				bool isBlank() const { return ( (ImplT*)this )->which() == TypeIndexT; };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, bool>
		{
			struct type
			{
				enum { WHICH_BOOL	= TypeIndexT };

				bool isBool() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const bool & asBool() const { return boost::get<bool>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, int>
		{
			struct type
			{
				enum { WHICH_INT	= TypeIndexT };

				bool isInt() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const int & asInt() const { return boost::get<int>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, double>
		{
			struct type
			{
				enum { WHICH_DOUBLE	= TypeIndexT };

				bool isDouble() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const double & asDouble() const { return boost::get<double>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, float>
		{
			struct type
			{
				enum { WHICH_FLOAT	= TypeIndexT };

				bool isFloat() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const float & asFloat() const { return boost::get<float>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, std::string>
		{
			struct type
			{
				enum { WHICH_STRING	= TypeIndexT };

				bool isString() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const std::string & asString() const { return boost::get<std::string>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, std::vector<ImplT>>
		{
			struct type
			{
				enum { WHICH_VECTOR	= TypeIndexT };

				bool isVector() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const std::vector<ImplT> & asVector() const { return boost::get<std::vector<ImplT>>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT, typename KeyT> struct get<ImplT, TypeIndexT, std::map<KeyT, ImplT>>
		{
			struct type
			{
				enum { WHICH_MAP		= TypeIndexT };

				bool isMap() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const std::map<KeyT, ImplT> & asMap() const { return boost::get<std::map<KeyT, ImplT>>( *((ImplT*)this) ); };
			};
		};
	};

}
