#include <math/vec3.h>

lux::vec3::vec3() : data{} {}

lux::vec3::vec3(double val) : data{ val, val , val } {}

lux::vec3::vec3(double x, double y, double z) : data{ x,y,z } {}

lux::vec3::vec3(double vals[3]) : data{vals[0], vals[1], vals[2]} {}

double lux::vec3::x() const
{
	return data[0];
}

double lux::vec3::y() const
{
	return data[1];
}

double lux::vec3::z() const
{
	return data[2];
}

double lux::vec3::r() const
{
	return data[0];
}

double lux::vec3::g() const
{
	return data[1];
}

double lux::vec3::b() const
{
	return data[2];
}

lux::vec3 lux::vec3::operator-() const
{
	return vec3(-data[0], -data[1], -data[2]);
}

lux::vec3 lux::vec3::operator+(vec3 const& rhs) const
{
	return vec3(data[0] + rhs.data[0], data[1] + rhs.data[1], data[2] + rhs.data[2]);
}

lux::vec3 lux::vec3::operator-(vec3 const& rhs) const
{
	return vec3(data[0] - rhs.data[0], data[1] - rhs.data[1], data[2] - rhs.data[2]);
}

lux::vec3 lux::vec3::operator*(vec3 const& rhs) const
{
	return vec3(data[0] * rhs.data[0], data[1] * rhs.data[1], data[2] * rhs.data[2]);
}

lux::vec3 lux::vec3::operator/(vec3 const& rhs) const
{
	return vec3(data[0] / rhs.data[0], data[1] / rhs.data[1], data[2] / rhs.data[2]);
}

lux::vec3& lux::vec3::operator+=(vec3 const& rhs)
{
	data[0] += rhs.data[0];
	data[1] += rhs.data[1];
	data[2] += rhs.data[2];
	return *this;
}

lux::vec3& lux::vec3::operator-=(vec3 const& rhs)
{
	data[0] -= rhs.data[0];
	data[1] -= rhs.data[1];
	data[2] -= rhs.data[2];
	return *this;
}

lux::vec3& lux::vec3::operator*=(vec3 const& rhs)
{
	data[0] *= rhs.data[0];
	data[1] *= rhs.data[1];
	data[2] *= rhs.data[2];
	return *this;
}

lux::vec3& lux::vec3::operator/=(vec3 const& rhs)
{
	data[0] /= rhs.data[0];
	data[1] /= rhs.data[1];
	data[2] /= rhs.data[2];
	return *this;
}

lux::vec3 lux::vec3::operator*(double val) const
{
	return vec3(data[0] * val, data[1] * val, data[2] * val);
}

lux::vec3 lux::vec3::operator/(double val) const
{
	val = 1.0 / val;
	return vec3(data[0] * val, data[1] * val, data[2] * val);
}

lux::vec3& lux::vec3::operator*=(double val)
{
	data[0] *= val;
	data[1] *= val;
	data[2] *= val;
	return *this;
}

lux::vec3& lux::vec3::operator/=(double val)
{
	val = 1.0 / val;
	data[0] *= val;
	data[1] *= val;
	data[2] *= val;
	return *this;
}

bool lux::vec3::operator==(vec3 const& rhs) const
{
	return data[0] == rhs.data[0] && data[1] == rhs.data[1] && data[2] == rhs.data[2];
}

bool lux::vec3::operator!=(vec3 const& rhs) const
{
	return !this->operator==(rhs);
}
