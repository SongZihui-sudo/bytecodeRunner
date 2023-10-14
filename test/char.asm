main():
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    add ebp, 1
    mov [acc], 'a'
    add ebp, 2
    mov [acc], 'b'
    ps
    sub esp, 16
    mov esp, acc
    pop ebp
    leave
    ret
