#pragma once
#include <windows.h>

// call: HRESULT ��ȯ �Լ� ȣ��
// msg : ���� �� ����� C-string
#define HR_CHECK(hr, msg)                         \
        if (FAILED(hr)) {                                \
            OutputDebugString(msg);                     \
            return;                                      \
        }                                                
