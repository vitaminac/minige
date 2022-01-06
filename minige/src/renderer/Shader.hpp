#pragma once
#include "so.h"
#include <memory>
#include <string>
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/mat4.hpp"
#include "physics/light.hpp"
#include "Texture.hpp"

namespace gengine {
	namespace renderer {
		class SO_API Shader {
		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();
			void enable() const;
			void disable() const;
			const unsigned int getId() const;
			void setUniformInteger(const std::string& name, const int value) const;
			void setUniformFloat(const std::string& name, const float value) const;
			void setUniformVector2(const std::string& name, const math::vec2& vector) const;
			void setUniformVector3(const std::string& name, const math::vec3& vector) const;
			void setUniformVector4(const std::string& name, const math::vec4& vector) const;
			void setUniformMat4(const std::string& name, const math::mat4& matrix) const;
			void setLight(const std::string& name, physics::Light light) const;
			void setTexture(const std::string& name, const Texture& texture);
		};
	}
}