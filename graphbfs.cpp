#include <iostream>
#include <queue>
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

//cari jalur pakai BFS
void shortestPathBFS(int start, int goal) {
    queue<int> q; // ini ngebuat antrian dengan nama q
    bool visited[MAX] = {false}; // bagian ini ngeset semua vertex sebagai belum dikunjungi {false, false, false, false, false}
    int dist[MAX]; // inisialisasi array untuk menyimpan jarak dari vertex awal
    int prev[MAX]; // inisialisasi array untuk menyimpan jalur

    for (int i = 0; i < MAX; i++) {
        dist[i] = -1; // ngeset jarak semua vertex ke -1 (belum terjangkau)
        prev[i] = -1; // ngeset jalur semua vertex ke -1 (belum ada jalur)
    }

    q.push(start); // masukin vertex awal ke antrian, contohnya start = 0 berarti antrian sekarang ada [0]
    visited[start] = true; // ubah status vertex awal jadi sudah dikunjungi
    dist[start] = 0; // karena ini vertex awal, jaraknya ke dirinya sendiri adalah 0

    while (!q.empty()) { // ini maksudnya perulangan selama antrian tidak kosong
        int curr = q.front(); // ambil elemen paling depan dari antrian, tadikan dalam antrean ada [0], berarti curr = 0
        q.pop(); // hapus elemen paling depan dari antrian, berarti antrian sekarang jadi kosong [] tapi nilai 0 dah ada di variabel curr

        for (int i = 0; i < jumlahVertex; i++) {
            if (edge[curr][i] == 1 && !visited[i]) { // cek semua vertex yang terhubung dengan curr dan belum dikunjungi
                visited[i] = true; // ngubah status vertex i jadi sudah dikunjungi
                dist[i] = dist[curr] + 1; // ngupdate jarak vertex i, misal dist[1] = dist[0] + 1 = 0 + 1 = 1
                prev[i] = curr; // nyimpen jalur, misal prev[1] = 0 artinya buat ke 1 harus dari 0
                q.push(i); // masukin vertex i ke antrian, misal antrian sekarang [] jadi [1]
                // lebih lengkapnya liat dibawah
            }
        }
    }

    // tampilkan hasil
    if (dist[goal] == -1) { // kalo jarak ke goal masih -1 berarti ga ada jalur
        cout << "Tidak ada jalur dari " << start << " ke " << goal << endl;
    } else {
        cout << "Jarak terpendek: " << dist[goal] << endl; // misal goal = 3, berarti jarak terpendek dari start ke goal, disini dist[3] = dist[2] + 1 = 1 + 1 = 2
        cout << "Jalur: ";
        int path[MAX], count = 0;
        for (int at = goal; at != -1; at = prev[at]) // ini buat ngelacak jalur dari goal ke start, misal goal = 3, prev[3] = 2, prev[2] = 0, prev[1] = 0, prev[0] = -1
            path[count++] = at; // simpen jalur di array path, sekarang path = [3, 2, 0], count = 3
        for (int i = count - 1; i >= 0; i--) // ini buat nampilin jalur dari start ke goal, jadi dibalikin dari path tadi
            cout << path[i] << (i ? " -> " : "\n"); // misal path[2] = 0, path[1] = 2, path[0] = 3, jadi outputnya 0 -> 2 -> 3
    }
}

int main(){
    tambahVertex();
    tambahVertex();
    tambahVertex();
    tambahVertex();
    tambahEdge(0, 1);
    tambahEdge(0, 2);
    tambahEdge(1, 1);
    tambahEdge(1, 2);
    tambahEdge(2, 1);
    tambahEdge(2, 2);
    tambahEdge(2, 3);
    tampilGraph();
    shortestPathBFS(0, 3);
}

/*
<queue>
| Fungsi    | Kegunaan                                           |
| --------- | -------------------------------------------------- |
| `push(x)` | Menambahkan elemen ke belakang antrian             |
| `pop()`   | Menghapus elemen paling depan                      |
| `front()` | Mengambil elemen paling depan (tanpa menghapus)    |
| `back()`  | Mengambil elemen paling belakang (tanpa menghapus) |
| `empty()` | Mengecek apakah antrian kosong (true/false)        |
| `size()`  | Mengembalikan jumlah elemen di antrian             |

Penjelasan : BFS
BFS (Breadth-First Search) adalah algoritma pencarian yang menjelajahi graf atau pohon secara melintang, yaitu dengan 
mengunjungi semua tetangga dari suatu node sebelum melanjutkan ke level berikutnya. 
Algoritma ini menggunakan struktur data antrian (queue) untuk menyimpan node-node yang akan dikunjungi selanjutnya. 
BFS sering digunakan untuk menemukan jalur terpendek dalam graf tak berbobot.

tabel curr = 0
| i | edge[0][i] | visited[i]? | Aksi     |
| - | ---------- | ----------- | -------- |
| 0 | 0          | true        | dilewati |
| 1 | 1          | false       | push(1)  |
| 2 | 1          | false       | push(2)  |
| 3 | 0          | —           | dilewati |

dalam q sekarang ada [1, 2]
| Variabel  | Nilai                     |
| --------- | ------------------------- |
| `q`       | [1, 2]                    |
| `visited` | {true, true, true, false} |
| `dist`    | {0, 1, 1, -1}             |
| `prev`    | {-1, 0, 0, -1}            |
dist[1] = dist[0] + 1 = 0 + 1 = 1
prev[1] = 0
dist[2] = dist[0] + 1 = 0 + 1 = 1
prev[2] = 0

curr = 1, q = [2]
| i | edge[1][i] | visited[i]? | Aksi                        |
| - | ---------- | ----------- | --------------------------- |
| 0 | 0          | true        | dilewati                    |
| 1 | 0          | true        | dilewati                    |
| 2 | 1          | true        | **sudah pernah dikunjungi** |
| 3 | 0          | false       | dilewati                    |
tidak terjadi push karena tidak ada edge 1 ke 3, dalam q sekarang tetap [2]

curr = 2, q = []
| i | edge[2][i] | visited[i]? | Aksi     |
| - | ---------- | ----------- | -------- |
| 0 | 0          | true        | dilewati |
| 1 | 0          | true        | dilewati |
| 2 | 0          | true        | dilewati |
| 3 | 1          | false       | push(3)  |


dalam q sekarang ada [3]
| Variabel  | Nilai                    |
| --------- | ------------------------ |
| `q`       | [3]                      |
| `visited` | {true, true, true, true} |
| `dist`    | {0, 1, 1, 2}             |
| `prev`    | {-1, 0, 0, 2}            |
dist[3] = dist[2] + 1 = 1 + 1 = 2
prev[3] = 2

curr = 3, q = []
karena tidak ada edge dari 3 ke node lain, antrian menjadi kosong [] sehingga while loop berhenti

hasilnya
| Vertex | dist (jarak) | prev (asal) |
| ------ | ------------ | ----------- |
| 0      | 0            | -1          |
| 1      | 1            | 0           |
| 2      | 1            | 0           |
| 3      | 2            | 2           |

Logika for loop pada penyimpanan dalam array path:
| Iterasi | Nilai `at`             | prev[at] | path[] setelah disimpan | count |
| ------- | ---------------------- | -------- | ----------------------- | ----- |
| 1       | 3                      | 2        | [3]                     | 1     |
| 2       | 2                      | 0        | [3, 2]                  | 2     |
| 3       | 0                      | -1       | [3, 2, 0]               | 3     |
| 4       | stop (karena at == -1) |          |                         |       |

*/
