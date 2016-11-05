def array(a,b=none,c=none,d=none,e=none,f=none,g=none):
    if (b is none):
        return native rtl_allocatearray(a)
    elif (c is none):
        return native rtl_allocatearray(a,b)
    elif (d is none):
        return native rtl_allocatearray(a,b,c)
    elif (e is none):
        return native rtl_allocatearray(a,b,c,d)
    elif (f is none):
        return native rtl_allocatearray(a,b,c,d,e)
    elif (g is none):
        return native rtl_allocatearray(a,b,c,d,e,f)
    else:
        return native rtl_allocatearray(a,b,c,d,e,f,g)

def shared_mem_array(a,b=none,c=none,d=none,e=none,f=none,g=none):
    if (b is none):
        return native rtl_allocatesharedarray(a)
    elif (c is none):
        return native rtl_allocatesharedarray(a,b)
    elif (d is none):
        return native rtl_allocatesharedarray(a,b,c)
    elif (e is none):
        return native rtl_allocatesharedarray(a,b,c,d)
    elif (f is none):
        return native rtl_allocatesharedarray(a,b,c,d,e)
    elif (g is none):
        return native rtl_allocatesharedarray(a,b,c,d,e,f)
    else:
        return native rtl_allocatesharedarray(a,b,c,d,e,f,g)

def size(arr):
    dims=ndim(arr)
    if dims > 0:
        s=shape(arr)
        arraylength=1
        i=0
        while i<dims:
            arraylength*=s[i]
            i+=1
        return arraylength
    else:
        return 0

def freearray(arr):
    native rtl_free(arr)

def len(arr):
    return size(arr)

def ndim(arr):
    return native rtl_numdims(arr)

def shape(arr):
    i=ndim(arr)
    shape_val=[0]*i
    j=0
    while j<i:
        shape_val[j]=native rtl_dsize(arr, j)
        j+=1
    return shape_val

def nbytes(arr):
    return size(arr) * 4
