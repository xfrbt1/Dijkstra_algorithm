#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define none INT32_MAX

void write_matrix_bin(char * filename, int **matrix, int n)
{

    FILE *file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j< n; j++)
        {
            fwrite(&matrix[i][j], sizeof(int), 1, file);
        }
    }
    fclose(file);
}

int **read_matrix(char * filename, int * n)
{
    int **weight_matrix;
    FILE *file = fopen(filename, "rb");

    fread(n, sizeof(int), 1, file);
    weight_matrix = malloc(sizeof(int*) * *n);

    for(int i = 0; i < *n; i++)
    {
        *(weight_matrix + i) = malloc(sizeof(int) * *n);
    }
    for(int i = 0; i < *n; i++)
    {
        for(int j = 0; j < *n; j++)
        {
            fread(&weight_matrix[i][j], sizeof(int), 1, file);
        }
    }

    fclose(file);

    return weight_matrix;
}

int **create_dynamic_matrix(int n)
{
    int **matrix = malloc(sizeof(int*) * n);

    for(int i =0; i <n; i++)
    {
        *(matrix+i) = malloc(sizeof(int) * n);
    }
    return matrix;
}

void print_matrix(int **matrix, int n)
{
    printf("  ");
    for (int i =0; i < n; i++)
    {
        printf("|%d ", i);
    }

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("|%d", i);
        for (int j = 0; j < n; j++)
        {
            if (*(*(matrix + i)+j) !=0) printf("[%d]", *(*(matrix + i)+j));
            else printf("[_]");
        }
        printf("\n");
    }
}

void fill_weight_matrix(int ** matrix, int n)
{
    char vertex_i = 97, vertex_j = 97;

    for(unsigned int i =0; i<n; i++)
    {
        matrix[i][i] = 0;
        for(unsigned int j = i + 1; j < n; j++)
        {
            int value;
            printf("vertex %c with vertex %c(value or 0): ", vertex_i+i, vertex_j+j);
            scanf("%d", &value);
            matrix[i][j] = value;
            matrix[j][i] = value;
        }
    }
}

void random_fill_weight_matrix(int ** matrix, int n)
{

    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        matrix[i][i] = 0;

        for(int j = i + 1; j < n; j++)
        {
            int value = rand()%10;

            if (value % 3 == 0)
            {
                matrix[i][j] = 0;
                matrix[j][i] = 0;
            }
            else
            {
                matrix[i][j] = value;
                matrix[j][i] = value;
            }

        }
    }
}

void initialization(int * dist, int * vis_vert, int *path, int n, int vertex)
{
    for (int i = 0; i < n; i++)
    {
        *(dist+i) = none;
        *(vis_vert+i) = false;
        *(path + i) = -1;
    }

    *(dist+vertex)=0;

}

int find_min_index(const int * dist, int * vis_vert, int n)
{
    int min = none, min_index;

    for(int i = 0; i < n; i++)
    {
        if(*(vis_vert+i)==false && *(dist+i)<=min)
        {
            min = *(dist+i);
            min_index = i;
        }
    }

    *(vis_vert+min_index) = true;

    return min_index;
}

void dijkstra(int ** matrix, int *dist, int * vis_vert, int * path, int n)
{

    for (int i = 0; i < n; i++)
    {
        int index_of_min_node = find_min_index(dist, vis_vert, n);

        for(int j = 0; j < n; j++)
        {
            if(vis_vert[j] == false)
            {
                if (matrix[index_of_min_node][j] != 0)
                {
                    if (matrix[index_of_min_node][j] + dist[index_of_min_node] <= dist[j])
                    {
                            dist[j] = matrix[index_of_min_node][j] + dist[index_of_min_node];
                            path[j] = index_of_min_node;
                    }
                }
            }
        }

        printf("\nshortest path to %c(%d)\n",  (char) 97 +index_of_min_node, index_of_min_node);

        int k = index_of_min_node;

        while( k != -1)
        {
            printf("(%d|%c)<-", k, (char)97 +k);
            k = path[k];
        }

        printf("\nweight = %d\n", dist[index_of_min_node]);
    }
}

int  * shortest_distance(int ** matrix, int n, int vertex)
{
    int *distance;
    int *visited_vertices;
    int *path;

    distance = malloc(sizeof(int) * n);
    visited_vertices = malloc(sizeof(int) * n);
    path = malloc(sizeof(int)* n);


    initialization(distance, visited_vertices, path, n, vertex);

    dijkstra(matrix, distance, visited_vertices, path, n);

    free(visited_vertices);
    free(path);

    return distance;

}

void print_result(int * dist, int n, int vertex)
{
    int start_vertex = 97, current_vertex = 97;

    printf("\n\n");

    for(int i =0; i < n; i++)
    {
        if (dist[i] == none)
        {
            printf("%d from %c(%d) -> %c(%d) = do not exist\n", i+1, start_vertex+vertex, vertex, current_vertex+i, i);
        }
        else
        {
            printf("%d from %c(%d) -> %c(%d) = %d\n",i+1, start_vertex+vertex, vertex, current_vertex+i, i, dist[i]);
        }
    }
    printf("\n");
}

int get_integer(const char *msg)
{
    char answer[256];
    int n;

    fgets(answer, sizeof(answer), stdin);

    while (sscanf(answer, "%d", &n) != 1)
    {
        printf("incorrect input, try again: ");
        fgets(answer, sizeof(answer), stdin);
    }

    return n;
}

char *get_str()
{
    int len = 0, capacity = 1;
    char *s = (char*) malloc(sizeof(char));
    char c = getchar();

    while (c != '\n')
    {
        s[(len)++] = c;
        if (len >= capacity)
        {
            capacity *= 2;
            s = (char*) realloc(s, capacity * sizeof(char));
        }
        c = getchar();
    }
    s[len] = '\0';
    return s;
}

int main() {

    char *filename1 = "graph_from_exprep.bin";
    char *filename2 = "graph_from_exprep1.bin";
    char *filename3 = "writen_graph.bin";

    while(1)
    {

        int ch;

        printf("3 - random graph\n"
               "2 - ready graph\n"
               "1 - new graph\n"
               "0 - exit\n"
               "choose option: ");
        scanf("%d", &ch);

        if (ch == 3)
        {
            int **weight_matrix, n, start_vertex;
            char *ans;

            printf("input amount of vertex: ");
            scanf("%d", &n);
            fflush(stdin);

            weight_matrix = create_dynamic_matrix(n);
            random_fill_weight_matrix(weight_matrix, n);

            write_matrix_bin(filename3, weight_matrix, n);

            printf("\nGRAPH:\n\n");
            print_matrix(weight_matrix, n);

            int chgr;

            printf("\ndraw graph(1-yes): ");
            scanf("%d", &chgr);
            fflush(stdin);

            if (chgr == 1)system("/Users/aleksej/Desktop/python/graphs_visulasation/venv/bin/python /Users/aleksej/Desktop/python/graphs_visulasation/transformation.py");

            printf("\n№ of start node: ");
            scanf("%d", &start_vertex);
            fflush(stdin);

            int *dist = shortest_distance(weight_matrix, n, start_vertex);
            print_result(dist, n, start_vertex);

            system("/Users/aleksej/Desktop/python/graphs_visulasation/venv/bin/python /Users/aleksej/Desktop/python/graphs_visulasation/transformation.py");

            free(dist);
            continue;
        }

        if (ch == 2)
        {
            int **weight_matrix, n, start_vertex;
            int chgr;

            printf("1 - 5 nodes\n2 - 10 nodes\nchoose graph: ");
            scanf("%d", &chgr);

            if(chgr == 1)weight_matrix = read_matrix(filename1, &n);
            if(chgr == 2)weight_matrix = read_matrix(filename2, &n);

            write_matrix_bin(filename3, weight_matrix, n);

            printf("\nGRAPH:\n\n");
            print_matrix(weight_matrix, n);

            system("/Users/aleksej/Desktop/python/graphs_visulasation/venv/bin/python /Users/aleksej/Desktop/python/graphs_visulasation/transformation.py");
            fflush(stdin);

            printf("\n№ of start node: ");
            scanf("%d", &start_vertex);

            int *dist = shortest_distance(weight_matrix, n, start_vertex);
            print_result(dist, n, start_vertex);

            system("/Users/aleksej/Desktop/python/graphs_visulasation/venv/bin/python /Users/aleksej/Desktop/python/graphs_visulasation/transformation.py");

            free(dist);
            continue;

        }

        if (ch == 1)
        {
            int **weight_matrix, n, start_vertex;

            printf("input amount of vertex: ");
            scanf("%d", &n);

            weight_matrix = create_dynamic_matrix(n);
            fill_weight_matrix(weight_matrix, n);
            write_matrix_bin(filename3, weight_matrix, n);

            printf("\nGRAPH:\n\n");
            print_matrix(weight_matrix, n);

            int chgr;

            printf("\ndraw graph(1-yes): ");
            scanf("%d", &chgr);

            if (chgr == 1)system("/Users/aleksej/Desktop/python/graphs_visulasation/venv/bin/python /Users/aleksej/Desktop/python/graphs_visulasation/transformation.py");
            fflush(stdin);

            printf("\n№ of start node: ");
            scanf("%d", &start_vertex);

            int *dist = shortest_distance(weight_matrix, n, start_vertex);
            print_result(dist, n, start_vertex);

            system("/Users/aleksej/Desktop/python/graphs_visulasation/venv/bin/python /Users/aleksej/Desktop/python/graphs_visulasation/transformation.py");

            free(dist);
            continue;
        }

        else
        {
            break;
        }

    }

    return 0;
}
