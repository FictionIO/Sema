
#pragma once

#include <string>
#include <vector>
#include <map>

#include <boost/variant/get.hpp>
#include <boost/blank.hpp>

#include <sema/detail/types.hpp>

namespace sema {

	struct default_interfaces
	{
		template<typename ImplT, std::size_t TypeIndexT, typename T>
		struct get { using type	= unspecified; };

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, boost::blank>
		{
			struct type
			{
				bool isBlank() const { return ( (ImplT*)this )->which() == TypeIndexT; };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, bool>
		{
			struct type
			{
				bool isBool() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const bool & asBool() const { return boost::get<bool>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, int>
		{
			struct type
			{
				bool isInt() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const int & asInt() const { return boost::get<int>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, double>
		{
			struct type
			{
				bool isDouble() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const double & asDouble() const { return boost::get<double>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, float>
		{
			struct type
			{
				bool isFloat() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const float & asFloat() const { return boost::get<float>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, std::string>
		{
			struct type
			{
				bool isString() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const std::string & asString() const { return boost::get<std::string>( *((ImplT*)this) ); };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT> struct get<ImplT, TypeIndexT, std::vector<ImplT>>
		{
			struct type
			{
				bool isVector() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const std::vector<ImplT> & asVector() const { return boost::get<std::vector<ImplT>>( *((ImplT*)this) ); };

				const ImplT & operator [] ( const std::size_t & index ) const { return asVector()[ index ]; };
			};
		};

		template<typename ImplT, std::size_t TypeIndexT, typename KeyT> struct get<ImplT, TypeIndexT, std::map<KeyT, ImplT>>
		{
			struct type
			{
				bool isMap() const { return ( (ImplT*)this )->which() == TypeIndexT; };
				const std::map<KeyT, ImplT> & asMap() const { return boost::get<std::map<KeyT, ImplT>>( *((ImplT*)this) ); };
				std::map<KeyT, ImplT> & asMap() { return boost::get<std::map<KeyT, ImplT>>( *((ImplT*)this) ); };

				const ImplT & operator [] ( const KeyT & key ) const { return asMap().at( key ); };
				ImplT & operator [] ( const KeyT & key ) { return asMap()[ key ]; };
			};
		};
	};

}
