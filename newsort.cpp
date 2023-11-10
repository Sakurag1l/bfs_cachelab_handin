#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

struct Node
{
    int id;         
    int in_degree;  
    int out_degree; 
} nodes[N];

int edge_num = 0;
int node_num = 0;             
int edge[N][2];        // 边数
bool visited[N]; 
int idx[N];
vector<int> edge_map[N];


bool cmp(struct Node &node1, struct Node &node2)
{
    return node1.in_degree > node2.in_degree;
}

void de_sort()
{

    // 根据读取的数据进行计数
    for (int i = 0;i < edge_num;i++)
    {
        int t_in = edge[i][0],t_out = edge[i][1];
        nodes[t_out].in_degree += 1;
        nodes[t_in].out_degree += 1;
        int t_num = 0;
        if (!visited[t_in])
        {
            idx[node_num++] = t_in;
            visited[t_in] = true;
        }
    }

    sort(nodes + 1, nodes + N, cmp);

    // for (int i = 1; i < node_num; i++)
    // {
    //     for(auto item : edge_map[i])
    //     {
    //         cout << nodes[i].id << " " << item << endl;
    //     }
    // }
}

void save(const char *write_name)
{


    FILE *fd = fopen(write_name, "w");

    if(fd ==  NULL){
        printf("Open Failed!");
        exit(1);
    }


    for (int i = 1; i < node_num; i++)
    {
        for(auto item : edge_map[i])
        {
            fprintf(fd, "%u %u\n", nodes[i].id, item);
        }
    }

    fclose(fd);


 
}
int main()
{
    const char *file_name = "data.txt";
    const char *write_name = "newsort.map";
    FILE *fd = fopen(file_name, "r");
    char data[N];

    if(fd == NULL){
        printf("Open Failed!");
        exit(1);
    }

    unsigned int in, out = 0;
    while(fgets(data, N, fd))
    {
        sscanf(data, "%u %u", &in, &out);
        edge[edge_num][0] = in;
        edge[edge_num][1] = out;
        edge_num += 1;
        edge_map[in].push_back(out);
    }

    for (int i = 1; i < N; i++)
    {
        nodes[i].id = i;
        nodes[i].in_degree = 0;
        nodes[i].out_degree = 0;
    }

    de_sort();
    save(write_name);
    return 0;
}
