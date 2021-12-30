#pragma once
#include <iostream>

#define LB_DEBUG(...) std::cout << "[DEBUG] " << __VA_ARGS__ <<  std::endl 
#define LB_INFO(...) std::cout << "[INFO] " << __VA_ARGS__ <<  std::endl 
#define LB_WARN(...) std::cout << "[WARN] " << __VA_ARGS__ <<  std::endl 
#define LB_ERROR(...) std::cout << "[ERROR] " << __VA_ARGS__ <<  std::endl 
