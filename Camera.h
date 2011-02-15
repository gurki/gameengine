//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _CAMERA_H
#define _CAMERA_H

#include "PivotObject3.h"

class Camera : public PivotObject3
{
	public:
		
		Camera(void);
		Camera(const vec3& position, const quat& rotation, const vec3& pivot);
		
		void SetOrthographic(void);
		void SetProjective(void);
		
	private:


};

#endif