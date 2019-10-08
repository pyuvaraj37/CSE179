#include <stdio.h>
#include <omp.h>

int minKey(int key[], bool mstSet[]) 
{ 
// Initialize min value 
int min = INT_MAX, min_index; 
  
for (int v = 0; v < V; v++) 
    if (mstSet[v] == false && key[v] < min) 
        min = key[v], min_index = v; 
  
return min_index; 
} 

int printMST(int parent[], int n, int graph[V][V]) 
{ 
printf("Edge \tWeight\n"); 
for (int i = 1; i < V; i++) 
    printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]); 
} 

void primMST(int graph[V][V]) 
{ 
    int parent[V];  
    int key[V];    
    bool mstSet[V];  
  
  
    for (int i = 0; i < V; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
  
    key[0] = 0;      
    parent[0] = -1; // First node is always root of MST  
  
    #pragma omp for schedule(dynamic, 5) 
    for (int count = 0; count < V-1; count++) 
    { 

        int u = minKey(key, mstSet); 
  
        mstSet[u] = true; 
  
      
        /#pragma omp for schedule(dynamic, 5) 
        for (int v = 0; v < V; v++) 
  
        if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
            parent[v] = u, key[v] = graph[u][v]; 
    } 
    printMST(parent, V, graph); 
} 



int main() {

   FILE *fp;
   int buff[100][100];

   fp = fopen("graph.txt", "r");
   
   for (int i = 0; i < 100; i++) {
   		for (int j = 0; j < 100; j++) {
   			 fscanf(fp, "%d", &buff[i][j]);
   			 printf("%d\n", buff[i][j]);
   		}
   }
  
   fclose(fp);

   primMST(buff);

   return 0;
}