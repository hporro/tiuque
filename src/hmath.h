#pragma once

#include <cmath>

namespace hmath {

    // --------------------------------------------------------------------------------------------------------------------------------
    // Constants
    // --------------------------------------------------------------------------------------------------------------------------------
    const double H_PI = 3.1415926535;

    // --------------------------------------------------------------------------------------------------------------------------------
    // To simplify some code, is always usefull a pow2 function
    // --------------------------------------------------------------------------------------------------------------------------------
    template<class T>
    T pow2(T x){
        return x*x;
    }
    template<class T>
    T pow3(T x){
        return x*x*x;
    }

    // --------------------------------------------------------------------------------------------------------------------------------
    // Definition of a general vector structure, and some common operators
    // The dim template parameter represents the number of dimentions of the vector
    // The T template parameter represents the type of the elements of the vector
    // --------------------------------------------------------------------------------------------------------------------------------
    template<int dim, class T>
    struct hvector{
        T coord[dim];
        const T& operator[](const unsigned int i) const {
            return coord[i];
        }
        T& operator[](const unsigned int i) {
            return coord[i];
        }
        template<class E>
        hvector<dim,T>& operator+=(const hvector<dim,E>& o){
            for(int i=0;i<dim;i++){
                coord[i]+=(T)o[i];
            }
            return *this;
        }
        template<class E>
        hvector<dim,T>& operator-=(const hvector<dim,E>& o){
            for(int i=0;i<dim;i++){
                coord[i]-=(T)o[i];
            }
            return *this;
        }
        template<class E>
        hvector<dim,T>& operator*=(const E& a){
            for(int i=0;i<dim;i++){
                coord[i]*=(T)a;
            }
            return *this;
        }
        template<class E>
        hvector<dim,T>& operator/=(const E& a){
            for(int i=0;i<dim;i++){
                coord[i]/=(T)a;
            }
            return *this;
        }
    };
    template<int dim, class T>
    hvector<dim,T> operator+(const hvector<dim,T>& a, const hvector<dim,T>& b){
        hvector<dim,T> res;
        for(int i=0;i<dim;i++){
            res[i]=a[i]+b[i];
        }
        return res;
    }
    template<int dim, class T>
    hvector<dim,T> operator-(const hvector<dim,T>& a, const hvector<dim,T>& b){
        hvector<dim,T> res;
        for(int i=0;i<dim;i++){
            res[i]=a[i]-b[i];
        }
        return res;
    }
    template<int dim, class T>
    hvector<dim,T> operator*(const hvector<dim,T>& a, const T& b){
        hvector<dim,T> res;
        for(int i=0;i<dim;i++){
            res[i]=a[i]*b;
        }
        return res;
    }
    template<int dim, class T>
    hvector<dim,T> operator/(const hvector<dim,T>& a, const T& b){
        hvector<dim,T> res;
        for(int i=0;i<dim;i++){
            res[i]=a[i]/b;
        }
        return res;
    }

    // --------------------------------------------------------------------------------------------------------------------------------
    // Some more usefull operations on vectors
    // --------------------------------------------------------------------------------------------------------------------------------
    template<int dim, class T>
    T mod(const hvector<dim,T> &v){
        T sum = 0;
        for(int i=0;i<dim;i++){
            sum += pow2(v[i]);
        }
        return std::sqrt(sum);
    }
    template<int dim, class T>
    void normalize(hvector<dim,T> &v){
        T norm = mod(v);
        for(int i=0;i<dim;i++){
            v[i]/=norm;
        }
    }
    template<int dim, class T>
    T dot(const hvector<dim,T> &a, const hvector<dim,T> &b){
        T dot = 0;
        for(int i=0;i<dim;i++){
            dot += a[i]*b[i];
        }
        return dot;
    }

    // --------------------------------------------------------------------------------------------------------------------------------
    // Definition of 2D vectors
    // --------------------------------------------------------------------------------------------------------------------------------

    template<class T>
    using vec2 = hvector<2,T>;

    // cross product defined for all 2 dimentional vectors
    template<class T>
    T cross(const vec2<T>& a, const vec2<T>& b){
        return a[0]*b[1] - b[0]*a[1];
    }

    using int2 = vec2<int>;
    using float2 = vec2<float>;
    using double2 = vec2<double>;

    // --------------------------------------------------------------------------------------------------------------------------------
    // Definition of 3D vectors
    // --------------------------------------------------------------------------------------------------------------------------------
    template<class T>
    using vec3 = hvector<3,T>;
    using int3 = vec3<int>;
    using float3 = vec3<float>;
    using double3 = vec3<double>;

    // --------------------------------------------------------------------------------------------------------------------------------
    // Definition of 4D vectors
    // --------------------------------------------------------------------------------------------------------------------------------
    template<class T>
    using vec4 = hvector<4,T>;
    using int4 = vec4<int>;
    using float4 = vec4<float>;
    using double4 = vec4<double>;

    // --------------------------------------------------------------------------------------------------------------------------------
    // A matrix with m rows and n columns
    // Implementation based on hvector, and very similar to it
    // --------------------------------------------------------------------------------------------------------------------------------
    template<int m, int n, class T>
    struct hmatrix {
        hvector<n,T> coord[m];
        const hvector<n,T>& operator[](const unsigned int i) const {
            return coord[i];
        }
        hvector<n,T>& operator[](const unsigned int i) {
            return coord[i];
        }
        template<class E>
        hmatrix<m,n,T>& operator+=(const hmatrix<m,n,E>& o){
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    coord[i][j]+=(T)o[i][j];
                }
            }
            return *this;
        }
        template<class E>
        hmatrix<m,n,T>& operator-=(const hmatrix<m,n,E>& o){
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    coord[i][j]-=(T)o[i][j];
                }
            }
            return *this;
        }
        template<class E>
        hmatrix<m,n,T>& operator*=(const E& a){
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    coord[i][j]*=(T)a;
                }
            }
            return *this;
        }
        template<class E>
        hmatrix<m,n,T>& operator/=(const E& a){
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    coord[i][j]/=(T)a;
                }
            }
            return *this;
        }
    };
}