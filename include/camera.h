#ifndef CAMERA_H_
#define CAMERA_H_

#include <string.h>

namespace domain {
class Camera {
protected:
	float pos[3];
	float up[3];
	float at[3];

public:
	Camera();
	virtual ~Camera();
	float* getPos();
	float* getAtVector();
	virtual void update() = 0;
	virtual void load() = 0;

};

}

#endif /* CAMERA_H_ */
