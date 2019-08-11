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

        vec3 operator*(const mat4& left, const vec3& right)
        {
            return vec3(
                left.columns[0].x * right.x + left.columns[1].x * right.y + left.columns[2].x * right.z,
                left.columns[0].y * right.x + left.columns[1].y * right.y + left.columns[2].y * right.z,
                left.columns[0].z * right.x + left.columns[1].z * right.y + left.columns[2].z * right.z
            );
        }

        vec4 operator*(const mat4& left, const vec4& right)
        {
            return vec4(
                left.columns[0].x * right.x + left.columns[1].x * right.y + left.columns[2].x * right.z + left.columns[3].x * right.w,
                left.columns[0].y * right.x + left.columns[1].y * right.y + left.columns[2].y * right.z + left.columns[3].y * right.w,
                left.columns[0].z * right.x + left.columns[1].z * right.y + left.columns[2].z * right.z + left.columns[3].z * right.w,
                left.columns[0].w * right.x + left.columns[1].w * right.y + left.columns[2].w * right.z + left.columns[3].w * right.w
            );
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
            mat4.elements[0 + 3 * 4] = translation.x;
            mat4.elements[1 + 3 * 4] = translation.y;
            mat4.elements[2 + 3 * 4] = translation.z;
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

            auto x = axis.x;
            auto y = axis.y;
            auto z = axis.z;

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
            mat4.elements[0 + 0 * 4] = k.x;
            mat4.elements[1 + 1 * 4] = k.y;
            mat4.elements[2 + 2 * 4] = k.z;
            return mat4;
        }

        mat4 mat4::orthographic(const vec3& min_corner, const vec3& max_corner)
        {
            auto mat4 = mat4::zero();
            mat4.elements[0 + 0 * 4] = 2.0f / (max_corner.x - min_corner.x);
            mat4.elements[1 + 1 * 4] = 2.0f / (max_corner.y - min_corner.y);
            mat4.elements[2 + 2 * 4] = -2.0f / (max_corner.z - min_corner.z);

            mat4.elements[0 + 3 * 4] = -(max_corner.x + min_corner.x) / (max_corner.x - min_corner.x);
            mat4.elements[1 + 3 * 4] = -(max_corner.y + min_corner.y) / (max_corner.y - min_corner.y);
            mat4.elements[2 + 3 * 4] = -(max_corner.z + min_corner.z) / (max_corner.z - min_corner.z);

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