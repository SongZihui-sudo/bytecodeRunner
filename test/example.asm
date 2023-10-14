add_func():
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    add edi, 2
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
    mov edi, 1
    call add_func()
    sub esp, 16
    mov esp, acc
    pop ebp
    leave
    ret
