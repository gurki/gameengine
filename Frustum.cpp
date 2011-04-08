//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Frustum.h"

Frustum::Frustum(void)
{
	left =-0.5f;
	right = 0.5f;
	
	top =-0.5f;
	bottom = 0.5f;

	near = 0.0f;
	far = 1.0f;
}

Frustum::Frustum(real left, real right, real top, real bottom, real near, real far)
{
	this->left = left;
	this->right = right;

	this->top = top;
	this->bottom = bottom;
	 
	this->near = near;
	this->far = far;
}