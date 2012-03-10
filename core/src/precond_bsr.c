/*! \file precond_bsr.c
 *  \brief Preconditioners for sparse matrices in BSR format.
 */

#include "fasp.h"
#include "fasp_functs.h"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/**
 * \fn void fasp_precond_dbsr_diag (REAL *r, REAL *z, void *data)
 *
 * \brief Diagonal preconditioner z=inv(D)*r
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \note: works for general nb (Xiaozhe)
 *
 * \author Zhou Zhiyang, Xiaozhe Hu
 * \date 10/26/2010
 */
void fasp_precond_dbsr_diag (REAL *r, 
                             REAL *z, 
                             void *data)
{
	precond_diagbsr *diag = (precond_diagbsr *)data;
	const INT nb = diag->nb; 
	
	switch (nb)
	{
		case 2:
			fasp_precond_dbsr_diag_nc2( r, z, diag );
			break;
			
		case 3:
			fasp_precond_dbsr_diag_nc3( r, z, diag );
			break;
			
		case 5:
			fasp_precond_dbsr_diag_nc5( r, z, diag );
			break;
			
		case 7:
			fasp_precond_dbsr_diag_nc7( r, z, diag );
			break;
			
		default:
		{
			REAL *diagptr = diag->diag.val;
			const INT nb2 = nb*nb;
			const INT m = diag->diag.row/nb2;	
			
			unsigned INT i;
			for (i = 0; i < m; ++i) 
			{
				fasp_blas_smat_mxv(&(diagptr[i*nb2]),&(r[i*nb]),&(z[i*nb]),nb);
			}
		}
			break;
	}
	
}

/**
 * \fn void fasp_precond_dbsr_diag_nc2 (REAL *r, REAL *z, void *data)
 *
 * \brief Diagonal preconditioner z=inv(D)*r.
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \note: works for 2-component (Xiaozhe)
 *
 * \author Zhou Zhiyang, Xiaozhe Hu
 * \date 11/18/2011
 */
void fasp_precond_dbsr_diag_nc2 (REAL *r, 
								 REAL *z, 
								 void *data )
{
	precond_diagbsr *diag    = (precond_diagbsr *)data;
	REAL            *diagptr = diag->diag.val;
	
	const INT m = diag->diag.row/4;	
	
	unsigned INT i;
	for (i = 0; i < m; ++i) 
	{
		fasp_blas_smat_mxv_nc2(&(diagptr[i*4]),&(r[i*2]),&(z[i*2]));
	}	
}

/**
 * \fn void fasp_precond_dbsr_diag_nc3 (REAL *r, REAL *z, void *data)
 *
 * \brief Diagonal preconditioner z=inv(D)*r.
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \note: works for 3-component (Xiaozhe)
 *
 * \author Zhou Zhiyang, Xiaozhe Hu
 * \date 01/06/2011
 */
void fasp_precond_dbsr_diag_nc3 (REAL *r, 
                                 REAL *z, 
                                 void *data )
{
	precond_diagbsr *diag    = (precond_diagbsr *)data;
	REAL            *diagptr = diag->diag.val;
	
	const INT m = diag->diag.row/9;	
	
	unsigned INT i;
	for (i = 0; i < m; ++i) 
	{
		fasp_blas_smat_mxv_nc3(&(diagptr[i*9]),&(r[i*3]),&(z[i*3]));
	}	
}

/**
 * \fn void fasp_precond_dbsr_diag_nc5 (REAL *r, REAL *z, void *data)
 *
 * \brief Diagonal preconditioner z=inv(D)*r.
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \note: works for 5-component (Xiaozhe)
 *
 * \author Zhou Zhiyang, Xiaozhe Hu
 * \date 01/06/2011
 */
void fasp_precond_dbsr_diag_nc5 (REAL *r, 
                                 REAL *z, 
                                 void *data )
{
	precond_diagbsr *diag    = (precond_diagbsr *)data;
	REAL            *diagptr = diag->diag.val;
	
	const INT m = diag->diag.row/25;	
	
	unsigned INT i;
	for (i = 0; i < m; ++i) 
	{
		fasp_blas_smat_mxv_nc5(&(diagptr[i*25]),&(r[i*5]),&(z[i*5]));
	}	
}

/**
 * \fn void fasp_precond_dbsr_diag_nc7 (REAL *r, REAL *z, void *data)
 *
 * \brief Diagonal preconditioner z=inv(D)*r.
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \note: works for 7-component (Xiaozhe)
 *
 * \author Zhou Zhiyang, Xiaozhe Hu
 * \date 01/06/2011
 */
void fasp_precond_dbsr_diag_nc7 (REAL *r, 
                                 REAL *z, 
                                 void *data )
{
	precond_diagbsr *diag   = (precond_diagbsr *)data;
	REAL            *diagptr = diag->diag.val;
	
	const INT m = diag->diag.row/49;	
	
	unsigned INT i;
	for (i = 0; i < m; ++i) 
	{
		fasp_blas_smat_mxv_nc7(&(diagptr[i*49]),&(r[i*7]),&(z[i*7]));
	}	
}

/**
 * \fn void fasp_precond_dbsr_ilu (REAL *r, REAL *z, void *data)
 *
 * \brief preconditioning using ILU decomposition
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \note: works for general nb (Xiaozhe)
 *
 * \author Shiquan Zhang
 * \date 11/09/2010
 */
void fasp_precond_dbsr_ilu (REAL *r, 
                            REAL *z, 
                            void *data)
{
	const ILU_data  *iludata=(ILU_data *)data;
	const INT        m=iludata->row, mm1=m-1, mm2=m-2, memneed=2*m;
	const INT        nb=iludata->nb, nb2=nb*nb, size=m*nb;
	
    INT        *ijlu=iludata->ijlu;
	REAL       *lu=iludata->luval;
    
    INT         ib, ibstart,ibstart1;
	INT         i, j, jj, begin_row, end_row;
	REAL       *zz, *zr, *mult;	   
	
	if (iludata->nwork<memneed) {
		printf("### ERROR: Need %d memory, only %d available!!!\n", memneed, iludata->nwork);
		exit(ERROR_ALLOC_MEM);
	}
	
	zz   = iludata->work; 
	zr   = zz + size;
	mult = zr + size;
	
	memcpy(zr, r, size*sizeof(REAL));
	
	switch (nb) {
			
		case 1:
			
			// forward sweep: solve unit lower matrix equation L*zz=zr
			zz[0]=zr[0];
			for (i=1;i<=mm1;++i) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				for (j=begin_row;j<=end_row;++j) {
					jj=ijlu[j];
					if (jj<i) zr[i]-=lu[j]*zz[jj];
					else break;
				}
				zz[i]=zr[i];
			}
			
			// backward sweep: solve upper matrix equation U*z=zz
			z[mm1]=zz[mm1]*lu[mm1];
			for (i=mm2;i>=0;i--) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				for (j=end_row;j>=begin_row;j--) {
					jj=ijlu[j];
					if (jj>i) zz[i]-=lu[j]*z[jj];
					else break;
				} 
				z[i]=zz[i]*lu[i];
			}
			
			break; //end (if nb==1) 
			
		case 3:
			
			// forward sweep: solve unit lower matrix equation L*zz=zr
			zz[0] = zr[0];
			zz[1] = zr[1];
			zz[2] = zr[2];
			
			for (i=1;i<=mm1;++i) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb;
				for (j=begin_row;j<=end_row;++j) {
					jj=ijlu[j];
					if (jj<i)
					{
						fasp_blas_smat_mxv_nc3(&(lu[j*nb2]),&(zz[jj*nb]),mult);
						for (ib=0;ib<nb;++ib) zr[ibstart+ib]-=mult[ib];
					}
					else break;
				}
				
				zz[ibstart]   = zr[ibstart];
				zz[ibstart+1] = zr[ibstart+1];
				zz[ibstart+2] = zr[ibstart+2];
			}
			
			// backward sweep: solve upper matrix equation U*z=zz
			ibstart=mm1*nb2;
			ibstart1=mm1*nb;
			fasp_blas_smat_mxv_nc3(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]));
			
			for (i=mm2;i>=0;i--) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb2;
				ibstart1=i*nb;
				for (j=end_row;j>=begin_row;j--) {
					jj=ijlu[j];
					if (jj>i) 
						
					{
						fasp_blas_smat_mxv_nc3(&(lu[j*nb2]),&(z[jj*nb]),mult);
						for (ib=0;ib<nb;++ib) zz[ibstart1+ib]-=mult[ib];
					}
					
					else break;
				} 
				
				fasp_blas_smat_mxv_nc3(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]));
				
			}
			
			break; // end (if nb=3)
			
		case 5:
			
			// forward sweep: solve unit lower matrix equation L*zz=zr
			fasp_array_cp(nb,&(zr[0]),&(zz[0]));
			
			for (i=1;i<=mm1;++i) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb;
				for (j=begin_row;j<=end_row;++j) {
					jj=ijlu[j];
					if (jj<i)
					{
						fasp_blas_smat_mxv_nc5(&(lu[j*nb2]),&(zz[jj*nb]),mult);
						for (ib=0;ib<nb;++ib) zr[ibstart+ib]-=mult[ib];
					}
					else break;
				}
				
				fasp_array_cp(nb,&(zr[ibstart]),&(zz[ibstart]));
			}
			
			// backward sweep: solve upper matrix equation U*z=zz
			ibstart=mm1*nb2;
			ibstart1=mm1*nb;
			fasp_blas_smat_mxv_nc5(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]));
			
			for (i=mm2;i>=0;i--) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb2;
				ibstart1=i*nb;
				for (j=end_row;j>=begin_row;j--) {
					jj=ijlu[j];
					if (jj>i) 
						
					{
						fasp_blas_smat_mxv_nc5(&(lu[j*nb2]),&(z[jj*nb]),mult);
						for (ib=0;ib<nb;++ib) zz[ibstart1+ib]-=mult[ib];
					}
					
					else break;
				} 
				
				fasp_blas_smat_mxv_nc5(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]));
				
			}
			
			break; //end (if nb==5)
			
		case 7:
			
			// forward sweep: solve unit lower matrix equation L*zz=zr
			fasp_array_cp(nb,&(zr[0]),&(zz[0]));
			
			for (i=1;i<=mm1;++i) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb;
				for (j=begin_row;j<=end_row;++j) {
					jj=ijlu[j];
					if (jj<i)
					{
						fasp_blas_smat_mxv_nc7(&(lu[j*nb2]),&(zz[jj*nb]),mult);
						for (ib=0;ib<nb;++ib) zr[ibstart+ib]-=mult[ib];
					}
					else break;
				}
				
				fasp_array_cp(nb,&(zr[ibstart]),&(zz[ibstart]));
			}
			
			// backward sweep: solve upper matrix equation U*z=zz
			ibstart=mm1*nb2;
			ibstart1=mm1*nb;
			fasp_blas_smat_mxv_nc7(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]));
			
			for (i=mm2;i>=0;i--) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb2;
				ibstart1=i*nb;
				for (j=end_row;j>=begin_row;j--) {
					jj=ijlu[j];
					if (jj>i) 
						
					{
						fasp_blas_smat_mxv_nc7(&(lu[j*nb2]),&(z[jj*nb]),mult);
						for (ib=0;ib<nb;++ib) zz[ibstart1+ib]-=mult[ib];
					}
					
					else break;
				} 
				
				fasp_blas_smat_mxv_nc7(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]));
				
			}
			
			break; //end (if nb==7)
			
		default:
			
			// forward sweep: solve unit lower matrix equation L*zz=zr
			fasp_array_cp(nb,&(zr[0]),&(zz[0]));
			
			for (i=1;i<=mm1;++i) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb;
				for (j=begin_row;j<=end_row;++j) {
					jj=ijlu[j];
					if (jj<i)
					{
						fasp_blas_smat_mxv(&(lu[j*nb2]),&(zz[jj*nb]),mult,nb);
						for (ib=0;ib<nb;++ib) zr[ibstart+ib]-=mult[ib];
					}
					else break;
				}
				
				fasp_array_cp(nb,&(zr[ibstart]),&(zz[ibstart]));
			}
			
			// backward sweep: solve upper matrix equation U*z=zz
			ibstart=mm1*nb2;
			ibstart1=mm1*nb;
			fasp_blas_smat_mxv(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]),nb);
			
			for (i=mm2;i>=0;i--) {
				begin_row=ijlu[i]; end_row=ijlu[i+1]-1;
				ibstart=i*nb2;
				ibstart1=i*nb;
				for (j=end_row;j>=begin_row;j--) {
					jj=ijlu[j];
					if (jj>i) 
						
					{
						fasp_blas_smat_mxv(&(lu[j*nb2]),&(z[jj*nb]),mult,nb);
						for (ib=0;ib<nb;++ib) zz[ibstart1+ib]-=mult[ib];
					}
					
					else break;
				} 
				
				fasp_blas_smat_mxv(&(lu[ibstart]),&(zz[ibstart1]),&(z[ibstart1]),nb);
				
			}
			
			break; // end everything else 
	}
	
	return;
}

/**
 * \fn void fasp_precond_dbsr_FASP3(double *r, double *z, void *data)
 * \brief get z from r by classic AMG
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \author Xiaozhe Hu
 * \date 08/07/2011
 */
void fasp_precond_dbsr_amg (double *r, 
                            double *z, 
                            void *data)
{
	precond_data_bsr *predata=(precond_data_bsr *)data;
	const int row=predata->mgl_data[0].A.ROW;
	const int nb = predata->mgl_data[0].A.nb;
	const int maxit=predata->maxit;
	unsigned int i;
	const int m = row*nb;
	
	AMG_param amgparam; fasp_param_amg_init(&amgparam);
	amgparam.cycle_type = predata->cycle_type;
	amgparam.smoother   = predata->smoother;
	amgparam.smooth_order = predata->smooth_order;
	amgparam.presmooth_iter  = predata->presmooth_iter;
	amgparam.postsmooth_iter = predata->postsmooth_iter;
	amgparam.relaxation = predata->relaxation;
	amgparam.coarse_scaling = predata->coarse_scaling;
	amgparam.tentative_smooth = predata->tentative_smooth;
	amgparam.ILU_levels = predata->mgl_data->ILU_levels;
	
	AMG_data_bsr *mgl = predata->mgl_data;
	mgl->b.row=m; fasp_array_cp(m,r,mgl->b.val); // residual is an input 
	mgl->x.row=m; fasp_dvec_set(m,&mgl->x,0.0);
	
	for (i=0;i<maxit;++i) fasp_solver_mgcycle_bsr(mgl,&amgparam); //fasp_solver_mgrecurmgl,&amgparam,0); //
	
	fasp_array_cp(m,mgl->x.val,z);	
}

/**
 * \fn void fasp_precond_dbsr_nl_amli(REAL *r, REAL *z, void *data)
 *
 * \brief get z from r by nonliear AMLI-cycle
 *
 * \param r pointer to residual
 * \param z pointer to preconditioned residual
 * \param data pointer to precondition data
 *
 * \author Xiaozhe Hu
 * \date 02/06/2012
 */
void fasp_precond_dbsr_nl_amli (REAL *r, 
                                REAL *z, 
                                void *data)
{
	
	precond_data_bsr *precdata=(precond_data_bsr *)data;
    const INT row=precdata->mgl_data[0].A.ROW;
	const INT nb = precdata->mgl_data[0].A.nb;
	const INT maxit=precdata->maxit;
    const SHORT num_levels = precdata->max_levels;
	unsigned INT i;
	const INT m = row*nb;
	
	AMG_param amgparam; fasp_param_amg_init(&amgparam);
    fasp_param_prec_to_amg_bsr(&amgparam,precdata);
	
	AMG_data_bsr *mgl = precdata->mgl_data;
	mgl->b.row=m; fasp_array_cp(m,r,mgl->b.val); // residual is an input 
	mgl->x.row=m; fasp_dvec_set(m,&mgl->x,0.0);
	
	for (i=0;i<maxit;++i) fasp_solver_nl_amli_bsr(mgl,&amgparam,0, num_levels); 
	
	fasp_array_cp(m,mgl->x.val,z);	
    
}

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/
