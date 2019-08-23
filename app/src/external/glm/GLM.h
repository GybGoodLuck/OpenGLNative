#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <string>

using namespace std;
namespace glm {

    class GLM {
    public:
        static string ToString(const glm::vec3 &v) {
            string ret = "[";
            char str[64];
            for (int j = 0; j < 3; j++) {
                snprintf(str, sizeof(str), "%f", v[j]);
                string x(str);
                ret += x + " ";
            }
            ret += "]";
            return ret;
        }

        static string ToString(const glm::vec4 &v) {
            string ret = "[";
            char str[64];
            for (int j = 0; j < 4; j++) {
                snprintf(str, sizeof(str), "%f", v[j]);
                string x(str);
                ret += x + " ";
            }
            ret += "]";
            return ret;
        }

        // in wxyz order
        static string ToString(const glm::fquat &v) {
            string ret = "[";
            char str[64];
            for (int j = 0; j < 4; j++) {
                int id = j == 0 ? 3 : j - 1;
                snprintf(str, sizeof(str), "%f", v[id]);
                string x(str);
                ret += x + " ";
            }
            ret += "]";
            return ret;
        }

        static string ToString(const glm::mat4 &m) {
            string ret = "\n";
            char str[64];
            for (int i = 0; i < 4; i++) {
                ret += "[";
                for (int j = 0; j < 4; j++) {
                    snprintf(str, sizeof(str), "%f", m[i][j]);
                    string x(str);
                    ret += x + " ";
                }
                ret += "]\n";
            }
            return ret;
        }

        template<typename T>
        static bool CopyGlm(float *dest, const T &src) {
            if (dest == nullptr) {
                return false;
            }
            memcpy(dest, glm::value_ptr(src), sizeof(T));
            return true;
        }

        static bool CopyGlm(float *dest, const glm::fquat &src) {
            if (dest == nullptr) {
                return false;
            }
            dest[0] = src.w;
            dest[1] = src.x;
            dest[2] = src.y;
            dest[3] = src.z;
            return true;
        }

        template<typename T>
        static bool CopyGlm(T &dest, const float *src) {
            if (src == nullptr) {
                return false;
            }
            memcpy(glm::value_ptr(dest), src, sizeof(T));
            return true;
        }

        static bool CopyGlm(glm::fquat &dest, const float *src) {
            if (src == nullptr) {
                return false;
            }
            dest = glm::fquat(src[0], src[1], src[2], src[3]);
            return true;
        }

        // f,n in abs value
        static glm::mat4 GetPerspective(float l, float r, float t, float b, float f,
                                        float n) {
            glm::mat4 ret;
            ret[0][0] = 2 * n / (r - l);
            ret[1][1] = 2 * n / (t - b);
            ret[2][0] = (r + l) / (r - l);
            ret[2][1] = (t + b) / (t - b);
            ret[2][2] = -(f + n) / (f - n);
            ret[2][3] = -1;
            ret[3][2] = -2 * f * n / (f - n);
            ret[3][3] = 0;
            return ret;
        }

        // x,y,in
        static glm::vec3 GetIntersect(const glm::vec3 &xDir, const glm::vec3 &yDir,
                                      const glm::vec3 &xyCenter,
                                      const glm::vec3 &inDir,
                                      const glm::vec3 &inCenter) {
            glm::mat3 m(xDir, yDir, -inDir);
            m = glm::inverse(m);
            return m * (inCenter - xyCenter);
        }
    };

}  // namespace IrisVRCommon

#define LOG_GLM(x) ILOGI("%s %s", #x, GLM::ToString((x)).c_str())