
#pragma once

#include <wv/detail/types.hpp>

namespace wv {

	struct no_interface
	{
		template<typename ImplT, std::size_t TypeIndexT, typename T> \
		struct get { using type	= unspecified; };
	};

}
