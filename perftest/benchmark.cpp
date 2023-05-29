//
// Created by Kenneth Balslev on 28/04/2023.
//

#include <KSteam.hpp>
#include <benchmark/benchmark.h>

#include <random>

auto init = [](double pres, double temp) {

    using namespace KSteam;

    auto T = KSteam::calcPropertyPT(pres, temp, "T");
    auto P  = KSteam::calcPropertyPT(pres, temp, "P");
    auto V  = KSteam::calcPropertyPT(pres, temp, "V");
    auto H  = KSteam::calcPropertyPT(pres, temp, "H");
    auto S  = KSteam::calcPropertyPT(pres, temp, "S");
    auto Cp = KSteam::calcPropertyPT(pres, temp, "Cp");
    auto U  = KSteam::calcPropertyPT(pres, temp, "U");

    return std::vector<double>{T, P, V, H, S, Cp, U};
};

static void BM_FlashPT_H(benchmark::State& state) {

    std::random_device rd;
    std::mt19937 mt_generator(rd());

    // Set up a uniform distribution for the desired range [0, 99]
    std::uniform_int_distribution<int> distribution(0, 99);

    // Generate a random integer using the Mersenne Twister generator and the distribution

    double pres = 1.0e+05;
    double result {};

    for (auto _ : state) {
        state.PauseTiming();
        int i = distribution(mt_generator);
        state.ResumeTiming();

        result = KSteam::calcPropertyPT(pres, i + 273.16, "H");
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_FlashPT_H)->Unit(benchmark::kMillisecond);

static void BM_FlashPH_T(benchmark::State& state) {

    std::random_device rd;
    std::mt19937 mt_generator(rd());

    // Set up a uniform distribution for the desired range [0, 99]
    std::uniform_int_distribution<int> distribution(0, 99);

    // Generate a random integer using the Mersenne Twister generator and the distribution

    double pres = 1.0e+05;
    double result {};

    for (auto _ : state) {
        state.PauseTiming();
        int i = distribution(mt_generator);
        auto init_vector = init(pres, i + 273.16);
        state.ResumeTiming();

        result = KSteam::calcPropertyPH(pres, init_vector[3], "T");
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_FlashPH_T)->Unit(benchmark::kMillisecond);

static void BM_FlashPS_T(benchmark::State& state) {

    std::random_device rd;
    std::mt19937 mt_generator(rd());

    // Set up a uniform distribution for the desired range [0, 99]
    std::uniform_int_distribution<int> distribution(0, 99);

    // Generate a random integer using the Mersenne Twister generator and the distribution

    double pres = 1.0e+05;
    double result {};

    for (auto _ : state) {
        state.PauseTiming();
        int i = distribution(mt_generator);
        auto init_vector = init(pres, i + 273.16);
        state.ResumeTiming();

        result = KSteam::calcPropertyPS(pres, init_vector[4], "T");
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_FlashPS_T)->Unit(benchmark::kMillisecond);

static void BM_FlashPV_T(benchmark::State& state) {

    std::random_device rd;
    std::mt19937 mt_generator(rd());

    // Set up a uniform distribution for the desired range [0, 99]
    std::uniform_int_distribution<int> distribution(0, 99);

    // Generate a random integer using the Mersenne Twister generator and the distribution

    double pres = 1.0e+05;
    double result {};

    for (auto _ : state) {
        state.PauseTiming();
        int i = distribution(mt_generator);
        auto init_vector = init(pres, i + 273.16);
        state.ResumeTiming();

        result = KSteam::calcPropertyPV(pres, init_vector[2], "T");
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_FlashPV_T)->Unit(benchmark::kMillisecond);

static void BM_FlashPU_T(benchmark::State& state) {

    std::random_device rd;
    std::mt19937 mt_generator(rd());

    // Set up a uniform distribution for the desired range [0, 99]
    std::uniform_int_distribution<int> distribution(0, 99);

    // Generate a random integer using the Mersenne Twister generator and the distribution

    double pres = 1.0e+05;
    double result {};

    for (auto _ : state) {
        state.PauseTiming();
        int i = distribution(mt_generator);
        auto init_vector = init(pres, i + 273.16);
        state.ResumeTiming();

        result = KSteam::calcPropertyPU(pres, init_vector[6], "T");
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_FlashPU_T)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();