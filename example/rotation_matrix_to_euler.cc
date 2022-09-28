#include "opencv2/opencv.hpp"
#include <opencv2/core/mat.hpp>

// Checks if a matrix is a valid rotation matrix.
bool isRotationMatrix(cv::Mat &R)
{
	cv::Mat Rt;
	transpose(R, Rt);
	cv::Mat shouldBeIdentity = Rt * R;
	cv::Mat I = cv::Mat::eye(3,3, shouldBeIdentity.type());

	printf("norm %.5f\n",norm(I, shouldBeIdentity));
	return  norm(I, shouldBeIdentity) < 0.2;

}

// Calculates rotation matrix to euler angles
// The result is the same as MATLAB except the order
// of the euler angles ( x and z are swapped ).
cv::Vec3f rotationMatrixToEulerAngles()
{

	/*
m44[0,0]=0.99
m44[0,1]=-0.11
m44[0,2]=-0.04
m44[1,0]=0.11
m44[1,1]=0.99
m44[1,2]=0.07
m44[2,0]=0.03
m44[2,1]=-0.07
m44[2,2]=1.00
*/

	cv::Mat R = (cv::Mat_<double>(3,3) << 0.99,-0.11,-0.04,0.11,0.99,0.07,0.03,-0.07,1.00);
    //cout << "R = " << endl << " " << R << endl ;
	//cv::Mat &R

	assert(isRotationMatrix(R));

	float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

	bool singular = sy < 1e-6; // If

	float x, y, z;
	if (!singular)
	{
		x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
		y = atan2(-R.at<double>(2,0), sy);
		z = atan2(R.at<double>(1,0), R.at<double>(0,0));
	}
	else
	{
		x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
		y = atan2(-R.at<double>(2,0), sy);
		z = 0;
	}
	printf("%.2f,%.2f,%.2f\n",x,y,z);
	return cv::Vec3f(x, y, z);
}

int main(){
	rotationMatrixToEulerAngles();
}
