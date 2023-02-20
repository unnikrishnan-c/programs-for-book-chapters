
 #include "connected_component.h"
 int   changed =0, hchanged =0;


 void   relaxgraph ( int & p ,HGraph & unnigraph ) 
 {

 int falcft0=unnigraph.index[p+1]-unnigraph.index[p];
int falcft1=unnigraph.index[p];
for(int falcft2=0;falcft2<falcft0;falcft2++){
int ut0=2*(falcft1+falcft2);
 int ut1=unnigraph.edges[ut0].ipe;
int ut2=unnigraph.edges[ut0+1].ipe;
int t=ut1;
HMIN(&(((struct struct_graph  *)(unnigraph.extra))->dist[ut1]),((struct struct_graph  *)(unnigraph.extra))->dist[p],ut1,changed);


 HMIN(&(((struct struct_graph  *)(unnigraph.extra))->dist[p]),((struct struct_graph  *)(unnigraph.extra))->dist[ut1],p,changed);


 }

 }
void   reset ( int & t ,HGraph & graph ) 
 {

 ((struct struct_graph  *)(graph.extra))->dist[t]=graph.points[t].ipe; 

 }
void   SSSP ( char    *  name ) 
 {

 HGraph  graph ;

 

 graph.read2(name);

int hostgraph=0;
alloc_extra_graph(graph,hostgraph,graph.npoints);
; 

  double   t1 , t2 ;


 t1=rtclock();


 #pragma omp parallel for   num_threads(FALC_THREADS)
for(int i=0;i<graph.npoints;i++)reset(i,graph);

 ((struct struct_graph  *)(graph.extra))->dist[0]=0; 

 
 while(1)  { 

 changed=0; 

 #pragma omp parallel for   num_threads(FALC_THREADS)
for(int i=0;i<graph.npoints;i++)relaxgraph(i,graph);

 if( changed==0  )
break;

 }

 t2=rtclock();


 printf("\nTIME =%f",(t2-t1)*1000);


  int   maxdist =0;

int total_wccs=0;
int curr_wcc=0;
 for (int   i =0;i<graph.npoints;i++) {
 if(((struct struct_graph  *)(graph.extra))->dist[i]!=curr_wcc){
	 curr_wcc=((struct struct_graph  *)(graph.extra))->dist[i];
	 total_wccs++;
 }

 }

 printf("\ntotal connected components= %d\n",total_wccs);


 return ;

 }
int   main ( int   argc ,char    *  argv [ ] ) 
 { 
alloc_sync_array();
if(argc>2)FALC_THREADS=atoi(argv[2]);

 if( argc!=4  )
{

 printf("error:-exec -t threads  file");


 return 1;

 }

 SSSP(argv[3]);


 }
