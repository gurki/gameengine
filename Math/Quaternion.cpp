//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Quaternion.h"
#include "Matrix4x4.h"

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion::Quaternion(void)
{
	*this = Identity();
}

Quaternion::Quaternion(real w, const vec3& v)
{
	this->w = w;
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Quaternion::Quaternion(real w, real x, real y, real z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//
		 
void Quaternion::operator = (const Quaternion& quat)
{
	w = quat.w;
	x = quat.x;
	y = quat.y;
	z = quat.z;
}

bool Quaternion::operator == (const Quaternion& q) const
{
	return w == q.w && x == q.x && y == q.y && z == q.z;
}

bool Quaternion::operator != (const Quaternion& q) const
{
	return w != q.w || x != q.x || y != q.y || z != q.z;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion Quaternion::operator * (real n) const
{
	Quaternion q;

	q.w = w * n;
	q.x = x * n;
	q.y = y * n;
	q.z = z * n;

	return q;
}

Quaternion Quaternion::operator / (real n) const
{
	Quaternion q;

	q.w = w / n;
	q.x = x / n;
	q.y = y / n;
	q.z = z / n;

	return q;
}

Quaternion& Quaternion::operator *= (real n)
{
	w *= n;
	x *= n;
	y *= n;
	z *= n;

	return *this;
}

Quaternion& Quaternion::operator /= (real n)
{
	w /= n;
	x /= n;
	y /= n;
	z /= n;

	return *this;
}

Quaternion operator * (real n, const Quaternion& quat)
{
	Quaternion q;

	q.w = quat.w * n;
	q.x = quat.x * n;
	q.y = quat.y * n;
	q.z = quat.z * n;

	return q;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

vec3 Quaternion::operator * (const vec3& vec) const
{
	Quaternion vecQuat, resQuat;

	vecQuat.w = 0.0f;
	vecQuat.x = vec.x;
	vecQuat.y = vec.y;
	vecQuat.z = vec.z;
 
	resQuat = ((*this) * vecQuat) * Conjugated();
 
	return vec3(resQuat.x, resQuat.y, resQuat.z);
}

vec3 operator * (const vec3& vec, const Quaternion& q)
{
	Quaternion vecQuat, resQuat;

	vecQuat.w = 0.0f;
	vecQuat.x = vec.x;
	vecQuat.y = vec.y;
	vecQuat.z = vec.z;

	resQuat = (q * vecQuat) * q.Conjugated();
 
	return vec3(resQuat.x, resQuat.y, resQuat.z);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion Quaternion::operator + (const Quaternion& quat) const
{
	Quaternion q;

	q.w = w + quat.w;
	q.x = x + quat.x;
	q.y = y + quat.y;
	q.z = z + quat.z;
			
	return q;
}

Quaternion Quaternion::operator - (const Quaternion& quat) const
{
	Quaternion q;

	q.w = w - quat.w;
	q.x = x - quat.x;
	q.y = y - quat.y;
	q.z = z - quat.z;
					
	return q;
}

Quaternion Quaternion::operator * (const Quaternion& quat) const
{
	Quaternion q;

	q.w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
	q.x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
	q.y = w * quat.y - x * quat.z + y * quat.w + z * quat.x;
	q.z = w * quat.z + x * quat.y - y * quat.x + z * quat.w;
	
	return q;
}

Quaternion& Quaternion::operator += (const Quaternion& quat)
{
	w += quat.w;
	x += quat.x;
	y += quat.y;
	z += quat.z;

	return *this;
}

Quaternion& Quaternion::operator -= (const Quaternion& quat)
{
	w -= quat.w;
	x -= quat.x;
	y -= quat.y;
	z -= quat.z;
		
	return *this;
}

Quaternion& Quaternion::operator *= (const Quaternion& quat)
{
	w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
   	x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
	y = w * quat.y - x * quat.z + y * quat.w + z * quat.x;
	z = w * quat.z + x * quat.y - y * quat.x + z * quat.w;

	return *this;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion& Quaternion::Normalise(void)
{
	real n = w * w + x * x + y * y + z * z;

	if(n == 0.0 || n == 1.0)
	{
		return * this;
	}

	n = sqrtr(n);

	w /= n;
	x /= n;
	y /= n;
	z /= n;

	return *this;
}

Quaternion Quaternion::Normalised(void) const
{
	real n = w * w + x * x + y * y + z * z;

	if(n == 0.0 || n == 1.0)
	{
		return *this;
	}

	Quaternion q = *this;

	n = sqrtr(n);

	q.w /= n;
	q.x /= n;
	q.y /= n;
	q.z /= n;

	return q;
}

Quaternion& Quaternion::Conjugate(void)
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

Quaternion Quaternion::Conjugated(void) const
{
	return Quaternion(w, -x,-y,-z);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion Quaternion::WithAxisAngle(const vec3& axis, real radians)
{
	Quaternion q;

	real a = 0.5f * radians;
	real s = sinr(a);
	
	vec3 v = axis;

	v.Normalise();

	q.w = cosr(a);
	q.x = v.x * s;
	q.y = v.y * s;
	q.z = v.z * s;

	return q;
}

Quaternion Quaternion::WithEulerAngles(real yaw, real pitch, real roll)
{
	Quaternion q;

	real y = 0.5f * yaw;
	real r = 0.5f * roll;
	real p = 0.5f * pitch;

	real siny = sinr(y);
	real sinr = sinr(r);
	real sinp = sinr(p);

	real cosy = cosr(y);
	real cosr = cosr(r);
	real cosp = cosr(p);

	q.w = cosy * cosp * cosr + siny * sinp * sinr;   
    q.x = cosy * sinp * cosr + siny * cosp * sinr;   
    q.y = siny * cosp * cosr - cosy * sinp * sinr;   
    q.z = cosy * cosp * sinr - siny * sinp * cosr;   
	/*
	q.w = cosy * cosr * cosp - siny * sinr * sinp;
	q.x = siny * sinr * cosp + cosy * cosr * sinp;
	q.y = siny * cosr * cosp + cosy * sinr * sinp;
	q.z = cosy * sinr * cosp - siny * cosr * sinp;
	*/
	return q;
}

Quaternion Quaternion::WithFromToOrientations(const vec3& from, const vec3& to)
{
	Quaternion q;

	vec3 f = from;
	vec3 t = to;

	f.Normalise();
	t.Normalise();

	vec3 n = t.Cross(f);

	q.w = 0.5f * t.Dot(f);

	real s = sinr(acosr(q.w));

	q.x = n.x * s;
	q.y = n.y * s;
	q.z = n.z * s;

	return q;
}

Quaternion Quaternion::WithOrientation(const vec3& orientation)
{
	 /*
	 // Step 1. Setup basis vectors describing the rotation given the input vector and assuming an initial up direction of (0, 1, 0)
	Vector3 vForward = orientation.Normalised();
    Vector3 vUp = Vector3(0, 1.0f, 0.0f);           // Y Up vector
    Vector3 vRight = vForward.Cross(vForward);    // The perpendicular vector to Up and Direction
    vUp = vForward.Cross(vRight);            // The actual up vector given the direction and the right vector
            
    // Step 2. Put the three vectors into the matrix to bulid a basis rotation matrix
    // This step isnt necessary, but im adding it because often you would want to convert from matricies to quaternions instead of vectors to quaternions
    // If you want to skip this step, you can use the vector values directly in the quaternion setup below
    Matrix4x4 mBasis = Matrix4x4(vRight.x, vRight.y, vRight.z, 0.0f,
                                vUp.x, vUp.y, vUp.z, 0.0f,
                                vForward.x, vForward.y, vForward.z, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);
            
    // Step 3. Build a quaternion from the matrix
    Quaternion qrot = Quaternion();
    qrot.w = (float)sqrt(1.0f + mBasis.m11 + mBasis.m22 + mBasis.m33) / 2.0f;
    double dfWScale = qrot.w * 4.0;
    qrot.x = (float)((mBasis.m32 - mBasis.m23) / dfWScale);
    qrot.y = (float)((mBasis.m13 - mBasis.m31) / dfWScale);
    qrot.z = (float)((mBasis.m21 - mBasis.m12) / dfWScale);

    return qrot;
	*/
	Quaternion q;

	vec3 f = vec3::Forward();
	vec3 t = orientation;

	t.Normalise();

	vec3 n = t.Cross(f);

	q.w = 0.5f * t.Dot(f);

	real s = sinr(acosr(q.w));

	q.x = n.x * s;
	q.y = n.y * s;
	q.z = n.z * s;

	return q;
}

Quaternion Quaternion::WithRotationAboutX(real radians)
{
	Quaternion q;

	real w = 0.5f * radians;
	
	q.w = cosr(w);
	q.x = sinr(w);
	q.y = 0.0;
	q.z = 0.0;

	return q;
}

Quaternion Quaternion::WithRotationAboutY(real radians)
{
	Quaternion q;

	real w = 0.5f * radians;

	q.w = cosr(w);
	q.x = 0.0;
	q.y = sinr(w);
	q.z = 0.0;

	return q;
}

Quaternion Quaternion::WithRotationAboutZ(real radians)
{
	Quaternion q;

	real w = 0.5f * radians;

	q.w = cosr(w);
	q.x = 0.0;
	q.y = 0.0;
	q.z = sinr(w);

	return q;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

vec3 Quaternion::GetOrientation(void) const
{
	return (*this) * vec3::Forward();
}

AxisAngle Quaternion::GetAxisAngle(void) const
{
	AxisAngle axisangle;

	axisangle.axis = vec3(x, y, z);
	axisangle.angle = acosr(w) * 2.0f;

	return axisangle;
}

EulerAngles Quaternion::GetEulerAngles(void) const
{
	EulerAngles eulerangles;

	eulerangles.yaw = atan2r(2.0 * (w * x + y * z), 1.0 - 2.0 * (z * z + x * x));
	eulerangles.pitch = asinr(2.0 * (w * z - y * x));
	eulerangles.roll = atan2r(2.0 * (w * y + z * x), 1.0 - 2.0 * (y * y + z * z));
	
	return eulerangles;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

ostream& operator << (ostream& out, const Quaternion& q)
{
	out << "{" << q.w << ", (" << q.x << ", " << q.y << ", " << q.z << ")}";

	return out;
}

istream& operator >> (istream& in, Quaternion& q)
{
	real w, x, y, z;

	in >> w >> x >> y >> z;

	q = Quaternion(w, x, y, z);

	q.Normalise();

	return in;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

const Quaternion Quaternion::Zero(void)
{
	static const Quaternion q(0, 0, 0, 0);
	return q;
}

const Quaternion Quaternion::Identity(void)
{
	static const Quaternion q(1, 0, 0, 0);
	return q;
}