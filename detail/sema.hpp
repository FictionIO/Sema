//-----------------------------------------------------------------------------
// boost sema/detail/sema.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2016 Ali Nakipoglu
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <utility>

#include <boost/sema/detail/internal.hpp>

namespace boost { namespace sema {

	template<typename IterfacesT, typename TypeT, typename ... TypesT>
	struct sema :
		construct_variant<sema<IterfacesT, TypeT, TypesT...>, TypeT, TypesT...>::type,
		construct_base<sema<IterfacesT, TypeT, TypesT...>, IterfacesT, TypeT, TypesT...>::type
	{
		using this_type		= sema<IterfacesT, TypeT, TypesT...>;
		using base_type		= typename construct_variant<this_type, TypeT, TypesT...>::type;

		using base_type::base_type;
	};

} }
