#pragma once

// constants (INF and EPS may need to be modified)
// If so, define INF or EPS as macros before
// including the headers that use it

constexpr ld PI = acos(-1);

#ifdef EPS
    constexpr ld __temp_EPS = EPS;
    #undef EPS
    constexpr ld EPS = __temp_EPS;
#else
    constexpr ld EPS = 1e-12;
#endif

#ifdef INF
    constexpr ld __temp_INF = EPS;
    #undef INF
    constexpr ld INF = __temp_INF;
#else
    constexpr ld INF = 1e20;
#endif
