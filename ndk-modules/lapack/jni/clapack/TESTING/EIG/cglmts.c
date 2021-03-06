/* cglmts.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"
#include "blaswrap.h"

/* Table of constant values */

static integer c__1 = 1;
static complex c_b13 = {-1.f,-0.f};
static complex c_b15 = {1.f,0.f};

/* Subroutine */ int cglmts_(integer *n, integer *m, integer *p, complex *a, 
	complex *af, integer *lda, complex *b, complex *bf, integer *ldb, 
	complex *d__, complex *df, complex *x, complex *u, complex *work, 
	integer *lwork, real *rwork, real *result)
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, b_dim1, b_offset, bf_dim1, 
	    bf_offset;
    real r__1;

    /* Local variables */
    real eps;
    integer info;
    real unfl;
    extern /* Subroutine */ int cgemv_(char *, integer *, integer *, complex *
, complex *, integer *, complex *, integer *, complex *, complex *
, integer *);
    real anorm, bnorm;
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *);
    real dnorm, xnorm, ynorm;
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *);
    extern /* Subroutine */ int cggglm_(integer *, integer *, integer *, 
	    complex *, integer *, complex *, integer *, complex *, complex *, 
	    complex *, complex *, integer *, integer *);
    extern doublereal slamch_(char *);
    extern /* Subroutine */ int clacpy_(char *, integer *, integer *, complex 
	    *, integer *, complex *, integer *);
    extern doublereal scasum_(integer *, complex *, integer *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */

/*  Purpose */
/*  ======= */

/*  CGLMTS tests CGGGLM - a subroutine for solving the generalized */
/*  linear model problem. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The number of rows of the matrices A and B.  N >= 0. */

/*  M       (input) INTEGER */
/*          The number of columns of the matrix A.  M >= 0. */

/*  P       (input) INTEGER */
/*          The number of columns of the matrix B.  P >= 0. */

/*  A       (input) COMPLEX array, dimension (LDA,M) */
/*          The N-by-M matrix A. */

/*  AF      (workspace) COMPLEX array, dimension (LDA,M) */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the arrays A, AF. LDA >= max(M,N). */

/*  B       (input) COMPLEX array, dimension (LDB,P) */
/*          The N-by-P matrix A. */

/*  BF      (workspace) COMPLEX array, dimension (LDB,P) */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the arrays B, BF. LDB >= max(P,N). */

/*  D       (input) COMPLEX array, dimension( N ) */
/*          On input, the left hand side of the GLM. */

/*  DF      (workspace) COMPLEX array, dimension( N ) */

/*  X       (output) COMPLEX array, dimension( M ) */
/*          solution vector X in the GLM problem. */

/*  U       (output) COMPLEX array, dimension( P ) */
/*          solution vector U in the GLM problem. */

/*  WORK    (workspace) COMPLEX array, dimension (LWORK) */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */

/*  RWORK   (workspace) REAL array, dimension (M) */

/*  RESULT   (output) REAL */
/*          The test ratio: */
/*                           norm( d - A*x - B*u ) */
/*            RESULT = ----------------------------------------- */
/*                     (norm(A)+norm(B))*(norm(x)+norm(u))*EPS */

/*  ==================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */

/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    af_dim1 = *lda;
    af_offset = 1 + af_dim1;
    af -= af_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    bf_dim1 = *ldb;
    bf_offset = 1 + bf_dim1;
    bf -= bf_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --d__;
    --df;
    --x;
    --u;
    --work;
    --rwork;

    /* Function Body */
    eps = slamch_("Epsilon");
    unfl = slamch_("Safe minimum");
/* Computing MAX */
    r__1 = clange_("1", n, m, &a[a_offset], lda, &rwork[1]);
    anorm = dmax(r__1,unfl);
/* Computing MAX */
    r__1 = clange_("1", n, p, &b[b_offset], ldb, &rwork[1]);
    bnorm = dmax(r__1,unfl);

/*     Copy the matrices A and B to the arrays AF and BF, */
/*     and the vector D the array DF. */

    clacpy_("Full", n, m, &a[a_offset], lda, &af[af_offset], lda);
    clacpy_("Full", n, p, &b[b_offset], ldb, &bf[bf_offset], ldb);
    ccopy_(n, &d__[1], &c__1, &df[1], &c__1);

/*     Solve GLM problem */

    cggglm_(n, m, p, &af[af_offset], lda, &bf[bf_offset], ldb, &df[1], &x[1], 
	    &u[1], &work[1], lwork, &info);

/*     Test the residual for the solution of LSE */

/*                       norm( d - A*x - B*u ) */
/*       RESULT = ----------------------------------------- */
/*                (norm(A)+norm(B))*(norm(x)+norm(u))*EPS */

    ccopy_(n, &d__[1], &c__1, &df[1], &c__1);
    cgemv_("No transpose", n, m, &c_b13, &a[a_offset], lda, &x[1], &c__1, &
	    c_b15, &df[1], &c__1);

    cgemv_("No transpose", n, p, &c_b13, &b[b_offset], ldb, &u[1], &c__1, &
	    c_b15, &df[1], &c__1);

    dnorm = scasum_(n, &df[1], &c__1);
    xnorm = scasum_(m, &x[1], &c__1) + scasum_(p, &u[1], &c__1);
    ynorm = anorm + bnorm;

    if (xnorm <= 0.f) {
	*result = 0.f;
    } else {
	*result = dnorm / ynorm / xnorm / eps;
    }

    return 0;

/*     End of CGLMTS */

} /* cglmts_ */
