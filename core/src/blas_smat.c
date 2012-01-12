/*! \file blas_smat.c
 *  \brief BLAS operations for small full matrix.
 */

#include "fasp.h"
#include "fasp_functs.h"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/**
 * \fn void fasp_blas_smat_mxv_nc2(double *a, double *b, double *c)
 * \brief compute the product of a 2*2 matrix a and a vector b, stored in c
 *
 * \param *a   pointer to the double vector which stands a 2*2 matrix
 * \param *b   pointer to the double vector with length 2
 * \param *c   pointer to the double vector with length 2
 * 
 * \author Xiaozhe Hu
 * \date 18/11/2010
 */
void fasp_blas_smat_mxv_nc2 (double *a, 
                             double *b, 
							 double *c)
{	double b0,b1;
	b0=b[0];
	b1=b[1];
	c[0] = a[0]*b0 + a[1]*b1;
	c[1] = a[2]*b0 + a[3]*b1;
}

/**
 * \fn void fasp_blas_smat_mxv_nc3(double *a, double *b, double *c)
 * \brief compute the product of a 3*3 matrix a and a vector b, stored in c
 *
 * \param *a   pointer to the double vector which stands a 3*3 matrix
 * \param *b   pointer to the double vector with length 3
 * \param *c   pointer to the double vector with length 3
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_mxv_nc3 (double *a, 
                             double *b, 
												     double *c)
{	double b0,b1,b2;
	b0=b[0];
	b1=b[1];
	b2=b[2];
	c[0] = a[0]*b0 + a[1]*b1 + a[2]*b2;
	c[1] = a[3]*b0 + a[4]*b1 + a[5]*b2;
	c[2] = a[6]*b0 + a[7]*b1 + a[8]*b2;
}

/**
 * \fn void fasp_blas_smat_mxv_nc5(double *a, double *b, double *c)
 * \brief compute the product of a 5*5 matrix a and a vector b, stored in c
 *
 * \param *a   pointer to the double vector which stands a 5*5 matrix
 * \param *b   pointer to the double vector with length 5
 * \param *c   pointer to the double vector with length 5
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_mxv_nc5 (double *a, 
                             double *b, 
														 double *c)
{	
	double b0,b1,b2,b3,b4;
	b0=b[0];
	b1=b[1];
	b2=b[2];
	b3=b[3];
	b4=b[4];
	c[0] = a[0]*b0 + a[1]*b1 + a[2]*b2 + a[3]*b3 + a[4]*b4;
	c[1] = a[5]*b0 + a[6]*b1 + a[7]*b2 + a[8]*b3 + a[9]*b4;
	c[2] = a[10]*b0 + a[11]*b1 + a[12]*b2 + a[13]*b3 + a[14]*b4;
	c[3] = a[15]*b0 + a[16]*b1 + a[17]*b2 + a[18]*b3 + a[19]*b4;
	c[4] = a[20]*b0 + a[21]*b1 + a[22]*b2 + a[23]*b3 + a[24]*b4;
}

/**
 * \fn void fasp_blas_smat_mxv_nc7(double *a, double *b, double *c)
 * \brief compute the product of a 7*7 matrix a and a vector b, stored in c
 *
 * \param *a   pointer to the double vector which stands a 7*7 matrix
 * \param *b   pointer to the double vector with length 7
 * \param *c   pointer to the double vector with length 7
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_mxv_nc7 (double *a, 
                             double *b, 
												     double *c)
{	
	double b0,b1,b2,b3,b4,b5,b6;
	b0=b[0];
	b1=b[1];
	b2=b[2];
	b3=b[3];
	b4=b[4];
	b5=b[5];
	b6=b[6];
	c[0] = a[0]*b0  +  a[1]*b1 + a[2]*b2 + a[3]*b3  + a[4]*b4  + a[5]*b5 + a[6]*b6;
	c[1] = a[7]*b0  +  a[8]*b1 + a[9]*b2 + a[10]*b3 + a[11]*b4 + a[12]*b5 + a[13]*b6;
	c[2] = a[14]*b0 + a[15]*b1 + a[16]*b2 + a[17]*b3 + a[18]*b4 + a[19]*b5 + a[20]*b6;
	c[3] = a[21]*b0 + a[22]*b1 + a[23]*b2 + a[24]*b3 + a[25]*b4 + a[26]*b5 + a[27]*b6;
	c[4] = a[28]*b0 + a[29]*b1 + a[30]*b2 + a[31]*b3 + a[32]*b4 + a[33]*b5 + a[34]*b6;
	c[5] = a[35]*b0 + a[36]*b1 + a[37]*b2 + a[38]*b3 + a[39]*b4 + a[40]*b5 + a[41]*b6;
	c[6] = a[42]*b0 + a[43]*b1 + a[44]*b2 + a[45]*b3 + a[46]*b4 + a[47]*b5 + a[48]*b6;
}

/**
 * \fn void fasp_blas_smat_mxv(double *a, double *b, double *c, int n)
 * \brief compute the product of a small full matrix a and a vector b, stored in c
 *
 * \param *a   pointer to the double vector which stands a n*n matrix
 * \param *b   pointer to the double vector with length n
 * \param *c   pointer to the double vector with length n
 * \param  n   the dimension of the matrix
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 04/21/2010  
 */
void fasp_blas_smat_mxv (double *a, 
                         double *b, 
												 double *c,
									    	 int n)
{	
	switch (n)
	{
		case 2:
			fasp_blas_smat_mxv_nc2(a, b, c);
			break;
			
		case 3: 
			fasp_blas_smat_mxv_nc3(a, b, c);
			break;
			
		case 5:
			fasp_blas_smat_mxv_nc5(a, b, c);
			break;
			
		case 7:
			fasp_blas_smat_mxv_nc7(a, b, c);
			break;
			
		default:
		{
			int i,j,in=0;
			double temp;
			
			for (i=0; i<n; ++i, in+=n){
				temp = 0.0;
				for (j=0; j<n; ++j) temp += a[in+j]*b[j];
				c[i]=temp;
			} //! end for i
		}
			break;
	}
	return;
}

/**
 * \fn void fasp_blas_smat_inv_nc2(double *a)
 * \brief Compute the inverse matrix of a 2*2 full matrix A (in place)
 *
 * \param *a pointer to the double vector which stands a 2*2 matrix 
 * 
 * \author Xiaozhe Hu
 * \date 18/11/2011
 */
void fasp_blas_smat_inv_nc2 (double *a)
{ 
	const double a0 = a[0], a1 = a[1];
	const double a2 = a[2], a3 = a[3];
	
	const double det = a0*a3 - a1*a2;
	double det_inv;
	
	if (ABS(det)<1e-22) {
		printf("## Warning: Matrix is nearly singular! det = %e\n", det);
		/*
		 printf("##----------------------------------------------\n");
		 printf("## %12.5e %12.5e \n", a0, a1);
		 printf("## %12.5e %12.5e \n", a2, a3);
		 printf("##----------------------------------------------\n");
		 getchar(); 
		 */
	}
	
	det_inv = 1.0/det;
	
	a[0] = a3*det_inv; a[1] = - a1*det_inv; 
	
	a[2] = - a2*det_inv; a[3] = a0*det_inv; 
	
}

/**
 * \fn void fasp_blas_smat_inv_nc3(double *a)
 * \brief Compute the inverse matrix of a 3*3 full matrix A (in place)
 *
 * \param *a pointer to the double vector which stands a 3*3 matrix 
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_inv_nc3 (double *a)
{ 
	const double a0 = a[0], a1 = a[1], a2 = a[2];
	const double a3 = a[3], a4 = a[4], a5 = a[5];
	const double a6 = a[6], a7 = a[7], a8 = a[8];
	
	const double M0 = a4*a8-a5*a7, M3 = a2*a7-a1*a8, M6 = a1*a5-a2*a4;
	const double M1 = a5*a6-a3*a8, M4 = a0*a8-a2*a6, M7 = a2*a3-a0*a5;
	const double M2 = a3*a7-a4*a6, M5 = a1*a6-a0*a7, M8 = a0*a4-a1*a3;
	const double det = a0*M0+a3*M3+a6*M6;
	double det_inv;
	
	if (ABS(det)<1e-22) {
		printf("## Warning: Matrix is nearly singular! det = %e\n", det);
		/*
		 printf("##----------------------------------------------\n");
		 printf("## %12.5e %12.5e %12.5e \n", a0, a1, a2);
		 printf("## %12.5e %12.5e %12.5e \n", a3, a4, a5);
		 printf("## %12.5e %12.5e %12.5e \n", a5, a6, a7);
		 printf("##----------------------------------------------\n");
		 getchar(); 
		 */
	}
	
	det_inv = 1.0/det;
	
	a[0] = M0*det_inv; a[1] = M3*det_inv; a[2] = M6*det_inv;
	
	a[3] = M1*det_inv; a[4] = M4*det_inv; a[5] = M7*det_inv;
	
	a[6] = M2*det_inv; a[7] = M5*det_inv; a[8] = M8*det_inv;	
}

/**
 * \fn void fasp_blas_smat_inv_nc5(double *a)
 * \brief Compute the inverse matrix of a 5*5 full matrix A (in place)
 *
 * \param *a pointer to the double vector which stands a 5*5 matrix 
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_inv_nc5 (double *a)
{ 
	const double a0=a[0],   a1=a[1],   a2=a[2],   a3=a[3],   a4=a[4];
	const double a5=a[5],   a6=a[6],   a7=a[7],   a8=a[8],   a9=a[9];
	const double a10=a[10], a11=a[11], a12=a[12], a13=a[13], a14=a[14];
	const double a15=a[15], a16=a[16], a17=a[17], a18=a[18], a19=a[19];
	const double a20=a[20], a21=a[21], a22=a[22], a23=a[23], a24=a[24];
	
	double det0, det1, det2, det3, det4, det, det_inv;
	
	det0  =  a6  * ( a12 * (a18*a24-a19*a23) + a17 * (a14*a23-a13*a24) + a22 * (a13*a19 - a14*a18) );
	det0 +=  a11 * ( a7  * (a19*a23-a18*a24) + a17 * (a8*a24 -a9*a23 ) + a22 * (a9*a18  - a8*a19)  );
	det0 +=  a16 * ( a7  * (a13*a24-a14*a23) + a12 * (a9*a23 -a8*a24 ) + a22 * (a8*a14  - a9*a13)  ); 
	det0 +=  a21 * ( a17 * (a9*a13 -a8*a14 ) + a7  * (a14*a18-a13*a19) + a12 * (a8*a19  - a9*a18)  );
	
	det1  =  a1  * ( a22 * (a14*a18-a13*a19) + a12 * (a19*a23-a18*a24) + a17 * (a13*a24 - a14*a23) );
	det1 +=  a11 * ( a17 * (a4*a23 - a3*a24) + a2  * (a18*a24-a19*a23) + a22 * (a3*a19  - a4*a18)  ); 
	det1 +=  a16 * ( a12 * (a3*a24 - a4*a23) + a2  * (a14*a23-a13*a24) + a22 * (a4*a13  - a3*a14)  );
	det1 +=  a21 * ( a2  * (a13*a19-a14*a18) + a12 * (a4*a18 -a3*a19 ) + a17 * (a3*a14  - a4*a13)  ); 
	
	det2  =  a1  * ( a7 * (a18*a24-a19*a23) + a17 * (a9*a23-a8*a24) + a22 * (a8*a19 - a9*a18) );
	det2 +=  a6  * ( a2 * (a19*a23-a18*a24) + a17 * (a3*a24-a4*a23) + a22 * (a4*a18 - a3*a19) );	
	det2 +=  a16 * ( a2 * (a8*a24 -a9*a23 ) + a7  * (a4*a23-a3*a24) + a22 * (a3*a9  - a4*a8)  );
	det2 +=  a21 * ( a7 * (a3*a19 -a4*a18 ) + a2  * (a9*a18-a8*a19) + a17 * (a4*a8  - a3*a9)  );
	
	det3  =  a1  * ( a12* (a8*a24 -a9*a23)  + a7  * (a14*a23-a13*a24) + a22 * (a9*a13 - a8*a14) );
	det3 +=  a6  * ( a2 * (a13*a24-a14*a23) + a12 * (a4*a23 -a3*a24 ) + a22 * (a3*a14 - a4*a13) );	
	det3 +=  a11 * ( a7 * (a3*a24 -a4*a23)  + a2  * (a9*a23 -a8*a24 ) + a22 * (a4*a8  - a3*a9)  );
	det3 +=  a21 * ( a2 * (a8*a14 -a9*a13)  + a7  * (a4*a13 -a3*a14 ) + a12 * (a3*a9  - a4*a8)  );
	
	det4  =  a1  * ( a7 * (a13*a19-a14*a18) + a12 * (a9*a18 -a8*a19 ) + a17 * (a8*a14 - a9*a13) );
	det4 +=  a6  * ( a12* (a3*a19 -a4*a18 ) + a17 * (a4*a13 -a3*a14 ) + a2  * (a14*a18- a13*a19));
	det4 +=  a11 * ( a2 * (a8*a19 -a9*a18 ) + a7  * (a4*a18 -a3*a19 ) + a17 * (a3*a9  - a4*a8)  );
	det4 +=  a16 * ( a7 * (a3*a14 -a4*a13 ) + a2  * (a9*a13 -a8*a14 ) + a12 * (a4*a8  - a3*a9)  );
	
	det = det0*a0 + det1*a5+ det2*a10 + det3*a15 + det4*a20;
	
	if (ABS(det)<1e-22) {
		printf("## Warning: Matrix is nearly singular! det = %e\n", det);
		/*
		 printf("##----------------------------------------------\n");
		 printf("## %12.5e %12.5e %12.5e %12.5e %12.5e\n", a0,  a1,  a2,  a3,  a4);
		 printf("## %12.5e %12.5e %12.5e %12.5e %12.5e\n", a5,  a6,  a7,  a8,  a9);
		 printf("## %12.5e %12.5e %12.5e %12.5e %12.5e\n", a10, a11, a12, a13, a14);
		 printf("## %12.5e %12.5e %12.5e %12.5e %12.5e\n", a15, a16, a17, a18, a19);
		 printf("## %12.5e %12.5e %12.5e %12.5e %12.5e\n", a20, a21, a22, a23, a24);
		 printf("##----------------------------------------------\n");
		 getchar(); 
		 */
	}
	
	det_inv = 1/det;
	
	a[0]  = a6  * (a12*a18*a24-a12*a19*a23-a17*a13*a24+a17*a14*a23+a22*a13*a19-a22*a14*a18);
	a[0] += a11 * (a7*a19*a23 -a7*a18*a24 +a17*a8*a24 -a17*a9*a23 -a22*a8*a19 +a22*a9*a18);
	a[0] += a16 * (a7*a13*a24 -a7*a14*a23 -a12*a8*a24 +a12*a9*a23 +a22*a8*a14 -a22*a9*a13);
	a[0] += a21 * (a7*a14*a18 -a7*a13*a19 +a12*a8*a19 -a12*a9*a18 -a17*a8*a14 +a17*a9*a13);
	a[0] *= det_inv;
	
	a[1]  = a1  * (a12*a19*a23-a12*a18*a24+a22*a14*a18-a17*a14*a23-a22*a13*a19+a17*a13*a24);
	a[1] += a11 * (a22*a3*a19 +a2*a18*a24 -a17*a3*a24 -a22*a4*a18 -a2*a19*a23 +a17*a4*a23 );
	a[1] += a16 * (a12*a3*a24 -a12*a4*a23 -a22*a3*a14 +a2*a14*a23 +a22*a4*a13 -a2*a13*a24 );
	a[1] += a21 * (a12*a4*a18 -a12*a3*a19 -a2*a14*a18 -a17*a4*a13 +a2*a13*a19 +a17*a3*a14 );
	a[1] *= det_inv;
	
	a[2]  = a1  * (a7*a18*a24-a7*a19*a23-a17*a8*a24+a17*a9*a23+a22*a8*a19-a22*a9*a18);
	a[2] += a6  * (a2*a19*a23-a2*a18*a24+a17*a3*a24-a17*a4*a23-a22*a3*a19+a22*a4*a18);
	a[2] += a16 * (a2*a8*a24 -a2*a9*a23 -a7*a3*a24 +a7*a4*a23 +a22*a3*a9 -a22*a4*a8);
	a[2] += a21 * (a2*a9*a18 -a2*a8*a19 +a7*a3*a19 -a7*a4*a18 -a17*a3*a9 +a17*a4*a8);
	a[2] *= det_inv;
	
	a[3]  = a1  * (a12*a8*a24-a12*a9*a23+a7*a14*a23-a7*a13*a24+a22*a9*a13-a22*a8*a14);
	a[3] += a6  * (a12*a4*a23-a12*a3*a24+a22*a3*a14-a22*a4*a13+a2*a13*a24-a2*a14*a23);
	a[3] += a11 * (a7*a3*a24 -a7*a4*a23 +a22*a4*a8 -a22*a3*a9 +a2*a9*a23 -a2*a8*a24);
	a[3] += a21 * (a12*a3*a9 -a12*a4*a8 +a2*a8*a14 -a2*a9*a13 +a7*a4*a13 -a7*a3*a14 );
	a[3] *= det_inv;
	
	a[4]  = a1  * (a7*a13*a19-a7*a14*a18-a12*a8*a19+a12*a9*a18+a17*a8*a14-a17*a9*a13);
	a[4] += a6  * (a2*a14*a18-a2*a13*a19+a12*a3*a19-a12*a4*a18-a17*a3*a14+a17*a4*a13);
	a[4] += a11 * (a2*a8*a19 -a2*a9*a18 -a7*a3*a19 +a7*a4*a18 +a17*a3*a9 -a17*a4*a8 );
	a[4] += a16 * (a2*a9*a13 -a2*a8*a14 +a7*a3*a14 -a7*a4*a13 -a12*a3*a9 +a12*a4*a8 );
	a[4] *= det_inv;
	
  a[5]  = a5  * (a12*a19*a23-a12*a18*a24+a22*a14*a18-a22*a13*a19+a17*a13*a24-a17*a14*a23);
	a[5] += a20 * (a12*a9*a18 -a12*a8*a19 +a7*a13*a19 -a18*a7*a14 +a17*a8*a14 -a9*a17*a13 );
	a[5] += a15 * (a22*a9*a13 -a12*a9*a23 +a12*a24*a8 +a7*a14*a23 -a24*a7*a13 -a22*a14*a8 );
	a[5] += a10 * (a18*a7*a24 -a18*a22*a9 -a17*a8*a24 +a17*a9*a23 +a22*a8*a19 -a19*a23*a7 );
	a[5] *= det_inv;
	
	a[6]  = a2  * (a19*a23*a10-a14*a23*a15	-a18*a24*a10+a18*a14*a20-a13*a19*a20+a24*a13*a15);
	a[6] += a12 * (a18*a0*a24 -a18*a20*a4 +a3*a19*a20 -a19*a23*a0 +a4*a23*a15 -a24*a15*a3 );
	a[6] += a17 * (a4*a13*a20 -a13*a24*a0 +a14*a23*a0 -a3*a14*a20 +a24*a3*a10 -a4*a23*a10 );
	a[6] += a22 * (a14*a15*a3 -a18*a14*a0 +a18*a4*a10 -a4*a13*a15 +a13*a19*a0 -a3*a19*a10 );
	a[6] *= det_inv;
	
	a[7]  = a0  * (a18*a9*a22 -a18*a24*a7 +a19*a23*a7 -a9*a23*a17 +a24*a8*a17 -a8*a19*a22 );
	a[7] += a5  * (a2*a18*a24 -a2*a19*a23 +a17*a4*a23 -a17*a3*a24 +a22*a3*a19 -a22*a4*a18 );
	a[7] += a15 * (a4*a8*a22  -a3*a9*a22  -a24*a8*a2  +a9*a23*a2  -a4*a23*a7  +a24*a3*a7  );
	a[7] += a20 * (a18*a4*a7  -a18*a9*a2  +a9*a3*a17  -a4*a8*a17  +a8*a19*a2  -a3*a19*a7  );
	a[7] *= det_inv;
	
	a[8]  =	a0  * (a12*a9*a23 -a12*a24*a8 +a22*a14*a8 -a7*a14*a23 +a24*a7*a13 -a9*a22*a13 );
	a[8] += a5  * (a12*a3*a24 -a12*a4*a23 -a22*a3*a14 +a2*a14*a23 -a2*a13*a24 +a22*a4*a13 );
	a[8] += a10 * (a22*a9*a3  -a4*a22*a8  +a4*a7*a23  -a2*a9*a23  +a24*a2*a8  -a7*a24*a3  );
	a[8] += a20 * (a7*a14*a3  -a4*a7*a13  +a9*a2*a13  +a12*a4*a8  -a12*a9*a3  -a2*a14*a8  );
	a[8] *= det_inv;
	
	a[9]  =	a0  * (a12*a8*a19-a12*a18*a9+a18*a7*a14-a8*a17*a14+a17*a13*a9-a7*a13*a19);
	a[9] +=	a5  * (a2*a13*a19-a2*a14*a18-a12*a3*a19+a12*a4*a18+a17*a3*a14-a17*a4*a13);
	a[9] +=	a10 * (a18*a2*a9-a18*a7*a4+a3*a7*a19-a2*a8*a19+a17*a8*a4-a3*a17*a9);
	a[9] +=	a15 * (a8*a2*a14-a12*a8*a4+a12*a3*a9-a3*a7*a14+a7*a13*a4-a2*a13*a9);
	a[9] *=	det_inv;
	
	a[10] = a5  * (a18*a24*a11-a24*a13*a16+a14*a23*a16-a19*a23*a11+a13*a19*a21-a18*a14*a21);
	a[10]+= a10 * (a19*a23*a6-a9*a23*a16+a24*a8*a16-a8*a19*a21+a18*a9*a21-a18*a24*a6);
	a[10]+= a15 * (a24*a13*a6-a14*a23*a6-a24*a8*a11+a9*a23*a11+a14*a8*a21-a13*a9*a21);
	a[10]+= a20 * (a18*a14*a6-a18*a9*a11+a8*a19*a11-a13*a19*a6+a9*a13*a16-a14*a8*a16);
	a[10]*= det_inv;
	
	a[11] = a4  * (a21*a13*a15-a11*a23*a15+a16*a23*a10-a13*a16*a20+a18*a11*a20-a18*a21*a10);
	a[11]+= a14 * (a18*a0*a21-a1*a18*a20+a16*a3*a20-a23*a0*a16+a1*a23*a15-a21*a3*a15);
  a[11]+= a19 * (a1*a13*a20-a1*a23*a10+a23*a0*a11+a21*a3*a10-a11*a3*a20-a13*a0*a21);
	a[11]+= a24 * (a13*a0*a16-a18*a0*a11+a11*a3*a15+a1*a18*a10-a1*a13*a15-a16*a3*a10);
	a[11]*= det_inv;
	
	a[12] = a4  * (a5*a21*a18-a18*a20*a6+a20*a16*a8-a5*a16*a23+a15*a6*a23-a21*a15*a8);
	a[12]+= a9  * (a1*a20*a18-a1*a15*a23+a0*a16*a23-a18*a0*a21-a20*a16*a3+a15*a21*a3);
	a[12]+= a19 * (a20*a6*a3-a5*a21*a3+a0*a21*a8-a23*a0*a6+a1*a5*a23-a1*a20*a8);
	a[12]+= a24 * (a1*a15*a8-a0*a16*a8+a18*a0*a6-a1*a5*a18+a5*a16*a3-a6*a15*a3);
	a[12]*= det_inv;
	
	a[13] = a0  * (a24*a11*a8-a6*a24*a13+a21*a9*a13-a11*a9*a23+a14*a6*a23-a14*a21*a8);
	a[13]+= a1  * (a5*a13*a24-a5*a14*a23+a14*a20*a8+a10*a9*a23-a24*a10*a8-a20*a9*a13);
	a[13]+= a3  * (a6*a10*a24-a10*a9*a21+a5*a14*a21-a5*a24*a11+a20*a9*a11-a14*a6*a20);
	a[13]+= a4  * (a5*a11*a23-a5*a21*a13+a21*a10*a8-a6*a10*a23+a20*a6*a13-a11*a20*a8);
	a[13]*= det_inv;
	
	a[14] = a0  * (a13*a19*a6-a14*a18*a6-a11*a19*a8+a14*a16*a8+a11*a18*a9-a13*a16*a9);
	a[14]+= a1  * (a14*a18*a5-a13*a19*a5+a10*a19*a8-a14*a15*a8-a10*a18*a9+a13*a15*a9);
	a[14]+= a3  * (a11*a19*a5-a11*a15*a9+a10*a16*a9-a10*a19*a6+a14*a15*a6-a14*a16*a5);
	a[14]+= a4  * (a11*a15*a8-a11*a18*a5+a13*a16*a5-a13*a15*a6+a10*a18*a6-a10*a16*a8); 
	a[14]*= det_inv;
	
	a[15] = a5  * (a19*a22*a11-a24*a17*a11+a12*a24*a16-a22*a14*a16-a12*a19*a21+a17*a14*a21);
	a[15]+= a10 * (a24*a17*a6-a19*a22*a6-a24*a7*a16+a22*a9*a16+a19*a7*a21-a17*a9*a21);
	a[15]+= a15 * (a22*a14*a6-a9*a22*a11+a24*a7*a11-a12*a24*a6-a7*a14*a21+a12*a9*a21);
	a[15]+= a20 * (a12*a19*a6-a17*a14*a6-a19*a7*a11+a9*a17*a11+a7*a14*a16-a12*a9*a16);
	a[15]*= det_inv;
	
	a[16] = a0  * (a11*a17*a24-a11*a19*a22-a12*a16*a24+a12*a19*a21+a14*a16*a22-a14*a17*a21);
	a[16]+= a1  * (a10*a19*a22-a10*a17*a24+a12*a15*a24-a12*a19*a20-a14*a15*a22+a14*a17*a20);
	a[16]+= a2  * (a10*a16*a24-a10*a19*a21-a11*a15*a24+a11*a19*a20+a14*a15*a21-a14*a16*a20);
	a[16]+= a4  * (a10*a17*a21*+a11*a15*a22-a11*a17*a20-a12*a15*a21+a12*a16*a20-a10*a16*a22);
	a[16]*= det_inv;	
	
	a[17] = a0  * (a21*a9*a17-a6*a24*a17+a19*a6*a22-a0*a16*a9*a22+a24*a16*a7-a19*a21*a7);
	a[17]+= a1  * (a5*a24*a17-a5*a19*a22+a19*a20*a7-a20*a9*a17+a15*a9*a22-a24*a15*a7);
	a[17]+= a2  * (a5*a19*a21-a19*a6*a20-a5*a24*a16+a24*a6*a15-a15*a9*a21+a20*a9*a16);
	a[17]+= a4  * (a16*a5*a22-a6*a15*a22+a20*a6*a17-a5*a21*a17-a6*a15*a22+a21*a15*a7-a16*a20*a7);
	a[17]*= det_inv;	
	
	a[18] = a0  * (a12*a24*a6 - a14*a22*a6 - a11*a24*a7 + a14*a21*a7 + a11*a22*a9 - a12*a21*a9);
	a[18]+= a1  * (a14*a22*a5 - a12*a24*a5 + a10*a24*a7 - a14*a20*a7 - a10*a22*a9 + a12*a20*a9);
  a[18]+= a2  * (a11*a24*a5 - a11*a20*a9 + a14*a20*a6 - a14*a21*a5 + a10*a21*a9  - a10*a24*a6);  
  a[18]+= a4  * (a11*a20*a7 - a11*a22*a5 + a12*a21*a5 + a10*a22*a6 - a12*a20*a6 - a10*a21*a7);
	a[18]*= det_inv;	
	
	a[19] = a0  * (a12*a16*a9-a6*a12*a19+a6*a17*a14-a17*a11*a9+a11*a7*a19-a16*a7*a14);
	a[19]+= a1  * (a5*a12*a19-a5*a17*a14-a12*a15*a9+a17*a10*a9+a15*a7*a14-a10*a7*a19);
  a[19]+= a2  * (a11*a15*a9-a5*a11*a19+a5*a16*a14-a6*a15*a14+a6*a10*a19-a16*a10*a9);
	a[19]+= a4  * (a5*a17*a11-a5*a12*a16+a12*a6*a15+a10*a7*a16-a17*a6*a10-a15*a7*a11);
	a[19]*= det_inv;	
	
	a[20] = a5  * (a12*a18*a21-a12*a23*a16+a22*a13*a16-a18*a22*a11+a23*a17*a11-a17*a13*a21);
	a[20]+= a15 * (a12*a23*a6-a12*a8*a21+a8*a22*a11-a23*a7*a11+a7*a13*a21-a22*a13*a6);
	a[20]+= a20 * (a12*a8*a16-a12*a18*a6+a18*a7*a11-a8*a17*a11+a17*a13*a6-a7*a13*a16);
	a[20]+= a10 * (a17*a8*a21-a22*a8*a16-a18*a7*a21+a18*a22*a6+a23*a7*a16-a23*a17*a6);
	a[20]*= det_inv;	
	
	a[21] = a0  * (a12*a23*a16-a12*a18*a21+a17*a13*a21+a18*a22*a11-a23*a17*a11-a22*a13*a16);
	a[21]+= a1  * (a12*a18*a20-a12*a23*a15+a22*a13*a15+a23*a17*a10-a17*a13*a20-a18*a22*a10);
	a[21]+= a2  * (a18*a21*a10-a18*a11*a20-a21*a13*a15+a16*a13*a20-a23*a16*a10+a23*a11*a15);
	a[21]+= a3  * (a17*a11*a20-a12*a16*a20+a12*a21*a15-a21*a17*a10-a22*a11*a15+a16*a22*a10);
	a[21]*= det_inv;	
	
	a[22] = a0  *	(a18*a21*a7-a18*a6*a22+a23*a6*a17+a16*a8*a22-a21*a8*a17-a23*a16*a7);
	a[22]+= a1  * (a5*a18*a22-a5*a23*a17-a15*a8*a22+a20*a8*a17-a18*a20*a7+a23*a15*a7);
	a[22]+= a3  * (a16*a20*a7+a6*a15*a22-a6*a20*a17-a5*a16*a22+a5*a21*a17-a21*a15*a7);
	a[22]+= a2  * (a5*a23*a16-a5*a18*a21+a18*a6*a20+a15*a8*a21-a20*a8*a16-a23*a6*a15);
	a[22]*= det_inv;	
	
	a[23] =	a0  * (a12*a21*a8-a22*a11*a8+a11*a7*a23-a6*a12*a23-a21*a7*a13+a6*a22*a13);
	a[23]+=	a1  * (a5*a12*a23-a5*a22*a13-a10*a7*a23+a20*a7*a13+a22*a10*a8-a12*a20*a8);
	a[23]+= a2  * (a5*a21*a13+a11*a20*a8+a6*a10*a23-a5*a11*a23-a21*a10*a8-a6*a20*a13);
	a[23]+= a3  * (a5*a22*a11-a5*a12*a21+a10*a7*a21-a22*a6*a10-a20*a7*a11+a12*a6*a20);
	a[23]*= det_inv;		
	
	a[24] =	a0  * (a17*a11*a8-a11*a7*a18+a6*a12*a18-a12*a16*a8+a16*a7*a13-a6*a17*a13);
	a[24]+= a1  * (a5*a17*a13-a5*a12*a18+a10*a7*a18+a12*a15*a8-a17*a10*a8-a15*a7*a13);
	a[24]+= a2  * (a5*a11*a18-a5*a16*a13+a16*a10*a8+a6*a15*a13-a11*a15*a8-a6*a10*a18);
	a[24]+= a3  * (a5*a12*a16+a17*a6*a10-a5*a17*a11-a12*a6*a15-a10*a7*a16+a15*a7*a11);
	a[24]*= det_inv;		
}

/**
 * \fn void fasp_blas_smat_inv_nc7 (double *a)
 * \brief comput the inverse matrix of a 7*7 matrix a
 *
 * \param *a pointer to the double vector which stands a 7*7 matrix 
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_inv_nc7 (double *a)
{	
	// Do nothing -- Chensong! Should never be called.
	fasp_blas_smat_inv(a,7);
}

/**
 * \fn int fasp_blas_smat_inv(double *a, int n)
 * \brief compute the inverse matrix of a small full matrix a
 *
 * \param *a   pointer to the double vector which stands a n*n matrix
 * \param  n   the dimension of the matrix
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 04/21/2010  
 */
int fasp_blas_smat_inv (double *a, 
                        int n)
{ 
	
	switch (n)
	{
		case 2:
			fasp_blas_smat_inv_nc2(a);
			break;
		 
		case 3:
			fasp_blas_smat_inv_nc3(a);
			break;
		case 5: 
			fasp_blas_smat_inv_nc5(a);
			break;			
		default:
		{ int i,j,k,l,u,kn,in;
			double alinv;
			
			for (k=0; k<n; ++k){
				
				kn = k*n;
				l  = kn+k;
				
				if (ABS(a[l]) < SMALLREAL){
					printf("Warning: An diagonal entry of a dense matrix is close to 0!!  a[%d,%d] = %e \n", k,k,a[l]);
					a[l] = SMALLREAL;
				}
				alinv = 1.0/a[l];
				a[l] = alinv;
				
				for (j=0; j<k; ++j) {
					u = kn+j; a[u] *= alinv;
				}
				
				for (j=k+1; j<n; ++j) {
					u = kn+j; a[u] *= alinv;
				}
				
				for (i=0; i<k; ++i) {
					in = i*n;
					for (j=0; j<n; ++j)
						if (j!=k) { 
							u = in+j; a[u] -= a[in+k]*a[kn+j];
						} //! end if (j!=k)
				}
				
				for (i=k+1; i<n; ++i) {
					in = i*n;
					for (j=0; j<n; ++j)
						if (j!=k) { 
							u = in+j; a[u] -= a[in+k]*a[kn+j];
						} //! end if (j!=k)
				}
				
				for (i=0; i<k; ++i) {
					u=i*n+k; a[u] *= -alinv;
				}
				
				for (i=k+1; i<n; ++i) {
					u=i*n+k; a[u] *= -alinv;
				}				
				
			} //! end for (k=0; k<n; ++k)
			break;
		}
			
	}
	
	return SUCCESS;
}

/**
 * \fn void fasp_blas_smat_mul_nc2(double *a, double *b, double *c)
 * \brief compute the matrix product of two 2* matrices a and b, stored in c
 *
 * \param *a pointer to the double vector which stands a n*n matrix
 * \param *b pointer to the double vector which stands a n*n matrix
 * \param *c pointer to the double vector which stands a n*n matrix
 * 
 * \author Xiaozhe Hu
 * \date 18/11/2011
 */
void fasp_blas_smat_mul_nc2 (double *a, 
							 double *b, 
							 double *c)
{ 
	const double a0 = a[0], a1 = a[1];
	const double a2 = a[2], a3 = a[3];
	
	const double b0 = b[0], b1 = b[1];
	const double b2 = b[2], b3 = b[3];
	
	c[0] = a0*b0 + a1*b2;
	c[1] = a0*b1 + a1*b3;
	c[2] = a2*b0 + a3*b2;
	c[3] = a2*b1 + a3*b3;

}

/**
 * \fn void fasp_blas_smat_mul_nc3(double *a, double *b, double *c)
 * \brief compute the matrix product of two 3*3 matrices a and b, stored in c
 *
 * \param *a pointer to the double vector which stands a n*n matrix
 * \param *b pointer to the double vector which stands a n*n matrix
 * \param *c pointer to the double vector which stands a n*n matrix
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_mul_nc3 (double *a, 
														 double *b, 
														 double *c)
{ 
	const double a0 = a[0], a1 = a[1], a2 = a[2];
	const double a3 = a[3], a4 = a[4], a5 = a[5];
	const double a6 = a[6], a7 = a[7], a8 = a[8];
	
	const double b0 = b[0], b1 = b[1], b2 = b[2];
	const double b3 = b[3], b4 = b[4], b5 = b[5];
	const double b6 = b[6], b7 = b[7], b8 = b[8];
	
	c[0] = a0*b0 + a1*b3 + a2*b6;
	c[1] = a0*b1 + a1*b4 + a2*b7;
	c[2] = a0*b2 + a1*b5 + a2*b8;
	
	c[3] = a3*b0 + a4*b3 + a5*b6;
	c[4] = a3*b1 + a4*b4 + a5*b7;
	c[5] = a3*b2 + a4*b5 + a5*b8;
	
	c[6] = a6*b0 + a7*b3 + a8*b6;
	c[7] = a6*b1 + a7*b4 + a8*b7;
	c[8] = a6*b2 + a7*b5 + a8*b8;
}

/**
 * \fn void fasp_blas_smat_mul_nc5(double *a, double *b, double *c)
 * \breif compute the matrix product of two 5*5 matrices a and b, stored in c
 *
 * \param *a pointer to the double vector which stands a 5*5 matrix
 * \param *b pointer to the double vector which stands a 5*5 matrix
 * \param *c pointer to the double vector which stands a 5*5 matrix
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_mul_nc5 (double *a, 
														 double *b, 
														 double *c)
{ 
	const double a0  = a[0],  a1  = a[1],  a2  = a[2],  a3  = a[3],  a4  = a[4];
	const double a5  = a[5],  a6  = a[6],  a7  = a[7],  a8  = a[8],  a9  = a[9];
	const double a10 = a[10], a11 = a[11], a12 = a[12], a13 = a[13], a14 = a[14];
	const double a15 = a[15], a16 = a[16], a17 = a[17], a18 = a[18], a19 = a[19];
	const double a20 = a[20], a21 = a[21], a22 = a[22], a23 = a[23], a24 = a[24];
	
	const double b0  = b[0],  b1  = b[1],  b2  = b[2],  b3  = b[3],  b4  = b[4];
	const double b5  = b[5],  b6  = b[6],  b7  = b[7],  b8  = b[8],  b9  = b[9];
	const double b10 = b[10], b11 = b[11], b12 = b[12], b13 = b[13], b14 = b[14];
	const double b15 = b[15], b16 = b[16], b17 = b[17], b18 = b[18], b19 = b[19];
	const double b20 = b[20], b21 = b[21], b22 = b[22], b23 = b[23], b24 = b[24];
	
	c[0] = a0*b0 + a1*b5 + a2*b10 + a3*b15 + a4*b20;
	c[1] = a0*b1 + a1*b6 + a2*b11 + a3*b16 + a4*b21;
	c[2] = a0*b2 + a1*b7 + a2*b12 + a3*b17 + a4*b22;
	c[3] = a0*b3 + a1*b8 + a2*b13 + a3*b18 + a4*b23;
	c[4] = a0*b4 + a1*b9 + a2*b14 + a3*b19 + a4*b24;
	
	c[5] = a5*b0 + a6*b5 + a7*b10 + a8*b15 + a9*b20;
	c[6] = a5*b1 + a6*b6 + a7*b11 + a8*b16 + a9*b21;
	c[7] = a5*b2 + a6*b7 + a7*b12 + a8*b17 + a9*b22;
	c[8] = a5*b3 + a6*b8 + a7*b13 + a8*b18 + a9*b23;
	c[9] = a5*b4 + a6*b9 + a7*b14 + a8*b19 + a9*b24;
	
	c[10] = a10*b0 + a11*b5 + a12*b10 + a13*b15 + a14*b20;
	c[11] = a10*b1 + a11*b6 + a12*b11 + a13*b16 + a14*b21;
	c[12] = a10*b2 + a11*b7 + a12*b12 + a13*b17 + a14*b22;
	c[13] = a10*b3 + a11*b8 + a12*b13 + a13*b18 + a14*b23;
	c[14] = a10*b4 + a11*b9 + a12*b14 + a13*b19 + a14*b24;
	
	c[15] = a15*b0 + a16*b5 + a17*b10 + a18*b15 + a19*b20;
	c[16] = a15*b1 + a16*b6 + a17*b11 + a18*b16 + a19*b21;
	c[17] = a15*b2 + a16*b7 + a17*b12 + a18*b17 + a19*b22;
	c[18] = a15*b3 + a16*b8 + a17*b13 + a18*b18 + a19*b23;
	c[19] = a15*b4 + a16*b9 + a17*b14 + a18*b19 + a19*b24;
	
	c[20] = a20*b0 + a21*b5 + a22*b10 + a23*b15 + a24*b20;
	c[21] = a20*b1 + a21*b6 + a22*b11 + a23*b16 + a24*b21;
	c[22] = a20*b2 + a21*b7 + a22*b12 + a23*b17 + a24*b22;
	c[23] = a20*b3 + a21*b8 + a22*b13 + a23*b18 + a24*b23;
	c[24] = a20*b4 + a21*b9 + a22*b14 + a23*b19 + a24*b24;
}

/**
 * \fn void fasp_blas_smat_mul_nc7(double *a, double *b, double *c)
 * \brief compute the matrix product of two 7*7 matrices a and b, stored in c
 *
 * \param *a pointer to the double vector which stands a 7*7 matrix
 * \param *b pointer to the double vector which stands a 7*7 matrix
 * \param *c pointer to the double vector which stands a 7*7 matrix
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_smat_mul_nc7 (double *a, 
														 double *b, 
														 double *c)
{ 
	const double a0  = a[0],  a1  = a[1],  a2  = a[2],  a3  = a[3],  a4  = a[4],  a5  = a[5],  a6  = a[6];
	const double a7  = a[7],  a8  = a[8],  a9  = a[9],  a10 = a[10], a11 = a[11], a12 = a[12], a13 = a[13];
	const double a14 = a[14], a15 = a[15], a16 = a[16], a17 = a[17], a18 = a[18], a19 = a[19], a20 = a[20];
	const double a21 = a[21], a22 = a[22], a23 = a[23], a24 = a[24], a25 = a[25], a26 = a[26], a27 = a[27];
	const double a28 = a[28], a29 = a[29], a30 = a[30], a31 = a[31], a32 = a[32], a33 = a[33], a34 = a[34];
	const double a35 = a[35], a36 = a[36], a37 = a[37], a38 = a[38], a39 = a[39], a40 = a[40], a41 = a[41];
	const double a42 = a[42], a43 = a[43], a44 = a[44], a45 = a[45], a46 = a[46], a47 = a[47], a48 = a[48];
	
	const double b0  = b[0],  b1  = b[1],  b2  = b[2],  b3  = b[3],  b4  = b[4],  b5  = b[5],  b6  = b[6];
	const double b7  = b[7],  b8  = b[8],  b9  = b[9],  b10 = b[10], b11 = b[11], b12 = b[12], b13 = b[13];
	const double b14 = b[14], b15 = b[15], b16 = b[16], b17 = b[17], b18 = b[18], b19 = b[19], b20 = b[20];
	const double b21 = b[21], b22 = b[22], b23 = b[23], b24 = b[24], b25 = b[25], b26 = b[26], b27 = b[27];
	const double b28 = b[28], b29 = b[29], b30 = b[30], b31 = b[31], b32 = b[32], b33 = b[33], b34 = b[34];
	const double b35 = b[35], b36 = b[36], b37 = b[37], b38 = b[38], b39 = b[39], b40 = b[40], b41 = b[41];
	const double b42 = b[42], b43 = b[43], b44 = b[44], b45 = b[45], b46 = b[46], b47 = b[47], b48 = b[48];
	
	c[0] = a0*b0 + a1*b7 +  a2*b14 + a3*b21 + a4*b28 + a5*b35 + a6*b42;
	c[1] = a0*b1 + a1*b8 +  a2*b15 + a3*b22 + a4*b29 + a5*b36 + a6*b43;
	c[2] = a0*b2 + a1*b9 +  a2*b16 + a3*b23 + a4*b30 + a5*b37 + a6*b44;
	c[3] = a0*b3 + a1*b10 + a2*b17 + a3*b24 + a4*b31 + a5*b38 + a6*b45;
	c[4] = a0*b4 + a1*b11 + a2*b18 + a3*b25 + a4*b32 + a5*b39 + a6*b46;
	c[5] = a0*b5 + a1*b12 + a2*b19 + a3*b26 + a4*b33 + a5*b40 + a6*b47;
	c[6] = a0*b6 + a1*b13 + a2*b20 + a3*b27 + a4*b34 + a5*b41 + a6*b48;
	
	c[7]  = a7*b0 + a8*b7 +  a9*b14 + a10*b21 + a11*b28 + a12*b35 + a13*b42;
	c[8]  = a7*b1 + a8*b8 +  a9*b15 + a10*b22 + a11*b29 + a12*b36 + a13*b43;
	c[9]  = a7*b2 + a8*b9 +  a9*b16 + a10*b23 + a11*b30 + a12*b37 + a13*b44;
	c[10] = a7*b3 + a8*b10 + a9*b17 + a10*b24 + a11*b31 + a12*b38 + a13*b45;
	c[11] = a7*b4 + a8*b11 + a9*b18 + a10*b25 + a11*b32 + a12*b39 + a13*b46;
	c[12] = a7*b5 + a8*b12 + a9*b19 + a10*b26 + a11*b33 + a12*b40 + a13*b47;
	c[13] = a7*b6 + a8*b13 + a9*b20 + a10*b27 + a11*b34 + a12*b41 + a13*b48;
	
	c[14] = a14*b0 + a15*b7 +  a16*b14 + a17*b21 + a18*b28 + a19*b35 + a20*b42;
	c[15] = a14*b1 + a15*b8 +  a16*b15 + a17*b22 + a18*b29 + a19*b36 + a20*b43;
	c[16] = a14*b2 + a15*b9 +  a16*b16 + a17*b23 + a18*b30 + a19*b37 + a20*b44;
	c[17] = a14*b3 + a15*b10 + a16*b17 + a17*b24 + a18*b31 + a19*b38 + a20*b45;
	c[18] = a14*b4 + a15*b11 + a16*b18 + a17*b25 + a18*b32 + a19*b39 + a20*b46;
	c[19] = a14*b5 + a15*b12 + a16*b19 + a17*b26 + a18*b33 + a19*b40 + a20*b47;
	c[20] = a14*b6 + a15*b13 + a16*b20 + a17*b27 + a18*b34 + a19*b41 + a20*b48;
	
	c[21] = a21*b0 + a22*b7 +  a23*b14 + a24*b21 + a25*b28 + a26*b35 + a27*b42;
	c[22] = a21*b1 + a22*b8 +  a23*b15 + a24*b22 + a25*b29 + a26*b36 + a27*b43;
	c[23] = a21*b2 + a22*b9 +  a23*b16 + a24*b23 + a25*b30 + a26*b37 + a27*b44;
	c[24] = a21*b3 + a22*b10 + a23*b17 + a24*b24 + a25*b31 + a26*b38 + a27*b45;
	c[25] = a21*b4 + a22*b11 + a23*b18 + a24*b25 + a25*b32 + a26*b39 + a27*b46;
	c[26] = a21*b5 + a22*b12 + a23*b19 + a24*b26 + a25*b33 + a26*b40 + a27*b47;
	c[27] = a21*b6 + a22*b13 + a23*b20 + a24*b27 + a25*b34 + a26*b41 + a27*b48;
	
	c[28] = a28*b0 + a29*b7 +  a30*b14 + a31*b21 + a32*b28 + a33*b35 + a34*b42;
	c[29] = a28*b1 + a29*b8 +  a30*b15 + a31*b22 + a32*b29 + a33*b36 + a34*b43;
	c[30] = a28*b2 + a29*b9 +  a30*b16 + a31*b23 + a32*b30 + a33*b37 + a34*b44;
	c[31] = a28*b3 + a29*b10 + a30*b17 + a31*b24 + a32*b31 + a33*b38 + a34*b45;
	c[32] = a28*b4 + a29*b11 + a30*b18 + a31*b25 + a32*b32 + a33*b39 + a34*b46;
	c[33] = a28*b5 + a29*b12 + a30*b19 + a31*b26 + a32*b33 + a33*b40 + a34*b47;
	c[34] = a28*b6 + a29*b13 + a30*b20 + a31*b27 + a32*b34 + a33*b41 + a34*b48;
	
	c[35] = a35*b0 + a36*b7 +  a37*b14 + a38*b21 + a39*b28 + a40*b35 + a41*b42;
	c[36] = a35*b1 + a36*b8 +  a37*b15 + a38*b22 + a39*b29 + a40*b36 + a41*b43;
	c[37] = a35*b2 + a36*b9 +  a37*b16 + a38*b23 + a39*b30 + a40*b37 + a41*b44;
	c[38] = a35*b3 + a36*b10 + a37*b17 + a38*b24 + a39*b31 + a40*b38 + a41*b45;
	c[39] = a35*b4 + a36*b11 + a37*b18 + a38*b25 + a39*b32 + a40*b39 + a41*b46;
	c[40] = a35*b5 + a36*b12 + a37*b19 + a38*b26 + a39*b33 + a40*b40 + a41*b47;
	c[41] = a35*b6 + a36*b13 + a37*b20 + a38*b27 + a39*b34 + a40*b41 + a41*b48;
	
	c[42] = a42*b0 + a43*b7 +  a44*b14 + a45*b21 + a46*b28 + a47*b35 + a48*b42;
	c[43] = a42*b1 + a43*b8 +  a44*b15 + a45*b22 + a46*b29 + a47*b36 + a48*b43;
	c[44] = a42*b2 + a43*b9 +  a44*b16 + a45*b23 + a46*b30 + a47*b37 + a48*b44;
	c[45] = a42*b3 + a43*b10 + a44*b17 + a45*b24 + a46*b31 + a47*b38 + a48*b45;
	c[46] = a42*b4 + a43*b11 + a44*b18 + a45*b25 + a46*b32 + a47*b39 + a48*b46;
	c[47] = a42*b5 + a43*b12 + a44*b19 + a45*b26 + a46*b33 + a47*b40 + a48*b47;
	c[48] = a42*b6 + a43*b13 + a44*b20 + a45*b27 + a46*b34 + a47*b41 + a48*b48;
}

/**
 * \fn void fasp_blas_smat_mul(double *a, double *b, double *c, int n)
 * \brief compute the matrix product of two small full matrices a and b, stored in c
 *
 * \param *a pointer to the double vector which stands a n*n matrix
 * \param *b pointer to the double vector which stands a n*n matrix
 * \param *c pointer to the double vector which stands a n*n matrix
 * \param  n the dimension of the matrix
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 04/21/2010  
 */
void fasp_blas_smat_mul (double *a, 
												 double *b, 
												 double *c, 
												 int n)
{ 
	
	switch (n)
	{
		case 2: 
			fasp_blas_smat_mul_nc2(a, b, c); break;
		
		case 3:
			fasp_blas_smat_mul_nc3(a, b, c); break;
			
		case 5: 
			fasp_blas_smat_mul_nc5(a, b, c); break;
			
		case 7:
			fasp_blas_smat_mul_nc7(a, b, c); break;
			
		default:
		{ const int n2 = n*n;
			int i,j,k;
			double temp;
			
			for (i=0; i<n2; i+=n){
				for (j=0; j<n; ++j){ 
					temp = 0.0; // Fixed by Cheosong. Feb/22/2011.
					for (k=0; k<n; ++k) temp += a[i+k]*b[k*n+j];
					c[i+j] = temp;
				} //! end for j
			} //! end for i
		}
			break;
	}			
	return;
}

/**
 * \fn void fasp_blas_array_axpyz_nc2(double a, double *x, double *y, double *z)
 * \brief z = a*x + y, z is the third vector and the length of x, y and z is 2
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector 1
 * \param *y   pointer to the original vector 2
 * \param *z   pointer to the destination vector
 * 
 * \author Xiaozhe Hu
 * \date 18/11/2011
 */
void fasp_blas_array_axpyz_nc2 (double a, 
                                double *x, 
								double *y, 
								double *z) 
{
	z[0] = a*x[0] + y[0];
	z[1] = a*x[1] + y[1];
	
	z[2] = a*x[2] + y[2];
	z[3] = a*x[3] + y[3];
	
}

/**
 * \fn void fasp_blas_array_axpyz_nc3(double a, double *x, double *y, double *z)
 * \brief z = a*x + y, z is the third vector and the length of x, y and z is 3
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector 1
 * \param *y   pointer to the original vector 2
 * \param *z   pointer to the destination vector
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_array_axpyz_nc3 (double a, 
                                double *x, 
																double *y, 
																double *z) 
{
	z[0] = a*x[0] + y[0];
	z[1] = a*x[1] + y[1];
	z[2] = a*x[2] + y[2];
	
	z[3] = a*x[3] + y[3];
	z[4] = a*x[4] + y[4];
	z[5] = a*x[5] + y[5];
	
	z[6] = a*x[6] + y[6];
	z[7] = a*x[7] + y[7];
	z[8] = a*x[8] + y[8];  
}

/**
 * \fn void fasp_blas_array_axpyz_nc5(double a, double *x, double *y, double *z)
 * \brief z = a*x + y, z is the third vector and the length of x, y and z is 5
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector 1
 * \param *y   pointer to the original vector 2
 * \param *z   pointer to the destination vector
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_array_axpyz_nc5 (double a, 
                                double *x, 
																double *y, 
																double *z) 
{
	z[0] = a*x[0] + y[0];
	z[1] = a*x[1] + y[1];
	z[2] = a*x[2] + y[2];
	z[3] = a*x[3] + y[3];
	z[4] = a*x[4] + y[4];
	
	z[5] = a*x[5] + y[5];
	z[6] = a*x[6] + y[6];
	z[7] = a*x[7] + y[7];
	z[8] = a*x[8] + y[8];  
	z[9] = a*x[9] + y[9];  
	
	z[10] = a*x[10] + y[10];
	z[11] = a*x[11] + y[11];
	z[12] = a*x[12] + y[12];
	z[13] = a*x[13] + y[13];
	z[14] = a*x[14] + y[14];
	
	z[15] = a*x[15] + y[15];
	z[16] = a*x[16] + y[16];
	z[17] = a*x[17] + y[17];
	z[18] = a*x[18] + y[18];  
	z[19] = a*x[19] + y[19];
	
	z[20] = a*x[20] + y[20];
	z[21] = a*x[21] + y[21];
	z[22] = a*x[22] + y[22];
	z[23] = a*x[23] + y[23];
	z[24] = a*x[24] + y[24];
}

/**
 * \fn void fasp_blas_array_axpyz_nc7(double a, double *x, double *y, double *z)
 * \brief z = a*x + y, z is the third vector and the length of x, y and z is 7
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector 1
 * \param *y   pointer to the original vector 2
 * \param *z   pointer to the destination vector
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_array_axpyz_nc7 (double a, 
                                double *x, 
																double *y, 
																double *z) 
{
	z[0] = a*x[0] + y[0];
	z[1] = a*x[1] + y[1];
	z[2] = a*x[2] + y[2];
	z[3] = a*x[3] + y[3];
	z[4] = a*x[4] + y[4];
	z[5] = a*x[5] + y[5];
	z[6] = a*x[6] + y[6];
	
	z[7] = a*x[7] + y[7];
	z[8] = a*x[8] + y[8];  
	z[9] = a*x[9] + y[9];  
	z[10] = a*x[10] + y[10];
	z[11] = a*x[11] + y[11];
	z[12] = a*x[12] + y[12];
	z[13] = a*x[13] + y[13];
	
	z[14] = a*x[14] + y[14];
	z[15] = a*x[15] + y[15];
	z[16] = a*x[16] + y[16];
	z[17] = a*x[17] + y[17];
	z[18] = a*x[18] + y[18];  
	z[19] = a*x[19] + y[19];
	z[20] = a*x[20] + y[20];
	
	z[21] = a*x[21] + y[21];
	z[22] = a*x[22] + y[22];
	z[23] = a*x[23] + y[23];
	z[24] = a*x[24] + y[24];
	z[25] = a*x[25] + y[25];
	z[26] = a*x[26] + y[26];
	z[27] = a*x[27] + y[27];
	
	z[28] = a*x[28] + y[28];  
	z[29] = a*x[29] + y[29];  
	z[30] = a*x[30] + y[30];
	z[31] = a*x[31] + y[31];
	z[32] = a*x[32] + y[32];
	z[33] = a*x[33] + y[33];
	z[34] = a*x[34] + y[34];
	
	z[35] = a*x[35] + y[35];
	z[36] = a*x[36] + y[36];
	z[37] = a*x[37] + y[37];
	z[38] = a*x[38] + y[38];  
	z[39] = a*x[39] + y[39];  
	z[40] = a*x[40] + y[40];
	z[41] = a*x[41] + y[41];
	
	z[42] = a*x[42] + y[42];
	z[43] = a*x[43] + y[43];
	z[44] = a*x[44] + y[44];
	z[45] = a*x[45] + y[45];
	z[46] = a*x[46] + y[46];
	z[47] = a*x[47] + y[47];
	z[48] = a*x[48] + y[48];  
}

/**
 * \fn void fasp_blas_array_axpy_nc2(double a, double *x, double *y)
 * \brief y = a*x + y, the length of x and y is 2
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector
 * \param *y   pointer to the destination vector
 * 
 * \author Xiaozhe Hu
 * \date 18/11/2011
 */
void fasp_blas_array_axpy_nc2 (double a, 
                               double *x, 
							   double *y) 
{
	y[0] += a*x[0];
	y[1] += a*x[1];
	
	y[2] += a*x[2];
	y[3] += a*x[3];
	
}

/**
 * \fn void fasp_blas_array_axpy_nc3(double a, double *x, double *y)
 * \brief y = a*x + y, the length of x and y is 3
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector
 * \param *y   pointer to the destination vector
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_array_axpy_nc3 (double a, 
                               double *x, 
															 double *y) 
{
	y[0] += a*x[0];
	y[1] += a*x[1];
	y[2] += a*x[2];
	
	y[3] += a*x[3];
	y[4] += a*x[4];
	y[5] += a*x[5];
	
	y[6] += a*x[6];
	y[7] += a*x[7];
	y[8] += a*x[8];
}

/**
 * \fn void fasp_blas_array_axpy_nc5(double a, double *x, double *y)
 * \brief y = a*x + y, the length of x and y is 5
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector
 * \param *y   pointer to the destination vector
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_array_axpy_nc5 (double a, 
                               double *x, 
															 double *y) 
{
	y[0] += a*x[0];
	y[1] += a*x[1];
	y[2] += a*x[2];
	y[3] += a*x[3];
	y[4] += a*x[4];
	
	y[5] += a*x[5];
	y[6] += a*x[6];
	y[7] += a*x[7];
	y[8] += a*x[8];
	y[9] += a*x[9];
	
	y[10] += a*x[10];
	y[11] += a*x[11];
	y[12] += a*x[12];
	y[13] += a*x[13];
	y[14] += a*x[14];
	
	y[15] += a*x[15];
	y[16] += a*x[16];
	y[17] += a*x[17];
	y[18] += a*x[18];
	y[19] += a*x[19];
	
	y[20] += a*x[20];
	y[21] += a*x[21];
	y[22] += a*x[22];
	y[23] += a*x[23];
	y[24] += a*x[24];
}

/**
 * \fn void fasp_blas_array_axpy_nc7(double a, double *x, double *y)
 * \brief y = a*x + y, the length of x and y is 7
 *
 * \param  a   a real number
 * \param *x   pointer to the original vector
 * \param *y   pointer to the destination vector
 * 
 * \author Xiaozhe Hu, Shiquan Zhang
 * \date 05/01/2010
 */
void fasp_blas_array_axpy_nc7 (double a, 
                               double *x, 
															 double *y) 
{
	y[0] += a*x[0];
	y[1] += a*x[1];
	y[2] += a*x[2];
	y[3] += a*x[3];
	y[4] += a*x[4];
	y[5] += a*x[5];
	y[6] += a*x[6];
	
	y[7] += a*x[7];
	y[8] += a*x[8];
	y[9] += a*x[9];
	y[10] += a*x[10];
	y[11] += a*x[11];
	y[12] += a*x[12];
	y[13] += a*x[13];
	
	y[14] += a*x[14];
	y[15] += a*x[15];
	y[16] += a*x[16];
	y[17] += a*x[17];
	y[18] += a*x[18];
	y[19] += a*x[19];
	y[20] += a*x[20];
	
	y[21] += a*x[21];
	y[22] += a*x[22];
	y[23] += a*x[23];
	y[24] += a*x[24];
	y[25] += a*x[25];
	y[26] += a*x[26];
	y[27] += a*x[27];
	
	y[28] += a*x[28];
	y[29] += a*x[29];
	y[30] += a*x[30];
	y[31] += a*x[31];
	y[32] += a*x[32];
	y[33] += a*x[33];
	y[34] += a*x[34];
	
	y[35] += a*x[35];
	y[36] += a*x[36];
	y[37] += a*x[37];
	y[38] += a*x[38];
	y[39] += a*x[39];
	y[40] += a*x[40];
	y[41] += a*x[41];
	
	y[42] += a*x[42];
	y[43] += a*x[43];
	y[44] += a*x[44];
	y[45] += a*x[45];
	y[46] += a*x[46];
	y[47] += a*x[47];
	y[48] += a*x[48];
}

/**
 * \fn void fasp_blas_smat_ypAx_nc2(double *A, double *x, double *y)
 * \brief Compute y := y + Ax, where 'A' is a 2*2 dense matrix 
 *
 * \param *A   pointer to the 3*3 dense matrix
 * \param *x   pointer to the double vector with length 3
 * \param *y   pointer to the double vector with length 3
 *
 * \author Xiaozhe Hu
 * \date 2011/11/18
 */
void fasp_blas_smat_ypAx_nc2 (double *A, 
							  double *x, 
							  double *y )
{	double x0,x1;
	x0=x[0];
	x1=x[1];
	
	y[0] += A[0]*x0 + A[1]*x1;
	y[1] += A[2]*x0 + A[3]*x1;
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ypAx_nc3(double *A, double *x, double *y)
 * \brief Compute y := y + Ax, where 'A' is a 3*3 dense matrix 
 *
 * \param *A   pointer to the 3*3 dense matrix
 * \param *x   pointer to the double vector with length 3
 * \param *y   pointer to the double vector with length 3
 *
 * \author Zhiyang Zhou, Xiaozhe Hu
 * \date 2010/10/25
 */
void fasp_blas_smat_ypAx_nc3 (double *A, 
															double *x, 
															double *y )
{	double x0,x1,x2;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	
	y[0] += A[0]*x0 + A[1]*x1 + A[2]*x2;
	y[1] += A[3]*x0 + A[4]*x1 + A[5]*x2;
	y[2] += A[6]*x0 + A[7]*x1 + A[8]*x2;
	return;
} 

/**
 * \fn void fasp_blas_smat_ypAx_nc5(double *A, double *x, double *y)
 * \brief Compute y := y + Ax, where 'A' is a 5*5 dense matrix 
 *
 * \param *A   pointer to the 5*5 dense matrix
 * \param *x   pointer to the double vector with length 5
 * \param *y   pointer to the double vector with length 5
 *
 * \author Zhiyang Zhou, Xiaozhe Hu
 * \date 2010/10/25
 */
void fasp_blas_smat_ypAx_nc5 (double *A, 
															double *x,
															double *y )
{	double x0,x1,x2,x3,x4;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	x3=x[3];
	x4=x[4];
	
	y[0] += A[0]*x0 + A[1]*x1 + A[2]*x2 + A[3]*x3 + A[4]*x4;
	y[1] += A[5]*x0 + A[6]*x1 + A[7]*x2 + A[8]*x3 + A[9]*x4;
	y[2] += A[10]*x0 + A[11]*x1 + A[12]*x2 + A[13]*x3 + A[14]*x4;
	y[3] += A[15]*x0 + A[16]*x1 + A[17]*x2 + A[18]*x3 + A[19]*x4;
	y[4] += A[20]*x0 + A[21]*x1 + A[22]*x2 + A[23]*x3 + A[24]*x4;
	return;
} 

/**
 * \fn void fasp_blas_smat_ypAx_nc7(double *A, double *x, double *y)
 * \brief Compute y := y + Ax, where 'A' is a 7*7 dense matrix 
 *
 * \param *A   pointer to the 7*7 dense matrix
 * \param *x   pointer to the double vector with length 7
 * \param *y   pointer to the double vector with length 7
 *
 * \author Zhiyang Zhou, Xiaozhe Hu
 * \date 2010/10/25
 */
void fasp_blas_smat_ypAx_nc7 (double *A, 
															double *x, 
															double *y)
{	
	double x0,x1,x2,x3,x4,x5,x6;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	x3=x[3];
	x4=x[4];
	x5=x[5];
	x6=x[6];
	y[0] += A[0]*x0 + A[1]*x1 +    A[2]*x2 +  A[3]*x3 +  A[4]*x4 +  A[5]*x5 +  A[6]*x6;
	y[1] += A[7]*x0 + A[8]*x1 +    A[9]*x2 + A[10]*x3 + A[11]*x4 + A[12]*x5 + A[13]*x6;
	y[2] += A[14]*x0 + A[15]*x1 + A[16]*x2 + A[17]*x3 + A[18]*x4 + A[19]*x5 + A[20]*x6;
	y[3] += A[21]*x0 + A[22]*x1 + A[23]*x2 + A[24]*x3 + A[25]*x4 + A[26]*x5 + A[27]*x6;
	y[4] += A[28]*x0 + A[29]*x1 + A[30]*x2 + A[31]*x3 + A[32]*x4 + A[33]*x5 + A[34]*x6;
	y[5] += A[35]*x0 + A[36]*x1 + A[37]*x2 + A[38]*x3 + A[39]*x4 + A[40]*x5 + A[41]*x6;
	y[6] += A[42]*x0 + A[43]*x1 + A[44]*x2 + A[45]*x3 + A[46]*x4 + A[47]*x5 + A[48]*x6;
	return;
} 

/**
 * \fn void fasp_blas_smat_ypAx(double *A, double *x, double *y, int n)
 * \brief Compute y := y + Ax, where 'A' is a n*n dense matrix 
 *
 * \param *A   pointer to the n*n dense matrix
 * \param *x   pointer to the double vector with length n
 * \param *y   pointer to the double vector with length n
 * \param  n   the dimension of the dense matrix
 *
 * \author Zhiyang Zhou
 * \date 2010/10/25
 */
void fasp_blas_smat_ypAx (double *A, 
													double *x, 
													double *y, 
													int n)
{	
	switch (n) {
		case 2:
			{
			double x0,x1;
			x0=x[0];x1=x[1];
			y[0] += A[0]*x0 + A[1]*x1;
			y[1] += A[2]*x0 + A[3]*x1;
			break;
			}
		case 3:
			{
			double x0,x1,x2;
			x0=x[0];x1=x[1];x2=x[2];
			y[0] += A[0]*x0 + A[1]*x1 + A[2]*x2;
			y[1] += A[3]*x0 + A[4]*x1 + A[5]*x2;
			y[2] += A[6]*x0 + A[7]*x1 + A[8]*x2;
			break;
			}
		case 4:
			{
			double x0,x1,x2,x3;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];
			y[0] +=  A[0]*x0 + A[1]*x1 +  A[2]*x2 + A[3]*x3;
			y[1] +=  A[4]*x0 + A[5]*x1 +  A[6]*x2 + A[7]*x3;
			y[2] +=  A[8]*x0 + A[9]*x1 + A[10]*x2 + A[11]*x3;
			y[3] += A[12]*x0 + A[13]*x1 +A[14]*x2 + A[15]*x3;
			break;
			}
		case 5:
			{
			double x0,x1,x2,x3,x4;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];
			y[0] +=  A[0]*x0 +  A[1]*x1 +  A[2]*x2 +  A[3]*x3 +  A[4]*x4;
			y[1] +=  A[5]*x0 +  A[6]*x1 +  A[7]*x2 +  A[8]*x3 +  A[9]*x4;
			y[2] += A[10]*x0 + A[11]*x1 + A[12]*x2 + A[13]*x3 + A[14]*x4;
			y[3] += A[15]*x0 + A[16]*x1 + A[17]*x2 + A[18]*x3 + A[19]*x4;
			y[4] += A[20]*x0 + A[21]*x1 + A[22]*x2 + A[23]*x3 + A[24]*x4;
			break;
			}	
		case 6:
			{
			double x0,x1,x2,x3,x4,x5;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];x5=x[5];
			y[0] +=  A[0]*x0 +  A[1]*x1 +  A[2]*x2 +  A[3]*x3 +  A[4]*x4 +  A[5]*x5;
			y[1] +=  A[6]*x0 +  A[7]*x1 +  A[8]*x2 +  A[9]*x3 + A[10]*x4 + A[11]*x5;
			y[2] += A[12]*x0 + A[13]*x1 + A[14]*x2 + A[15]*x3 + A[16]*x4 + A[17]*x5;
			y[3] += A[18]*x0 + A[19]*x1 + A[20]*x2 + A[21]*x3 + A[22]*x4 + A[23]*x5;
			y[4] += A[24]*x0 + A[25]*x1 + A[26]*x2 + A[27]*x3 + A[28]*x4 + A[29]*x5;
			y[5] += A[30]*x0 + A[31]*x1 + A[32]*x2 + A[33]*x3 + A[34]*x4 + A[35]*x5;
			break;
			}
		case 7:
			{
			double x0,x1,x2,x3,x4,x5,x6;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];x5=x[5];x6=x[6];
			y[0] +=  A[0]*x0 +  A[1]*x1 +  A[2]*x2 +  A[3]*x3 +  A[4]*x4 +  A[5]*x5 +  A[6]*x6;
			y[1] +=  A[7]*x0 +  A[8]*x1 +  A[9]*x2 + A[10]*x3 + A[11]*x4 + A[12]*x5 + A[13]*x6;
			y[2] += A[14]*x0 + A[15]*x1 + A[16]*x2 + A[17]*x3 + A[18]*x4 + A[19]*x5 + A[20]*x6;
			y[3] += A[21]*x0 + A[22]*x1 + A[23]*x2 + A[24]*x3 + A[25]*x4 + A[26]*x5 + A[27]*x6;
			y[4] += A[28]*x0 + A[29]*x1 + A[30]*x2 + A[31]*x3 + A[32]*x4 + A[33]*x5 + A[34]*x6;
			y[5] += A[35]*x0 + A[36]*x1 + A[37]*x2 + A[38]*x3 + A[39]*x4 + A[40]*x5 + A[41]*x6;
			y[6] += A[42]*x0 + A[43]*x1 + A[44]*x2 + A[45]*x3 + A[46]*x4 + A[47]*x5 + A[48]*x6;
			break;
			}
		default: {
			int i,j,k;
			
			for (i = 0; i < n; i ++) 
			{
				k = i*n;
				for (j = 0; j < n; j ++) 
				{
					y[i] += A[k+j]*x[j];
				}
			}
			break;
		}
	}
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_nc2(double *A, double *x, double *y)
 * \brief Compute y := y - Ax, where 'A' is a n*n dense matrix 
 *
 * \param *A   pointer to the 2*2 dense matrix
 * \param *x   pointer to the double vector with length 3
 * \param *y   pointer to the double vector with length 3
 *
 * \author Xiaozhe Hu
 * \date 18/11/2011
 *
 * \note work for 2-component
 */
void fasp_blas_smat_ymAx_nc2 (double *A, 
							  double *x, 
							  double *y)
{	double x0,x1;
	x0=x[0];
	x1=x[1];
	
	y[0] -= A[0]*x0 + A[1]*x1;
	y[1] -= A[2]*x0 + A[3]*x1;
	
	return;
} 


/**
 * \fn void fasp_blas_smat_ymAx_nc3(double *A, double *x, double *y)
 * \brief Compute y := y - Ax, where 'A' is a n*n dense matrix 
 *
 * \param *A   pointer to the 3*3 dense matrix
 * \param *x   pointer to the double vector with length 3
 * \param *y   pointer to the double vector with length 3
 *
 * \author Xiaozhe Hu, Zhiyang Zhou
 * \date 01/06/2011
 *
 * \note work for 3-component
 */
void fasp_blas_smat_ymAx_nc3 (double *A, 
															double *x, 
															double *y)
{	double x0,x1,x2;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	
	y[0] -= A[0]*x0 + A[1]*x1 + A[2]*x2;
	y[1] -= A[3]*x0 + A[4]*x1 + A[5]*x2;
	y[2] -= A[6]*x0 + A[7]*x1 + A[8]*x2;
	
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_nc5(double *A, double *x, double *y)
 * \brief Compute y := y - Ax, where 'A' is a n*n dense matrix 
 *
 * \param *A   pointer to the 5*5 dense matrix
 * \param *x   pointer to the double vector with length 5
 * \param *y   pointer to the double vector with length 5
 *
 * \author Xiaozhe Hu, Zhiyang Zhou
 * \date 01/06/2011
 *
 * \note work for 5-component
 */
void fasp_blas_smat_ymAx_nc5 (double *A, 
															double *x, 
															double *y)
{	double x0,x1,x2,x3,x4;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	x3=x[3];
	x4=x[4];
	
	y[0] -= A[0]*x0 + A[1]*x1 + A[2]*x2 + A[3]*x3 + A[4]*x4;
	y[1] -= A[5]*x0 + A[6]*x1 + A[7]*x2 + A[8]*x3 + A[9]*x4;
	y[2] -= A[10]*x0 + A[11]*x1 + A[12]*x2 + A[13]*x3 + A[14]*x4;
	y[3] -= A[15]*x0 + A[16]*x1 + A[17]*x2 + A[18]*x3 + A[19]*x4;
	y[4] -= A[20]*x0 + A[21]*x1 + A[22]*x2 + A[23]*x3 + A[24]*x4;
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_nc7(double *A, double *x, double *y)
 * \brief Compute y := y - Ax, where 'A' is a 7*7 dense matrix 
 *
 * \param *A   pointer to the 7*7 dense matrix
 * \param *x   pointer to the double vector with length 7
 * \param *y   pointer to the double vector with length 7
 *
 * \author Xiaozhe Hu, Zhiyang Zhou
 * \date 01/06/2011
 *
 * \note work for 7-component
 */
void fasp_blas_smat_ymAx_nc7 (double *A, 
															double *x, 
															double *y)
{	double x0,x1,x2,x3,x4,x5,x6;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	x3=x[3];
	x4=x[4];
	x5=x[5];
	x6=x[6];
	y[0] -= A[0]*x0 + A[1]*x1 +    A[2]*x2 +  A[3]*x3 +  A[4]*x4 +  A[5]*x5 +  A[6]*x6;
	y[1] -= A[7]*x0 + A[8]*x1 +    A[9]*x2 + A[10]*x3 + A[11]*x4 + A[12]*x5 + A[13]*x6;
	y[2] -= A[14]*x0 + A[15]*x1 + A[16]*x2 + A[17]*x3 + A[18]*x4 + A[19]*x5 + A[20]*x6;
	y[3] -= A[21]*x0 + A[22]*x1 + A[23]*x2 + A[24]*x3 + A[25]*x4 + A[26]*x5 + A[27]*x6;
	y[4] -= A[28]*x0 + A[29]*x1 + A[30]*x2 + A[31]*x3 + A[32]*x4 + A[33]*x5 + A[34]*x6;
	y[5] -= A[35]*x0 + A[36]*x1 + A[37]*x2 + A[38]*x3 + A[39]*x4 + A[40]*x5 + A[41]*x6;
	y[6] -= A[42]*x0 + A[43]*x1 + A[44]*x2 + A[45]*x3 + A[46]*x4 + A[47]*x5 + A[48]*x6;
	
	
	return;
}

/**
 * \fn void fasp_blas_smat_ymAx(double *A, double *x, double *y, int n)
 * \brief Compute y := y - Ax, where 'A' is a n*n dense matrix 
 *
 * \param *A   pointer to the n*n dense matrix
 * \param *x   pointer to the double vector with length n
 * \param *y   pointer to the double vector with length n
 * \param  n   the dimension of the dense matrix
 *
 * \author Zhiyang Zhou, Xiaozhe Hu
 * \date 2010/10/25
 */
void fasp_blas_smat_ymAx (double *A, 
													double *x, 
													double *y,
													int n)
{	
	switch (n) {
		case 2:
			{
			double x0,x1;
			x0=x[0];x1=x[1];
			y[0] -= A[0]*x0 + A[1]*x1;
			y[1] -= A[2]*x0 + A[3]*x1;
			break;
			}
		case 3:
			{
			double x0,x1,x2;
			x0=x[0];x1=x[1];x2=x[2];
			y[0] -= A[0]*x0 + A[1]*x1 + A[2]*x2;
			y[1] -= A[3]*x0 + A[4]*x1 + A[5]*x2;
			y[2] -= A[6]*x0 + A[7]*x1 + A[8]*x2;
			break;
			}
		case 4:
			{
			double x0,x1,x2,x3;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];
			y[0] -=  A[0]*x0 + A[1]*x1 +  A[2]*x2 + A[3]*x3;
			y[1] -=  A[4]*x0 + A[5]*x1 +  A[6]*x2 + A[7]*x3;
			y[2] -=  A[8]*x0 + A[9]*x1 + A[10]*x2 + A[11]*x3;
			y[3] -= A[12]*x0 + A[13]*x1 +A[14]*x2 + A[15]*x3;
			break;
			}
		case 5:
			{
			double x0,x1,x2,x3,x4;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];
			y[0] -=  A[0]*x0 +  A[1]*x1 +  A[2]*x2 +  A[3]*x3 +  A[4]*x4;
			y[1] -=  A[5]*x0 +  A[6]*x1 +  A[7]*x2 +  A[8]*x3 +  A[9]*x4;
			y[2] -= A[10]*x0 + A[11]*x1 + A[12]*x2 + A[13]*x3 + A[14]*x4;
			y[3] -= A[15]*x0 + A[16]*x1 + A[17]*x2 + A[18]*x3 + A[19]*x4;
			y[4] -= A[20]*x0 + A[21]*x1 + A[22]*x2 + A[23]*x3 + A[24]*x4;
			break;
			}
		case 6:
			{
			double x0,x1,x2,x3,x4,x5;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];x5=x[5];
			y[0] -=  A[0]*x0 +  A[1]*x1 +  A[2]*x2 +  A[3]*x3 +  A[4]*x4 +  A[5]*x5;
			y[1] -=  A[6]*x0 +  A[7]*x1 +  A[8]*x2 +  A[9]*x3 + A[10]*x4 + A[11]*x5;
			y[2] -= A[12]*x0 + A[13]*x1 + A[14]*x2 + A[15]*x3 + A[16]*x4 + A[17]*x5;
			y[3] -= A[18]*x0 + A[19]*x1 + A[20]*x2 + A[21]*x3 + A[22]*x4 + A[23]*x5;
			y[4] -= A[24]*x0 + A[25]*x1 + A[26]*x2 + A[27]*x3 + A[28]*x4 + A[29]*x5;
			y[5] -= A[30]*x0 + A[31]*x1 + A[32]*x2 + A[33]*x3 + A[34]*x4 + A[35]*x5;
			break;
			}
		case 7:	
			{
			double x0,x1,x2,x3,x4,x5,x6;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];x5=x[5];x6=x[6];
			y[0] -=  A[0]*x0 +  A[1]*x1 +  A[2]*x2 +  A[3]*x3 +  A[4]*x4 +  A[5]*x5 +  A[6]*x6;
			y[1] -=  A[7]*x0 +  A[8]*x1 +  A[9]*x2 + A[10]*x3 + A[11]*x4 + A[12]*x5 + A[13]*x6;
			y[2] -= A[14]*x0 + A[15]*x1 + A[16]*x2 + A[17]*x3 + A[18]*x4 + A[19]*x5 + A[20]*x6;
			y[3] -= A[21]*x0 + A[22]*x1 + A[23]*x2 + A[24]*x3 + A[25]*x4 + A[26]*x5 + A[27]*x6;
			y[4] -= A[28]*x0 + A[29]*x1 + A[30]*x2 + A[31]*x3 + A[32]*x4 + A[33]*x5 + A[34]*x6;
			y[5] -= A[35]*x0 + A[36]*x1 + A[37]*x2 + A[38]*x3 + A[39]*x4 + A[40]*x5 + A[41]*x6;
			y[6] -= A[42]*x0 + A[43]*x1 + A[44]*x2 + A[45]*x3 + A[46]*x4 + A[47]*x5 + A[48]*x6;
			break;
			}
		default: {
			int i,j,k;
			
			for (i = 0; i < n; i ++) 
			{
				k = i*n;
				for (j = 0; j < n; j ++) 
				{
					y[i] -= A[k+j]*x[j];
				}
			}
			break;
		}
	}
	
	return;
} 

/**
 * \fn void fasp_blas_smat_aAxpby( double alpha, double *A, double *x, double beta, double *y, int n )
 * \brief Compute y:=alpha*A*x + beta*y, here x,y are vectors, A is a n*n full matrix.   
 *
 * \param  alpha   a real number
 * \param *A       pointer to the double vector which stands for a n*n full matrix 
 * \param *x       pointer to the double vector with length n
 * \param  beta    a real number
 * \param *y       pointer to the double vector with length n
 * \param  n       the length of vector x and y
 *
 * \author Zhiyang Zhou
 * \date 2010/10/25
 */
void fasp_blas_smat_aAxpby (double alpha, 
                            double *A, 
														double *x, 
														double beta, 
														double *y, 
														int n )
{
	int    i,j,k;
	double tmp = 0.0;
	
	if (alpha == 0)
	{
		for (i = 0; i < n; i ++) y[i] *= beta;
		return;
	}
	
	//! y := (beta/alpha)y
	tmp = beta / alpha;
	if (tmp != 1.0)
	{
		for (i = 0; i < n; i ++) y[i] *= tmp;
	}
	
	//! y := y + A*x
	for (i = 0; i < n; i ++)
	{
		k = i*n;
		for (j = 0; j < n; j ++)
		{
			y[i] += A[k+j]*x[j];
		}
	}     
	
	//! y := alpha*y
	if (alpha != 1.0)
	{
		for (i = 0; i < n; i ++) y[i] *= alpha;
	}
}

/**
 * \fn void fasp_blas_smat_ymAx_ns2(double *A, double *x, double *y)
 * \brief Compute ys := ys - Ass*xs, where 'A' is a 2*2 dense matrix, Ass is its saturaton part 1*1.
 * 
 * \param *A   pointer to the 2*2 dense matrix
 * \param *x   pointer to the double vector with length 1
 * \param *y   pointer to the double vector with length 1
 *
 * \author Xiaozhe Hu
 * \date 2011/11/18
 * 
 * \note only for block smoother for saturation block without explictly use saturation block!!
 * \note work for 2-component (Xiaozhe)
 */
void fasp_blas_smat_ymAx_ns2 (double *A,
							  double *x, 
							  double *y)
{	
	y[0] -= A[3]*x[0];
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_ns3(double *A, double *x, double *y)
 * \brief Compute ys := ys - Ass*xs, where 'A' is a 3*3 dense matrix, Ass is its saturaton part 2*2.
 * 
 * \param *A   pointer to the 3*3 dense matrix
 * \param *x   pointer to the double vector with length 2
 * \param *y   pointer to the double vector with length 2
 *
 * \author Xiaozhe Hu
 * \date 2010/10/25
 * 
 * \note only for block smoother for saturation block without explictly use saturation block!!
 * \note work for 3-component (Xiaozhe)
 */
void fasp_blas_smat_ymAx_ns3 (double *A,
															double *x, 
															double *y)
{	double x0,x1;
	x0=x[0];
	x1=x[1];
	y[0] -= A[4]*x0 + A[5]*x1;
	y[1] -= A[7]*x0 + A[8]*x1;
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_ns5(double *A, double *x, double *y)
 * \brief Compute ys := ys - Ass*xs, where 'A' is a 5*5 dense matrix, Ass is its saturaton part 4*4.
 * 
 * \param *A   pointer to the 5*5 dense matrix
 * \param *x   pointer to the double vector with length 4
 * \param *y   pointer to the double vector with length 4
 *
 * \author Xiaozhe Hu
 * \date 2010/10/25
 * 
 * \note only for block smoother for saturation block without explictly use saturation block!!
 * \note work for 5-component (Xiaozhe)
 */
void fasp_blas_smat_ymAx_ns5 (double *A, 
															double *x, 
															double *y)
{	double x0,x1,x2,x3;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	x3=x[3];
	
	y[0] -=  A[6]*x0 +  A[7]*x1 +  A[8]*x2 +  A[9]*x3;
	y[1] -= A[11]*x0 + A[12]*x1 + A[13]*x2 + A[14]*x3;
	y[2] -= A[16]*x0 + A[17]*x1 + A[18]*x2 + A[19]*x3;
	y[3] -= A[21]*x0 + A[22]*x1 + A[23]*x2 + A[24]*x3;
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_ns7(double *A, double *x, double *y)
 * \brief Compute ys := ys - Ass*xs, where 'A' is a 7*7 dense matrix, Ass is its saturaton part 6*6.
 * 
 * \param *A   pointer to the 7*7 dense matrix
 * \param *x   pointer to the double vector with length 6
 * \param *y   pointer to the double vector with length 6
 *
 * \author Xiaozhe Hu
 * \date 2010/10/25
 * 
 * \note only for block smoother for saturation block without explictly use saturation block!!
 * \note work for 7-component (Xiaozhe)
 */
void fasp_blas_smat_ymAx_ns7 (double *A, 
															double *x, 
															double *y)
{	double x0,x1,x2,x3,x4,x5;
	x0=x[0];
	x1=x[1];
	x2=x[2];
	x3=x[3];
	x4=x[4];
	x5=x[5];
	
	y[0] -=  A[8]*x0 +  A[9]*x1 + A[10]*x2 + A[11]*x3 + A[12]*x4 + A[13]*x5;
	y[1] -= A[15]*x0 + A[16]*x1 + A[17]*x2 + A[18]*x3 + A[19]*x4 + A[20]*x5;
	y[2] -= A[22]*x0 + A[23]*x1 + A[24]*x2 + A[25]*x3 + A[26]*x4 + A[27]*x5;
	y[3] -= A[29]*x0 + A[30]*x1 + A[31]*x2 + A[32]*x3 + A[33]*x4 + A[34]*x5;
	y[4] -= A[36]*x0 + A[37]*x1 + A[38]*x2 + A[39]*x3 + A[40]*x4 + A[41]*x5;
	y[5] -= A[43]*x0 + A[44]*x1 + A[45]*x2 + A[46]*x3 + A[47]*x4 + A[48]*x5;
	
	return;
} 

/**
 * \fn void fasp_blas_smat_ymAx_ns( double *A, double *x, double *y, int n )
 * \brief Compute ys := ys - Ass*xs, where 'A' is a n*n dense matrix, Ass is its saturaton part (n-1)*(n-1).
 * 
 * \param *A   pointer to the n*n dense matrix
 * \param *x   pointer to the double vector with length n-1
 * \param *y   pointer to the double vector with length n-1
 * \param  n   the dimension of the dense matrix
 * 
 * \note only for block smoother for saturation block without explictly use saturation block!!
 *
 * \author Xiaozhe Hu
 * \date 2010/10/25
 */
void fasp_blas_smat_ymAx_ns (double *A, 
														 double *x, 
														 double *y, 
														 int n)
{	
	switch (n) {
		case 2:
			y[0] -= A[3]*x[0];
			break;
		 
		case 3: 
			{
			double x0,x1;
			x0=x[0];x1=x[1];
			y[0] -= A[4]*x0 + A[5]*x1;
			y[1] -= A[7]*x0 + A[8]*x1;
			break;
			}
		case 5:
			{
			double x0,x1,x2,x3;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];
			y[0] -=  A[6]*x0 +  A[7]*x1 +  A[8]*x2 +  A[9]*x3;
			y[1] -= A[11]*x0 + A[12]*x1 + A[13]*x2 + A[14]*x3;
			y[2] -= A[16]*x0 + A[17]*x1 + A[18]*x2 + A[19]*x3;
			y[3] -= A[21]*x0 + A[22]*x1 + A[23]*x2 + A[24]*x3;
			break;
			}
		case 7:
			{
			double x0,x1,x2,x3,x4,x5;
			x0=x[0];x1=x[1];x2=x[2];x3=x[3];x4=x[4];x5=x[5];
			y[0] -=  A[8]*x0 +  A[9]*x1 + A[10]*x2 + A[11]*x3 + A[12]*x4 + A[13]*x5;
			y[1] -= A[15]*x0 + A[16]*x1 + A[17]*x2 + A[18]*x3 + A[19]*x4 + A[20]*x5;
			y[2] -= A[22]*x0 + A[23]*x1 + A[24]*x2 + A[25]*x3 + A[26]*x4 + A[27]*x5;
			y[3] -= A[29]*x0 + A[30]*x1 + A[31]*x2 + A[32]*x3 + A[33]*x4 + A[34]*x5;
			y[4] -= A[36]*x0 + A[37]*x1 + A[38]*x2 + A[39]*x3 + A[40]*x4 + A[41]*x5;
			y[5] -= A[43]*x0 + A[44]*x1 + A[45]*x2 + A[46]*x3 + A[47]*x4 + A[48]*x5;
			break;
			}
		default: {
			int i,j,k;
			
			for (i = 1; i < n; i ++) 
			{
				k = i*n;
				for (j = 1; j < n; j ++) 
				{
					y[i-1] -= A[k+j]*x[j-1];
				}
			}
			break;
		}
	}
	
	return;
} 

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/