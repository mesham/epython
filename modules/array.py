def array(a,b=none,c=none,d=none,e=none,f=none,g=none):
    if (b is none):
        dim ret[a]
        return ret
    elif (c is none):
        dim ret[a,b]
        return ret
    elif (d is none):
        dim ret[a,b,c]
        return ret
    elif (e is none):
        dim ret[a,b,c,d]
        return ret
    elif (f is none):
        dim ret[a,b,c,d,e]
        return ret
    elif (g is none):
        dim ret[a,b,c,d,e,f]
        return ret
    else:
        dim ret[a,b,c,d,e,f,g]
        return ret

def shared_mem_array(a,b=none,c=none,d=none,e=none,f=none,g=none):
    if (b is none):
        sdim ret[a]
        return ret
    elif (c is none):
        sdim ret[a,b]
        return ret
    elif (d is none):
        sdim ret[a,b,c]
        return ret
    elif (e is none):
        sdim ret[a,b,c,d]
        return ret
    elif (f is none):
        sdim ret[a,b,c,d,e]
        return ret
    elif (g is none):
        sdim ret[a,b,c,d,e,f]
        return ret
    else:
        sdim ret[a,b,c,d,e,f,g]
        return ret

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
