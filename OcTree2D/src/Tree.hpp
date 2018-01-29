/**
 *    > Author:   whpointz
 *    > Mail:     506273980@qq.com
 *    > Github:   https://www.github.com/whpointz
 *    > Description:
 *
 *    > Created Time: 2017/06/24 13:56:56
 **/


#ifndef _TREE_HPP_
#define _TREE_HPP_


#include "constants.hpp"

// Struct data of TreeNode
template <class T,int Child_num>
struct TreeNode
{
	glm::vec3 _data;//color
	T _min;//left top node 
	T _max;//right bottom node

	TreeNode<T, Child_num>* _children[Child_num]; //0 1 2 3 . the 4 children node in this Parent's node

	TreeNode()
	{
		_data = glm::vec3(0, 0, 0);
		for (auto i = 0; i < Child_num; i++)
		{
			_children[i] = NULL;
		}
	}

	~TreeNode()
	{
		for (int i = 0; i < Child_num; i++)
		{
			delete _children[i];
		}
	}
};

//Class of the Tree
template <class T, int Child_num>
class Tree
{
public:
	Tree() : _root(nullptr)
	{
	}

	~Tree()
	{
		delete _root;
	}


	//Build the Tree
	TreeNode<T, Child_num>* BuildTree(int depth, T min, T max)
	{
		depth = depth - 1;

		//返回空指针
		if (depth < 0) return nullptr;

		//构造root元素，根据四个子树来更新root
		TreeNode<T, Child_num>* root = new TreeNode<T, Child_num>;
		T mid = T((min.x + max.x) / 2, (min.y + max.y) / 2);

		//更新max min
		root->_max = max;
		root->_min = min;

		//更新四个子树
		root->_children[0] = BuildTree(depth, min, mid);
		root->_children[1] = BuildTree(depth, T(mid.x, min.y), T(max.x, mid.y));
		root->_children[2] = BuildTree(depth, T(min.x, mid.y), T(mid.x, max.y));
		root->_children[3] = BuildTree(depth, mid, max);

		//更新data
		if (root->_children[0] != NULL)
		{
			//the root data is the average num of the 4 children's data.
			root->_data.x = (root->_children[0]->_data.x + root->_children[1]->_data.x + root->_children[2]->_data.x + root->_children[3]->_data.x) / 4;
			root->_data.y = (root->_children[0]->_data.y + root->_children[1]->_data.y + root->_children[2]->_data.y + root->_children[3]->_data.y) / 4;
			root->_data.z = (root->_children[0]->_data.z + root->_children[1]->_data.z + root->_children[2]->_data.z + root->_children[3]->_data.z) / 4;
		}
		else
		{
			Mat my_mat(image_data, Rect(int(min.x), int(min.y), int(max.x) - int(min.x), int(max.y) - int(min.y)));//(beginx beginy lenx leny)
			Mat channels[3];
			split(my_mat, channels);//get the 3 channels of the Rect and RGB is the mean of the different channels of the Rect
			root->_data.x = mean(channels[0]).val[0];//求取算术平均值
			root->_data.y = mean(channels[1]).val[0];
			root->_data.z = mean(channels[2]).val[0];
			//cout << glm::to_string(root->_data) << endl<<endl;
		}
		return root;
	}

	TreeNode<T, Child_num>* _root;
	Mat image_data;
};


typedef TreeNode<glm::vec2,4> QuadTreeNode;

typedef Tree<glm::vec2,4> QuadTree;


#endif /* _TREE_HPP_ */

