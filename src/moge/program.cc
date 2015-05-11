#include "program.hh"
#include "exceptions.hh"

namespace moge
{
	namespace program_detail
	{
		namespace
		{
			void check_error(GLuint id)
			{
				GLint ok;
				glGetProgramiv(id, GL_LINK_STATUS, &ok);
				if (ok) return;

				GLint len;
				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);

				std::string msg(len, '\0');
				glGetProgramInfoLog(id, len, {}, &msg[0]);

				throw program_failure{msg.c_str()};
			}
		}

		program::program(std::initializer_list<GLuint> const& shaders)
		{
			for (auto s: shaders) glAttachShader(*this, s);
			glLinkProgram(*this);
			for (auto s: shaders) glDetachShader(*this, s);
			check_error(*this);
		}
	}
}

