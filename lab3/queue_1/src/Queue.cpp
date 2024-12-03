#include "../include/Queue.hpp"

template <typename T>
Queue<T>::~Queue() {
  clear();
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
  Node* newNode = new Node(value);

  if (isEmpty()) {
    front_ = rear_ = newNode;
  } else {
    rear_->next = newNode;
    rear_ = newNode;
  }
  size_++;
}

template <typename T>
T Queue<T>::dequeue() {
  if (isEmpty()) {
    throw std::runtime_error("Cannot dequeue from empty queue");
  }

  Node* temp = front_;
  T value = front_->data;
  front_ = front_->next;
  delete temp;
  size_--;

  if (isEmpty()) {
    rear_ = nullptr;
  }

  return value;
}

template <typename T>
const T& Queue<T>::peek() const {
  if (isEmpty()) {
    throw std::runtime_error("Cannot peek empty queue");
  }
  return front_->data;
}

template <typename T>
void Queue<T>::clear() {
  while (!isEmpty()) {
    dequeue();
  }
}

template <typename T>
int Queue<T>::orangesRotting(std::vector<std::vector<int>>& grid) {
  if (grid.empty() || grid[0].empty()) return 0;

  int rows = grid.size();
  int cols = grid[0].size();
  int fresh = 0;
  Queue<std::pair<int, int>> rottenQueue;

  // Count fresh oranges and add rotten ones to queue
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 1)
        fresh++;
      else if (grid[i][j] == 2)
        rottenQueue.enqueue({i, j});
    }
  }

  if (fresh == 0) return 0;

  int minutes = 0;
  // Define directions: up, down, left, right
  // This part is needed because we need to check the neighbors of the rotten or not
  const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  while (!rottenQueue.isEmpty() && fresh > 0) {
    int size = rottenQueue.size();
    while (size--) {
      auto current = rottenQueue.dequeue();
      int row = current.first;
      int col = current.second;

      // Check all four directions
      for (int i = 0; i < 4; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
            grid[newRow][newCol] == 1) {
          grid[newRow][newCol] = 2;
          fresh--;
          rottenQueue.enqueue({newRow, newCol});
        }
      }
    }
    minutes++;
  }

  return fresh == 0 ? minutes : -1;
}

template <typename T>
int Queue<T>::leastInterval(std::vector<char>& tasks, int n) {
  // Count frequency of each task
  std::vector<int> freq(26, 0);
  for (char task : tasks) {
    freq[task - 'A']++;
  }

  // Find task with maximum frequency
  int maxFreq = 0;
  for (int f : freq) {
    if (f > maxFreq) {
      maxFreq = f;
    }
  }

  // Count how many tasks have the maximum frequency
  int maxCount = 0;
  for (int f : freq) {
    if (f == maxFreq) {
      maxCount++;
    }
  }

  // Calculate minimum units needed
  // Formula: max((maxFreq-1)*(n+1) + maxCount, tasks.size())
  int minUnits = (maxFreq - 1) * (n + 1) + maxCount;
  if (minUnits < static_cast<int>(tasks.size())) {  // static_cast is needed because sizetype is unsigned
    minUnits = static_cast<int>(tasks.size());
  }

  return minUnits;
}

template <typename T>
bool Queue<T>::jumpGame(std::vector<int>& nums) {
  if (nums.empty()) return false;

  Queue<size_t> positions;
  std::vector<bool> visited(nums.size(), false);

  positions.enqueue(0);
  visited[0] = true;

  while (!positions.isEmpty()) {
    size_t currentPos = positions.dequeue();

    // If we can reach the last index from here, return true
    if (currentPos >= nums.size() - 1) return true;

    // Try all possible jumps from current position
    for (int jump = 1; jump <= nums[currentPos]; jump++) {
      size_t nextPos = currentPos + jump;

      if (nextPos < nums.size() && !visited[nextPos]) {
        positions.enqueue(nextPos);
        visited[nextPos] = true;
      }
    }
  }

  return false;
}

// Explicit template instantiations
template class Queue<int>;
template class Queue<double>;
template class Queue<char>;
template class Queue<std::string>;
