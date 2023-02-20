#include "undirected_triangle_counting.h"

cudaDeviceProp prop0;
__device__ int changed = 0;;
int hchanged;
__global__ void TC(GGraph graph, int FALCX)
{ //each traingle counted six times, naive algorithm
	int id = blockIdx.x *blockDim.x + threadIdx.x + FALCX;

	if (id < graph.npoints)
	{
		int p = id;//p
		int startsrc=graph.index[p];
		int endsrc=graph.index[p+1];
		for(int kk=startsrc;kk<endsrc;kk++){
			int t=graph.edges[2*kk].ipe;//t
			for(int ll=startsrc;ll<endsrc;ll++){//
				int r=graph.edges[2*ll].ipe;//r, edges p--t, p--r
				if(t==r)continue;//t==r go to next edge.
				int nbrs_r_start=graph.index[r];//check edge t--r exist, where t!=r
				int nbrs_r_end=graph.index[r+1];
				for(int i=nbrs_r_start;i<nbrs_r_end;i++)
				       	if (graph.edges[2*i].ipe==t)atomicAdd(&changed,1);//edge t--r exist, making triangle p-t,t--r, t--p
			}
		}
	}
}

int main(int argc, char *name[])
{
	cudaGetDeviceProperties(&prop0, 0);
	alloc_sync_array();

	if (argc != 2)
	{
		printf("error: exec filename");

		return 1;
	}

	HGraph hgraph;

	hgraph.read2(name[1]);

	int hosthgraph = 0;
	alloc_extra_hgraph(hgraph, hosthgraph, hgraph.npoints);;

	GGraph graph;

	hgraph.cloneGPU(graph, 0);
	int graphflag = 0;

	alloc_extra_graph(graph, graphflag, graph.npoints);

	int TPB0 = 1024;

	int graphpointkernelblocks = graph.npoints/ TPB0+1;

	int graphedgekernelblocks = graph.nedges/ TPB0+1;
	copygraphcurrentsize(graph);
	cudaSetDevice(0);

	double t1, t2;

	t1 = rtclock();

	int falcvt1;
	falcvt1 = 0;
	struct struct_hgraph temp1;
	cudaMemcpy(&temp1, ((struct struct_hgraph *)(graph.extra)), sizeof(struct struct_hgraph), cudaMemcpyDeviceToHost);
	if (cudaMemcpy(&(temp1.dist[0]), &(falcvt1), sizeof(int), cudaMemcpyHostToDevice) != cudaSuccess) printf("memcpyerror 1");

	int falcvt2;
	falcvt2 = 0;
	if (cudaMemcpyToSymbol(changed, &(falcvt2), sizeof(int), 0, cudaMemcpyHostToDevice) != cudaSuccess) printf("memcpyerror 2");
printf("%d %d %d\n",  graph.npoints, graphpointkernelblocks,TPB0);
	cudaSetDevice(0);
	for (int kk = 0; kk < graph.npoints; kk += graphpointkernelblocks *TPB0)
	{
		TC <<<graphpointkernelblocks, TPB0>>> (graph, kk);
	}

	cudaDeviceSynchronize();
	cudaSetDevice(0);

	t2 = rtclock();

	printf("\nTIME =%f\n", (t2 - t1) *1000);

	int count;

	if (cudaMemcpyFromSymbol(&(count), changed, sizeof(int), 0, cudaMemcpyDeviceToHost) != cudaSuccess) printf("memcpyerror 3");
        int triangles=count/6;
	printf("\ntriangles=%d \n", triangles);

	return;

}
