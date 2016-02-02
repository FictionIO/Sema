//-----------------------------------------------------------------------------
// boost sema/detail/internal.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2016 Ali Nakipoglu
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <type_traits>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>

#include <boost/variant.hpp>

#include <boost/sema/detail/types.hpp>
#include <boost/sema/detail/container.hpp>

namespace boost { namespace sema {

	template<typename TypesVecT, typename TypeT>
	struct has_type
	{
		static const bool value			= !std::is_same<typename boost::mpl::find<TypesVecT, TypeT>::type, typename boost::mpl::end<TypesVecT>::type>::value;
	};

	template<typename TypesVecT, typename TypeT>
	struct type_index
	{
		static const std::size_t value	= boost::mpl::find<TypesVecT, TypeT>::type::pos::value;
	};

	template<typename ... TypesT>
	struct to_type_vec
	{
		using type		= boost::mpl::vector<TypesT...>;
	};

	template<typename ImplT, typename InterfacesT, typename TypesVecT>
	struct to_interface_type
	{
		template<typename T>
		struct apply
		{
			enum
			{
				Index	= boost::mpl::find<TypesVecT, T>::type::pos::value,
			};

			using type	= typename InterfacesT:: template get<ImplT, Index, T>::type;
		};
	};

	template<typename ImplT, typename InterfacesT, typename TypesVecT>
	struct to_interface_types_vec
	{
		using func		= to_interface_type<ImplT, InterfacesT, TypesVecT>;
		using type		= typename boost::mpl::transform<TypesVecT, typename func::apply<boost::mpl::_1>>::type;
	};

	template<typename ImplT>
	struct to_real_type
	{
		template<typename T>
		struct apply
		{
			using type	= T;
		};

		template<template<typename ...> typename ContainerT, typename ... ParamsT>
		struct apply<container<ContainerT, ParamsT...>>
		{
			using type	= typename container<ContainerT, ParamsT...>:: template get<ImplT>::type;
		};
	};

	template<typename ImplT, typename TypesVecT>
	struct to_real_types_vec
	{
		using func		= to_real_type<ImplT>;
		using type		= typename boost::mpl::transform<TypesVecT, typename func::apply<boost::mpl::_1>>::type;
	};

	template<typename ImplT, typename InterfacesT, typename ... TypesT>
	struct construct_base
	{
		using types					= typename to_type_vec<TypesT...>::type;
		using realtypes				= typename to_real_types_vec<ImplT, types>::type;
		using interface_types		= typename to_interface_types_vec<ImplT, InterfacesT, realtypes>::type;
		using valid_interface_types	= typename boost::mpl::remove<interface_types, unspecified>::type;
		using type					= typename boost::mpl::inherit_linearly<	valid_interface_types,
																				boost::mpl::inherit<boost::mpl::_1, boost::mpl::_2>
																			>::type;
	};

	template<typename ImplT, typename ... TypesT>
	struct construct_variant
	{
		using types					= typename to_type_vec<TypesT...>::type;
		using realtypes				= typename to_real_types_vec<ImplT, types>::type;
		using type					= typename boost::make_variant_over<realtypes>::type;
	};

} }
