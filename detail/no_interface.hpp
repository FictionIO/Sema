
#pragma once

#include <sema/detail/types.hpp>

namespace sema {

	struct no_interface
	{
		template<typename ImplT, std::size_t TypeIndexT, typename T> \
		struct get { using type	= unspecified; };
	};

}
