#pragma once
#include <windows.h>

// call: HRESULT 반환 함수 호출
// msg : 실패 시 출력할 C-string
#define HR_CHECK(hr, msg)                         \
        if (FAILED(hr)) {                                \
            OutputDebugString(msg);                     \
            return;                                      \
        }                                                
