
#pragma once

#include <utility>

#include <sema/detail/internal.hpp>

namespace sema {

	template<typename IterfacesT, typename TypeT, typename ... TypesT>
	struct sema :
		construct_variant<sema<IterfacesT, TypeT, TypesT...>, TypeT, TypesT...>::type,
		construct_base<sema<IterfacesT, TypeT, TypesT...>, IterfacesT, TypeT, TypesT...>::type
	{
		using this_type		= sema<IterfacesT, TypeT, TypesT...>;
		using base_type		= typename construct_variant<this_type, TypeT, TypesT...>::type;

		using base_type::base_type;
	};

}
