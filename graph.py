MAX = 5
jumlah_vertex = 0
edge = [[0] * MAX for _ in range(MAX)]  # adjacency matrix

def tambah_vertex():
    global jumlah_vertex
    if jumlah_vertex < MAX:
        jumlah_vertex += 1
        print("Vertex berhasil ditambahkan")
    else:
        print("Vertex sudah penuh")

def tambah_edge(a, b, bobot):
    if a < jumlah_vertex and b < jumlah_vertex:
        edge[a][b] = bobot
        print(f"Edge {a} ke {b} dengan bobot {bobot} sudah ditambahkan")
    else:
        print("Vertex tidak valid!")

def tampil_graph():
    for i in range(jumlah_vertex):
        for j in range(jumlah_vertex):
            print(edge[i][j], end=" ")
        print()

# ==============================
# Dijkstra TANPA PRIORITY QUEUE
# ==============================
def shortest_path_dijkstra(start, goal):
    dist = [float('inf')] * jumlah_vertex
    prev = [-1] * jumlah_vertex
    visited = [False] * jumlah_vertex

    dist[start] = 0

    for _ in range(jumlah_vertex):
        # Cari vertex dengan jarak terkecil yang belum dikunjungi
        min_dist = float('inf')
        u = -1
        for v in range(jumlah_vertex):
            if not visited[v] and dist[v] < min_dist:
                min_dist = dist[v]
                u = v

        if u == -1:  # semua vertex sudah dikunjungi atau tidak terjangkau
            break

        visited[u] = True  # tandai sudah dikunjungi

        # Perbarui jarak ke semua tetangga dari u
        for v in range(jumlah_vertex):
            if edge[u][v] > 0 and not visited[v]:
                new_dist = dist[u] + edge[u][v]
                if new_dist < dist[v]:
                    dist[v] = new_dist
                    prev[v] = u

    # tampilkan hasil
    if dist[goal] == float('inf'):
        print(f"Tidak ada jalur dari {start} ke {goal}")
    else:
        print(f"Jarak terpendek: {dist[goal]}")
        print("Jalur: ", end="")
        path = []
        at = goal
        while at != -1:
            path.append(at)
            at = prev[at]
        path.reverse()
        print(" -> ".join(map(str, path)))

# ==============================
# MAIN PROGRAM
# ==============================
if __name__ == "__main__":
    tambah_vertex()
    tambah_vertex()
    tambah_vertex()
    tambah_vertex()

    tambah_edge(0, 1, 4)
    tambah_edge(0, 2, 1)
    tambah_edge(2, 1, 2)
    tambah_edge(1, 3, 1)
    tambah_edge(2, 3, 5)

    print("\nMatriks Ketetanggaan (Adjacency Matrix):")
    tampil_graph()

    print("\nHasil Dijkstra tanpa heap:")
    shortest_path_dijkstra(0, 3)
