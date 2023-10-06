main():
    let tmp1 99
    let tmp2 100
    push ebp
    mov ebp esp
    add tmp1 tmp2
    pr acc
    pop ebp
    leave
    ret
