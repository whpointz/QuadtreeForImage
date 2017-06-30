/**
 *    > Author:   whpointz
 *    > Mail:     506273980@qq.com
 *    > Github:   https://www.github.com/whpointz
 *    > Description:
 *
 *    > Created Time: 2017/06/24 14:00:17
**/

#ifndef _POINT_HPP_
#define _POINT_HPP_

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"


class Ponit2D
{
public:

	glm::vec2 position_;
	glm::vec3 color_;

	Ponit2D(const glm::vec2 &position, const glm::vec3 &color) :position_(position), color_(color){}
	Ponit2D(const glm::vec2 &position) :position_(position), color_(glm::vec3(0.0)){}

	void print(){ 
		printf("(%d %d):(%d %d %d)\n",position_.x,position_.y,color_.x,color_.y,color_.z);
	}
};





#endif /* _POINT_HPP_ */