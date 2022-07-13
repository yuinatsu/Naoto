//#include "Vector2.h"

//--------------------------------------------------------------------------
//●座標の初期化
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
//●デストラクタ
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>::~Vector2Template()
{
}

//--------------------------------------------------------------------------
//●代入演算子
//--------------------------------------------------------------------------
template<class T> Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return (*this);
}

//--------------------------------------------------------------------------
//●添え字演算子
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
//●単項演算子：Vector2
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
//●単項演算子：int
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

// 自分自身に＋記号を付与する
template<class T> Vector2Template<T> Vector2Template<T>::operator+() const
{
	return (*this);
}

// 自分自身に－記号を付与する
template<class T> Vector2Template<T> Vector2Template<T>::operator-() const
{
	return Vector2Template<T>(-this->x, -this->y);
}

//--------------------------------------------------------------------------
//●比較演算子
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
//●クラス外関数：Vector2 と int
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
//●クラス外関数：Vector2 と Vector2
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
