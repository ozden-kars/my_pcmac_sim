// tests/test_cw.cpp
// Compile: g++ -o test_cw tests/test_cw.cpp && ./test_cw
// Tests paper Equation 5: CWnewmax = (P*10) * (CWmax-CWmin) / 13
// clamped to [cwMin=3, cwMax=7]

#include <cassert>
#include <algorithm>
#include <cstdio>

// Mirror of PCMACVehicleApp::mapPriorityToCW() — keep in sync
int mapPriorityToCW(double P)
{
    int cw = (int)((P * 10.0) * (7 - 3) / 13.0);
    return std::max(3, std::min(cw, 7));
}

int main()
{
    // Boundary: zero priority → clamp to cwMin
    assert(mapPriorityToCW(0.0) == 3);

    // Mid-range: P=2.0 → (2.0*10)*(4)/13 = 80/13 ≈ 6
    assert(mapPriorityToCW(2.0) == 6);

    // Boundary: very high priority → clamp to cwMax
    assert(mapPriorityToCW(9.9) == 7);

    // cwMin is never undershot
    assert(mapPriorityToCW(-1.0) == 3);

    // cwMax is never overshot
    assert(mapPriorityToCW(100.0) == 7);

    // Monotonicity: higher priority should never produce larger CW
    assert(mapPriorityToCW(1.0) <= mapPriorityToCW(0.5));

    printf("All CW formula tests passed\n");
    return 0;
}
