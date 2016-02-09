
#pragma once

#include <type_traits>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>

#include <boost/variant.hpp>

#include <wv/detail/types.hpp>

namespace wv {

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

	template<typename PlaceholderT, typename WithT>
	struct substitute_placeholder
	{
		template<typename InputT>
		struct apply
		{
			template<typename T>
			struct substitute
			{
				using type	= T;
			};

			template<template <typename, typename ...> typename T, typename ParamT, typename ... ParamsT>
			struct substitute<T<ParamT, ParamsT...>>
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
					using type	= T<TypesT...>;
				};

				using originals			= boost::mpl::vector<ParamT, ParamsT...>;
				using func				= typename substitute_placeholder<PlaceholderT, WithT>:: template apply<boost::mpl::_1>;
				using substitutedTypes	= typename boost::mpl::transform<originals, func>::type;
				using packed			= typename boost::mpl::fold<substitutedTypes, packed_types<>, pack_types<boost::mpl::_1, boost::mpl::_2>>::type;
				using type				= typename unpack<packed>::type;
			};

			template<>
			struct substitute<PlaceholderT>
			{
				using type	= WithT;
			};

			using type		= typename substitute<InputT>::type;
		};
	};

	template<typename ImplT, typename TypesVecT>
	struct to_substitude_types_vec
	{
		using func		= typename substitute_placeholder<boost::recursive_variant_, ImplT>:: template apply<boost::mpl::_1>;
		using type		= typename boost::mpl::transform<TypesVecT, func>::type;
	};

	template<typename ImplT, typename InterfacesT, typename ... TypesT>
	struct construct_base
	{
		using types					= typename to_type_vec<TypesT...>::type;
		using substitudes			= typename to_substitude_types_vec<ImplT, types>::type;
		using interface_types		= typename to_interface_types_vec<ImplT, InterfacesT, substitudes>::type;
		using valid_interface_types	= typename boost::mpl::remove<interface_types, unspecified>::type;
		using type					= typename boost::mpl::inherit_linearly<	valid_interface_types,
																				boost::mpl::inherit<boost::mpl::_1, boost::mpl::_2>
																			>::type;
	};

	template<typename ImplT, typename ... TypesT>
	struct construct_variant
	{
		using types					= typename to_type_vec<TypesT...>::type;
		using substitudes			= typename to_substitude_types_vec<ImplT, types>::type;
		using type					= typename boost::make_variant_over<substitudes>::type;
	};

}
