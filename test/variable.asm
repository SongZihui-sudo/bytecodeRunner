main():
    let tmp1, 99
    let tmp2, 100
    push ebp
    mov ebp, esp
    add esp, 16
    mov esp, acc
    add tmp1, tmp2
    pr acc
    sub esp, 16
    mov esp, acc
    pop ebp
    leave
    ret
