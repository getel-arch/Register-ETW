#include <windows.h>
#include <stdio.h>
#include <evntrace.h>
#include <evntcons.h>
#include <ole2.h>
#include <initguid.h> // Added for CLSIDFromString and GUID

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "advapi32.lib")

#define PROCESS_TRACE_CREATE_OPCODE 1
#define PROCESS_PROVIDER_GUID L"{22FB2CD6-0E7B-422B-A0C7-2FAD1FD0E716}"

VOID WINAPI ProcessEventCallback(PEVENT_RECORD eventRecord) {
    if (eventRecord->EventHeader.EventDescriptor.Opcode == PROCESS_TRACE_CREATE_OPCODE) {
        WCHAR* imageName = (WCHAR*)(eventRecord->UserData + sizeof(ULONG64) + sizeof(ULONG));
        if (wcsstr(imageName, L"calc.exe") != NULL) {
            printf("Calculator process created!\n");
        }
    }
}

int main() {
    ULONG status = ERROR_SUCCESS;
    TRACEHANDLE hTrace = 0;
    EVENT_TRACE_LOGFILE trace = {0};
    GUID providerGuid;

    // Use proper wide string handling
    WCHAR loggerName[] = L"Microsoft-Windows-Kernel-Process";

    CLSIDFromString(PROCESS_PROVIDER_GUID, &providerGuid);

    trace.LoggerName = loggerName;  // Now using proper WCHAR array
    trace.ProcessTraceMode = PROCESS_TRACE_MODE_REAL_TIME | PROCESS_TRACE_MODE_EVENT_RECORD;
    trace.EventRecordCallback = ProcessEventCallback;

    hTrace = OpenTrace(&trace);
    if (hTrace == INVALID_PROCESSTRACE_HANDLE) {
        printf("Failed to open trace. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("Monitoring for calculator process creation...\n");
    printf("Press Ctrl+C to stop\n");

    status = ProcessTrace(&hTrace, 1, NULL, NULL);
    if (status != ERROR_SUCCESS) {
        printf("ProcessTrace failed with %lu\n", status);
    }

    CloseTrace(hTrace);
    return 0;
}
