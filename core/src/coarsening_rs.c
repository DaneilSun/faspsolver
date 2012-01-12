/*! \file coarsening_rs.c
 *  \brief Coarsening with a modified Ruge-Stuben strategy.
 */

#include "fasp.h"
#include "fasp_functs.h"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/**
 * \fn int fasp_amg_coarsening_rs(dCSRmat *A, ivector *vertices, dCSRmat *P, 
 *                                AMG_param *param)
 * \brief RS coarsening
 *
 * \param *A          pointer to the coefficient matrix, the index starts from zero
 * \param *vertices   pointer to the indicator ivector of the CF splitting of the vertices
 *                        0: fine gird points
 *                        1: coarse grid points
 *                        2: isolated grid points
 * \param *P          pointer to the resulted interpolation matrix (nonzero pattern only)
 * \param *param      pointer to AMG parameters
 * \return            SUCCESS or Error message
 *
 * Refter to Multigrid by U. Trottenberg, C. W. Oosterlee and A. Schuller 
 *           Appendix P475 A.7 (by A. Brandt, P. Oswald and K. Stuben)
 *           Academic Press Inc., San Diego, CA, 2001. 
 * 
 * \author Xuehai Huang, Chensong Zhang, Xiaozhe Hu, Ludmil Zikatanov
 * \date 09/06/2010
 */
int fasp_amg_coarsening_rs (dCSRmat *A, 
														ivector *vertices, 
														dCSRmat *P, 
														AMG_param *param)
{	
	const int   coarsening_type = param->coarsening_type;
	const int   row = A->row;
	const double epsilon_str = param->strong_threshold;
	
	int status = SUCCESS, col = 0;	
	iCSRmat S; // strong n-couplings
	
#if DEBUG_MODE
	printf("coarsening_rs ...... [Start]\n");
#endif
	
#if CHMEM_MODE
	fasp_mem_usage();
#endif
	
#if DEBUG_MODE
	printf("Step 1. form dependent sets ......\n");
#endif
	
	// Step 1: generate S and S transpose
	switch (coarsening_type) {
		case 1: // modified Ruge-Stuben
			generate_S(A, &S, param); break;
		case 3: // compatible relaxation still uses S from modified Ruge-Stuben
			generate_S(A, &S, param); break;
		default: // classical Ruge-Stuben
			generate_S_rs(A, &S, epsilon_str, coarsening_type); break;
	}
	if (S.nnz == 0) return RUN_FAIL;
	
#if DEBUG_MODE
	printf("Step 2. choose C points ......\n");
#endif
	
	// Step 2: standard coarsening algorithm 
	switch (coarsening_type){
		case 3: // compatible relaxation (Need to be modified --Chensong)
			col = fasp_amg_coarsening_cr(0,A->row-1, A, vertices, param);	
			break;
		default:
			col = form_coarse_level(A, &S, vertices, row);
			break;
	}
	
#if DEBUG_MODE
	printf("Step 3. find support of C points ......\n");
#endif
	
	// Step 3: generate sparsity pattern of P
	 generate_sparsity_P(P, &S, vertices, row, col);
	
#if DEBUG_MODE
	printf("coarsening_rs ...... [Finish]\n");
#endif
	
	fasp_mem_free(S.IA);
	fasp_mem_free(S.JA);
	
#if CHMEM_MODE
	fasp_mem_usage();
#endif
	
	return status;
}

/*---------------------------------*/
/*--      Private Functions      --*/
/*---------------------------------*/

#define LIST_HEAD -1
#define LIST_TAIL -2

/**************************************************************
 *
 * dispose_elt(): dispose of memory space used by the element
 *                pointed to by element_ptr.  Use the 'free()'
 *                system call to return it to the free memory 
 *                pool.
 *
 **************************************************************/
void dispose_elt( LinkList element_ptr )
{
	if (element_ptr) fasp_mem_free( element_ptr );
}

/*****************************************************************
 * 
 * remove_point:   removes a point from the lists
 *
 ****************************************************************/
void remove_point(LinkList *LoL_head_ptr, LinkList *LoL_tail_ptr,
												 int measure, int index, int *lists, int *where)
{
	LinkList   LoL_head = *LoL_head_ptr;
	LinkList   LoL_tail = *LoL_tail_ptr;
	LinkList   list_ptr;
	
	list_ptr = LoL_head;
	
	do
	{
		if (measure == list_ptr->data)
		{
			
			/* point to be removed is only point on list,
			 which must be destroyed */
			if (list_ptr->head == index && list_ptr->tail == index)
			{
				/* removing only list, so num_left better be 0! */
				if (list_ptr == LoL_head && list_ptr == LoL_tail)
				{
					LoL_head = NULL;
					LoL_tail = NULL;
					dispose_elt(list_ptr);
					
					*LoL_head_ptr = LoL_head;
					*LoL_tail_ptr = LoL_tail;
					return;
				}
				else if (LoL_head == list_ptr) /*removing 1st (max_measure) list */
				{
					list_ptr -> next_elt -> prev_elt = NULL;
					LoL_head = list_ptr->next_elt;
					dispose_elt(list_ptr);
					
					*LoL_head_ptr = LoL_head;
					*LoL_tail_ptr = LoL_tail;
					return;
				}
				else if (LoL_tail == list_ptr)     /* removing last list */
				{
					list_ptr -> prev_elt -> next_elt = NULL;
					LoL_tail = list_ptr->prev_elt;
					dispose_elt(list_ptr);
					
					*LoL_head_ptr = LoL_head;
					*LoL_tail_ptr = LoL_tail;
					return;
				}
				else
				{
					list_ptr -> next_elt -> prev_elt = list_ptr -> prev_elt;
					list_ptr -> prev_elt -> next_elt = list_ptr -> next_elt;
					dispose_elt(list_ptr);
					
					*LoL_head_ptr = LoL_head;
					*LoL_tail_ptr = LoL_tail;
					return;
				}
			}
			else if (list_ptr->head == index)      /* index is head of list */
			{
				list_ptr->head = lists[index];
				where[lists[index]] = LIST_HEAD;
				return;
			}
			else if (list_ptr->tail == index)      /* index is tail of list */
			{
				list_ptr->tail = where[index];
				lists[where[index]] = LIST_TAIL;
				return;
			}
			else                              /* index is in middle of list */
			{
				lists[where[index]] = lists[index];
				where[lists[index]] = where[index];
				return;
			}
		}
		list_ptr = list_ptr -> next_elt;
	} while (list_ptr != NULL);
	
	printf("No such list!\n");
	return;
}

/*****************************************************************
 *
 * create_elt() : Create an element using Item for its data field
 *
 *****************************************************************/
LinkList create_elt( int Item )
{
	LinkList new_elt_ptr;
	
	/* Allocate memory space for the new node. 
	 * return with error if no space available
	 */	
	new_elt_ptr = (LinkList) fasp_mem_calloc(1,sizeof(ListElement));
	
	new_elt_ptr -> data = Item;
	new_elt_ptr -> next_elt = NULL;
	new_elt_ptr -> prev_elt = NULL;
	new_elt_ptr -> head = LIST_TAIL;
	new_elt_ptr -> tail = LIST_HEAD;
	
	return (new_elt_ptr);
}

/*****************************************************************
 * 
 * enter_list   places point in new list
 *
 ****************************************************************/
void enter_list(LinkList *LoL_head_ptr, LinkList *LoL_tail_ptr,
											 int measure, int index, int *lists, int *where)
{
	LinkList   LoL_head = *LoL_head_ptr;
	LinkList   LoL_tail = *LoL_tail_ptr;
	
	LinkList   list_ptr;
	LinkList   new_ptr;
	
	int         old_tail;
	
	list_ptr =  LoL_head;
	
	if (LoL_head == NULL)   /* no lists exist yet */
	{
		new_ptr = create_elt(measure);
		new_ptr->head = index;
		new_ptr->tail = index;
		lists[index] = LIST_TAIL;
		where[index] = LIST_HEAD; 
		LoL_head = new_ptr;
		LoL_tail = new_ptr;
		
		*LoL_head_ptr = LoL_head;
		*LoL_tail_ptr = LoL_tail;
		return;
	}
	else
	{
		do
		{
      if (measure > list_ptr->data)
      {
				new_ptr = create_elt(measure);
				
				new_ptr->head = index;
				new_ptr->tail = index;
				
				lists[index] = LIST_TAIL;
				where[index] = LIST_HEAD;
				
				if ( list_ptr->prev_elt != NULL)
				{ 
					new_ptr->prev_elt            = list_ptr->prev_elt;
					list_ptr->prev_elt->next_elt = new_ptr;   
					list_ptr->prev_elt           = new_ptr;
					new_ptr->next_elt            = list_ptr;
				}
				else
				{
					new_ptr->next_elt  = list_ptr;
					list_ptr->prev_elt = new_ptr;
					new_ptr->prev_elt  = NULL;
					LoL_head = new_ptr;
				}
				
				*LoL_head_ptr = LoL_head;
				*LoL_tail_ptr = LoL_tail; 
				return;
      }
      else if (measure == list_ptr->data)
      {
				old_tail = list_ptr->tail;
				lists[old_tail] = index;
				where[index] = old_tail;
				lists[index] = LIST_TAIL;
				list_ptr->tail = index;
				return;
      }
      
      list_ptr = list_ptr->next_elt;
		} while (list_ptr != NULL);
		
		new_ptr = create_elt(measure);   
		new_ptr->head = index;
		new_ptr->tail = index;
		lists[index] = LIST_TAIL;
		where[index] = LIST_HEAD;
		LoL_tail->next_elt = new_ptr;
		new_ptr->prev_elt = LoL_tail;
		new_ptr->next_elt = NULL;
		LoL_tail = new_ptr;
		
		*LoL_head_ptr = LoL_head;
		*LoL_tail_ptr = LoL_tail;
		return;
	}
}

/**
 * \fn void generate_S(dCSRmat *A, iCSRmat *S, AMG_param *param)
 * \brief generate the set of all strong couplings S
 * \param *A pointer to the coefficient matrix
 * \param *S pointer to the set of all strong couplings matrix
 * \param *param pointer to AMG parameters
 */
void generate_S(dCSRmat *A, iCSRmat *S, AMG_param *param)
{
	double max_row_sum=param->max_row_sum;
	double epsilon_str=param->strong_threshold;
	const int row=A->row, col=A->col;
	const int nnz=A->IA[row]-A->IA[0];
	
	int index, i, j, begin_row, end_row;
	int *ia=A->IA, *ja=A->JA;
	double *aj=A->val;
	
	// get the diagnal entry of A
	dvector diag; fasp_dcsr_getdiag(0, A, &diag);
	
	/** Step 1: generate S */
	double row_scale, row_sum;
	
	// copy the structure of A to S
	S->row=row; S->col=col; S->nnz=nnz; S->val=NULL;
	
	S->IA=(int*)fasp_mem_calloc(row+1, sizeof(int));
	
#if CHMEM_MODE
	total_alloc_mem += (row+1)*sizeof(double);
#endif
	
	S->JA=(int*)fasp_mem_calloc(nnz, sizeof(int));
	
#if CHMEM_MODE
	total_alloc_mem += (nnz)*sizeof(int);
#endif
	
	memcpy(S->IA,ia,(row+1)*sizeof(int));
	memcpy(S->JA,ja,    nnz*sizeof(int));
	
	for (i=0;i<row;++i) {
		
		/** compute scaling factor and row sum */
		row_scale=0; row_sum=0;
		
		begin_row=ia[i]; end_row=ia[i+1]-1;
		for (j=begin_row;j<=end_row;j++) {
			row_scale=MIN(row_scale, aj[j]);
			row_sum+=aj[j];
		}
		row_sum=ABS(row_sum)/MAX(SMALLREAL,ABS(diag.val[i]));
		
		/* compute row entries of S */
		for (j=begin_row;j<=end_row;j++) {
			if (ja[j]==i) {S->JA[j]=-1; break;}
		}
		
		/** if $|\sum_{j=1}^n a_{ij}|> \theta_2 |a_{ii}|$ */
		if ((row_sum>max_row_sum)&&(max_row_sum<1)) { 
			/** make all dependencies weak */
			for (j=begin_row;j<=end_row;j++) S->JA[j]=-1;
		}
		/** otherwise */
		else {
			for (j=begin_row;j<=end_row;j++) {
				/** if $a_{ij}>=\epsilon_{str}*\min a_{ij}$, the connection $a_{ij}$ is set to be weak connection */
				if (A->val[j]>=epsilon_str*row_scale) S->JA[j]=-1; 
			}
		}
		
	} // end for i
	
	/* Compress the strength matrix */
	index=0;
	for (i=0;i<row;++i) {
		S->IA[i]=index;
		begin_row=ia[i]; end_row=ia[i+1]-1;
		for (j=begin_row;j<=end_row;j++) {
			if (S->JA[j]>-1) {
				S->JA[index]=S->JA[j];
				index++;
			}
		}
	}
	
	if (index > 0) {
		S->IA[row]=index;
		S->nnz=index;
		S->JA=(int*)fasp_mem_realloc(S->JA,index*sizeof(int));
	}
	else {
		S->nnz = 0;
		S->JA = NULL;
	}
	
	fasp_dvec_free(&diag);
}

/**
 * \fn void generate_S_rs(dCSRmat *A, iCSRmat *S, double epsilon_str, int coarsening_type)
 * \brief generate the set of all strong negative couplings(coarsening_type=2) or strong absolute couplings(coarsening_type=3)
 * \param *A pointer to the coefficient matrix
 * \param *S pointer to the set of all strong couplings matrix
 * \param epsilon_str strong coupled ratio
 * \param coarsening_type coarsening type(2: strong negative couplings, 3: strong absolute couplings)
 */
void generate_S_rs(dCSRmat *A, iCSRmat *S, double epsilon_str, int coarsening_type)
{
	int i,j;
	double *amax=(double *)fasp_mem_calloc(A->row,sizeof(double));
	
	// get the maximum absolute negative value data in each row of A
	if (coarsening_type==2) // original RS coarsening, just consider negative strong coupled
	{
		for (i=0;i<A->row;++i)
		{
			amax[i]=0;
			for (j=A->IA[i];j<A->IA[i+1];j++)
			{
				if ((-A->val[j])>amax[i] && A->JA[j]!=i)
				{
					amax[i]=-A->val[j];
				}
			}
		}
	}
	
	if (coarsening_type==3) // original RS coarsening, consider absolute strong coupled
	{
		for (i=0;i<A->row;++i)
		{
			amax[i]=0;
			for (j=A->IA[i];j<A->IA[i+1];j++)
			{
				if (ABS(A->val[j])>amax[i] && A->JA[j]!=i)
				{
					amax[i]=ABS(A->val[j]);
				}
			}
		}
	}
	
	// step 1: Find first the structure IA of S
	S->row=A->row;
	S->col=A->col;
	S->val=NULL;
	S->JA=NULL;
	S->IA=(int*)fasp_mem_calloc(S->row+1, sizeof(int));
	
	if (coarsening_type==2)
	{
		for (i=0;i<S->row;++i)
		{
			for (j=A->IA[i];j<A->IA[i+1];j++)
			{
				if ((-A->val[j])>=epsilon_str*amax[i] && A->JA[j]!=i)
				{
					S->IA[i+1]++;
				}
			}	
		}
	}
	
	if (coarsening_type==3)
	{
		for (i=0;i<S->row;++i)
		{
			for (j=A->IA[i];j<A->IA[i+1];j++)
			{
				if (ABS(A->val[j])>=epsilon_str*amax[i] && A->JA[j]!=i)
				{
					S->IA[i+1]++;
				}
			}
		}
	}
	
	for (i=0;i<S->row;++i) S->IA[i+1]+=S->IA[i];
	
	// step 2: Find the structure JA of S
	int index=0;
	S->JA=(int*)fasp_mem_calloc(S->IA[S->row],sizeof(int));
	
	if (coarsening_type==2)
	{
		for (i=0;i<S->row;++i)
		{
			for (j=A->IA[i];j<A->IA[i+1];j++)
			{
				if ((-A->val[j])>=epsilon_str*amax[i] && A->JA[j]!=i)
				{
					S->JA[index]= A->JA[j];
					index++;
				}
			}
		}
	}
	
	if (coarsening_type==3)
	{
		for (i=0;i<S->row;++i)
		{
			for (j=A->IA[i];j<A->IA[i+1];j++)
			{
				if (ABS(A->val[j])>=epsilon_str*amax[i] && A->JA[j]!=i)
				{
					S->JA[index]= A->JA[j];
					index++;
				}
			}
		}
	}
	
	fasp_mem_free(amax);
}

/**
 * \fn static int form_coarse_level(dCSRmat *A, iCSRmat *S, ivector *vertices, int row)
 * \brief find coarse level points
 * \param *A pointer to the coefficient matrix
 * \param *S pointer to the set of all strong couplings matrix
 * \param *vertices pointer to the type of vertices (points)
 * \param row integer number of rows of P
 * \return col integer number of cols of P
 */
int form_coarse_level(dCSRmat *A, iCSRmat *S, ivector *vertices, int row)
{
	int col = 0; // initialize col(P): returning output 
	unsigned int maxlambda, maxnode, num_left=0;	
	double measure, new_meas;
	
	int *ia=A->IA, *vec=vertices->val;
	int ci_tilde = -1, ci_tilde_mark = -1;
	int set_empty = 1, C_i_nonempty = 0;
	int ji,jj,i,j,k,l,index;
	
	int *work = (int*)fasp_mem_calloc(4*row,sizeof(int));	
	int *lists = work, *where = lists+row, *lambda = where+row, *graph_array = lambda+row;
	
	LinkList LoL_head = NULL, LoL_tail = NULL, list_ptr = NULL;	
	
	iCSRmat ST; fasp_icsr_trans(S, &ST);
	
	/**************************************************/
	/* Coarsening Phase ONE: find coarse level points */
	/**************************************************/	
	
	// 1. Initialize lambda
	for (i=0;i<row;++i) lambda[i]=ST.IA[i+1]-ST.IA[i];
	
	// 2. Before the following algorithm starts, filter out the variables which
	// have no connections at all and assign special F-variables.
	for (i=0;i<row;++i)
	{
		if ( (ia[i+1]-ia[i])<=1 ) {
			vec[i]=ISPT; // set i as an ISOLATED fine node
			lambda[i]=0;
		}
		else {
			vec[i]=UNPT; // set i as a undecided node
			num_left++;
		}
	}
	
	// 3. Set the variables with nonpositvie measure as F-variables
	for (i=0;i<row;++i)
	{
		measure=lambda[i];
		if (vec[i]!=ISPT) {
			if (measure>0) {
				enter_list(&LoL_head, &LoL_tail, lambda[i], i, lists, where);
			}
			else {
				if (measure<0) printf("Warning: negative lambda!\n");
				vec[i]=FGPT; // set i as fine node
				for (k=S->IA[i];k<S->IA[i+1];++k) {
					j=S->JA[k];
					if (vec[j]!=ISPT) {
						if (j<i) {
							new_meas=lambda[j];
							if (new_meas>0) {
								remove_point(&LoL_head, &LoL_tail, new_meas, j, lists, where);
							}
							new_meas= ++(lambda[j]);
							enter_list(&LoL_head, &LoL_tail,  new_meas, j, lists, where);
						}
						else {
							new_meas= ++(lambda[j]);
						}
					}
				}
				--num_left;
			}
		}
	}
	
	// 4. Main loop
	while (num_left>0) {
		
		// pick $i\in U$ with $\max\lambda_i: C:=C\cup\{i\}, U:=U\\{i\}$
		maxnode=LoL_head->head;
		maxlambda=lambda[maxnode];
		
		vec[maxnode]=CGPT; // set maxnode as coarse node
		lambda[maxnode]=0;
		--num_left;
		remove_point(&LoL_head, &LoL_tail, maxlambda, maxnode, lists, where);
		col++;
		
		// for all $j\in S_i^T\cap U: F:=F\cup\{j\}, U:=U\backslash\{j\}$
		for (i=ST.IA[maxnode];i<ST.IA[maxnode+1];++i) {
			j=ST.JA[i];
			
			/** if j is unkown */
			if (vec[j]==UNPT) {
				vec[j]=FGPT;  // set j as fine node
				remove_point(&LoL_head, &LoL_tail, lambda[j], j, lists, where);
				--num_left;
				
				for (l=S->IA[j];l<S->IA[j+1];l++) {
					k=S->JA[l];
					if (vec[k]==UNPT) // k is unkown
					{
						remove_point(&LoL_head, &LoL_tail, lambda[k], k, lists, where);
						new_meas= ++(lambda[k]);
						enter_list(&LoL_head, &LoL_tail,new_meas, k, lists, where);
					}
				}
				
			} // if
		} // i
		
		for (i=S->IA[maxnode];i<S->IA[maxnode+1];++i) {
			j=S->JA[i];
			if (vec[j]==UNPT) // j is unkown
			{
				measure=lambda[j];
				remove_point(&LoL_head, &LoL_tail,measure, j, lists, where);
				lambda[j]=--measure;
				if (measure>0) {
					enter_list(&LoL_head, &LoL_tail,measure, j, lists, where);
				}
				else {
					vec[j]=FGPT; // set j as fine variable
					--num_left;
					
					for (l=S->IA[j];l<S->IA[j+1];l++) {
						k=S->JA[l];
						if (vec[k]==UNPT) // k is unkown
						{
							remove_point(&LoL_head, &LoL_tail, lambda[k], k, lists, where);
							new_meas= ++(lambda[k]);
							enter_list(&LoL_head, &LoL_tail,new_meas, k, lists, where);
						}
					} // end for l
				} // end if
			} // end if
		} // end for
	} // while
	
	if (LoL_head) {
		list_ptr=LoL_head;
		LoL_head->prev_elt=NULL;
		LoL_head->next_elt=NULL;
		LoL_head = list_ptr->next_elt;
		fasp_mem_free(list_ptr);
	}
	
	/****************************************************************/
	/* Coarsening Phase TWO: check fine points for coarse neighbors */
	/****************************************************************/	
	for (i=0; i < row; ++i) graph_array[i] = -1;
	
	for (i=0; i < row; ++i)
	{
		if (ci_tilde_mark |= i) ci_tilde = -1;
		
		if (vec[i] == FGPT) // F-variable
		{
			for (ji = S->IA[i]; ji < S->IA[i+1]; ++ji) {
				j = S->JA[ji];
				if (vec[j] == CGPT) // C-variable
					graph_array[j] = i;
			} // end for ji
			
			for (ji = S->IA[i]; ji < S->IA[i+1]; ++ji) {
				
				j = S->JA[ji];
				
				if (vec[j] == FGPT) {
					set_empty = 1;
					
					for (jj = S->IA[j]; jj < S->IA[j+1]; ++jj) {
						index = S->JA[jj];
						if (graph_array[index] == i) {
							set_empty = 0;
							break;
						}
					} // end for jj
					
					if (set_empty) {
						if (C_i_nonempty) {
							vec[i] = CGPT;
							col++;
							if (ci_tilde > -1) {
								vec[ci_tilde] = FGPT;
								col--;
								ci_tilde = -1;
							}
							C_i_nonempty = 0;
							break;
						}
						else {
							ci_tilde = j;
							ci_tilde_mark = i;
							vec[j] = CGPT;
							col++;
							C_i_nonempty = 1;
							i--;
							break;
						} // end if C_i_nonempty
					} // end if set_empty
					
				}
			}
		}
	}
	
	fasp_icsr_free(&ST);
	
	fasp_mem_free(work);
	
	return col;
}

/**
 * \fn static void generate_sparsity_P(dCSRmat *P, iCSRmat *S, ivector *vertices, int row, int col)
 * \brief find coarse level points
 * \param *P pointer to the prolongation matrix
 * \param *S pointer to the set of all strong couplings matrix
 * \param *vertices pointer to the type of vertices (points)
 * \param row integer number of rows of P
 * \param col integer number of cols of P
 */
void generate_sparsity_P(dCSRmat *P, iCSRmat *S, ivector *vertices, int row, int col)
{
	int i,j,k,index=0;
	int *vec=vertices->val;
	
	P->row=row; P->col=col;	
	P->IA=(int*)fasp_mem_calloc(row+1, sizeof(int));	
	
#if CHMEM_MODE
	total_alloc_mem += (row+1)*sizeof(int);
#endif
	
	// step 1: Find the structure IA of P first		
	for (i=0;i<row;++i)
	{
		if (vec[i]==FGPT) // if node i is on fine grid
		{
			for (j=S->IA[i];j<S->IA[i+1];j++)
			{
				k=S->JA[j];
				if (vec[k]==CGPT)
				{
					P->IA[i+1]++;
				}
			}
		}
		else if (vec[i]==ISPT) { // if node i is a special fine node
			P->IA[i+1]=0;
		}
		else { // if node i is on coarse grid 
			P->IA[i+1]=1;
		}
	}	
	
	for (i=0;i<P->row;++i) P->IA[i+1]+=P->IA[i];
	
	P->nnz=P->IA[P->row]-P->IA[0];
	
	// step 2: Find the structure JA of P
	P->JA=(int*)fasp_mem_calloc(P->nnz,sizeof(int));	
	P->val=(double*)fasp_mem_calloc(P->nnz,sizeof(double));
	
#if CHMEM_MODE
	total_alloc_mem += (P->nnz)*sizeof(int);
	total_alloc_mem += (P->nnz)*sizeof(double);
#endif
	
	for (i=0;i<row;++i)
	{
		if (vec[i]==FGPT) // fine node
		{
			for (j=S->IA[i];j<S->IA[i+1];j++) {
				k=S->JA[j];
				if (vec[k]==CGPT) {
					P->JA[index]=k;
					index++;
				} // end if 
			} // end for j
		} // end if
		else if (vec[i]==ISPT) 
		{
			// if node i is a special fine node, do nothing
		}
		else // if node i is on coarse grid 
		{
			P->JA[index]=i;
			index++;
		}
	}	
	
}

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/