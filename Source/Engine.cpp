#include "Engine.h"
#include "Function.h"
#include <unordered_set>
#include <vector>

namespace Autograd {
void backward(const std::shared_ptr<Value> &loss) {
  // Initialize the topological sort containers
  std::vector<std::shared_ptr<Function>> topo;
  std::unordered_set<std::shared_ptr<Function>> visited;

  // Explicit stack for DFS
  // Stores: {Function pointer, children_processed_flag}
  std::vector<std::pair<std::shared_ptr<Function>, bool>> stack;

  // Start DFS if the loss node actually has a creator function
  if (loss && loss->creator) {
    stack.push_back({loss->creator, false});
  }

  // Run the Iterative DFS Loop to populate 'topo'
  while (!stack.empty()) {
    auto &[curr_func, children_processed] = stack.back();

    if (children_processed) {
      // All children of curr_func have been processed, we can add it to topo
      topo.push_back(curr_func);
      stack.pop_back();
    } else {
      // First time seeing curr_func, mark children as processed so that we
      // process its parent step next time
      children_processed = true;

      if (visited.find(curr_func) == visited.end()) {
        visited.insert(curr_func);

        // Go through all input Value nodes of this function
        for (const auto &input_val : curr_func->inputs) {
          // If input_val is Internal Node and the creator function has not been
          // visited, push it onto the stack
          if (input_val && input_val->creator) {
            if (visited.find(input_val->creator) == visited.end()) {
              stack.push_back({input_val->creator, false});
            }
          }
        }
      }
    }
  }

  // --- The Execution Pass ---
  // Seed the gradient of the loss node to 1.0
  if (loss) {
    loss->grad = 1.0;
  }

  for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
    auto &func = *it;

    // Upgrade the weak_ptr to a shared_ptr to safely access its data
    if (auto out_node = func->output.lock()) {
      // Pass the output's gradient to the function's backward method
      func->backward(out_node->grad);
    }
  }
}
} // namespace Autograd