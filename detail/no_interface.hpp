//-----------------------------------------------------------------------------
// boost sema/detail/no_interface.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2016 Ali Nakipoglu
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <boost/sema/detail/types.hpp>

namespace boost { namespace sema {

	struct no_interface
	{
		template<typename ImplT, std::size_t TypeIndexT, typename T> \
		struct get { using type	= unspecified; };
	};
} }
