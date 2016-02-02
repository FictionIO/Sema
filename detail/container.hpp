//-----------------------------------------------------------------------------
// boost sema/detail/container.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2016 Ali Nakipoglu
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <boost/mpl/vector.hpp>
#include <boost/mpl/replace.hpp>
#include <boost/mpl/fold.hpp>

#include <boost/sema/detail/placeholders.hpp>

namespace boost { namespace sema {

	template<template<typename ...> typename ContainerT, typename ... ParamsT>
	struct container
	{
		template<typename T>
		struct get
		{
			template<typename ... TypesT>
			struct packed_types{};

			template<typename Type1T, typename Type2T>
			struct pack_types;

			template<typename TypeT, typename ... TypesT>
			struct pack_types<packed_types<TypesT...>, TypeT>
			{
				using type	= packed_types<TypesT..., TypeT>;
			};

			template<typename ... TypesT>
			struct unpack
			{
				using type	= void;
			};

			template<typename ... TypesT>
			struct unpack<packed_types<TypesT...>>
			{
				using type	= ContainerT<TypesT...>;
			};

			using in		= boost::mpl::vector<ParamsT...>;
			using out		= typename boost::mpl::replace<in, _1, T>::type;
			using packed	= typename boost::mpl::fold<	out,
															packed_types<>,
															pack_types<boost::mpl::_1, boost::mpl::_2>
														>::type;

			using type		= typename unpack<packed>::type;

		};
	};

} }
