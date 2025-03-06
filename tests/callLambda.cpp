#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "gmock-win32.h"
#include <Windows.h>
#include <commdlg.h>

// 'reinterpret_cast': pointer truncation from 'HANDLE' to 'DWORD'
#pragma warning( disable: 4311 )
// cast to smaller integer type 'unsigned long' from 'void *'
#ifdef __clang__
#	pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif // __clang__

MOCK_STDCALL_FUNC( BOOL, GetOpenFileNameW, OPENFILENAMEW* );

TEST(callLambda, OpenFileName) {
    ON_MODULE_FUNC_CALL(GetOpenFileNameW, ::testing::_).WillByDefault([](OPENFILENAMEW* pofn) {
        return true;
    });

    OPENFILENAMEW ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    EXPECT_TRUE(GetOpenFileNameW(&ofn));
}
