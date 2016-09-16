int dim1, dim2, dim3;
 int i,j,k;
 double *** array = (double ***)malloc(dim1*sizeof(double**));

        for (i = 0; i< dim1; i++) {

         array[i] = (double **) malloc(dim2*sizeof(double *));

          for (j = 0; j < dim2; j++) {

              array[i][j] = (double *)malloc(dim3*sizeof(double));
          }

        }
