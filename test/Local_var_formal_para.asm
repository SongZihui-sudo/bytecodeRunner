test_func():
    push ebp
    mov ebp esp
    sub esp 0x10
    add ebp 1
    mov 32 [acc]
    add [acc] edi
    pr acc
    add esp 0x10
    pop ebp
    ret
main():
    push ebp
    mov ebp esp
    sub esp 0x10
    mov edi 1
    cmp edi 0
    jne  16
    call test_func()
    add esp 0x10
    pop ebp
    leave
    ret
