#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <math.h>
enum COORDSYS {C84, c84, C54, c54};

class Transformation
{
private:
	int CoordSysParam;		//选择54坐标系或84坐标系
	static double PI;
	//84坐标地球参数
	static double a84;		//a
	static double b84;		//b
	static double f84;		//f
	static double e_284;		//e^2
	//54坐标地球参数
	static double a54;		//a
	static double b54;		//b
	static double f54;		//f
	static double e_254;		//e^2

public:
	Transformation()
	{
		CoordSysParam = 84;
	}

	Transformation(enum COORDSYS CoordSys)
	{
		if(CoordSys == C84 || CoordSys == c84)
			CoordSysParam = 84;
		else
			CoordSysParam = 54;
	}

	virtual ~Transformation()	{}

	//设置坐标系
	void set_CoordSys(enum COORDSYS CoordSys);
	//获取坐标系
	int get_CoordSys();

private:
	int calc_two_pnt_dist_raw(double L1, double B1, double L2, double B2, double& s, double& angle12, double& angle21);
	int calc_coord_by_distance_raw(double L1, double B1, double s, double angle12, double& L2, double& B2, double& angle21);

public:
	//正解计算函数
 	int calc_coord_by_point(double L1, double B1, double s, double Angle, double& L2, double& B2, double& Angle21);
 	int calc_coord_by_point(double L1, double B1, double s, double Angle, double& L2, double& B2);

	//反解计算函数
 	int calc_two_pnt_dist(double L1, double B1, double L2, double B2, double& s, double& angle, double& angle21);
 	int calc_two_pnt_dist(double L1, double B1, double L2, double B2, double& s, double& angle);
 	int calc_two_pnt_dist(double L1, double B1, double L2, double B2, double& s);
	int calc_two_pnt_dirc(double L1, double B1, double L2, double B2, double& angle);
};


#endif