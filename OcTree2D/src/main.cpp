/**
 *    > Author:   whpointz
 *    > Mail:     506273980@qq.com
 *    > Github:   https://www.github.com/whpointz
 *    > Description:
 *
 *    > Created Time: 2017/06/24 13:30:54
 **/

// OpenCv 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//Octree
#include "Octree.hpp"

//IO
#include <iostream>
#include <queue>
using namespace std;


int main()
{
	QuadTree* Octree_zwh = new QuadTree;
	Octree_zwh->image_data = logo;

	printf("Start build the tree!\n");
	QuadTreeNode* Root = Octree_zwh->BuildTree(Depth, glm::vec2(0, 0), glm::vec2(Octree_zwh->image_data.cols, Octree_zwh->image_data.rows));
	printf("Build the Tree end!\n");

	//a new mat to store the ans
	char imagename[10];
	sprintf_s(imagename, "ans%d.jpg", Depth);
	Mat ans = logo.clone();

	//out all the data in the Octreel
	queue<QuadTreeNode*> S;
	S.push(Root);
	while (!S.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			if (S.front()->_children[i] != nullptr)
				S.push(S.front()->_children[i]);
		}

		//if the node is the leaf node , update the ans image. 
		//using the data: _min _max _data
		if (S.front()->_children[0] == nullptr)
		{
			for (int i = S.front()->_min.x; i < S.front()->_max.x; i++)
			{
				for (int j = S.front()->_min.y; j < S.front()->_max.y; j++)
				{
					if (i >= 0 && i < ans.cols && j >= 0 && j < ans.rows)
					{
						ans.at<Vec3b>(j, i)[0] = S.front()->_data.x;
						ans.at<Vec3b>(j, i)[1] = S.front()->_data.y;
						ans.at<Vec3b>(j, i)[2] = S.front()->_data.z;
					}
				}
			}
			//cout << glm::to_string(S.front()->_min) << " " << glm::to_string(S.front()->_max) << " " << glm::to_string(S.front()->_data) << endl;
		}
		S.pop();
	}
	printf("update ans mat end!\n");
	//save the ans mat
	imwrite(imagename, ans);
	//imshow("logo", logo);
	//waitKey();
}
