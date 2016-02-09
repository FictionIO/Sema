
#pragma once

#include <utility>

#include <wv/detail/internal.hpp>

namespace wv {

	template<typename IterfacesT, typename TypeT, typename ... TypesT>
	struct wrapped_variant :
		construct_variant<wrapped_variant<IterfacesT, TypeT, TypesT...>, TypeT, TypesT...>::type,
		construct_base<wrapped_variant<IterfacesT, TypeT, TypesT...>, IterfacesT, TypeT, TypesT...>::type
	{
		using this_type		= wrapped_variant<IterfacesT, TypeT, TypesT...>;
		using base_type		= typename construct_variant<this_type, TypeT, TypesT...>::type;

		using base_type::base_type;
	};

}
