INCLUDELIB kernel32.lib        ; 표준 Windows 라이브러리 링크

ExitProcess PROTO :DWORD       ; WinAPI: ExitProcess(UINT uExitCode);

.DATA
; 필요한 전역 변수 있으면 여기 선언

.CODE

main PROC                      ; 프로그램 엔트리 포인트

    ; Win64 호출 규약: 함수 호출 전에 스택을 16바이트 정렬해야 함
    sub     rsp, 28h           ; shadow space + 정렬

    xor     ecx, ecx           ; ECX/RCX = 0 (종료 코드 0)
    call    ExitProcess        ; ExitProcess(0) 호출 → 여기서 반환되지 않음

    ; ExitProcess는 돌아오지 않지만, 형식상 정리 코드 (실제로는 실행 안 됨)
    add     rsp, 28h
    ret

main ENDP

END
