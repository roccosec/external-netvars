#include <Windows.h>
#include <iostream>
#include <string>

#define CURL_STATICLIB 
#include <curl/curl.h>
#include <regex>
#include <curl/json.hpp>
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "Crypt32")
#pragma comment(lib, "wldap32")
#pragma comment(lib, "Normaliz")

using namespace std;

#include "api_handler.h"