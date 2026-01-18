# Bitboard Chess Engine

A high-performance, low-latency chess move generation engine written in C++. This project implements a fully bitwise architecture using **64-bit Bitboards** and **Magic Bitboard Hashing**, achieving search throughput of **>20 Million Nodes Per Second (NPS)** on a single core.

### 🚀 Technical Highlights
* **Architecture:** Zero-array board representation. The entire game state is encoded in 12 `uint64_t` integers, maximizing CPU cache locality and allowing parallel move computation via bitwise intrinsics (`AND`, `XOR`, `__builtin_ctz`).
* **O(1) Attack Lookups:** Implemented **Magic Bitboards**—a perfect hashing technique that maps sliding piece occupancy variations to pre-computed attack masks. This eliminates expensive ray-casting loops, reducing lookup complexity to constant time.
* **Branchless Optimization:** utilized `popcount` and `LSB` hardware instructions to iterate over pieces without conditional branching, minimizing pipeline flushes.
* **Correctness:** Validated against the standard `Perft` (Performance Test) suite, ensuring strict adherence to FIDE rules across 100M+ positions (including edge cases like en passant, castling rights, and double-checks).

---

### ⚡ Performance Benchmarks
The engine includes a custom benchmarking tool (`perft`) that traverses the move tree to a fixed depth to measure raw throughput.

| Depth | Nodes Visited | Time (ms) | Nodes/Sec (NPS) |
| :--- | :--- | :--- | :--- |
| 4 | 197,281 | ~10ms | ~19,000,000 |
| 5 | 4,865,609 | ~240ms | ~20,200,000 |
| 6 | 119,060,324 | ~5,900ms | ~20,100,000 |

*(Benchmarks run on Apple M-Series / Standard x64 Architecture)*

---

### 🛠️ Build & Run
The project has zero external dependencies and compiles with any standard C++ compiler (Clang/GCC).

**1. Clone the Repository**
```bash
git clone [https://github.com/YOUR_USERNAME/bitboard-chess-engine.git](https://github.com/YOUR_USERNAME/bitboard-chess-engine.git)
cd bitboard-chess-engine
