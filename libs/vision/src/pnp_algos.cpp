/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include <mrpt/vision/pnp_algos.h>

#include <iostream>
using namespace std;

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
using namespace Eigen;

#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
using namespace cv;

#include <mrpt/vision/epnp.h>
#include <mrpt/vision/dls.h>
#include <mrpt/vision/upnp.h>

template<typename Derived>
int pnpalgo_dls(MatrixBase<Derived>& obj_pts, MatrixBase<Derived>& img_pts, int n, MatrixBase<Derived>& cam_intrinsic, MatrixBase<Derived>& pose_mat){
	
	MatrixXd cam_in_eig=cam_intrinsic.array().transpose(), img_pts_eig=img_pts.array().transpose(), obj_pts_eig=obj_pts.array().transpose(), t_eig;
	Matrix3d R_eig; 
	Mat cam_in_cv(3,3,CV_32F), img_pts_cv(2,n,CV_32F), obj_pts_cv(3,n,CV_32F), R_cv(3,3,CV_32F), t_cv(3,1,CV_32F);
	
	//cout<<"cam_in="<<endl<<cam_in_eig<<endl<<endl;
	//cout<<"obj_pts="<<endl<<obj_pts_eig<<endl<<endl;
	//cout<<"img_pts="<<endl<<img_pts_eig<<endl<<endl;
	
	eigen2cv(cam_in_eig, cam_in_cv);
	eigen2cv(img_pts_eig, img_pts_cv);
	eigen2cv(obj_pts_eig, obj_pts_cv);
	
	//cout<<cam_in_cv<<endl;
	//cout<<img_pts_cv<<endl;
	//cout<<obj_pts_cv<<endl;
	
	dls d(obj_pts_cv, img_pts_cv);
	d.compute_pose(R_cv,t_cv);
	
	//cout<<R_cv<<endl;
	//cout<<t_cv<<endl;
	
	cv2eigen(R_cv, R_eig);
	cv2eigen(t_cv, t_eig);
	
	//cout<<"R_eig="<<endl<<R_eig<<endl<<endl;
	//cout<<"t_eig="<<endl<<t_eig<<endl<<endl;
	
	Quaterniond q(R_eig);
	
	pose_mat << t_eig,q.vec();
	
	//pose_mat.block(0,0,3,3)=R_eig;
	//pose_mat.block(0,3,3,1)=t_eig;
	//pose_mat.row(3)<<0,0,0,1;
	//cout<<"t_eig="<<endl<<t_eig<<endl<<endl;
	//cout<<"q_eig="<<endl<<q.vec()<<endl<<endl;
	//cout<<"pose_eig="<<endl<<pose_mat<<endl<<endl;
	//cout<<"pose_cv="<<endl<<R_cv<<endl<<endl;
	
	return 1;
}

template<typename Derived>
int pnpalgo_epnp(MatrixBase<Derived>& obj_pts, MatrixBase<Derived>& img_pts, int n, MatrixBase<Derived>& cam_intrinsic, MatrixBase<Derived>& pose_mat){
	
	MatrixXd cam_in_eig=cam_intrinsic.array().transpose(), img_pts_eig=img_pts.array().transpose(), obj_pts_eig=obj_pts.array().transpose(), t_eig;
	Matrix3d R_eig; 
	Mat cam_in_cv(3,3,CV_32F), img_pts_cv(2,n,CV_32F), obj_pts_cv(3,n,CV_32F), R_cv, t_cv;
	
	//cout<<"cam_in="<<endl<<cam_in_eig<<endl<<endl;
	//cout<<"obj_pts="<<endl<<obj_pts_eig<<endl<<endl;
	//cout<<"img_pts="<<endl<<img_pts_eig<<endl<<endl;
	
	eigen2cv(cam_in_eig, cam_in_cv);
	eigen2cv(img_pts_eig, img_pts_cv);
	eigen2cv(obj_pts_eig, obj_pts_cv);
	
	//cout<<cam_in_cv<<endl;
	//cout<<img_pts_cv<<endl;
	//cout<<obj_pts_cv<<endl;
	
	epnp e(cam_in_cv, obj_pts_cv, img_pts_cv);
	e.compute_pose(R_cv,t_cv);
	
	//cout<<R_cv<<endl;
	//cout<<t_cv<<endl;
	
	cv2eigen(R_cv, R_eig);
	cv2eigen(t_cv, t_eig);
	
	Quaterniond q(R_eig);
	
	pose_mat << t_eig,q.vec();
	
	//cout<<"R_eig="<<endl<<R_eig<<endl<<endl;
	//cout<<"t_eig="<<endl<<t_eig<<endl<<endl;
	
	//pose_mat.block(0,0,3,3)=R_eig;
	//pose_mat.block(0,3,3,1)=t_eig;
	//pose_mat.row(3)<<0,0,0,1;
	
	//cout<<"pose_mat="<<endl<<pose_mat_eig<<endl<<endl;
	
	return 1;
}

template<typename Derived>
int pnpalgo_upnp(MatrixBase<Derived>& obj_pts, MatrixBase<Derived>& img_pts, int n, MatrixBase<Derived>& cam_intrinsic, MatrixBase<Derived>& pose_mat){
	
	MatrixXd cam_in_eig=cam_intrinsic.array().transpose(), img_pts_eig=img_pts.array().transpose(), obj_pts_eig=obj_pts.array().transpose(), t_eig;
	Matrix3d R_eig; 
	Mat cam_in_cv(3,3,CV_32F), img_pts_cv(2,n,CV_32F), obj_pts_cv(3,n,CV_32F), R_cv, t_cv;
	
	//cout<<"cam_in="<<endl<<cam_in_eig<<endl<<endl;
	//cout<<"obj_pts="<<endl<<obj_pts_eig<<endl<<endl;
	//cout<<"img_pts="<<endl<<img_pts_eig<<endl<<endl;
	
	eigen2cv(cam_in_eig, cam_in_cv);
	eigen2cv(img_pts_eig, img_pts_cv);
	eigen2cv(obj_pts_eig, obj_pts_cv);
	
	//cout<<cam_in_cv<<endl;
	//cout<<img_pts_cv<<endl;
	//cout<<obj_pts_cv<<endl;
	
	upnp u(cam_in_cv, obj_pts_cv, img_pts_cv);
	u.compute_pose(R_cv,t_cv);
	
	//cout<<R_cv<<endl;
	//cout<<t_cv<<endl;
	
	cv2eigen(R_cv, R_eig);
	cv2eigen(t_cv, t_eig);
	
	Quaterniond q(R_eig);
	
	pose_mat << t_eig,q.vec();
	
	//cout<<"R_eig="<<endl<<R_eig<<endl<<endl;
	//cout<<"t_eig="<<endl<<t_eig<<endl<<endl;
	
	//pose_mat.block(0,0,3,3)=R_eig;
	//pose_mat.block(0,3,3,1)=t_eig;
	//pose_mat.row(3)<<0,0,0,1;
	
	//cout<<"pose_mat="<<endl<<pose_mat_eig<<endl<<endl;
	
	return 1;
}
