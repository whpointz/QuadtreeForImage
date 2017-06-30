/**
 *    > Author:   whpointz
 *    > Mail:     506273980@qq.com
 *    > Github:   https://www.github.com/whpointz
 *    > Description:
 *
 *    > Created Time: 2017/06/24 13:56:56
**/


#ifndef _OCTREE_HPP_
#define _OCTREE_HPP_


#include "constants.hpp"

// Struct data of TreeNode
template<class T>
struct OctreeNode
{
	glm::vec3 _data;//position 
	T _min;//left top node 
	T _max;//right bottom node

	OctreeNode<T>* _children[4]; //0 1 2 3 . the 4 children node in this Parent's node

	OctreeNode(){
		_data = glm::vec3(0, 0, 0);
		for (int i = 0; i < 4; i++){
			_children[i] = 0;
		}
	}
	~OctreeNode(){
		if (_children[i])
		{
			delete _children[i];
		}
	}

};


template<class T>
class Octree_
{

private:
	OctreeNode<T>* _root;

public:
	Octree_(const T& min, const T &max) :_min(min), _max(max), _root(0){}
	Octree_() :_root(0){}

	~Octree_(){ delete _root; }

	OctreeNode<T>* BuildTree(OctreeNode<T>* &root, int maxdepth, T min, T max){
		maxdepth = maxdepth - 1;
		if (maxdepth>=0){
			root = new OctreeNode<T>();
			T mid = T ((min.x + max.x) / 2, (min.y + max.y) / 2);

			BuildTree(root->_children[0], maxdepth, min, mid);
			BuildTree(root->_children[1], maxdepth, T(mid.x, min.y), T(max.x, mid.y));
			BuildTree(root->_children[2], maxdepth, T(min.x, mid.y), T(mid.x, max.y));
			BuildTree(root->_children[3], maxdepth, mid, max);

			if (root->_children[0]!=0)
			{
				root->_data.x = (root->_children[0]->_data.x + root->_children[1]->_data.x + root->_children[2]->_data.x + root->_children[3]->_data.x) / 4;
				root->_data.y = (root->_children[0]->_data.y + root->_children[1]->_data.y + root->_children[2]->_data.y + root->_children[3]->_data.y) / 4;
				root->_data.z = (root->_children[0]->_data.z + root->_children[1]->_data.z + root->_children[2]->_data.z + root->_children[3]->_data.z) / 4;
			}
			else
			{
				//cout << glm::to_string(min) << " " << glm::to_string(max) << endl;
				Mat my_mat(logo, Rect(int(min.x), int(min.y), int(max.x) - int(min.x), int(max.y) - int(min.y)));
				//printf("%d %d\n", my_mat.cols, my_mat.rows);
				//imshow("mylogo", my_mat);
				//waitKey();
				Mat channels[3];
 				split(my_mat, channels);
 				root->_data.x = mean(channels[0]).val[0];
 				root->_data.y = mean(channels[1]).val[0];
 				root->_data.z = mean(channels[2]).val[0];
				//cout << glm::to_string(root->_data) << endl<<endl;
			}
			


			root->_max = max;
			root->_min = min;
		}
		return root;
	}
	
};


typedef  OctreeNode<glm::vec2>	OctreeNode2d;

typedef  Octree_<glm::vec2>	Octree2d;



#endif /* _OCTREE_HPP_ */

