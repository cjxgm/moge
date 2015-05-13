#pragma once
#include "gl.hh"
#include "meta/bind.hh"
#include "program.hh"
#include <string>
#include <type_traits>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace moge
{
	namespace uniform_variable_detail
	{
		namespace set_uniform_detail
		{
			void set_uniform(GLint u, float x) { glUniform1f(u, x); }
			void set_uniform(GLint u, glm::vec2 const& x) { glUniform2fv(u, 1, &x[0]); }
			void set_uniform(GLint u, glm::vec3 const& x) { glUniform3fv(u, 1, &x[0]); }
			void set_uniform(GLint u, glm::vec4 const& x) { glUniform4fv(u, 1, &x[0]); }
			void set_uniform(GLint u, glm::mat2 const& x) { glUniformMatrix2fv(u, 1, false, &x[0][0]); }
			void set_uniform(GLint u, glm::mat3 const& x) { glUniformMatrix3fv(u, 1, false, &x[0][0]); }
			void set_uniform(GLint u, glm::mat4 const& x) { glUniformMatrix4fv(u, 1, false, &x[0][0]); }
		}
		using set_uniform_detail::set_uniform;

		namespace get_uniform_detail
		{
			void get_uniform(GLuint p, GLint u, glm::vec2 & x) { glGetUniformfv(p, u, &x[0]); }
			void get_uniform(GLuint p, GLint u, glm::vec3 & x) { glGetUniformfv(p, u, &x[0]); }
			void get_uniform(GLuint p, GLint u, glm::vec4 & x) { glGetUniformfv(p, u, &x[0]); }
			void get_uniform(GLuint p, GLint u, glm::mat2 & x) { glGetUniformfv(p, u, &x[0][0]); }
			void get_uniform(GLuint p, GLint u, glm::mat3 & x) { glGetUniformfv(p, u, &x[0][0]); }
			void get_uniform(GLuint p, GLint u, glm::mat4 & x) { glGetUniformfv(p, u, &x[0][0]); }
		}
		using get_uniform_detail::get_uniform;

		template <class T>
		struct uniform_variable
		{
			using value_type = std::decay_t<T>;

			// TODO: validate uniform variable type and size
			uniform_variable(GLuint program, GLint uniform)
				: program{program}, uniform{uniform} {}

			uniform_variable(GLuint program, std::string const& uniform_name)
				: uniform_variable{program,
					glGetUniformLocation(program, uniform_name.c_str())}
			{}

			void set(value_type const& x)
			{
				meta::bind<moge::program> _{program};
				set_uniform(uniform, x);
			}

			auto get() const
			{
				meta::bind<moge::program> _{program};
				value_type x;
				get_uniform(program, uniform, x);
				return x;
			}

			auto& operator = (value_type const& x) { set(x); return *this; }
			operator value_type () const { return get(); }

		private:
			GLuint const program;
			GLint  const uniform;
		};
	}

	using uniform_variable_detail::uniform_variable;
}

