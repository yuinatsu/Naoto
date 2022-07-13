//#include "Vector2.h"

//--------------------------------------------------------------------------
//�����W�̏�����
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T> Vector2Template<T>::Vector2Template(T x, T y)
{
	Vector2Template<T>::x = x;
	Vector2Template<T>::y = y;
}

//--------------------------------------------------------------------------
//���f�X�g���N�^
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>::~Vector2Template()
{
}

//--------------------------------------------------------------------------
//��������Z�q
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return (*this);
}

//--------------------------------------------------------------------------
//���Y�������Z�q
//--------------------------------------------------------------------------
template<class T> int& Vector2Template<T>::operator[](int no)
{
	if (no == 0)
	{
		return x;
	}
	else if (no == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

//--------------------------------------------------------------------------
//���P�����Z�q�FVector2
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template<T>& vec)
{
	x += vec.x;
	y += vec.y;
	return (*this);
}

template<class T> Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return (*this);
}

template<class T> Vector2Template<T>& Vector2Template<T>::operator*=(const Vector2Template<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
	return (*this);
}

template<class T> Vector2Template<T>& Vector2Template<T>::operator/=(const Vector2Template<T>& vec)
{
	x /= vec.x;
	y /= vec.y;
	return (*this);
}

//--------------------------------------------------------------------------
//���P�����Z�q�Fint
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>& Vector2Template<T>::operator+=(T num)
{
	x += num;
	y += num;
	return (*this);
}

template<class T> Vector2Template<T>& Vector2Template<T>::operator-=(T num)
{
	x -= num;
	y -= num;
	return (*this);
}

template<class T> Vector2Template<T>& Vector2Template<T>::operator*=(T num)
{
	x *= num;
	y *= num;
	return (*this);
}

template<class T> Vector2Template<T>& Vector2Template<T>::operator/=(T num)
{
	x /= num;
	y /= num;
	return (*this);
}

// �������g�Ɂ{�L����t�^����
template<class T> Vector2Template<T> Vector2Template<T>::operator+() const
{
	return (*this);
}

// �������g�Ɂ|�L����t�^����
template<class T> Vector2Template<T> Vector2Template<T>::operator-() const
{
	return Vector2Template<T>(-this->x, -this->y);
}

//--------------------------------------------------------------------------
//����r���Z�q
//--------------------------------------------------------------------------
template<class T> bool Vector2Template<T>::operator==(const Vector2Template<T>& vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

template<class T> bool Vector2Template<T>::operator!=(const Vector2Template<T>& vec) const
{
	return ((x != vec.x) || (y != vec.y));
}

template<class T>
bool Vector2Template<T>::operator<(const Vector2Template<T>& vec) const
{
	return ((x < vec.x) && (y < vec.y));
}

template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template<T>& vec) const
{
	return ((x <= vec.x) && (y <= vec.y));
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template<T>& vec) const
{
	return ((x > vec.x) && (y > vec.y));
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T>& vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

//--------------------------------------------------------------------------
//���N���X�O�֐��FVector2 �� int
//--------------------------------------------------------------------------
template<class T> Vector2Template<T> operator+(const Vector2Template<T>& u, T v)
{
	
	return Vector2Template<T>(u.x + v , u.y + v);
}

template<class T> Vector2Template<T> operator-(const Vector2Template<T>& u, T v)
{
	return Vector2Template<T>(u.x - v, u.y - v);
}

template<class T> Vector2Template<T> operator*(const Vector2Template<T>& u, T v)
{
	return Vector2Template<T>(u.x * v, u.y * v);
}

template<class T> Vector2Template<T> operator/(const Vector2Template<T>& u, T v)
{
	return Vector2Template<T>(u.x / v, u.y / v);
}

template<class T> Vector2Template<T> operator%(const Vector2Template<T>& u, int v)
{
	return Vector2Template<T>(u.x % v, u.y % v);
}

//--------------------------------------------------------------------------
//���N���X�O�֐��FVector2 �� Vector2
//--------------------------------------------------------------------------
template<class T> Vector2Template<T> operator+(const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	return Vector2Template<T>(u.x + v.x , u.y + v.y);
}

template<class T> Vector2Template<T> operator-(const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	return Vector2Template<T>(u.x - v.x , u.y - v.y);
}

template<class T> Vector2Template<T> operator*(const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	return Vector2Template<T>(u.x * v.x, u.y * v.y);
}

template<class T> Vector2Template<T> operator/(const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	return Vector2Template<T>(u.x / v.x, u.y / v.y);
}

template<class T> Vector2Template<T> operator%(const Vector2Template<T>& u, const Vector2Template<T>& v)
{
	return Vector2Template<T>(u.x % v.x, u.y % v.y);
}
