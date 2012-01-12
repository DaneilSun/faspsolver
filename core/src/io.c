/*! \file io.c
 *  \brief Matrix-vector input/output subroutines
 *
 *  \note Read, write or print a matrix or a vector in various formats.
 *
 */

#include "fasp.h"
#include "fasp_functs.h"

/*---------------------------------*/
/*--      Public Functions       --*/
/*---------------------------------*/

/**
 * \fn void fasp_dcsrvec_read (char *filemat, char *filerhs, dCSRmat *A, dvector *b)
 *
 * \brief Read A and b from two disk files
 *
 * \param *filemat  char for the matrix file name
 * \param *filerhs  char for the vector file name
 * \param *A        pointer to the dCSR matrix
 * \param *b        pointer to the dvector
 *
 * \note 
 * CSR matrix file format:
 *   This routine reads a dCSRmat matrix and a dvector vector from a single disk file
 *   in the following format:
 * \par   
 *   nrow              % number of columns (rows)
 * \par   
 *   ia(j), j=0:nrow   % row index
 * \par   
 *   ja(j), j=0:nnz-1  % column index
 * \par    
 *   a(j), j=0:nnz-1   % entry value
 *
 * \note
 * RHS file format:
 * \par   
 *   n                 % number of entries
 * \par   
 *   b(j), j=0:nrow-1  % entry value
 *
 * \author Zhiyang Zhou
 * \date 2010/08/06
 *
 * \note Modified by Chensong Zhang on 2011/03/01
 * \note Modified by Chensong Zhang on 2012/01/05
 */ 
void fasp_dcsrvec_read (char *filemat, 
                        char *filerhs, 
                        dCSRmat *A, 
                        dvector *b )
{
	INT i,n,nz;
    INT wall;
	
	/* read the matrix from file */ 
	FILE *fp = fopen(filemat,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filemat);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dcsrvec_read: reading file %s...\n", filemat);
	
	wall = fscanf(fp,"%d\n",&n);
	A->row = n;
	A->col = n;
	A->IA = (INT *)fasp_mem_calloc(n+1, sizeof(int));
	
	for(i=0; i<n+1; ++i)
	{ 
		wall = fscanf(fp,"%d\n",&(A->IA[i])); 
		A->IA[i]--; 
	}
	
	nz = A->IA[n];
	A->nnz = nz;
	A->JA = (INT *)fasp_mem_calloc(nz, sizeof(int));
	A->val = (REAL *)fasp_mem_calloc(nz, sizeof(REAL));
	
	for(i=0; i<nz; ++i)
	{ 
		wall = fscanf(fp,"%d\n",&(A->JA[i])); 
		A->JA[i]--; 
	}
	
	for(i=0; i<nz; ++i) wall = fscanf(fp,"%le\n",&(A->val[i]));
	
	fclose(fp);
	
	/* Read the rhs from file */
	b->row = n;
	b->val = (REAL *)fasp_mem_calloc(n, sizeof(REAL));
	
	fp = fopen(filerhs,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filerhs);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dcsrvec_read: reading file %s...\n", filerhs);
	
	wall = fscanf(fp,"%d\n",&n);
	
	if (n!=b->row) {
		printf("### ERROR: rhs size %d does not match matrix size %d!\n",n,b->row);
		exit(ERROR_OPEN_FILE);
	}
	
	for(i=0; i<n; ++i) {
		wall = fscanf(fp,"%le\n", &(b->val[i]));
	}
    
	fclose(fp);
}

/**
 * \fn void fasp_dcsrvec2_read (char *filename, dCSRmat *A, dvector *b)
 *
 * \brief Read A and b from a SINGLE disk file
 *
 * \param *filename  char for file name
 * \param *A         pointer to the CSR matrix
 * \param *b         pointer to the dvector
 *
 * \note 
 * CSR matrix file format:
 *   This routine reads a dCSRmat matrix and a dvector vector from a single disk file.
 *   The difference between this and fasp_dcoovec_read is that this routine support
 *   non-square matrices. The file should be in the following format:
 * \par   
 *   nrow ncol         % number of rows and number of columns
 * \par   
 *   ia(j), j=0:nrow   % row index
 * \par   
 *   ja(j), j=0:nnz-1  % column index
 * \par    
 *   a(j), j=0:nnz-1   % entry value
 * \par   
 *   n                 % number of entries
 * \par   
 *   b(j), j=0:n-1     % entry value
 *
 * \author Xuehai Huang
 * \date 03/29/2009 
 */ 
void fasp_dcsrvec2_read (char *filename,
                         dCSRmat *A,
                         dvector *b)
{
	INT  i,m,n,nnz,idata; 
	INT  wall;
	REAL ddata;
    
	// Open input disk file
	FILE *fp=fopen(filename, "r");
	
	if (fasp_mem_check((void *)fp,NULL,ERROR_OPEN_FILE) < 0) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dcsrvec2_read: reading file %s...\n", filename);
	
	// Read CSR matrix
	wall = fscanf(fp, "%d %d", &m, &n);
	A->row=m; A->col=n;
	
	A->IA=(int*)fasp_mem_calloc(m+1, sizeof(int));	
	for (i=0;i<=m;++i) {
		wall = fscanf(fp, "%d", &idata);
		A->IA[i]=idata;
	}
	
	nnz=A->IA[m]-A->IA[0];	 A->nnz=nnz;
	
	A->JA=(int*)fasp_mem_calloc(nnz, sizeof(int));	
	A->val=(REAL*)fasp_mem_calloc(nnz, sizeof(REAL));
	
	for (i=0;i<nnz;++i) {
		wall = fscanf(fp, "%d", &idata);
		A->JA[i]=idata;
	}
	
	for (i=0;i<nnz;++i) {
		wall = fscanf(fp, "%lf", &ddata);
		A->val[i]=ddata;
	}
	
	// Read RHS vector
	wall = fscanf(fp, "%d", &m, &i);
	b->row=m;
	
	b->val=(REAL*)fasp_mem_calloc(m, sizeof(REAL));
	
	for (i=0;i<m;++i) {
		wall = fscanf(fp, "%lf", &ddata);
		b->val[i]=ddata;
	}
	
	fclose(fp);	
}

/**
 * \fn void fasp_dcoo_read(char *filename, dCSRmat *A)
 *
 * \brief Read A from matrix disk file in IJ format -- indices starting from 0
 *
 * \param *filename  char for matrix file name
 * \param *A         pointer to the CSR matrix
 *
 * \note 
 * File format:
 *   This routine reads a dCOOmat matrix from a disk file in the following format.
 * \par   
 *   nrow ncol nnz     % number of rows, number of columns, and nnz
 * \par   
 *   i  j  a_ij        % i, j a_ij in each line
 * \par
 *   And then it converts the matrix to dCSRmat format.
 *
 * \author Xuehai Huang, modified by Chensong
 * \date 03/29/2009 
 */
void fasp_dcoo_read (char *filename, 
                     dCSRmat *A)
{
	INT  i,j,k,m,n,nnz;
	INT  wall;
	REAL value;	
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dcoo_read: reading file %s...\n", filename);
	
	wall = fscanf(fp,"%d %d %d",&m,&n,&nnz); 
	
	dCOOmat Atmp=fasp_dcoo_create(m,n,nnz); 
	
	for (k=0;k<nnz;k++) {
		if ( fscanf(fp, "%d %d %le", &i, &j, &value) != EOF ) {
			Atmp.I[k]=i; Atmp.J[k]=j; Atmp.val[k]=value; 
		}
		else {
			printf("### ERROR: Wrong file format!\n"); exit(ERROR_WRONG_FILE);
		}
	}
	
	fclose(fp);
	
	fasp_format_dcoo_dcsr(&Atmp,A); 
	fasp_dcoo_free(&Atmp);
}

/**
 * \fn void fasp_dmtx_read(char *filename, dCSRmat *A)
 *
 * \brief Read A from matrix disk file in MatrixMarket general format
 *
 * \param *filename  char for matrix file name
 * \param *A         pointer to the CSR matrix
 *
 * \note 
 * File format:
 *   This routine reads a MatrixMarket general matrix from a mtx file.
 *   And it converts the matrix to dCSRmat format. For details of mtx format, 
 *   please refer to http://math.nist.gov/MatrixMarket/.
 *
 * \author Chensong Zhang
 * \date 09/05/2011 
 */
void fasp_dmtx_read (char *filename, 
                     dCSRmat *A)
{
	INT  i,j,m,n,nnz;
    INT  innz; // index of nonzeros
	REAL value;	
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dmtx_read: reading file %s...\n", filename);
    
	fscanf(fp,"%d %d %d",&m,&n,&nnz); 
    
	dCOOmat Atmp=fasp_dcoo_create(m,n,nnz); 
	
    innz = 0;
    
	while (innz < nnz) {
		if ( fscanf(fp, "%d %d %le", &i, &j, &value) != EOF ) {
            
            Atmp.I[innz]=i-1; 
            Atmp.J[innz]=j-1; 
            Atmp.val[innz]=value; 
            innz = innz + 1;
            
		}
		else {
			printf("### ERROR: Wrong file format!\n"); exit(ERROR_WRONG_FILE);
		}
	}
	    
	fclose(fp);
	
	fasp_format_dcoo_dcsr(&Atmp,A); 
	fasp_dcoo_free(&Atmp);
}

/**
 * \fn void fasp_dmtxsym_read(char *filename, dCSRmat *A)
 *
 * \brief Read A from matrix disk file in MatrixMarket sym format
 *
 * \param *filename  char for matrix file name
 * \param *A         pointer to the CSR matrix
 *
 * \note 
 * File format:
 *   This routine reads a MatrixMarket symmetric matrix from a mtx file.
 *   And it converts the matrix to dCSRmat format. For details of mtx format, 
 *   please refer to http://math.nist.gov/MatrixMarket/.
 *
 * \author Chensong Zhang
 * \date 09/02/2011 
 */
void fasp_dmtxsym_read (char *filename, 
                        dCSRmat *A)
{
	INT  i,j,m,n,nnz;
    INT  innz; // index of nonzeros
	REAL value;	
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dmtxsym_read: reading file %s...\n", filename);
    
	fscanf(fp,"%d %d %d",&m,&n,&nnz); 
    
    nnz = 2*(nnz-m) + m; // adjust for sym problem
	
	dCOOmat Atmp=fasp_dcoo_create(m,n,nnz); 
	
    innz = 0;
    
	while (innz < nnz) {
		if ( fscanf(fp, "%d %d %le", &i, &j, &value) != EOF ) {
            
            if (i==j) {
                Atmp.I[innz]=i-1; 
                Atmp.J[innz]=j-1; 
                Atmp.val[innz]=value; 
                innz = innz + 1;
            }
            else {
                Atmp.I[innz]=i-1; Atmp.I[innz+1]=j-1;
                Atmp.J[innz]=j-1; Atmp.J[innz+1]=i-1;
                Atmp.val[innz]=value; Atmp.val[innz+1]=value;
                innz = innz + 2;                
            }
            
		}
		else {
			printf("### ERROR: Wrong file format!\n"); exit(ERROR_WRONG_FILE);
		}
	}
    
	fclose(fp);
	
	fasp_format_dcoo_dcsr(&Atmp,A); 
	fasp_dcoo_free(&Atmp);	
}

/**
 * \fn void fasp_dstr_read (char *filename, dSTRmat *A)
 *
 * \brief Read A from a disk file in dSTRmat format
 *
 * \param *filename  char for vector file name
 * \param *A         pointer to the dSTRmat
 *
 * \note 
 * File format:
 *   This routine reads a dSTRmat matrix from a disk file in the following format:
 * \par
 * 	 nx, ny, nz
 * \par
 *   nc: number of components
 * \par
 *   nband: number of bands
 * \par
 *   n: size of diagonal, you must have diagonal
 * \par
 *   diag(j), j=0:n-1
 * \par
 *   offset, length: offset and length of off-diag1
 * \par
 *   offdiag(j), j=0:length-1
 * \par
 *   And it converts the matrix to dCSRmat format.
 *
 * \author Xuehai Huang
 * \date 03/29/2009 
 */
void fasp_dstr_read (char *filename,
                     dSTRmat *A)
{
	INT  nx, ny, nz, nxy, ngrid, nband, nc, offset;
	INT  i, k, n, wall;
	REAL value;
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dstr_read: reading file %s...\n", filename);
	
	wall = fscanf(fp,"%d %d %d",&nx,&ny,&nz); // read dimension of the problem
	A->nx = nx; A->ny = ny; A->nz = nz;
	
	nxy = nx*ny; ngrid = nxy*nz;
	A->nxy = nxy; A->ngrid = ngrid;
	
	wall = fscanf(fp,"%d",&nc); // read number of components
	A->nc = nc;
	
	wall = fscanf(fp,"%d",&nband); // read number of bands
	A->nband = nband;
	
	A->offsets=(int*)fasp_mem_calloc(nband, sizeof(int));
	
	// read diagonal	
	wall = fscanf(fp, "%d", &n);
	A->diag=(REAL *)fasp_mem_calloc(n, sizeof(REAL));
	for (i=0;i<n;++i) {
		wall = fscanf(fp, "%le", &value);
		A->diag[i]=value;
	}
	
	// read offdiags
	k = nband;
	A->offdiag=(REAL **)fasp_mem_calloc(nband, sizeof(REAL *));
	while (k--){
		wall = fscanf(fp,"%d %d",&offset,&n); // read number band k
		A->offsets[nband-k-1]=offset;
		
		A->offdiag[nband-k-1]=(REAL *)fasp_mem_calloc(n, sizeof(REAL));
		for (i=0;i<n;++i) {
			wall = fscanf(fp, "%le", &value);
			A->offdiag[nband-k-1][i]=value;
		}
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_dbsr_read (char *filename, dBSRmat *A)
 *
 * \brief Read A from a disk file in dBSRmat format
 *
 * \param *filename char for vector file name
 * \param *A pointer to the dBSRmat
 *
 * \note 
 * File format:
 *   This routine reads a dBSRmat matrix from a disk file in the following format:
 * \par
 *   ROW, COL, NNZ
 * \par
 *   nb: size of each block
 * \par
 *   storage_manner: storage manner of each block 
 * \par
 *   ROW+1: length of IA 
 * \par
 *   IA(i), i=0:ROW
 * \par
 *   NNZ: length of JA
 * \par
 *   JA(i), i=0:NNZ-1 
 * \par
 *   NNZ*nb*nb: length of val
 * \par
 *   val(i), i=0:NNZ*nb*nb-1  * \par
 * \par
 *   And it converts the matrix to dCSRmat format. 
 *
 * \author Xiaozhe Hu
 * \date 10/29/2010 
 */
void fasp_dbsr_read (char *filename, dBSRmat *A)
{
	INT  ROW, COL, NNZ, nb, storage_manner;
	INT  i, n;
	INT  index, wall;
	REAL value;
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dbsr_read: reading file %s...\n", filename);
	
	wall = fscanf(fp, "%d %d %d", &ROW,&COL,&NNZ); // read dimension of the problem
	A->ROW = ROW; A->COL = COL; A->NNZ = NNZ;
	
	wall = fscanf(fp, "%d", &nb); // read the size of each block
	A->nb = nb;
	
	wall = fscanf(fp, "%d", &storage_manner); // read the storage_manner of each block
	A->storage_manner = storage_manner;
	
	// allocate memory space
	fasp_dbsr_alloc(ROW, COL, NNZ, nb, storage_manner, A);
	
	// read IA
	wall = fscanf(fp, "%d", &n);
	for (i=0;i<n;++i) {
		wall = fscanf(fp, "%d", &index);
		A->IA[i] = index;
	}
	
	// read JA
	wall = fscanf(fp, "%d", &n);
	for (i=0; i<n; ++i){
		wall = fscanf(fp, "%d", &index);
		A->JA[i] = index;
	}
	
	// read val
	wall = fscanf(fp, "%d", &n);
	for (i=0; i<n; ++i){
		wall = fscanf(fp, "%le", &value);
		A->val[i] = value;
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_dvecind_read (char *filename, dvector *b)
 *
 * \brief Read b from matrix disk file in IJ format
 *
 * \param *filename  char for vector file name
 * \param *b         pointer to the dvector
 *
 * \note
 * File Format:
 *   This routine reads a dvector in the following format:
 * \par
 *	 nrow
 * \par
 *   ind_j, val_j, j=0:nrow-1
 * 
 * \author Chensong Zhang
 * \date 03/29/2009 
 */
void fasp_dvecind_read (char *filename,
                        dvector *b)
{
	INT  i, n, index, wall;
	REAL value;
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dvecind_read: reading file %s...\n", filename);
	
	wall = fscanf(fp,"%d",&n);	
	fasp_dvec_alloc(n,b);
	
	for (i=0;i<n;++i) {
		wall = fscanf(fp, "%d %le", &index, &value);
        if (value>BIGREAL || index>=n) {
            printf("### WARNING: index = %d, value = %lf\n", index, value);
        }
		b->val[index]=value;
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_dvec_read(char *filename, dvector *b)
 *
 * \brief Read b from a disk file in array format
 *
 * \param *filename char for vector file name
 * \param *b pointer to the dvector
 *
 * \note
 * File Format:
 *   This routine reads a dvector in the following format:
 * \par
 *	 nrow
 * \par
 *   val_j ... j=0:nrow-1
 * 
 * \author Chensong Zhang
 * \date 03/29/2009 
 */
void fasp_dvec_read (char *filename, 
                     dvector *b)
{
    
	INT  i, n, wall;
    REAL value;

	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dvec_read: reading file %s...\n", filename);
	
	wall = fscanf(fp,"%d",&n);	
	fasp_dvec_alloc(n,b);
	
	for (i=0;i<n;++i) {
		wall = fscanf(fp, "%le", &value);
		b->val[i]=value;
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_ivecind_read (char *filename, ivector *b)
 *
 * \brief Read b from matrix disk file in IJ format
 *
 * \param *filename char for vector file name
 * \param *b pointer to the ivector
 *
 * \note
 * File Format:
 *   This routine reads a ivector in the following format:
 * \par
 *	 nrow
 * \par
 *   ind_j, val_j ... j=0:nrow-1
 * 
 * \author Chensong Zhang
 * \date 03/29/2009 
 */
void fasp_ivecind_read (char *filename, 
                        ivector *b)
{
 	INT i, n, index, value;
	INT wall;
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_ivecind_read: reading file %s...\n", filename);
	
	wall = fscanf(fp,"%d",&n);	
	fasp_ivec_alloc(n,b);
	
	for (i=0;i<n;++i) {
        wall = fscanf(fp, "%d %d", &index, &value);
		b->val[index]=value;
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_ivec_read (char *filename, ivector *b)
 *
 * \brief Read b from a disk file in array format
 *
 * \param *filename char for vector file name
 * \param *b pointer to the ivector
 *
 * \note
 * File Format:
 *   This routine reads a ivector in the following format:
 * \par
 *	 nrow
 * \par
 *   val_j ... j=0:nrow-1
 * 
 * \author Xuehai Huang
 * \date 03/29/2009 
 */
void fasp_ivec_read (char *filename, 
                     ivector *b)
{
	INT i, n, value, wall;
    
	FILE *fp=fopen(filename,"r");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_ivec_read: reading file %s...\n", filename);
	
	wall = fscanf(fp,"%d",&n);	
	fasp_ivec_alloc(n,b);
	
	for (i=0;i<n;++i) {
		wall = fscanf(fp, "%d", &value);
		b->val[i]=value;
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_dcsr_write (char *filename, dCSRmat *A)
 *
 * \brief Write a matrix to disk file in IJ format (coordinate format)
 *
 * \param *A         pointer to the dCSRmat matrix
 * \param *filename  char for vector file name
 *
 * \note
 * File format: 
 *	 The routine writes the specified REAL vector in COO format. 
 *   The first line of the file gives the number of rows and the 
 *   number of columns. And then gives nonzero values in i,j,a(i,j)
 *   order. Refer to the reading subroutine \ref fasp_dcoo_read.
 *
 * \author Chensong Zhang
 * \date 03/29/2009       
 */
void fasp_dcsr_write (char *filename, 
                      dCSRmat *A)
{     
    const INT m=A->row, n=A->col;
    INT i, j;
    
	FILE *fp=fopen(filename, "w");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
    printf("fasp_dcsr_write: writing matrix to `%s'...\n",filename);
	
	fprintf(fp,"%d  %d  %d\n",m,n,A->nnz);	
    for (i = 0; i < m; ++i) {
		for (j = A->IA[N2C(i)]; j < A->IA[N2C(i+1)]; j++)
            fprintf(fp,"%d  %d  %le\n",i,A->JA[j],A->val[j]);
    }
	
	fclose(fp);
}

/**
 * \fn void fasp_dstr_write (char *filename, dSTRmat *A)
 *
 * \brief Write a dSTRmat to a disk file
 *
 * \param *filename  char for vector file name
 * \param *A         pointer to the dSTRmat
 *
 * \note
 * File format: 
 *	 The routine writes the specified REAL vector in STR format. 
 *   Refer to the reading subroutine \ref fasp_dstr_read.
 *
 * \author Shiquan Zhang
 * \date 03/29/2010  
 */
void fasp_dstr_write (char *filename, 
                      dSTRmat *A)
{
	const INT nx=A->nx, ny=A->ny, nz=A->nz;
	const INT ngrid=A->ngrid, nband=A->nband, nc=A->nc;
	
    INT *offsets=A->offsets;
	
	unsigned INT i, k, n;
	
	FILE *fp=fopen(filename,"w");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dstr_write: writing matrix to `%s'...\n",filename);
	
	fprintf(fp,"%d  %d  %d\n",nx,ny,nz); // write dimension of the problem
	
	fprintf(fp,"%d\n",nc); // read number of components
	
	fprintf(fp,"%d\n",nband); // write number of bands
	
	// write diagonal	
	n=ngrid*nc*nc; // number of nonzeros in each band
	fprintf(fp,"%d\n",n); // number of diagonal entries
	for (i=0;i<n;++i) fprintf(fp, "%le\n", A->diag[i]);
	
	// write offdiags
	k = nband;
	while (k--){
		INT offset=offsets[nband-k-1];
		n=(ngrid-ABS(offset))*nc*nc; // number of nonzeros in each band
		fprintf(fp,"%d  %d\n",offset,n); // read number band k
		for (i=0;i<n;++i) {
			fprintf(fp, "%le\n", A->offdiag[nband-k-1][i]);
		}
	}
	
	fclose(fp);
}

/**
 * \fn void fasp_dbsr_write (char *filename, dBSRmat *A)
 *
 * \brief Write a dBSRmat to a disk file
 *
 * \param *filename char for vector file name
 * \param *A pointer to the dBSRmat
 *
 * \note
 * File format: 
 *	 The routine writes the specified REAL vector in BSR format. 
 *   Refer to the reading subroutine \ref fasp_dbsr_read.
 *
 * \author Shiquan Zhang
 * \date 10/29/2010 
 */
void fasp_dbsr_write (char *filename, 
                      dBSRmat *A)
{
	const INT ROW = A->ROW, COL = A->COL, NNZ = A->NNZ;
	const INT nb = A->nb, storage_manner = A->storage_manner;
	
	INT  *ia  = A->IA;
	INT  *ja  = A->JA;
	REAL *val = A->val;
	
	unsigned INT i, n;
	
	FILE *fp=fopen(filename,"w");
	
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}
	
	printf("fasp_dstr_write: writing matrix to `%s'...\n",filename);
	
	fprintf(fp,"%d  %d  %d\n",ROW,COL,NNZ); // write dimension of the block matrix
	
	fprintf(fp,"%d\n",nb); // write the size of each block
	
	fprintf(fp,"%d\n",storage_manner); // write storage manner of each block
	
	// write A->IA
	n = ROW+1; // length of A->IA
	fprintf(fp,"%d\n",n); // length of A->IA
	for (i=0; i<n; ++i) fprintf(fp, "%d\n", ia[i]);
	
	// write A->JA
	n = NNZ; // length of A->JA
	fprintf(fp, "%d\n", n); // length of A->JA
	for (i=0; i<n; ++i) fprintf(fp, "%d\n", ja[i]);
	
	// write A->val
	n = NNZ*nb*nb; // length of A->val
	fprintf(fp, "%d\n", n); // length of A->val
	for (i=0; i<n; ++i) fprintf(fp, "%le\n", val[i]);
	
	fclose(fp);
}

/**
 * \fn void fasp_dvec_write (char *filename, dvector *vec)
 *
 * \brief Write a dvector to disk file in IJ format (coordinate format)
 *
 * \param *vec       pointer to the dvector
 * \param *filename  char for vector file name
 *
 * \note
 * File format: 
 *
 *	 The routine writes the specified REAL vector in IJ format. 
 *   The first line of the file is the length of the vector;
 *   and after that, each line gives index and value of the entries.    
 *
 * \author Xuehai Huang
 * \date 03/29/2009  
 */
void fasp_dvec_write (char *filename,
                      dvector *vec)
{
	INT m = vec->row, i;
	
	FILE *fp=fopen(filename,"w");
    
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}	
	
	printf("fasp_dvec_write: writing vector to `%s'...\n",filename);
	
	fprintf(fp,"%d\n",m);
	
	for (i=0;i<m;++i) fprintf(fp,"%d %le\n",i,vec->val[i]);
	
	fclose(fp);
}

/**
 * \fn void fasp_ivec_write (char *filename, dvector *vec)
 *
 * \brief Write a ivector to disk file in IJ format (coordinate format)
 *
 * \param *vec       pointer to the dvector
 * \param *filename  char for vector file name
 *
 * \note
 * File format: 
 *
 *	 The routine writes the specified REAL vector in IJ format. 
 *   The first line of the file is the length of the vector;
 *   and after that, each line gives index and value of the entries.  
 *
 * \author Xuehai Huang
 * \date 03/29/2009     
 */
void fasp_ivec_write (char *filename, 
                      ivector *vec)
{
	INT m = vec->row, i;
	
	FILE *fp=fopen(filename,"w");
    
	if ( fp==NULL ) {
        printf("### ERROR: Opening file %s failed!\n",filename);
		exit(ERROR_OPEN_FILE);
	}	
	
	printf("fasp_ivec_write: writing vector to `%s'...\n",filename);
	
	fprintf(fp,"%d\n",m);
	
	for (i=0;i<m;++i) fprintf(fp,"%d %d\n",i,vec->val[i]);
	
	fclose(fp);
}

/**
 * \fn void fasp_dvec_print (INT n, dvector *u) 
 *
 * \brief Print first n entries of a dvector
 *
 * \param  n   an interger (if n=0, then print all entries)
 * \param *u   pointer to a dvector
 *
 * \note
 * File format:
 *   The routine prints a dvector REAL vector type to the screen.
 * 
 * \par
 *   [i  u_i], i = index, u_i = i-th entry in REAL
 *
 * \author Chensong Zhang
 * \date 03/29/2009 
 */
void fasp_dvec_print (INT n, 
                      dvector *u) 
{
	unsigned INT i;	
	
	if (n<=0) n=u->row;
	for (i=0;i<n;++i) printf("vec_%d = %+.10E\n",i,u->val[N2C(i)]);
}

/**
 * \fn void fasp_ivec_print (INT n, ivector *u) 
 *
 * \brief Print first n entries of an ivector of INT type
 *
 * \param  n   an interger (if n=0, then print all entries)
 * \param *u   pointer to an ivector
 *
 * \note
 * File format:
 *   The routine prints an ivector REAL vector type to the screen.
 *
 * \par
 *   [i  u_i], i = index, u_i = i-th entry in int
 *
 * \author Chensong Zhang
 * \date 03/29/2009 
 */
void fasp_ivec_print (INT n, 
                      ivector *u) 
{
	unsigned INT i;	
	
	if (n<=0) n=u->row;
	for (i=0;i<n;++i) printf("vec_%d = %d\n",i,u->val[N2C(i)]);
}

/**
 * \fn void fasp_dcsr_print (dCSRmat *A)
 *
 * \brief Print out a dCSRmat matrix in IJ format (coordinate format)
 *
 * \param *A pointer to the dCSRmat matrix
 *
 * \note
 * File format: 
 *	 The routine prints the specified REAL vector in IJ format. 
 *   The first line of the file gives the number of rows and the number 
 *   of columns. And then gives nonzero values in i,j,a(i,j) order.
 *
 * \par
 *   [nrow  nnz]  % first line: number of rows, number of nonzeros
 * \par
 *   [i  j  a_ij], ...  % second to nnz+1 lines: i, j, a_ij
 *
 * \author Xuehai Huang
 * \date 03/29/2009     
 */
void fasp_dcsr_print (dCSRmat *A)
{     
    const INT m=A->row, n=A->col;
    INT i, j;
	
	printf("nrow = %d, ncol = %d, nnz = %d\n",m,n,A->nnz);	
    for (i = 0; i < m; ++i) {
		for (j=A->IA[N2C(i)]; j<A->IA[N2C(i+1)]; j++)
            printf("A_(%d,%d) = %+.10E\n",i,A->JA[j],A->val[j]);
    }
}

/*---------------------------------*/
/*--        End of File          --*/
/*---------------------------------*/