#include"graph_store.h"
#include"matrix_cal.h"


void get_outlink(MGraph G,int *outlink) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (G.arcs[i][j].adj != INT_MAX && i != j) {
				outlink[i]++;
			}
		}
	}
}

void pankrank_iteration(double *R, double error, MGraph *G,double d,int *outlink) {	
	bool cal = 1;
	double cvg = 1e-111;
	while (cal) {
		double temp[N] = { 0 };
		double prev[N] = { 0 };
		double tcvg = 0;
		for (int i = 0; i < N; i++)
		{
			prev[i] = R[i];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (G->arcs[j][i].adj==1) {
					double  aa= (double)R[j] / outlink[j];
					temp[i] += aa;
				}
			}
			R[i] = (1 - d) / N + d * temp[i];
		}
		for (int i = 0; i < N; i++) {
			tcvg = tcvg + (R[i] - prev[i]);
		}
		if (tcvg - cvg < 1e-36) break;
	}

}

void get_K(int *outlink, int **K) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				*(*K + i * N + j) = *(outlink + i);
			}
		}
	}
}

void get_M(AdjMatrix A,int *K,double **M) {
	int *temp = (int *)malloc(sizeof(int) * 100);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if((*A)->adj==1)
			*(temp + i * N + j) = (*A)->adj;
			else {
				*(temp + i * N + j) = 0;
			}
		}
	}
	dial_inv(&K);
	mul(K, temp, M);
}



void pagerank_matrix(AdjMatrix Adj,int *outlink,int d) {
	double *indentity_matrix = (double*)malloc(sizeof(double) * 100);
	double *M = (double*)malloc(sizeof(double) * 100);
	double *H = (double*)malloc(sizeof(double) * 100);
	int *K = (int *)malloc(sizeof(int) * 100);
	gen_identity_matrix(&indentity_matrix, N);
	get_K(outlink, &K);
	get_M(Adj, K, &M);
	munber_mul_matrix(&M, N, d);
	substract(&indentity_matrix, &M, &H);


}

int main() {
	//cout << 1 / 0;
	/*MGraph G;
	CreateDN(&G);
	double R[N]; //= (double *)malloc(sizeof(double)*N);
	int outlink[N] = { 0 };
	double d = 0.85;
	double err = 1e-35;
	for (int i = 0; i < N; i++) {
		*(R+i) = 1.0 / N;
	}
	get_outlink(G, outlink);
	pankrank_iteration(R, err, &G, 0.85, outlink);
	for (double r : R) {
		cout << r << endl;
	}*/
	//test();
	int *matrix = (int*)malloc(sizeof(int)*100);
	double *v = (double*)malloc(sizeof(double)*100);
	//int R[N] = { 2,1,8 };
	memset(v, 0, sizeof(double) * 100);
	create_matrix(&matrix);
	//trans(matrix);
	//int a = inv_num(R);
	//int b = fac(3);
	 //int c = mul_f(R, R);
	//inv(matrix);
	//get_cofactor(&matrix, 0, 1,4, &v);
	//get_cofactor(&v, 0, 1, 3, &v);
	//int e=0;
	//e = get_det(&matrix, N);
	//get_inverse_matrix(&matrix, N, &v);
	//get_adjoint_matrix(&matrix, N, &v);
	//e = det(matrix, N);
	//cout<<endl<<e;
	mul(matrix, matrix, &v);

	//inv(matrix);

	cout << "asd";

}
/*

8 14
1 2 3 4 5 6 7 8
1 6 1
1 8 1
2 8 1
2 1 1
3 4 1
3 8 1
4 2 1
4 8 1
4 5 1
5 8 1
6 8 1
6 7 1
6 5 1
7 8 1
8 3 1
0 0 0





1 2 0
-1 1 -4
3 -1 8
-142
5 1 1 1
-2 2 -1 4
-2 -3 -1 -5
0 1 2 11

1 2 3 4 5
6 7 8 9 10
1 2 5 7 8
2 -8 9 -8 -6
7 4 5 8 6

1 2
3 4
*/



