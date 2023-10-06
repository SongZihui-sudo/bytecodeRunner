add_func():
    push ebp
    mov ebp esp
    add edi 2
    pr acc
    pop ebp
    ret
main():
    push ebp
    mov ebp esp
    mov edi 1
    call add_func()
    pop ebp
    leave
    ret
