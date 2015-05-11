#include "utils.hh"
#include "exceptions.hh"
#include <sstream>
#include <fstream>
#include <iomanip>

namespace moge
{
	namespace utils
	{
		std::string load_file(std::string const& path)
		{
			std::ifstream f{path};
			std::stringstream ss;
			if (!f) {
				ss << "cannot open file " << std::quoted(path) << " for reading";
				throw io_failure{ss.str()};
			}
			ss << f.rdbuf();
			return ss.str();
		}
	}
}

