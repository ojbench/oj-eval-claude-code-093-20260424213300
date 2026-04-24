#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

struct State {
    int x, y, dir;
    bool operator<(const State& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return dir < other.dir;
    }
};

int main() {
    vector<vector<int>> grid(10, vector<int>(10));
    int pacman_x = -1, pacman_y = -1;

    // Read the grid
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 4) {
                pacman_x = i;
                pacman_y = j;
                grid[i][j] = 1; // Convert start position to empty space
            }
        }
    }

    // Directions: 0=up, 1=right, 2=down, 3=left
    // dx and dy for movement
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    // Right-hand rule: priority order for each current direction
    // For each direction, we try: right, straight, left, back
    int priority[4][4] = {
        {1, 0, 3, 2}, // current=up: right, up, left, down
        {2, 1, 0, 3}, // current=right: down, right, up, left
        {3, 2, 1, 0}, // current=down: left, down, right, up
        {0, 3, 2, 1}  // current=left: up, left, down, right
    };

    int x = pacman_x, y = pacman_y;
    int dir = 0; // Start moving up
    int score = 0;
    set<State> visited;

    // Main simulation loop
    while (true) {
        // Check if we've been in this state before (infinite loop detection)
        State current = {x, y, dir};
        if (visited.count(current)) {
            cout << "Silly Pacman" << endl;
            return 0;
        }
        visited.insert(current);

        // Check current cell
        if (grid[x][y] == 2) {
            score += 2;
            grid[x][y] = 1; // Eat the dot
        } else if (grid[x][y] == 3) {
            score -= 500;
            cout << score << endl;
            return 0;
        }

        // Try to move according to right-hand rule
        bool moved = false;
        for (int i = 0; i < 4; i++) {
            int next_dir = priority[dir][i];
            int nx = x + dx[next_dir];
            int ny = y + dy[next_dir];

            // Check bounds and if we can move (not a wall)
            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && grid[nx][ny] != 0) {
                x = nx;
                y = ny;
                dir = next_dir;
                moved = true;
                break;
            }
        }

        if (!moved) {
            // No valid moves (shouldn't happen in valid input)
            cout << score << endl;
            return 0;
        }
    }

    return 0;
}