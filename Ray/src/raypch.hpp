#ifndef _RAY_PCH_H_
#define _RAY_PCH_H_

#include "Platform/Util/PlatformDetection.hpp"

#if defined(RAY_PLATFORM_WINDOWS64) || defined(RAY_PLATFORM_WINDOWS32)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <memory>
#elif defined(RAY_PLATFORM_LINUX)
#include <bits/stdc++.h>
#endif

#endif