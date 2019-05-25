#include "mat4.h"

namespace gengine {
    namespace geometry {
        mat4 gengine::geometry::operator*(const mat4& left, const mat4& right)
        {
            auto matrix = mat4();
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    float sum = 0;
                    for (int k = 0; k < 4; k++) {
                        sum += left[k][j] * right[i][k];
                    }
                    matrix.elements[i * 4 + j] = sum;
                }
            }
            return matrix;
        }

        const vec4& mat4::operator[](const int index) const
        {
            return this->columns[index];
        }

        mat4 mat4::diagonal(const float diagonal)
        {
            auto mat4 = mat4::zero();
            mat4.elements[0 + 0 * 4] = diagonal;
            mat4.elements[1 + 1 * 4] = diagonal;
            mat4.elements[2 + 2 * 4] = diagonal;
            mat4.elements[3 + 3 * 4] = diagonal;
            return mat4;
        }

        mat4 mat4::identity()
        {
            return mat4::diagonal(1.0f);
        }

        mat4 mat4::zero()
        {
            auto matrix = mat4();
            for (int i = 0; i < 4 * 4; i++) {
                matrix.elements[i] = 0;
            }
            return matrix;
        }

        mat4 mat4::translation(const vec3& translation)
        {
            auto mat4 = mat4::identity();
            mat4.elements[0 + 3 * 4] = translation.getX();
            mat4.elements[1 + 3 * 4] = translation.getY();
            mat4.elements[2 + 3 * 4] = translation.getZ();
            return mat4;
        }
        mat4 mat4::rotation(const vec3& axis, const float angle)
        {
            auto mat4 = mat4::identity();
            auto radian = toRadians(angle);
            auto cosine = cos(radian);
            auto sine = sin(radian);
            /* one munis cosine */
            auto omcosine = 1 - cosine;

            auto x = axis.getX();
            auto y = axis.getY();
            auto z = axis.getZ();

            mat4.elements[0 + 0 * 4] = x * x * omcosine + cosine;
            mat4.elements[1 + 0 * 4] = x * y * omcosine + z * sine;
            mat4.elements[2 + 0 * 4] = x * z * omcosine - y * sine;

            mat4.elements[0 + 1 * 4] = y * x * omcosine - z * sine;
            mat4.elements[1 + 1 * 4] = y * y * omcosine + cosine;
            mat4.elements[2 + 1 * 4] = y * z * omcosine + y * sine;

            mat4.elements[0 + 2 * 4] = z * x * omcosine + z * sine;
            mat4.elements[1 + 2 * 4] = z * y * omcosine - x * sine;
            mat4.elements[2 + 2 * 4] = z * z * omcosine + cosine;

            return mat4;
        }

        mat4 mat4::scale(const vec3& k)
        {
            auto mat4 = mat4::identity();
            mat4.elements[0 + 0 * 4] = k.getX();
            mat4.elements[1 + 1 * 4] = k.getY();
            mat4.elements[2 + 2 * 4] = k.getZ();
            return mat4;
        }

        mat4 mat4::orthographic(const vec3& min_corner, const vec3& max_corner)
        {
            auto mat4 = mat4::zero();
            mat4.elements[0 + 0 * 4] = 2.0f / (max_corner.getX() - min_corner.getX());
            mat4.elements[1 + 1 * 4] = 2.0f / (max_corner.getY() - min_corner.getY());
            mat4.elements[2 + 2 * 4] = -2.0f / (max_corner.getZ() - min_corner.getZ());

            mat4.elements[0 + 3 * 4] = -(max_corner.getX() + min_corner.getX()) / (max_corner.getX() - min_corner.getX());
            mat4.elements[1 + 3 * 4] = -(max_corner.getY() + min_corner.getY()) / (max_corner.getY() - min_corner.getY());
            mat4.elements[2 + 3 * 4] = (max_corner.getZ() + min_corner.getZ()) / (max_corner.getZ() - min_corner.getZ());

            mat4.elements[3 + 3 * 4] = 1.0f;
            return mat4;
        }

        mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
        {
            mat4 mat4 = mat4::identity();

            float q = 1.0f / tan(toRadians(0.5f * fov));
            float a = q / aspectRatio;

            float b = (near + far) / (near - far);
            float c = (2.0f * near * far) / (near - far);

            mat4.elements[0 + 0 * 4] = a;
            mat4.elements[1 + 1 * 4] = q;
            mat4.elements[2 + 2 * 4] = b;
            mat4.elements[2 + 3 * 4] = -1.0f;
            mat4.elements[3 + 2 * 4] = c;

            return mat4;
        }
    }
}