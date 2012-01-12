/*! \file itsolver_Stokes.c
 *  \brief Iterative solvers for Stokes-type matrices (main file)
 */

#include <math.h>
#include <time.h>

#include "fasp.h"
#include "fasp_block.h"
#include "fasp_functs.h"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/**
 * \fn int fasp_solver_bdcsr_krylov_stokes (block_dCSRmat *A, dvector *b, dvector *x, itsolver_param *itparam, Stokes_param *precdata)
 * \brief Solve Ax=b by standard Krylov methods 
 *
 * \param *A:	       pointer to the block_dCSRmat matrix
 * \param *b:	       pointer to the dvector of right hand side
 * \param *x:	       pointer to the dvector of dofs
 * \param *itparam:  pointer to parameters for iterative solvers
 * \param *precdata: pionter to preconditioner data for Stokes
 * \return           number of iterations
 *
 * \author Chensong Zhang
 * \date 11/25/2010
 */
int fasp_solver_bdcsr_krylov_stokes (block_dCSRmat *Mat, 
																		 dvector *b, 
																		 dvector *x, 
																		 itsolver_param *itparam,
																		 precond_Stokes_param *param, 
																		 precond_Stokes_data *precdata)
{
	// parameters
	const int print_level = itparam->print_level;
	const int precond_type = itparam->precond_type;
	
	// Stokes matrix 
	dCSRmat *A = Mat->blocks[0];
	dCSRmat *B = Mat->blocks[1];
	const int n = A->row, nnzA = A->nnz, m = B->row;	
	
	// preconditioner data
	dCSRmat *M = precdata->M;
	precond prec;
	AMG_param amgparam;
	dvector diag_M;	
	
	// local variable
	clock_t solver_start, solver_end, setup_start, setup_end;
	double solver_duration, setup_duration;
	int status=SUCCESS;
	
	// initialize preconditioner 
	prec.data = &precdata; 
	switch (precond_type) {
		case 1:
			prec.fct = fasp_precond_stokes_bdiag;
			break;
		default:
			printf("Error: Unknown preconditioner type!\n");
			exit(ERROR_SOLVER_PRECTYPE);
	}
	
	// AMG parameters
	amgparam.print_level = param->print_level;
	amgparam.max_levels = param->max_levels;
	amgparam.AMG_type = param->AMG_type;
	
	//------ setup phase ------//
	setup_start = clock();
	
	precdata->colA = n;
	precdata->colB = m;
	precdata->col  = n+m;	
	
	// setup work array space
	precdata->w = (double *)fasp_mem_calloc(precdata->col,sizeof(double));
	
	// initialize AMG for A
	AMG_data *mgl=fasp_amg_data_create(amgparam.max_levels);
  mgl[0].A=fasp_dcsr_create(n,n,nnzA); fasp_dcsr_cp(A,&mgl[0].A);
	mgl[0].b=fasp_dvec_create(n); mgl[0].x=fasp_dvec_create(n);
	
	// setup AMG
	switch (amgparam.AMG_type) {
		case CLASSIC_AMG:
			fasp_amg_setup_rs(mgl, &amgparam);
			break;
		case SA_AMG:
			fasp_amg_setup_sa(mgl, &amgparam);
			break;
		default:
			printf("Error: Wrong AMG type %d!\n",amgparam.AMG_type);
			exit(ERROR_INPUT_PAR);
	}	
	precdata->max_levels = mgl[0].num_levels;
	precdata->mgl_data = mgl;
	
	// setup diagonal for M
	fasp_dcsr_getdiag(0,M,&diag_M);	
	precdata->diag_M = &diag_M;
	
	setup_end = clock();
	
	if (print_level>0) {
		setup_duration = (double)(setup_end - setup_start)/(double)(CLOCKS_PER_SEC);
		printf("Setup costs %f.\n", setup_duration);
	}
	
	//------ solver phase ------// 
	solver_start=clock();
	status=fasp_solver_bdcsr_itsolver(Mat,b,x,&prec,itparam);
	solver_end=clock();
	
	if (print_level>0) {
		solver_duration = (double)(solver_end - solver_start)/(double)(CLOCKS_PER_SEC);
		printf("Solver costs %f seconds.\n", solver_duration);	
		printf("Total costs %f seconds.\n", setup_duration + solver_duration);
	}
	
	// clean up memory
	if (mgl) fasp_amg_data_free(mgl);
	fasp_mem_free(precdata->w);
	
	return status;
}

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/