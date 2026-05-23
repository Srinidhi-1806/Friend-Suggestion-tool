#include <stdio.h>
#include <string.h>

#define MAX_USERS 6

char* users[MAX_USERS] = {"sasikumar", "sowmya", "srinidhi", "raja", "riya", "yuktha"};
int graph[MAX_USERS][MAX_USERS] = {0};
int visited[MAX_USERS];

// Get index for username
int getUserIndex(char* name) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i], name) == 0) return i;
    }
    return -1;
}

// DFS traversal (for reference/demo)
void dfs(int current) {
    visited[current] = 1;
    for (int i = 0; i < MAX_USERS; i++) {
        if (graph[current][i] && !visited[i]) {
            dfs(i);
        }
    }
}

// BFS-based friend suggestion
void suggestFriendsBFS(int userIndex, int suggested[]) {
    int queue[MAX_USERS];
    int front = 0, rear = 0;

    int directFriends[MAX_USERS] = {0};  // mark direct friends
    for (int i = 0; i < MAX_USERS; i++) {
        if (graph[userIndex][i]) {
            directFriends[i] = 1;
        }
    }

    // Standard BFS to explore level by level
    int visitedLocal[MAX_USERS] = {0};
    queue[rear++] = userIndex;
    visitedLocal[userIndex] = 1;

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < MAX_USERS; i++) {
            if (graph[current][i] && !visitedLocal[i]) {
                queue[rear++] = i;
                visitedLocal[i] = 1;

                // If i is not a direct friend and not self, it's a potential suggestion
                if (!directFriends[i] && i != userIndex) {
                    suggested[i] = 1;
                }
            }
        }
    }
}

int main() {
    char inputName[100];
    fgets(inputName, sizeof(inputName), stdin);
    inputName[strcspn(inputName, "\n")] = 0;

    // Define friendship edges
    graph[0][1] = graph[1][0] = 1; // sasikumar - sowmya
    graph[0][2] = graph[2][0] = 1; // sasikumar - srinidhi
    graph[1][3] = graph[3][1] = 1; // sowmya - raja
    graph[1][4] = graph[4][1] = 1; // sowmya - riya
    graph[2][3] = graph[3][2] = 1; // srinidhi - raja
    graph[2][5] = graph[5][2] = 1; // srinidhi - yuktha
    graph[3][4] = graph[4][3] = 1; // raja - riya
    graph[3][5] = graph[5][3] = 1; // raja - yuktha

    int index = getUserIndex(inputName);
    if (index == -1) {
        printf("[]\n");
        return 0;
    }

    int suggested[MAX_USERS] = {0};
    suggestFriendsBFS(index, suggested);

    printf("[");
    int first = 1;
    for (int i = 0; i < MAX_USERS; i++) {
        if (suggested[i]) {
            if (!first) printf(", ");
            printf("\"%s\"", users[i]);
            first = 0;
        }
    }
    printf("]\n");

    return 0;
}
