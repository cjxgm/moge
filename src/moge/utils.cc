#include "utils.hh"
#include <sstream>
#include <fstream>

namespace moge
{
	namespace utils
	{
		std::string load_file(std::string const& path)
		{
			std::ifstream f{path};
			std::stringstream ss;
			ss << f.rdbuf();
			return ss.str();
		}
	}
}

