#ifndef HILBERT_CURVE_H
#define HILBERT_CURVE_H

/******************************************************************************/
/*
  Purpose:

    D2XY converts a 1D Hilbert coordinate to a 2D Cartesian coordinate.

  Modified:

    05 December 2015

  Parameters:

    Input, int M, the index of the Hilbert curve.
    The number of cells is N=2^M.
    0 < M.

    Input, int D, the Hilbert coordinate of the cell.
    0 <= D < N * N.

    Output, int *X, *Y, the Cartesian coordinates of the cell.
    0 <= *X, *Y < N.
*/
void d2xy ( int m, int d, int *x, int *y );


/******************************************************************************/
/*
  Purpose:

    I4_POWER returns the value of I^J.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    23 October 2007

  Author:

    John Burkardt

  Parameters:

    Input, int I, J, the base and the power.  J should be nonnegative.

    Output, int I4_POWER, the value of I^J.
*/
int i4_power ( int i, int j );

void rot ( int n, int *x, int *y, int rx, int ry );
void timestamp ( );
int xy2d ( int n, int x, int y );

#endif
