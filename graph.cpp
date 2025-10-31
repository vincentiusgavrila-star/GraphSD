#include <iostream>
using namespace std;
const int MAX = 5;

int jumlahVertex = 0;
int edge[MAX][MAX];
void tambahVertex(){
    if (jumlahVertex < MAX)
    {
        jumlahVertex++;
        cout << "Vertex berhasil ditambahkan\n";
    }else{
        cout << "Vertex sudah penuh\n";
    }
}

void tambahEdge(int a, int b){
    if (a < jumlahVertex && b < jumlahVertex)
    {
        edge[a][b] = 1;
        // edge[b][a] = 0;
        cout << "Edge " << a << " ke " << b << " sudah ditambahkan\n";
    }else{
        cout << "Vertex tidak valid!";
    }
}

void tampilGraph(){
    for (int i = 0; i < jumlahVertex; i++)
    {
        for (int j = 0; j < jumlahVertex; j++)
        {
            cout << edge[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    tambahVertex();
    tambahVertex();
    tambahVertex();
    tambahEdge(0, 1);
    tambahEdge(0, 2);
    tambahEdge(1, 1);
    tambahEdge(1, 2);
    tambahEdge(2, 1);
    tambahEdge(2, 2);
}