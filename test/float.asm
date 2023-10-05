add_func():
    push ebp
    mov ebp esp
    add 1 2
    pr acc
    ret
main():
    push ebp
    mov esp ebp
    mov edi 1
    call add_func()
    leave
