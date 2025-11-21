#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX = 5;

int jumlahVertex = 0;
string kota[MAX];
int edge[MAX][MAX];

void tambahVertex(string namaKota)
{
    if (jumlahVertex < MAX)
    {
        kota[jumlahVertex] = namaKota;
        jumlahVertex++;
        cout << "Kota " << namaKota << " berhasil ditambahkan\n";
    }
    else
    {
        cout << "Kapasitas kota sudah penuh\n";
    }
}

void tambahEdge(string kotaA, string kotaB)
{
    int idxA = -1, idxB = -1;

    for (int i = 0; i < jumlahVertex; i++)
    {
        if (kota[i] == kotaA)
            idxA = i;
        if (kota[i] == kotaB)
            idxB = i;
    }

    if (idxA != -1 && idxB != -1)
    {
        edge[idxA][idxB] = 1;
        cout << "Jalan dari " << kotaA << " -> " << kotaB << " berhasil dibangun\n";
    }
    else
    {
        cout << "Kota tidak ditemukan!\n";
    }
}

void tampilJaringan()
{
    cout << "\nJARINGAN JALAN ANTAR KOTA:\n";
    cout << "================================\n";

    bool adaJalan = false;
    for (int i = 0; i < jumlahVertex; i++)
    {
        for (int j = 0; j < jumlahVertex; j++)
        {
            if (edge[i][j] == 1)
            {
                cout << kota[i] << " -> " << kota[j] << endl;
                adaJalan = true;
            }
        }
    }

    if (!adaJalan)
    {
        cout << "Belum ada jalan yang terhubung\n";
    }
    cout << "================================\n";
}

void tampilKota()
{
    cout << "\nDAFTAR KOTA YANG TERSEDIA:\n";
    cout << "==============================\n";
    for (int i = 0; i < jumlahVertex; i++)
    {
        cout << "   " << (i + 1) << ". " << kota[i] << endl;
    }
    cout << "==============================\n";
}

// Queue untuk BFS
int q[MAX];
int front = 0, rear = -1;

bool isEmpty()
{
    return front > rear;
}

void enqueue(int val)
{
    if (rear < MAX - 1)
    {
        rear++;
        q[rear] = val;
    }
}

int dequeue()
{
    if (!isEmpty())
    {
        int val = q[front];
        front++;
        return val;
    }
    return -1;
}

void visualisasiRute(vector<int> &path)
{
    cout << "\n   ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << "[" << kota[path[i]] << "]";
        if (i > 0)
            cout << " -> ";
    }
    cout << endl;
}

void cariRuteTerpendek(string startKota, string goalKota)
{
    int start = -1, goal = -1;

    for (int i = 0; i < jumlahVertex; i++)
    {
        if (kota[i] == startKota)
            start = i;
        if (kota[i] == goalKota)
            goal = i;
    }

    if (start == -1 || goal == -1)
    {
        cout << "Kota tidak ditemukan!\n";
        return;
    }

    if (start == goal)
    {
        cout << "Anda sudah berada di kota tujuan!\n";
        return;
    }

    bool visited[MAX] = {false};
    int dist[MAX];
    int prev[MAX];

    for (int i = 0; i < MAX; i++)
    {
        dist[i] = -1;
        prev[i] = -1;
    }

    // Reset queue
    front = 0;
    rear = -1;

    enqueue(start);
    visited[start] = true;
    dist[start] = 0;

    cout << "\nMencari rute dari " << startKota << " ke " << goalKota << "...\n";

    while (!isEmpty())
    {
        int curr = dequeue();

        for (int i = 0; i < jumlahVertex; i++)
        {
            if (edge[curr][i] == 1 && !visited[i])
            {
                visited[i] = true;
                dist[i] = dist[curr] + 1;
                prev[i] = curr;
                enqueue(i);

                cout << "Ditemukan: " << kota[curr] << " -> " << kota[i] << endl;

                if (i == goal)
                {
                    cout << "Tujuan tercapai!\n";
                    break;
                }
            }
        }
    }

    // Tampilkan hasil
    if (dist[goal] == -1)
    {
        cout << "\nTIDAK ADA RUTE\n";
        cout << "   Tidak ditemukan jalan dari " << startKota << " ke " << goalKota << endl;
    }
    else
    {
        cout << "\nRUTE DITEMUKAN!\n";
        cout << "   Dari: " << startKota << endl;
        cout << "   Ke: " << goalKota << endl;
        cout << "   Jumlah perjalanan: " << dist[goal] << " langkah\n";
        cout << "   Rute terpendek:";

        vector<int> path;
        for (int at = goal; at != -1; at = prev[at])
        {
            path.push_back(at);
        }

        visualisasiRute(path);
    }
}

void contohKasusNyata()
{
    cout << "\n"
         << string(50, '=') << endl;
    cout << "           SISTEM NAVIGASI WISATA JAWA-BALI" << endl;
    cout << string(50, '=') << endl;

    // Reset graph
    jumlahVertex = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            edge[i][j] = 0;
        }
    }

    cout << "\nMENAMBAHKAN KOTA...\n";
    tambahVertex("Jakarta");
    tambahVertex("Bandung");
    tambahVertex("Yogyakarta");
    tambahVertex("Surabaya");
    tambahVertex("Bali");

    cout << "\nMEMBANGUN JALAN...\n";
    tambahEdge("Jakarta", "Bandung");
    tambahEdge("Bandung", "Yogyakarta");
    tambahEdge("Yogyakarta", "Surabaya");
    tambahEdge("Surabaya", "Bali");
    tambahEdge("Jakarta", "Surabaya");

    tampilKota();
    tampilJaringan();

    cout << "\nMENCARI RUTE PERJALANAN...\n";
    cariRuteTerpendek("Jakarta", "Bali");

    cout << "\n"
         << string(40, '-') << endl;
    cariRuteTerpendek("Bandung", "Surabaya");

    cout << "\n"
         << string(40, '-') << endl;
    cariRuteTerpendek("Bali", "Jakarta");
}

void demoFiturTambahan()
{
    cout << "\n"
         << string(50, '=') << endl;
    cout << "           DEMO: JALAN ALTERNATIF" << endl;
    cout << string(50, '=') << endl;

    cout << "\nMenambahkan jalan alternatif...\n";
    tambahEdge("Bandung", "Surabaya");
    tambahEdge("Jakarta", "Bali");

    tampilJaringan();

    cout << "\nMENCARI RUTE DENGAN JALAN BARU...\n";
    cariRuteTerpendek("Jakarta", "Bali");
}

int main()
{
    cout << "DEMO STRUKTUR DATA: GRAPH UNTUK SISTEM NAVIGASI\n";

    contohKasusNyata();
    demoFiturTambahan();

    cout << "\n"
         << string(50, '=') << endl;
    cout << "           KESIMPULAN" << endl;
    cout << string(50, '=') << endl;
    cout << "Graph cocok untuk memodelkan jaringan transportasi\n";
    cout << "BFS efektif untuk mencari rute terpendek\n";
    cout << "Visualisasi membantu memahami konsep dengan mudah\n";

    return 0;
}