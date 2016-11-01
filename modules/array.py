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

def freearray(arr):
    EPY_I_FREE arr

def size(arr):
    return len(arr)

def ndim(arr):
    return EPY_I_DIMS(arr)

def shape(arr):
    i=EPY_I_DIMS(arr)
    shape_val=[0]*i
    j=0
    while j<i:
        shape_val[j]=EPY_I_DSIZE(arr, j)
        j+=1
    return shape_val

def nbytes(arr):
    return size(arr) * 4
