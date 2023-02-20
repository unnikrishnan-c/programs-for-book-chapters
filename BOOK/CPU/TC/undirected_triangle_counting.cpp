
 #include "undirected_triangle_counting.h"
 int   changed =0, hchanged ;


 void   TC ( int & p ,HGraph & graph ) 
 {


//p as input to TC function.
 int falcft0=graph.index[p+1]-graph.index[p];
int falcft1=graph.index[p];
for(int falcft2=0;falcft2<falcft0;falcft2++){//nbrs of p
	int ut0=2*(falcft1+falcft2);
        int ut1=graph.edges[ut0].ipe;//t, edge p--t
	for(int falcft3=0;falcft3<falcft0;falcft3++){//nbrs of p
		int ut3=2*(falcft1+falcft3);
                int ut4=graph.edges[ut3].ipe;//r, edges p--t, p--r
		if(ut1==ut4)continue;//if t==r continue
		int x=graph.index[ut4+1]- graph.index[ut4];//else check edge r--t exist
		int y=graph.index[ut4];
		for(int falcft4=0; falcft4< x;falcft4++){
		int ut5=2*(y+x);
			if(graph.edges[ut5].ipe==ut1)HADD(&changed,1);
		}
	 }
 }
 }
int   main ( int   argc ,char    *  argv [ ] ) 
 { 
alloc_sync_array();
if(argc>2)FALC_THREADS=atoi(argv[2]);

 if( argc!=4  )
{

 printf("error: exec -t threads filename");


 return 1;

 }

 HGraph  hgraph ;

 

 hgraph.read2(argv[3]);

int hosthgraph=0;
alloc_extra_hgraph(hgraph,hosthgraph,hgraph.npoints);
; 

  double   t1 , t2 ;


 t1=rtclock();


 changed=0; 

 #pragma omp parallel for   num_threads(FALC_THREADS)
for(int i=0;i<hgraph.npoints;i++)TC(i,hgraph);

 t2=rtclock();


 printf("\nTIME =%f\n",(t2-t1)*1000);


  int   count ;


 count=changed; 

 printf("\ntriangles=%d \n",count/6);


 return 1;

 }
