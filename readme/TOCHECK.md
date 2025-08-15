# IMPORTANT LIST TO TACKLE AFTER

1. Readability & Maintainability

Meaningful names: Classes, functions, variables.

Small functions: One function = one responsibility.

Consistent style: Indentation, naming, braces, etc.

Comment wisely: Explain why, not what.

2. Resource Management

RAII (Resource Acquisition Is Initialization): Wrap resources (memory, file handles, mutexes) in objects.

Prefer smart pointers (std::unique_ptr, std::shared_ptr) over raw pointers.

Avoid leaks, dangling pointers, and undefined behavior.

3. Performance Awareness

Avoid unnecessary copies (use references, move semantics).

Be careful with containers: know their complexity (vector vs list vs unordered_map).

Don’t optimize prematurely — profile first.

4. Error Handling & Safety

Use exceptions or optional types where appropriate (std::optional, std::expected in C++23).

Validate input arguments and invariants.

Don’t silently ignore errors.

5. Modularity & Coupling

Keep modules loosely coupled and highly cohesive.

Minimize dependencies between classes/modules.

Use interfaces (abstract classes) when you want flexibility or mocking.

6. Testing & Debuggability

Write unit tests and test edge cases.

Make code observable: logging, assertions, debug builds.

Prefer deterministic behavior to ease testing.

7. Const Correctness & Immutability

Mark functions const where they don’t modify state.

Prefer const & or const parameters where possible.

Reduces bugs and clarifies intent.

8. Encapsulation & Invariants

Keep internal data private/protected.

Expose minimal API necessary.

Protect class invariants — they should always be valid.

9. Dependency Management

Prefer composition over inheritance when possible.

Inject dependencies (dependency injection) instead of hardcoding them.

Avoid circular dependencies between modules.

10. Modern C++ Best Practices

Use range-based for loops when possible.

Prefer auto for readability (not everywhere — balance with clarity).

Use standard library algorithms (std::sort, std::find_if) instead of hand-rolled loops.