#include "shader.hh"
#include "exceptions.hh"

namespace moge
{
	namespace shader_detail
	{
		namespace
		{
			void check_error(GLuint id)
			{
				GLint ok;
				glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
				if (ok) return;

				GLint len;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

				std::string msg(len, '\0');
				glGetShaderInfoLog(id, len, {}, &msg[0]);

				throw shader_failure{msg.c_str()};
			}
		}

		template <GLenum TYPE>
		shader<TYPE>::shader(std::string const& source)
		{
			auto s = source.c_str();
			glShaderSource(*this, 1, &s, {});
			glCompileShader(*this);
			check_error(*this);
		}

		template struct shader<GL_VERTEX_SHADER  >;
		template struct shader<GL_GEOMETRY_SHADER>;
		template struct shader<GL_FRAGMENT_SHADER>;
	}
}

