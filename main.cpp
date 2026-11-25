// @author piercer
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    const size_t MB = 64;
    const char* tmp = "piercer_bench_tmp.bin";
    std::vector<char> buf(MB * 1024 * 1024, 0x5A);

    auto t0 = std::chrono::high_resolution_clock::now();
    {
        std::ofstream out(tmp, std::ios::binary);
        out.write(buf.data(), buf.size());
        out.flush();
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    {
        std::ifstream in(tmp, std::ios::binary);
        in.read(buf.data(), buf.size());
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::remove(tmp);

    double wSec = std::chrono::duration<double>(t1 - t0).count();
    double rSec = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "=== Piercer Disk I/O Benchmark (" << MB << " MB) ===\n";
    std::cout << "Write: " << (MB / wSec) << " MB/s\n";
    std::cout << "Read : " << (MB / rSec) << " MB/s\n";
    return 0;
}
