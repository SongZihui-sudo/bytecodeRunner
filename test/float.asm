test_func():
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    add ebp, 1
    mov [acc], 0.992
    add [acc], edi
    pr acc
    sub esp, 16
    mov esp, acc
    pop ebp
    ret
main():
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    mov edi, 0.345
    cmp edi, 0
    jne  22
    call test_func()
    sub esp, 16
    mov esp, acc
    pop ebp
    leave
    ret
