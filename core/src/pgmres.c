/*! \file pgmres.c
 *  \brief Krylov subspace methods -- Preconditioned GMRes.
 *
 *  Abstract algorithm of Krylov method    
 *
 *  Krylov method to solve A*x=b is to generate {x_k} to approximate x, 
 *  where x_k is the optimal solution in Krylov space 
 *
 *     V_k=span{r_0,A*r_0,A^2*r_0,...,A^{k-1}*r_0}, 
 *
 *  under some inner product. 
 *
 *  For the implementation, we generate a series of {p_k} such that V_k=span{p_1,...,p_k}. Details: 
 *
 *  Step 0. Given A, b, x_0, M  
 *  
 *  Step 1. Compute residual r_0 = b-A*x_0 and convergence check;  
 *  
 *  Step 2. Initialization z_0 = M^{-1}*r_0, p_0=z_0;  
 *  
 *  Step 3. Main loop ...
 *
 *  FOR k = 0:maxit  	
 *      - get step size alpha = f(r_k,z_k,p_k);  	
 *      - update solution: x_{k+1} = x_k + alpha*p_k;  	
 *      - perform stagnation check;  	
 *      - update residual: r_{k+1} = r_k - alpha*(A*p_k);    	
 *      - perform residual check;  	
 *      - obtain p_{k+1} using {p_0, p_1, ... , p_k};  	
 *      - prepare for next iteration;  	
 *      - prINT the result of k-th iteration; 
 *  END FOR
 * 
 *  Convergence check is: norm(r)/norm(b) < tol  
 *  
 *  Stagnation check is like following:    
 *      - IF norm(alpha*p_k)/norm(x_{k+1}) < tol_stag 
 *          -# compute r=b-A*x_{k+1}; 
 *          -# convergence check; 
 *          -# IF ( not converged & restart_number < Max_Stag_Check ) restart;
 *      - END IF  
 *  
 *  Residual check is like following:     
 *      - IF norm(r_{k+1})/norm(b) < tol             
 *          -# compute the real residual r = b-A*x_{k+1}; 
 *          -# convergence check; 
 *          -# IF ( not converged & restart_number < Max_Res_Check ) restart;
 *      - END IF 
 *
 *  Ref: Iterative methods for sparse linear systems (2nd Edition) 
 *  By Y. Saad, SIAM, 2003.
 *
 */  

#include <math.h>

#include "fasp.h"
#include "fasp_functs.h"
#include "its_util.inl"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/*!
 * \fn INT fasp_solver_dcsr_pgmres (dCSRmat *A, dvector *b, dvector *x, const INT maxit, 
 *                                  const REAL tol, precond *pre, const SHORT print_level, 
 *                                  const SHORT stop_type, const SHORT restart )
 *
 * \brief Solve "Ax=b" using PGMRES (right preconditioned) iterative method
 *
 * \param *A the pointer to the coefficient matrix
 * \param *b the pointer to the right hand side vector
 * \param *x the pointer to the solution vector
 * \param maxit the maximal iteration  
 * \param tol the tolerance
 * \param *pre pointer to preconditioner data
 * \param print_level how much of the SOLVE-INFORMATION be output?
 * \param stop_type this parameter is not used in my function at present, 
 *        the default stopping criterion,i.e.||r_k||/||r_0||<tol, is used. 
 * \param restart number of restart
 *
 * \return the total number of iteration 
 *
 * \author Zhiyang Zhou 
 * \date 2010/11/28
 */ 
INT fasp_solver_dcsr_pgmres (dCSRmat *A, 
                             dvector *b, 
                             dvector *x, 
                             const INT maxit, 
                             const REAL tol,
                             precond *pre, 
                             const INT print_level, 
                             const INT stop_type, 
                             const INT restart)
{
	const INT n                    = A->row;  
	const INT min_iter             = 0;
	
    // local variables
	SHORT    converged = FALSE; 
	INT      status = SUCCESS;
	INT      iter = 0;
	INT      restartplus1 = restart + 1;
	INT      i, j, k;
	
	REAL     epsmac = SMALLREAL; 
	REAL     r_norm, b_norm, den_norm;
	REAL     epsilon, gamma, t, r_norm_0;   
	
	REAL    *c = NULL, *s = NULL, *rs = NULL; 
	REAL    *norms = NULL, *r = NULL, *w = NULL;
	REAL   **p = NULL, **hh = NULL;
	REAL    *work = NULL;
	
	/* allocate memory */
	work = (REAL *)fasp_mem_calloc((restart+4)*(restart+n)+1-n, sizeof(REAL));
	
	p  = (REAL **)fasp_mem_calloc(restartplus1, sizeof(REAL *));
	
	hh = (REAL **)fasp_mem_calloc(restartplus1, sizeof(REAL *)); 
	
	if (print_level>PRINT_NONE) norms = (REAL *)fasp_mem_calloc(maxit+1, sizeof(REAL)); 
	
	r = work; w = r + n; rs = w + n; c  = rs + restartplus1; s  = c + restart;	
	
    for (i = 0; i < restartplus1; i ++) p[i] = s + restart + i*n;
	
    for (i = 0; i < restartplus1; i ++) hh[i] = p[restart] + n + i*restart;
	
	/* initialization */
	fasp_array_cp(n, b->val, p[0]);
	fasp_blas_dcsr_aAxpy(-1.0, A, x->val, p[0]);
	
	b_norm = fasp_blas_array_norm2(n, b->val);
	r_norm = fasp_blas_array_norm2(n, p[0]);
	r_norm_0 = r_norm;
	
	if ( print_level > PRINT_NONE)
	{
		norms[0] = r_norm;
		if ( print_level >= PRINT_SOME )
		{
            ITS_PUTNORM("right-hand side", b_norm);
            ITS_PUTNORM("residual", r_norm);
		}
	}
	
	if (b_norm > 0.0)  den_norm = b_norm;
	else               den_norm = r_norm;
	
	epsilon = tol*den_norm;
	
	/* outer iteration cycle */
	while (iter < maxit)
	{  
		rs[0] = r_norm;
		if (r_norm == 0.0)
		{
			fasp_mem_free(work); 
			fasp_mem_free(p); 
			fasp_mem_free(hh);
			fasp_mem_free(norms);
			return iter; 
		}
		
		if (r_norm <= epsilon && iter >= min_iter) 
		{
			fasp_array_cp(n, b->val, r);
			fasp_blas_dcsr_aAxpy(-1.0, A, x->val, r);
			r_norm = fasp_blas_array_norm2(n, r);
			
			if (r_norm <= epsilon)
			{
				if (print_level > PRINT_NONE) printf("Number of iterations = %d with L2 residual %e.\n", iter, r_norm);
				break;
			}
			else
			{
				if (print_level >= PRINT_SOME) printf("### WARNING: False convergence!\n");
			}
		}
		
		t = 1.0 / r_norm;
		for (j = 0; j < n; j ++) p[0][j] *= t;
		
		/* RESTART CYCLE (right-preconditioning) */
		i = 0;
		while (i < restart && iter < maxit)
		{
			i ++;  iter ++;
			
			fasp_array_set(n, r, 0.0);
			
			/* apply the preconditioner */
			if (pre == NULL)
				fasp_array_cp(n, p[i-1], r);
			else
				pre->fct(p[i-1], r, pre->data);          
			
			fasp_blas_dcsr_mxv(A, r, p[i]);
			
			/* modified Gram_Schmidt */
			for (j = 0; j < i; j ++)
			{
				hh[j][i-1] = fasp_blas_array_dotprod(n, p[j], p[i]);
				fasp_blas_array_axpy(n, -hh[j][i-1], p[j], p[i]);
			}
			t = fasp_blas_array_norm2(n, p[i]);
			hh[i][i-1] = t;	
			if (t != 0.0)
			{
				t = 1.0/t;
				for (j = 0; j < n; j ++) p[i][j] *= t;
			}
			
			for (j = 1; j < i; ++j)
			{
				t = hh[j-1][i-1];
				hh[j-1][i-1] = s[j-1]*hh[j][i-1] + c[j-1]*t;
				hh[j][i-1] = -s[j-1]*t + c[j-1]*hh[j][i-1];
			}
			t= hh[i][i-1]*hh[i][i-1];
			t+= hh[i-1][i-1]*hh[i-1][i-1];
			gamma = sqrt(t);
			if (gamma == 0.0) gamma = epsmac;
			c[i-1]  = hh[i-1][i-1] / gamma;
			s[i-1]  = hh[i][i-1] / gamma;
			rs[i]   = -s[i-1]*rs[i-1];
			rs[i-1] = c[i-1]*rs[i-1];
			hh[i-1][i-1] = s[i-1]*hh[i][i-1] + c[i-1]*hh[i-1][i-1];
			r_norm = fabs(rs[i]);
			
			if (print_level > PRINT_NONE) norms[iter] = r_norm;
			
			if (b_norm > 0 ) {
				if (print_level > PRINT_NONE) print_itinfo(print_level,stop_type,iter,norms[iter]/b_norm,norms[iter],norms[iter]/norms[iter-1]);
			}
			else {
				if (print_level > PRINT_NONE) print_itinfo(print_level,stop_type,iter,norms[iter],norms[iter],norms[iter]/norms[iter-1]);
			}
			
			/* should we exit the restart cycle? */
			if (r_norm <= epsilon && iter >= min_iter)
			{
				break;
			}         
		} /* end of restart cycle */
		
		/* now compute solution, first solve upper triangular system */		
		rs[i-1] = rs[i-1] / hh[i-1][i-1];
		for (k = i-2; k >= 0; k --)
		{
			t = 0.0;
			for (j = k+1; j < i; j ++)  t -= hh[k][j]*rs[j];
			
			t += rs[k];
			rs[k] = t / hh[k][k];
		}
		fasp_array_cp(n, p[i-1], w);
		for (j = 0; j < n; j ++) w[j] *= rs[i-1];
		for (j = i-2; j >= 0; j --)  fasp_blas_array_axpy(n, rs[j], p[j], w);
		fasp_array_set(n, r, 0.0);
		
		/* apply the preconditioner */
		if (pre == NULL)
			fasp_array_cp(n, w, r);
		else
			pre->fct(w, r, pre->data);
		
		fasp_blas_array_axpy(n, 1.0, r, x->val);
		
		if (r_norm  <= epsilon && iter >= min_iter) 
		{
			fasp_array_cp(n, b->val, r);
			fasp_blas_dcsr_aAxpy(-1.0, A, x->val, r);
			r_norm = fasp_blas_array_norm2(n, r);
			
			if (r_norm  <= epsilon)
			{
				if (print_level > PRINT_NONE) printf("Number of iterations = %d with L2 residual %e.\n", iter, r_norm);
				converged = 1; break;
			}
			else
			{
				if (print_level >= PRINT_SOME) printf("### WARNING: False convergence!\n");
				fasp_array_cp(n, r, p[0]); i = 0;
			}
		} /* end of convergence check */
		
		/* compute residual vector and continue loop */
		for (j = i; j > 0; j--)
		{
			rs[j-1] = -s[j-1]*rs[j];
			rs[j] = c[j-1]*rs[j];
		}
		
		if (i) fasp_blas_array_axpy(n, rs[i]-1.0, p[i], p[i]);
		
		for (j = i-1 ; j > 0; j --) fasp_blas_array_axpy(n, rs[j], p[j], p[i]);
		
		if (i)
		{
			fasp_blas_array_axpy(n, rs[0]-1.0, p[0], p[0]);
			fasp_blas_array_axpy(n, 1.0, p[i], p[0]);
		}        
	} /* end of iteration while loop */
	
	if (print_level > PRINT_NONE && iter >= maxit && r_norm > epsilon) 
	{
		printf("### WARNING: Not reaching the given tolerance in %d iterations!\n", maxit);
	}
	
    /*-------------------------------------------
     * Clean up workspace
     *------------------------------------------*/
	fasp_mem_free(work); 
	fasp_mem_free(p); 
	fasp_mem_free(hh);
	fasp_mem_free(norms);
	
	if (iter>=maxit) return ERROR_SOLVER_MAXIT;
	else if (status<0) return status;
	else return iter;
}

/**
 *	\fn INT fasp_solver_bdcsr_pgmres (block_Reservoir *A, dvector *b, dvector *u, const INT maxit, 
 *                                    const REAL tol, precond *pre, const SHORT print_level, 
 *                                    const SHORT stop_type, const SHORT restart)
 *
 *	\brief A preconditioned generalized minimum residual method (GMRES) method for solving Au=b 
 *
 *	\param *A	 pointer to the coefficient matrix
 *	\param *b	 pointer to the dvector of right hand side
 *	\param *u	 pointer to the dvector of dofs
 *	\param maxit integer, maximal number of iterations
 *	\param tol   REAL, the tolerance for stopage
 *	\param *pre  pointer to the structure of precondition (precond) 
 *  \param print_level how much information to print out
 *
 *	\return the number of iterations
 *
 *  \author Xiaozhe Hu
 *  \data 05/24/2010
 */
INT fasp_solver_bdcsr_pgmres (block_dCSRmat *A, 
                              dvector *b, 
                              dvector *u, 
                              const INT maxit, 
                              const REAL tol,
                              precond *pre, 
                              const SHORT print_level, 
                              const SHORT stop_type, 
                              const SHORT restart)
{
	const INT nrow=b->row, nrow_1=nrow-1;
	const REAL sol_inf_tol = 1e-16; // infinity norm tolrance

    // local variables
	INT i, j, j1, index, iter=0, m=restart;
	REAL beta, betai, tempe, tempb, tempu, hij, temp2;
	REAL absres0=BIGREAL, absres, relres1, infnormu, factor;
	
	if ((m<1)||(m>nrow)||(m>150)) m=10; // default restart level
	
	REAL *tmp=(REAL *)fasp_mem_calloc(m+1,sizeof(REAL));
	
	dvector *v=(dvector *)fasp_mem_calloc(m+1,sizeof(dvector));
	
	for (i=0;i<=m;++i) {
		v[i].row=nrow;
		v[i].val=(REAL*)fasp_mem_calloc(nrow,sizeof(REAL));
	}
	
	dvector y = fasp_dvec_create(m);
	
	REAL *r=(REAL*)fasp_mem_calloc(nrow,sizeof(REAL));
	
	REAL *z=(REAL *)fasp_mem_calloc(nrow,sizeof(REAL));
	
	REAL *w=(REAL *)fasp_mem_calloc(nrow,sizeof(REAL));		
	
	// generate the structure of H, i.e. H->IA, H->JA
	dCSRmat H=fasp_dcsr_create(m+1, m, m*(m+3)/2);
	
	H.IA[1]=m;
	for (i=2;i<=H.row;++i) H.IA[i]=H.IA[i-1]+m+2-i;
	
	for (i=0;i<H.row;++i) {
		if (i==0)
			index=0;
		else
			index=i-1;
		
		unsigned INT begin_row=H.IA[i], end_row1=H.IA[i+1];			
		for(j=begin_row;j<end_row1;++j) {
			H.JA[j]=index;
			index++;
		}
	}
	
	// compute norm for right hand side
	switch (stop_type) {
		case STOP_REL_PRECRES:
			if (pre != NULL) 
				pre->fct(b->val,z,pre->data); /* Preconditioning */
			else 
				fasp_array_cp(nrow,b->val,z); /* No preconditioner, B=I */
			tempb=sqrt(ABS(fasp_blas_array_dotprod(nrow,b->val,z)));
			break;
		case STOP_MOD_REL_RES:
			break;
		default: // STOP_REL_RES
			tempb=fasp_blas_array_norm2(nrow,b->val); // norm(b)
			break;
	}
	tempb=MAX(SMALLREAL,tempb);
	tempu=MAX(SMALLREAL,fasp_blas_array_norm2(nrow,u->val));
	
	// r = b-A*u
	fasp_array_cp(nrow,b->val,r); 
	fasp_blas_bdcsr_aAxpy(-1.0,A,u->val,r);
	tempe=fasp_blas_array_norm2(nrow,r);
	
	switch (stop_type) {
		case STOP_REL_PRECRES:
			if (pre == NULL)
				fasp_array_cp(nrow,r,z);
			else
				pre->fct(r,z,pre->data);
			temp2=sqrt(ABS(fasp_blas_array_dotprod(nrow,r,z)));
			relres1=temp2/tempb; 
			break;
		case STOP_MOD_REL_RES:
			relres1=tempe/tempu; 
			break;
        default: // STOP_REL_RES
			relres1=tempe/tempb; 
			break;
	}
	
	if (relres1<tol) { fasp_mem_free(r); goto FINISHED; }
	
	if  (iter < 0) goto FINISHED;
	
	while (iter++<maxit)
	{
		// z = B*r
		if (pre == NULL) {
			fasp_array_cp(nrow,r,z);  /* No preconditioner, B=I */
		}
		else {
			pre->fct(r,z,pre->data); /* Preconditioning */
		}
		
		beta=fasp_blas_array_norm2(nrow,z); betai=1.0/beta;
		
		// v_0 = z/beta
		for (i=0;i<=nrow_1;++i) v[0].val[i]=betai*z[i];
		
		for (j=0;j<m;++j)
		{
			// r = Av_j
			fasp_array_set(nrow, r, 0.0); 
			fasp_blas_bdcsr_aAxpy(1.0,A,v[j].val,r);
			
			// w = B*r
			if (pre == NULL) {
				fasp_array_cp(nrow,r,w);  /* No preconditioner, B=I */
			}
			else {
				pre->fct(r,w,pre->data); /* Preconditioning */
			}
			
			for (i=0;i<=j;++i)
			{
				if (i==0) index=0;
				else index=i-1;
				hij=fasp_blas_array_dotprod(nrow,w,v[i].val);
				H.val[H.IA[i]+j-index]=hij;
				fasp_blas_array_axpy(nrow, -hij, v[i].val, w);
			}
			
			j1=j+1;
			hij=fasp_blas_array_norm2(nrow,w);  // h_{j+1,j}=\|w\|_2
			H.val[H.IA[j1]]=hij;
			
			// v_{j+1}=w/h_{j+1,j}
			hij=1.0/hij;
			for (i=0;i<=nrow_1;++i) v[j1].val[i]=w[i]*hij;
		}
		
		fasp_aux_givens(beta, &H, &y, v, tmp);
		
		// u_m=u_0 + V_m*y_m
		for (i=0;i<m;++i) fasp_blas_array_axpy(nrow, y.val[i], v[i].val, u->val); // maybe we can check the residual for every iteration ?!
		
		// r = b-A*u
		fasp_array_cp(nrow,b->val,r); 
		fasp_blas_bdcsr_aAxpy(-1.0,A,u->val,r);
		
		// absolute and relative residuals
		absres=sqrt(fasp_blas_array_dotprod(nrow,r,r));
		
		tempu=sqrt(fasp_blas_dvec_dotprod(u,u));		
		
		switch (stop_type) {
			case STOP_REL_PRECRES:
				if (pre == NULL)
					fasp_array_cp(nrow,r,z);
				else
					pre->fct(r,z,pre->data);
				temp2=sqrt(ABS(fasp_blas_array_dotprod(nrow,r,z)));
				relres1=temp2/tempb; 
				break;
			case STOP_MOD_REL_RES:
				relres1=absres/tempu; 
				break;
			default: // STOP_REL_RES
				relres1=absres/tempb; 
				break;
		}
		
		// contraction factor
		factor=absres/absres0;
		
		// output iteration information if needed	
		print_itinfo(print_level,stop_type,iter,relres1,absres,factor);
		
		absres0=absres;
		
		// solution check, if soultion is too small, return ERROR_SOLVER_SOLSTAG.
		infnormu = fasp_blas_array_norminf(nrow, u->val); 
		if (infnormu <= sol_inf_tol)
		{
            if (print_level>PRINT_MIN) ITS_ZEROSOL;
			iter = ERROR_SOLVER_SOLSTAG;
			break;
		}
		
		if (relres1<tol) break;
	}
	
FINISHED:
	if (print_level>PRINT_NONE) ITS_FINAL(iter,maxit,relres1);
	
	fasp_dvec_free(&y);
	fasp_dcsr_free(&H);
	fasp_mem_free(tmp);
	fasp_mem_free(z); 
	fasp_mem_free(w);
	fasp_mem_free(r);	
	for (i=0;i<=m;++i) fasp_mem_free(v[i].val);
	fasp_mem_free(v);
	
	return iter;
}

/*!
 * \fn INT fasp_solver_dbsr_pgmres (dBSRmat *A, dvector *b, dvector *x, const INT maxit, 
 *                                  const REAL tol, precond *pre, const SHORT print_level, 
 *                                  const SHORT stop_type, const SHORT restart)
 *
 * \brief Solve "Ax=b" using PGMRES(right preconditioned) iterative method
 * \param *A the pointer to the coefficient matrix
 * \param *b the pointer to the right hand side vector
 * \param *x the pointer to the solution vector
 * \param maxit the maximal iteration  
 * \param tol the tolerance
 * \param *pre pointer to preconditioner data
 * \param print_level how much of the SOLVE-INFORMATION be output?
 * \param stop_type this parameter is not used in my function at present, 
 *        the default stopping criterion,i.e.||r_k||/||r_0||<tol, is used. 
 * \param restart number of restart
 *
 * \return the total number of iteration 
 *
 * \author Zhiyang Zhou 
 * \date 2010/12/21
 */ 
INT fasp_solver_dbsr_pgmres (dBSRmat *A, 
                             dvector *b, 
                             dvector *x, 
                             const INT maxit, 
                             const REAL tol,
                             precond *pre, 
                             const SHORT print_level, 
                             const SHORT stop_type, 
                             const SHORT restart)
{
	const INT n = A->ROW*A->nb;;  
	const INT min_iter = 0;
	
    // local variables
	SHORT     converged = 0; 
	INT       status = SUCCESS;
	INT       iter = 0;
	INT       restartplus1 = restart + 1;
	INT       i, j, k;
	
	REAL      epsmac = SMALLREAL; 
	REAL      r_norm, b_norm, den_norm;
	REAL      epsilon, gamma, t, r_norm_0;   
	
	REAL     *c = NULL, *s = NULL, *rs = NULL; 
	REAL     *norms = NULL, *r = NULL, *w = NULL;
	REAL    **p = NULL, **hh = NULL;
	REAL     *work = NULL;
	
	/* allocate memory */
	work = (REAL *)fasp_mem_calloc((restart+4)*(restart+n)+1-n, sizeof(REAL));
	
	p  = (REAL **)fasp_mem_calloc(restartplus1, sizeof(REAL *));
	
	hh = (REAL **)fasp_mem_calloc(restartplus1, sizeof(REAL *)); 
	
	if (print_level > PRINT_NONE) norms = (REAL *)fasp_mem_calloc(maxit+1, sizeof(REAL)); 
	
	r = work; w = r + n; rs = w + n; c  = rs + restartplus1; s  = c + restart;	
	for (i = 0; i < restartplus1; ++i) p[i] = s + restart + i*n;
	for (i = 0; i < restartplus1; ++i) hh[i] = p[restart] + n + i*restart;
	
	/* initialization */
	fasp_array_cp(n, b->val, p[0]);
	fasp_blas_dbsr_aAxpy(-1.0, A, x->val, p[0]);
	
	b_norm = fasp_blas_array_norm2(n, b->val);
	r_norm = fasp_blas_array_norm2(n, p[0]);
	r_norm_0 = r_norm;
	
	if ( print_level > PRINT_NONE)
	{
		norms[0] = r_norm;
		if ( print_level >= PRINT_SOME )
		{
            ITS_PUTNORM("right-hand side", b_norm);
            ITS_PUTNORM("residual", r_norm);
		}
	}
	
	if (b_norm > 0.0)  den_norm = b_norm;
	else               den_norm = r_norm;
	
	epsilon = tol*den_norm;
	
	/* outer iteration cycle */
	while (iter < maxit)
	{  
		rs[0] = r_norm;
		if (r_norm == 0.0)
		{
			fasp_mem_free(work); 
			fasp_mem_free(p); 
			fasp_mem_free(hh);
			fasp_mem_free(norms);
			return iter; 
		}
		
		if (r_norm <= epsilon && iter >= min_iter) 
		{
			fasp_array_cp(n, b->val, r);
			fasp_blas_dbsr_aAxpy(-1.0, A, x->val, r);
			r_norm = fasp_blas_array_norm2(n, r);
			
			if (r_norm <= epsilon)
			{
				if (print_level > PRINT_NONE) printf("Number of iterations = %d with L2 residual %e.\n", iter, r_norm);
				break;
			}
			else
			{
				if (print_level >= PRINT_SOME) printf("### WARNING: False convergence!\n");
			}
		}
		
		t = 1.0 / r_norm;
		for (j = 0; j < n; ++j) p[0][j] *= t;
		
		/* RESTART CYCLE (right-preconditioning) */
		i = 0;
		while (i < restart && iter < maxit)
		{
			++i;  ++iter;
			
			fasp_array_set(n, r, 0.0);
			
			/* apply the preconditioner */
			if (pre == NULL)
				fasp_array_cp(n, p[i-1], r);
			else
				pre->fct(p[i-1], r, pre->data);          
			
			fasp_blas_dbsr_mxv(A, r, p[i]);
			
			/* modified Gram_Schmidt */
			for (j = 0; j < i; ++j)
			{
				hh[j][i-1] = fasp_blas_array_dotprod(n, p[j], p[i]);
				fasp_blas_array_axpy(n, -hh[j][i-1], p[j], p[i]);
			}
			t = fasp_blas_array_norm2(n, p[i]);
			hh[i][i-1] = t;	
			if (t != 0.0)
			{
				t = 1.0/t;
				for (j = 0; j < n; ++j) p[i][j] *= t;
			}
			
			for (j = 1; j < i; j++)
			{
				t = hh[j-1][i-1];
				hh[j-1][i-1] = s[j-1]*hh[j][i-1] + c[j-1]*t;
				hh[j][i-1] = -s[j-1]*t + c[j-1]*hh[j][i-1];
			}
			t= hh[i][i-1]*hh[i][i-1];
			t+= hh[i-1][i-1]*hh[i-1][i-1];
			gamma = sqrt(t);
			if (gamma == 0.0) gamma = epsmac;
			c[i-1]  = hh[i-1][i-1] / gamma;
			s[i-1]  = hh[i][i-1] / gamma;
			rs[i]   = -s[i-1]*rs[i-1];
			rs[i-1] = c[i-1]*rs[i-1];
			hh[i-1][i-1] = s[i-1]*hh[i][i-1] + c[i-1]*hh[i-1][i-1];
			r_norm = fabs(rs[i]);
			
			if (print_level > PRINT_NONE) norms[iter] = r_norm;
			
			if (b_norm > 0 ) {
				if (print_level > PRINT_NONE) print_itinfo(print_level,stop_type,iter,norms[iter]/b_norm,norms[iter],norms[iter]/norms[iter-1]);
			}
			else {
				if (print_level > PRINT_NONE) print_itinfo(print_level,stop_type,iter,norms[iter],norms[iter],norms[iter]/norms[iter-1]);
			}
			
			/* should we exit the restart cycle? */
			if (r_norm <= epsilon && iter >= min_iter)
			{
				break;
			}         
		} /* end of restart cycle */
		
		/* now compute solution, first solve upper triangular system */		
		rs[i-1] = rs[i-1] / hh[i-1][i-1];
		for (k = i-2; k >= 0; --k)
		{
			t = 0.0;
			for (j = k+1; j < i; ++j)  t -= hh[k][j]*rs[j];
			
			t += rs[k];
			rs[k] = t / hh[k][k];
		}
		fasp_array_cp(n, p[i-1], w);
		for (j = 0; j < n; ++j) w[j] *= rs[i-1];
		for (j = i-2; j >= 0; --j)  fasp_blas_array_axpy(n, rs[j], p[j], w);
		fasp_array_set(n, r, 0.0);
		
		/* apply the preconditioner */
		if (pre == NULL)
			fasp_array_cp(n, w, r);
		else
			pre->fct(w, r, pre->data);
		
		fasp_blas_array_axpy(n, 1.0, r, x->val);
		
		if (r_norm  <= epsilon && iter >= min_iter) 
		{
			fasp_array_cp(n, b->val, r);
			fasp_blas_dbsr_aAxpy(-1.0, A, x->val, r);
			r_norm = fasp_blas_array_norm2(n, r);
			
			if (r_norm  <= epsilon)
			{
				if (print_level > PRINT_NONE) printf("Number of iterations = %d with L2 residual %e.\n", iter, r_norm);
				converged = 1; break;
			}
			else
			{
				if ( print_level >= PRINT_SOME ) printf("### WARNING: False convergence!\n");
				fasp_array_cp(n, r, p[0]); i = 0;
			}
		} /* end of convergence check */
		
		/* compute residual vector and continue loop */
		for (j = i; j > 0; j--)
		{
			rs[j-1] = -s[j-1]*rs[j];
			rs[j] = c[j-1]*rs[j];
		}
		
		if (i) fasp_blas_array_axpy(n, rs[i]-1.0, p[i], p[i]);
		
		for (j = i-1 ; j > 0; --j) fasp_blas_array_axpy(n, rs[j], p[j], p[i]);
		
		if (i)
		{
			fasp_blas_array_axpy(n, rs[0]-1.0, p[0], p[0]);
			fasp_blas_array_axpy(n, 1.0, p[i], p[0]);
		}        
	} /* end of iteration while loop */
	
	if (print_level > PRINT_NONE && iter >= maxit && r_norm > epsilon) 
	{
		printf("### WARNING: Not reaching the given tolerance in %d iterations!\n", maxit);
	}
	
    /*-------------------------------------------
     * Clean up workspace
     *------------------------------------------*/
	fasp_mem_free(work); 
	fasp_mem_free(p); 
	fasp_mem_free(hh);
	fasp_mem_free(norms);
	
	if (iter>=maxit) return ERROR_SOLVER_MAXIT;
	else if (status<0) return status;
	else return iter;
}

/*!
 * \fn INT fasp_solver_dstr_pgmres (dSTRmat *A, dvector *b, dvector *x, const INT maxit, 
 *                                  const REAL tol, precond *pre, const SHORT print_level, 
 *                                  const SHORT stop_type, const SHORT restart)
 *
 * \brief Solve "Ax=b" using PGMRES(right preconditioned) iterative method
 *
 * \param *A the pointer to the coefficient matrix
 * \param *b the pointer to the right hand side vector
 * \param *x the pointer to the solution vector
 * \param maxit the maximal iteration  
 * \param tol the tolerance
 * \param *pre pointer to preconditioner data
 * \param print_level how much of the SOLVE-INFORMATION be output?
 * \param stop_type this parameter is not used in my function at present, 
 *        the default stopping criterion,i.e.||r_k||/||r_0||<tol, is used. 
 * \param restart number of restart
 *
 * \return the total number of iteration 
 *
 * \author Zhiyang Zhou 
 * \date 2010/11/28
 */ 
INT fasp_solver_dstr_pgmres (dSTRmat *A, 
                             dvector *b, 
                             dvector *x, 
                             const INT maxit, 
                             const REAL tol,
                             precond *pre, 
                             const SHORT print_level, 
                             const SHORT stop_type, 
                             const SHORT restart )
{
	const INT n = A->nc*A->ngrid;  
	const INT min_iter = 0;
	
    // local varialbes
	SHORT     converged = 0; 
	INT       iter = 0;
	INT       status = SUCCESS;
	INT       restartplus1 = restart + 1;
	INT       i, j, k;
	
	REAL      epsmac = SMALLREAL; 
	REAL      r_norm, b_norm, den_norm;
	REAL      epsilon, gamma, t, r_norm_0;   
	
	REAL     *c = NULL, *s = NULL, *rs = NULL; 
	REAL     *norms = NULL, *r = NULL, *w = NULL;
	REAL    **p = NULL, **hh = NULL;
	REAL     *work = NULL;
	
	/* allocate memory */
	work = (REAL *)fasp_mem_calloc((restart+4)*(restart+n)+1-n, sizeof(REAL));
	
	p  = (REAL **)fasp_mem_calloc(restartplus1, sizeof(REAL *));
	
	hh = (REAL **)fasp_mem_calloc(restartplus1, sizeof(REAL *)); 
	
	if (print_level > PRINT_NONE) norms = (REAL *)fasp_mem_calloc(maxit+1, sizeof(REAL)); 
	
	r = work; w = r + n; rs = w + n; c  = rs + restartplus1; s  = c + restart;	
	for (i = 0; i < restartplus1; ++i) p[i] = s + restart + i*n;
	for (i = 0; i < restartplus1; ++i) hh[i] = p[restart] + n + i*restart;
	
	/* initialization */
	fasp_array_cp(n, b->val, p[0]);
	fasp_blas_dstr_aAxpy(-1.0, A, x->val, p[0]);
	
	b_norm = fasp_blas_array_norm2(n, b->val);
	r_norm = fasp_blas_array_norm2(n, p[0]);
	r_norm_0 = r_norm;
	
	if ( print_level > PRINT_NONE)
	{
		norms[0] = r_norm;
		if ( print_level >= PRINT_SOME )
		{
            ITS_PUTNORM("right-hand side", b_norm);
            ITS_PUTNORM("residual", r_norm);
		}
	}
	
	if (b_norm > 0.0)  den_norm = b_norm;
	else               den_norm = r_norm;
	
	epsilon = tol*den_norm;
	
	/* outer iteration cycle */
	while (iter < maxit)
	{  
		rs[0] = r_norm;
		if (r_norm == 0.0)
		{
			fasp_mem_free(work); 
			fasp_mem_free(p); 
			fasp_mem_free(hh);
			fasp_mem_free(norms);
			return iter; 
		}
		
		if (r_norm <= epsilon && iter >= min_iter) 
		{
			fasp_array_cp(n, b->val, r);
			fasp_blas_dstr_aAxpy(-1.0, A, x->val, r);
			r_norm = fasp_blas_array_norm2(n, r);
			
			if (r_norm <= epsilon)
			{
				if (print_level > PRINT_NONE) printf("Number of iterations = %d with L2 residual %e.\n", iter, r_norm);
				break;
			}
			else
			{
				if (print_level >= PRINT_SOME) printf("### WARNING: False convergence!\n");
			}
		}
		
		t = 1.0 / r_norm;
		for (j = 0; j < n; ++j) p[0][j] *= t;
		
		/* RESTART CYCLE (right-preconditioning) */
		i = 0;
		while (i < restart && iter < maxit)
		{
			++i;  ++iter;
			
			fasp_array_set(n, r, 0.0);
			
			/* apply the preconditioner */
			if (pre == NULL)
				fasp_array_cp(n, p[i-1], r);
			else
				pre->fct(p[i-1], r, pre->data);          
			
			//fasp_blas_dbsr_mxv(A, r, p[i]);
			fasp_blas_dstr_aAxpy(1.0, A, r, p[i]); // we need spmxv_str here. --Zhiyang Zhou
			
			/* modified Gram_Schmidt */
			for (j = 0; j < i; ++j)
			{
				hh[j][i-1] = fasp_blas_array_dotprod(n, p[j], p[i]);
				fasp_blas_array_axpy(n, -hh[j][i-1], p[j], p[i]);
			}
			t = fasp_blas_array_norm2(n, p[i]);
			hh[i][i-1] = t;	
			if (t != 0.0)
			{
				t = 1.0/t;
				for (j = 0; j < n; ++j) p[i][j] *= t;
			}
			
			for (j = 1; j < i; ++j)
			{
				t = hh[j-1][i-1];
				hh[j-1][i-1] = s[j-1]*hh[j][i-1] + c[j-1]*t;
				hh[j][i-1] = -s[j-1]*t + c[j-1]*hh[j][i-1];
			}
			t= hh[i][i-1]*hh[i][i-1];
			t+= hh[i-1][i-1]*hh[i-1][i-1];
			gamma = sqrt(t);
			if (gamma == 0.0) gamma = epsmac;
			c[i-1]  = hh[i-1][i-1] / gamma;
			s[i-1]  = hh[i][i-1] / gamma;
			rs[i]   = -s[i-1]*rs[i-1];
			rs[i-1] = c[i-1]*rs[i-1];
			hh[i-1][i-1] = s[i-1]*hh[i][i-1] + c[i-1]*hh[i-1][i-1];
			r_norm = fabs(rs[i]);
			
			if (print_level > PRINT_NONE) norms[iter] = r_norm;
			
			if (b_norm > 0 ) {
				if (print_level > PRINT_NONE) print_itinfo(print_level,stop_type,iter,norms[iter]/b_norm,norms[iter],norms[iter]/norms[iter-1]);
			}
			else {
				if (print_level > PRINT_NONE) print_itinfo(print_level,stop_type,iter,norms[iter],norms[iter],norms[iter]/norms[iter-1]);
			}
			
			/* should we exit the restart cycle? */
			if (r_norm <= epsilon && iter >= min_iter)
			{
				break;
			}         
		} /* end of restart cycle */
		
		/* now compute solution, first solve upper triangular system */		
		rs[i-1] = rs[i-1] / hh[i-1][i-1];
		for (k = i-2; k >= 0; k --)
		{
			t = 0.0;
			for (j = k+1; j < i; ++j)  t -= hh[k][j]*rs[j];
			
			t += rs[k];
			rs[k] = t / hh[k][k];
		}
		fasp_array_cp(n, p[i-1], w);
		for (j = 0; j < n; ++j) w[j] *= rs[i-1];
		for (j = i-2; j >= 0; j --)  fasp_blas_array_axpy(n, rs[j], p[j], w);
		fasp_array_set(n, r, 0.0);
		
		/* apply the preconditioner */
		if (pre == NULL)
			fasp_array_cp(n, w, r);
		else
			pre->fct(w, r, pre->data);
		
		fasp_blas_array_axpy(n, 1.0, r, x->val);
		
		if (r_norm  <= epsilon && iter >= min_iter) 
		{
			fasp_array_cp(n, b->val, r);
			fasp_blas_dstr_aAxpy(-1.0, A, x->val, r);
			r_norm = fasp_blas_array_norm2(n, r);
			
			if (r_norm  <= epsilon)
			{
				if (print_level > PRINT_NONE) printf("Number of iterations = %d with L2 residual %e.\n", iter, r_norm);
				converged = 1; break;
			}
			else
			{
				if (print_level >= PRINT_SOME) printf("### WARNING: False convergence!\n");
				fasp_array_cp(n, r, p[0]); i = 0;
			}
		} /* end of convergence check */
		
		/* compute residual vector and continue loop */
		for (j = i; j > 0; j--)
		{
			rs[j-1] = -s[j-1]*rs[j];
			rs[j] = c[j-1]*rs[j];
		}
		
		if (i) fasp_blas_array_axpy(n, rs[i]-1.0, p[i], p[i]);
		
		for (j = i-1 ; j > 0; j --) fasp_blas_array_axpy(n, rs[j], p[j], p[i]);
		
		if (i)
		{
			fasp_blas_array_axpy(n, rs[0]-1.0, p[0], p[0]);
			fasp_blas_array_axpy(n, 1.0, p[i], p[0]);
		}        
	} /* end of iteration while loop */
	
	if (print_level > PRINT_NONE && iter >= maxit && r_norm > epsilon) 
	{
		printf("### WARNING: Not reaching the given tolerance in %d iterations!\n", maxit);
	}
	
    /*-------------------------------------------
     * Clean up workspace
     *------------------------------------------*/
	fasp_mem_free(work); 
	fasp_mem_free(p); 
	fasp_mem_free(hh);
	fasp_mem_free(norms);
	
	if (iter>=maxit) return ERROR_SOLVER_MAXIT;
	else if (status<0) return status;
	else return iter;
}

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/
