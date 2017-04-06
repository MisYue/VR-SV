#include "transformation.h"

double Transformation::PI = 3.14159265358979323846;

double Transformation::a84 = 6378137.00000000;
double Transformation::b84 = 6356752.31424518;
double Transformation::f84 = 1/298.257223563;
double Transformation::e_284 = 6.739496742E-3;

double Transformation::a54 = 6378245.00000000;
double Transformation::b54 = 6356863.01877305;
double Transformation::f54 = 1/298.3;
double Transformation::e_254 = 6.738525414683E-3;


//��������ϵ
void Transformation::set_CoordSys(enum COORDSYS CoordSys)
{
	if(CoordSys == C84 || CoordSys == c84)
		CoordSysParam = 84;
	else
		CoordSysParam = 54;
};

//��ѯ���������ϵ
int Transformation::get_CoordSys()
{
	return CoordSysParam;
}

/***********************************************************************************************
���⹫ʽ����֪����Ĵ������(B1,L1),(B2,L2)�����ؾ���s��������λ��angle12,angle21
������	L1[in]:��һ��ľ��ȣ����ȣ���-PI~PI��
		B1[in]:��һ���γ�ȣ����ȣ���-PI/2~PI/2��
		L2[in]:�ڶ���ľ��ȣ����ȣ���-PI~PI��
		B2[in]:�ڶ����γ�ȣ����ȣ���-PI/2~PI/2��
		s[in/out]:�������루�ף�
		angle12[in/out]:��һ�㵽�ڶ���ķ�λ�ǣ����ȣ�����������Ϊ�㣬˳ʱ��Ϊ����0~2PI)
		angle21[in/out]:�ڶ��㵽��һ��ķ�λ�ǣ����ȣ�����������Ϊ�㣬˳ʱ��Ϊ����0~2PI)
����ֵ��0:�������ܽ������Կ���ʹһ�㣬������λ�Ǿ�Ϊ0
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_two_pnt_dist_raw(double L1, double B1, double L2, double B2, double& s, double& angle12, double& angle21)
{
	double u1, u2, sinu1, sinu2, cosu1, cosu2;
	double  lamda, lamda1, sinlamda, coslamda;
	double tri_derta;
	double x1, x2, x3, x4, x5, x6;
	double A, B, C, D, E, K1;
	double tanangle, temp1, temp2;

	double LONG_RAD = (CoordSysParam == 84? a84 : a54);
	double SHORT_RAD = (CoordSysParam == 84? b84 : b54);
	double E_2 = (CoordSysParam == 84? e_284 : e_254);
	double EARTH_f = (CoordSysParam == 84? f84 : f54);

	if((fabs(B1) <= 1e-20) && (fabs(B2) <= 1e-20))   //���������
	{
		s = LONG_RAD * fabs(L2 - L1);
		if(L2 >= L1)
		{
			angle12 = PI / 2.0;
			angle21 = 3.0 * PI /2.0;
		}
		else
		{
			angle12 = 3.0 * PI /2.0;
			angle21 = PI / 2.0;
		}
		return 1;
	}
	else if((PI/2.0-fabs(B1)<=1e-10) || (PI/2.0-fabs(B2)<=1e-10))
	{
		s = SHORT_RAD*fabs(B2 - B1);
		if(B2 >= B1)
		{
			angle12 = 0.0;
			angle21 = PI;
		}
		else
		{
			angle12 = PI;
			angle21 = 0.0;
		}
		return 1;
	}
	else if(fabs(B1 - B2) < (1e-10) && fabs(L1 - L2) < (1e-10))  //�������ǳ���
	{
		s = 0.0;
		angle12 = 0.0;
		angle21 = 0.0;
		return 0;
	}
	else
	{
		//formula(1)
		u1 = atan((1.0 - EARTH_f) * tan(B1));
		sinu1 = sin(u1);
		cosu1 = cos(u1);
		u2 = atan((1.0 - EARTH_f) * tan(B2));
		sinu2 = sin(u2);
		cosu2 = cos(u2);
		//formula(2)
		lamda = L2 - L1;
		int k = 0;

		do
		{
			if(++k > 1000)
				break;
			//formula(3)
			lamda1 = lamda;
			sinlamda = sin(lamda);
			coslamda = cos(lamda);
			//formula(4)
			x1 = pow(pow((cosu2 * sinlamda), 2) + pow((cosu1 * sinu2 - sinu1 * cosu2 * coslamda), 2), 0.5);
			//formula(5)
			x2 = sinu1 * sinu2 + cosu1 * cosu2 * coslamda;
			//formula(6)
			x3 = x1 / x2;
			//formula(7)
			x4 = cosu1 * cosu2 * sinlamda / x1;
			//formula(8)
			x5 = 1.0 - pow(x4, 2);
			//formula(9)
			C = EARTH_f * x5 * (4.0 + EARTH_f * (4.0 - 3.0 * x5)) / 16.0;
			//formula(10)
			x6 = x2 - 2.0 * sinu1 * sinu2 / x5;
			//formula(11)
			E = 2.0 * pow(x6,  2) - 1.0;
			//formula(12)
			lamda = (L2 - L1) + (1.0 - C) * EARTH_f * x4 * (atan((x3) + C * x1 * (x6 + E * C * x2)));
		}while(fabs(lamda - lamda1) > (0.3e-11));

		sinlamda = sin(lamda);
		coslamda = cos(lamda);

		//formula(13)
		K1 = (pow(1.0 + E_2 * x5, 0.5) -1.0) / (pow((1.0 + E_2 * x5), 0.5) + 1.0);
		//formula(14)
		B = K1 * (1.0 - 3.0 * pow(K1, 2) / 8.0);

		//formula(15)
		A = (1.0 + 0.25 * pow(K1, 2)) / (1.0 - K1);
		//formula(16)
		D = B * x6 * (4.0 * pow(x1, 2) - 3.0) * (2.0 *E-1.0) / 6.0;
		//formula(17)
		tri_derta = B * x1 * (x6 + 0.25 * B * (E * x2 - D));
		//formula(18)
		s = ((atan2(x1, x2) - tri_derta) * SHORT_RAD *A);
		//formula(19)
		temp1 = cosu2 * sinlamda;
		temp2 = (cosu1 * sinu2 - sinu1 * cosu2 * coslamda);
		tanangle = temp1 / temp2;
		if(temp2 < 0)
		{
			angle12 = atan(tanangle) + PI;
		}
		else if(temp2 > 0 && temp1 < 0)
		{
			angle12 = atan(tanangle) +2.0 * PI;
		}
		else
		{
			angle12 = atan(tanangle);
		}
		//formula(20)
		temp1 = -cosu1 * sinlamda;
		temp2 = (cosu2* sinu1 - sinu2 * cosu1 * coslamda);
		tanangle = temp1 / temp2;
		if(temp2 < 0)
		{
			angle21 = atan(tanangle) + PI;
		}
		else if(temp2 > 0 && temp1 < 0)
		{
			angle21 = atan(tanangle) +2.0 * PI;
		}
		else
		{
			angle21 = atan(tanangle);
		}
		return 1;
	}
}

/***********************************************************************************************
���⹫ʽ����֪����Ĵ������(B1,L1)�͵��ڶ���Ĵ�ؾ���s����λ��angle12����ڶ���������(B2,L2)������λ��angle21
������	L1[in]:��һ��ľ��ȣ����ȣ���-PI~PI��
		B1[in]:��һ���γ�ȣ����ȣ���-PI/2~PI/2��
		s[in]:�������루�ף�
		angle12[in/out]:��һ�㵽�ڶ���ķ�λ�ǣ����ȣ�����������Ϊ�㣬˳ʱ��Ϊ����0~2PI)
		L2[in/out]:�ڶ���ľ��ȣ����ȣ���-PI~PI��
		B2[in/out]:�ڶ����γ�ȣ����ȣ���-PI/2~PI/2��
		angle21[in/out]:�ڶ��㵽��һ��ķ�λ�ǣ����ȣ�����������Ϊ�㣬˳ʱ��Ϊ����0~2PI)
����ֵ��0:�������ܽ������Կ���ͬһ�㣬����λ�Ǿ�Ϊ0
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_coord_by_distance_raw(double L1, double B1, double s, double angle12, double& L2, double& B2, double& angle21)
{
	double cosderta, sinderta;
	double tri_derta;
	double A12;
	double u1, tanu1, tanderta1, sinu1, cosu1;
	double sinA12, cosA12;
	double derta, derta1, derta2;
	double sinm, x5, x6;
	double K1, A, B, C, D, E;
	double temp1, temp2, lamda;

    double LONG_RAD = (CoordSysParam == 84? a84 : a54);
	double SHORT_RAD = (CoordSysParam == 84? b84 : b54);
	double E_2 = (CoordSysParam == 84? e_284 : e_254);
	double EARTH_f = (CoordSysParam == 84? f84 : f54);

	if(fabs(s) < 1e-20)         //�������Ϊ�㣬��ΪΪͬһ��
    {
        L2 = L1;
        B2 = B1;
        angle21 = 0.0;
        return 0;
    }
    else if((fabs(B1) <= 1e-20) && (fabs(angle12 - PI/2.0) <= 1e-10)) //��һ���ڳ�����ҷ�λ��Ϊ90
    {
        L2 = s / LONG_RAD + L1;
        B2 = 0.0;
        angle12 = 1.5 * PI;
    }
	else if((fabs(B1) <= 1e-20) && (fabs(angle12 - PI/1.5) <= 1e-10)) //��һ���ڳ�����ҷ�λ��Ϊ270
	{
	    L2 = L1 - s / LONG_RAD ;
        B2 = 0.0;
        angle12 = 0.5 * PI;
	}
	else if(PI / 2.0 - fabs(B1) <= 1e-10)  //��һ������(��)����
	{
	    L2 = L1;
	    if(fabs(PI / 2.0 - B1) <= 1e-10)  //��һ���ڱ�����
	    {
	        B2 = B1 - s/SHORT_RAD;
	        angle21 = 0;
	    }
	    else                                //��һ�����ϼ���
        {
              B2 = B1 + s/SHORT_RAD;
              angle21 = PI;
        }
	}
	else
    {
        A12 = angle12;
        sinA12 = sin(A12);
        cosA12 = cos(A12);

        //formula(1)
        tanu1 = (1.0 - EARTH_f) * tan(B1);
        u1 = atan(tanu1);
        sinu1 = sin(u1);
        cosu1 = cos(u1);

        if(fabs(PI / 2.0 - A12) <= 1e-10)  //���Angle12=90
        {
            derta1 = (tanu1 >= 0.0)? PI/2.0 : -PI/2.0;
        }
        else if(fabs(1.5 * PI - A12) <= 1e-10)  //���Angle12=270
        {
            derta1 = (tanu1 >= 0.0)? -PI/2.0 : PI/2.0;
        }
        else
        {
            //formula(2)
            tanderta1 = tanu1 / cosA12;

            derta1 = atan(tanderta1);
            if((cosA12 < 0.0) && (tanu1 > 0.0))
            {
                derta1 += PI;
            }
            else if((cosA12 < 0.0) && (tanu1 < 0.0))
            {
                derta1 += -PI;
            }
        }
        //formula(3)
        sinm = cosu1 * sinA12;
        x5 = 1.0 - pow(sinm, 2);

        //formula(4)
        K1 = (pow((1.0 + E_2 * x5), 0.5) -1.0) /(pow((1.0 + E_2 * x5), 0.5) + 1.0);

        //formula(5)
        A = (1.0 + 0.25 * pow(K1, 2)) / (1.0 - K1);
        //formula(6)
        B = K1 * (1.0 - 3.0 * pow(K1, 2) / 8.0);
        //formula(7)
        derta = s / (SHORT_RAD * A);

        int k = 0;
        do
        {
            if(++k > 1000)
                break;
            derta2 = derta;

            cosderta = cos(derta);
            sinderta = sin(derta);

            //formula(9)
            x6 = cos(2.0 * derta1 + derta);
            E = 2.0 * pow(x6, 2) - 1.0;

            //formula(10)
            D = B * x6 * (4.0 * pow(sinderta, 2) - 3.0) * (2.0 * E -1.0) / 6.0;
            //formula(11)
            tri_derta = B * sinderta * (x6 + 0.25* B* (E * cosderta - D));
            //formula(12)
            derta = s / (SHORT_RAD * A) + tri_derta;
        }while(fabs(derta - derta2) > (0.3e-11));

        cosderta = cos(derta);
        sinderta = sin(derta);

        //formula(13)
		B2 = atan((sinu1 * cosderta + cosu1 * sinderta * cosA12) / ((1 - EARTH_f) * pow(((1 - x5) + pow((sinu1 * sinderta - cosu1 * cosderta * cosA12), 2)), 0.5)));

        //formula(14)
        temp1 = sinderta * sinA12;
        temp2 = cosu1 * cosderta - sinu1 * sinderta * cosA12;
        lamda = atan(temp1 / temp2);

        if((temp2 < 0) && (temp1 > 0))
        {
            lamda += PI;
        }
        if((temp2 < 0) && (temp1 < 0))
        {
            lamda += -PI;
        }

        //formula(15)
        C = EARTH_f * x5 * (4.0 + EARTH_f * (4.0 - 3.0 * x5)) / 16.0;

        //formula(16)
        L2 = L1 + lamda - (1 - C) * EARTH_f * sinm * ( derta + C * sinderta * (x6 + E *C* cosderta));

       if(fabs(L2) > PI)
       {
           if(L2 > 0)
                L2 -= 2 * PI;
           else if(L2 < 0)
                L2 += 2 * PI;
       }

       //formula(17)
       double temp1, temp2;
       double tanangle;

       temp1 = -sinm;
       temp2 = sinu1 * sinderta - cosu1 * cosderta * cosA12;
       tanangle = temp1 / temp2;

       if(temp2 < 0)
       {
           angle21 = atan(tanangle) + PI;
       }
       else
       {
           if(temp1 < 0)
            angle21 = atan(tanangle) + 2 * PI;
           else
            angle21 = atan(tanangle);
       }
    }
	return 1;
}

/***********************************************************************************************
���ܣ���֪һ��������͵��ڶ���ľ���ͷ�λ�ǣ���ڶ���������
������	L1[in]:��һ��ľ��ȣ��ȣ�
		B1[in]:��һ���γ�ȣ��ȣ�
		s[in]:�������루KM��
		Angle[in]:��һ�㵽�ڶ���ķ�λ�ǣ��ȣ�
		L2[in/out]:�ڶ���ľ��ȣ��ȣ�
		B2[in/out]:�ڶ����γ�ȣ��ȣ�
		Angle21[in/out]:�ڶ��㵽��һ��ķ�λ�ǣ��ȣ�
����ֵ��0:�������ܽ������Կ���ͬһ��
		1:������������ļ���
************************************************************************************************/
 int Transformation::calc_coord_by_point(double L1, double B1, double s, double Angle, double& L2, double& B2, double& Angle21)
 {
     double ratio = PI / 180.0;
 
     if(Angle <0)
         Angle += 360.0;
 
     Angle *= ratio;         //ת��Ϊ����
     L1 *= ratio;            //ת��Ϊ����
     B1 *= ratio;            //ת��Ϊ����
 
     s *= 1000.0;            //ת��Ϊ��
 
     int ret = calc_coord_by_distance_raw(L1, B1, s, Angle, L2, B2, Angle21);
 
     L2 /= ratio;             //ת��Ϊ��
     B2 /= ratio;             //ת��Ϊ��
 
     if(ret == 0)
         return 0;
 
     Angle21 /= ratio;          //ת��Ϊ��
 
     if(Angle21 < 0)
         Angle21 += 360.0;
 
     return ret;
 }

/***********************************************************************************************
���ܣ���֪һ��������͵��ڶ���ľ���ͷ�λ�ǣ���ڶ���������
������	L1[in]:��һ��ľ��ȣ��ȣ�
		B1[in]:��һ���γ�ȣ��ȣ�
		s[in]:�������루KM��
		Angle[in]:��һ�㵽�ڶ���ķ�λ�ǣ��ȣ�
		L2[in/out]:�ڶ���ľ��ȣ��ȣ�
		B2[in/out]:�ڶ����γ�ȣ��ȣ�
����ֵ��0:�������ܽ������Կ���ͬһ��
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_coord_by_point(double L1, double B1, double s, double Angle, double& L2, double& B2)
{
    double Angle21;
    return calc_coord_by_point(L1, B1, s, Angle, L2, B2, Angle21);
}

/***********************************************************************************************
���ܣ���֪���������꣬�������ͷ�λ��
������	L1[in]:��һ��ľ��ȣ��ȣ���-180~180��
		B1[in]:��һ���γ�ȣ��ȣ���-180/2~180/2��
		L2[in]:�ڶ���ľ��ȣ��ȣ���-180~180��
		B2[in]:�ڶ����γ�ȣ��ȣ���-180/2~180/2��
		s[in/out]:�������루Km��
		angle[in/out]:��һ�㵽�ڶ���ķ�λ�ǣ��ȣ�
		angle21[in/out]:�ڶ��㵽��һ��ķ�λ�ǣ��ȣ�
����ֵ��0:�������ܽ������Կ���ͬһ�㣬��λ��Ϊ0
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_two_pnt_dist(double L1, double B1, double L2, double B2, double& s, double& angle, double& angle21)
{
    double ratio = PI / 180.0;

    L1 *= ratio;            //ת��Ϊ����
    B1 *= ratio;            //ת��Ϊ����
    L2 *= ratio;            //ת��Ϊ����
    B2 *= ratio;            //ת��Ϊ����

    int ret = calc_two_pnt_dist_raw(L1, B1, L2, B2, s, angle, angle21);

    s /= 1000.0;             //ת��Ϊ����
    if(ret == 0)
        return 0;

    angle /= ratio;         //ת��Ϊ��

    if(angle < 0)
        angle += 360.0;        //0~360

    angle21 /= ratio;         //ת��Ϊ��

    if(angle21 < 0)
        angle21 += 360.0;        //0~360

    return ret;
}

/***********************************************************************************************
���ܣ���֪���������꣬�������ͷ�λ��
������	L1[in]:��һ��ľ��ȣ��ȣ���-180~180��
		B1[in]:��һ���γ�ȣ��ȣ���-180/2~180/2��
		L2[in]:�ڶ���ľ��ȣ��ȣ���-180~180��
		B2[in]:�ڶ����γ�ȣ��ȣ���-180/2~180/2��
		s[in/out]:�������루Km��
		angle[in/out]:��һ�㵽�ڶ���ķ�λ�ǣ��ȣ�
����ֵ��0:�������ܽ������Կ���ͬһ�㣬��λ��Ϊ0
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_two_pnt_dist(double L1, double B1, double L2, double B2, double& s, double& angle)
{
    double angle21;
    return calc_two_pnt_dist(L1, B1, L2, B2, s, angle, angle21);
}


/***********************************************************************************************
���ܣ���֪�������꣬�������
������	L1[in]:��һ��ľ��ȣ��ȣ���-180~180��
		B1[in]:��һ���γ�ȣ��ȣ���-180~180��
		L2[in]:�ڶ���ľ��ȣ��ȣ���-180~180��
		B2[in]:�ڶ����γ�ȣ��ȣ���-180~180��
		s[in/out]:�������루Km��
����ֵ��0:�������ܽ������Կ���ͬһ��
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_two_pnt_dist(double L1, double B1, double L2, double B2, double& s)
{
    double angle;
    return calc_two_pnt_dist(L1, B1, L2, B2, s, angle);
}

/***********************************************************************************************
���ܣ���֪�������꣬���һ�㵽�ڶ���ķ�λ������Ϊ�㣩
������	L1[in]:��һ��ľ��ȣ��ȣ���-180~180��
		B1[in]:��һ���γ�ȣ��ȣ���-180~180��
		L2[in]:�ڶ���ľ��ȣ��ȣ���-180~180��
		B2[in]:�ڶ����γ�ȣ��ȣ���-180~180��
		Angle[in/out]:��һ�㵽�ڶ���ķ�λ�ǣ��ȣ�
����ֵ��0:�������ܽ������Կ���ͬһ��
		1:������������ļ���
************************************************************************************************/
int Transformation::calc_two_pnt_dirc(double L1, double B1, double L2, double B2, double& angle)
{
    double s;
    return calc_two_pnt_dist(L1, B1, L2, B2, s, angle);
}