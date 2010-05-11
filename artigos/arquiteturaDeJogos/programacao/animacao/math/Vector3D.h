/* Vinícius Godoy de Mendonça */
#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

namespace math
{
	class Vector2D;

    /**
        This class represents a 3 coordinate space mathematical vector.
        All operations expected for a vector, like sum, subtraction, product,
        cross product, dot product and normalization are provided.

        The class also provides useful interoperability with Vector2D class.
    */
    class Vector3D
    {
    private:
        float   x;
        float   y;
        float   z;

    public:
        /** Creates a new null vector 3D */
        explicit Vector3D();

        /** Create a new vector 3D based on the given values.
        @param _x x coordinate
        @param _y y coordinate
        @param _z z coordinate
        */
        explicit Vector3D(float _x, float _y, float _z);

        /**
          Creates a new Vector3D using the x and y coordinates
          from the given Vector2D and the given z coordinate.
          @param Vector2D& A 2D vector
          @param z A z coordinate.
        */
        explicit Vector3D(const Vector2D& other, float _z);

        /**
            Creates a new Vector3D using the x and y coordinates
            from the given Vector2D and applying 0 in the Z coordinate
            @param Vector2D& A 2D vector
        */
        explicit Vector3D(const Vector2D& other);

        /**
            Creates a new Vector3D from the given array. The coordinates
            will be mapped as following. Index 0 as x, index 1 as y and
            index 2 as z
            @param xyz An array containing the x, y, z coordinates
        */
        explicit Vector3D(float xyz[3]);

        /** @return the X coordinate */
        inline float getX() const
        {
            return x;
        }

        /** @return the Y coordinate */
        inline float getY() const
        {
            return y;
        }

        /** @return the Z coordinate */
        inline float getZ() const
        {
            return z;
        }

        /**
            Changes the x coordinate.
            This method was kept void for efficient inlining.
            @param _x x coordinate.
        */
        inline void setX(float _x)
        {
            x = _x;
        };

        /**
            Changes the y coordinate.
            This method was kept void for efficient inlining.
            @param _y y coordinate.
        */
        inline void setY(float _y)
        {
            y = _y;
        };

        /**
            Changes the z coordinate.
            This method was kept void for efficient inlining.
            @param _z z coordinate.
        */
        inline void setZ(float _z)
        {
            z = _z;
        };

        /**
            Adds to x coordinate
            @param _x The amount to add in x
            @return This vector.
        */
        Vector3D& addX(float _x);

        /**
            Adds to y coordinate
            @param _y The amount to add in y
            @return This vector.
        */
        Vector3D& addY(float _y);

        /**
            Adds to z coordinate
            @param _z The amount to add in z
            @return This vector.
        */
        Vector3D& addZ(float _z);

        /**
            Adds to all vector coordinates

            @param _x The amount to add in x
            @param _y The amount to add in y
            @param _z The amount to add in z

            @return This vector.
        */
        Vector3D& add(float _x, float _y, float _z);

        /**
            Sets the x, y and z coordinates in one single operation.

            @param _x The x coordinate
            @param _y The y coordinate
            @param _z The z coordinate
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D& set(float _x, float _y, float _z);

        /**
            Sets the x, y and z coordinates in one single operation. The
            coordinates will be mapped as following. Array index 0 as x,
            index 1 as y and index 2 as z

            @param xyz An array containing the x, y, z coordinates
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D& set(const float xyz[3]);

        /**
            Sets the x, y and z coordinates in one single operation.
            The x and y coordinates will be taken from the given Vector2D.

            @param Vector2D& A 2D vector
            @param z A z coordinate.
        */
        Vector3D& set(const Vector2D& v, float _z);

        /**
            Allows write access to the vector coordinates as if was
            an array containing the x in index 0, y in index 1
            and z in index 2. No bounds check are made, so be careful.
            @param k The coordinate index. As descrived above.
        */
        float& operator [](long k);

        /**
            Allows read access to the vector coordinates as if was
            an array containing the x in index 0, y in index 1
            and z in index 2. No bounds check are made, so be careful.
            @param k The coordinate index. As descrived above.
        */
        const float& operator [](long k) const;

        /** Assigns the value from the other Vector3D in this Vector3D.*/
        Vector3D& operator =(const Vector2D& other);

        /** Assignment operator. z will be assigned to 0. */
        Vector3D& operator +=(const Vector3D& other);

        /** Adds the given Vector3D values to this vector */
        Vector3D& operator +=(const Vector2D& other);

        /** Subtracts this Vector3D from the given vector */
        Vector3D& operator -=(const Vector3D& other);

        /**
            Subtracts this Vector2D from the given vector.
            Z coordinate will be left unchanged.
        */
        Vector3D& operator -=(const Vector2D& other);

        /** Multiplies this vector by the given scalar constant. */
        Vector3D& operator *=(float c);

        /** Divides this vector by the given vector */
        Vector3D& operator /=(float c);

        /** Creates a new Vector that is the negation of this one. */
        Vector3D operator -(void) const;
        /** Creates a new vector with the sum of this and the given one.*/
        Vector3D operator +(const Vector3D& other) const;
        /**
            Creates a new vector with the sum of this and the given one.
            The z coordinate will remain equal to this vector z coordinate.
        */
        Vector3D operator +(const Vector2D& other) const;

        /** Creates a new vector with the subtraction of this and the given
            one.*/
        Vector3D operator -(const Vector3D& other) const;

        /**
            Creates a new vector with the subtraction of this and the given one
            The z coordinate will remain equal to this vector z coordinate.
        */
        Vector3D operator -(const Vector2D& other) const;

        /** Creates a new vector with the product of this vector and the given
            scalar constant.*/
        Vector3D operator *(float c) const;

        /** Creates a new vector with the division of this vector and the given
            scalar constant.*/
        Vector3D operator /(float c) const;

        /** Creates a new vector with the product of this vector and the given
            one.*/
        Vector3D operator *(const Vector3D& other) const;

        /** Test if two vectors are equal */
        bool operator ==(const Vector3D& other) const;

        /** Test if two vectors are different */
        bool operator !=(const Vector3D& other) const;

        /** @return the size (magnitude) of this vector squared */
        float getSizeSqr() const;

        /** @return the size (magnitude) of this vector */
        float getSize() const;

        /** Sets the size (magnitude) of this vector */
        Vector3D& setSize(float size);

        /** Creates a new vector with the cross product from this vector and
            the given one.
            @param other The vector that the cross product will be applyed.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D cross(const Vector3D& other) const;

        /** Apply a cross product in this vector with the given vector.
            @param other The vector that will be used in the cross product.
            @return This own vector, modified by the cross product,
                    for invocation chaning.
        */
        Vector3D& applyCross(const Vector3D& other);

        /**
            Applies the dot product of this vector and the other one.
            @return The dot product.
        */
        float dot(const Vector3D& other) const;
        /**
            Applies the dot product of this vector and the other one.
            The z coordinate will be ignored.

            @return The dot product.
        */
        float dot(const Vector2D& other) const;

        /**
            Changes the size of this vector to one.
            Orientation is left unchanged.
        */
        Vector3D& normalize(void);

        /**
            Rotates this vector around the x axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D& rotateX(float angle);

        /**
            Rotates this vector around the y axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D& rotateY(float angle);

        /**
            Rotates this vector around the z axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D& rotateZ(float angle);

        /**
            Rotates this vector around the given axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3D& rotateAxis(float angle, const Vector3D& axis);
    };
}
#endif // VECTOR3D_H_INCLUDED
