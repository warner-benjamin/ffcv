import ctypes
from enum import Enum
from numba import njit
import numpy as np
import platform
from ctypes import CDLL, c_int64, c_uint8, c_uint64, POINTER, c_void_p, c_ubyte, c_uint32, c_bool, c_double, c_int, cdll
import ffcvx._libffcv

lib = CDLL(ffcvx._libffcv.__file__)
if platform.system() == "Windows":
    libc = cdll.msvcrt
    read_c = libc._read
else:
    libc = cdll.LoadLibrary('libc.so.6')
    read_c = libc.pread

#---------------------------------------------------------------------------------------

read_c.argtypes = [c_uint32, c_void_p, c_uint64, c_uint64]

def read(fileno:int, destination:np.ndarray, offset:int):
    return read_c(fileno, destination.ctypes.data, destination.size, offset)

#---------------------------------------------------------------------------------------

ctypes_cv_resize = lib.cv_resize
ctypes_cv_resize.argtypes = 11 * [c_int64]

def resize_crop_cv(source, start_row, end_row, start_col, end_col, destination):
    ctypes_cv_resize(0,
                  source.ctypes.data,
                  source.shape[0], source.shape[1],
                  start_row, end_row, start_col, end_col,
                  destination.ctypes.data,
                  destination.shape[0], destination.shape[1])

#---------------------------------------------------------------------------------------

class IppInterpolation(Enum):
    Nearest = 1
    Linear = 2
    Cubic = 4
    Super = 8
    Lanczos = 16

np_types_to_ipp = {
    np.int8: 3,
    np.uint8: 1,
    np.int16: 7,
    np.uint16: 5,
    np.int32: 11,
    np.uint32: 9,
    np.int64: 17,
    np.uint64: 15,
    np.float32: 13,
    np.float64: 19,
}

ctypes_ipp_resize = lib.ipp_resize
ctypes_ipp_resize.argtypes = [c_int, POINTER(c_ubyte), POINTER(c_ubyte), c_int, c_int,
                              c_int, c_int, c_int, c_int, c_int, c_int, c_double]
ctypes_ipp_resize.restype = c_int

def resize_crop_ipp(source:np.ndarray,
                    start_row:int,
                    end_row:int,
                    start_col:int,
                    end_col:int,
                    destination:np.ndarray,
                    antialiasing:bool,
                    interpolation:IppInterpolation
                ):
    source = source[start_row:end_row, start_col:end_col]
    status = ctypes_ipp_resize(np_types_to_ipp.get(source.dtype, -1), source.ctypes.data_as(POINTER(c_ubyte)),
                               destination.ctypes.data_as(POINTER(c_ubyte)), source.shape[0], source.shape[1],
                               destination.shape[0], destination.shape[0], source.shape[2], int(antialiasing),
                               interpolation.value, 6, 0)
    if status == 0:
        pass # No errors
    elif status == -221:
        raise Exception("FFCVX IPP Error: Error when loading the dynamic library.")
    elif status == -15:
        raise Exception("FFCVX IPP Error: Incorrect value for string length.")
    elif status == -14:
        raise Exception("FFCVX IPP Error: The requested mode is currently not supported.")
    elif status == -13:
        raise Exception("FFCVX IPP Error: Context parameter does not match the operation.")
    elif status == -12:
        raise Exception("FFCVX IPP Error: Scale bounds are out of range.")
    elif status == -11:
        raise Exception("FFCVX IPP Error: Argument is out of range, or point is outside the image.")
    elif status == -10:
        raise Exception("FFCVX IPP Error: An attempt to divide by zero.")
    elif status == -9:
        raise Exception("FFCVX IPP Error: Memory allocated for the operation is not enough.")
    elif status == -8:
        raise Exception("FFCVX IPP Error: Null pointer error.")
    elif status == -7:
        raise Exception("FFCVX IPP Error: Incorrect values for bounds: the lower bound is greater than the upper bound.")
    elif status == -6:
        raise Exception("FFCVX IPP Error: Incorrect value for data size.")
    elif status == -5:
        raise Exception("FFCVX IPP Error: Incorrect arg/param of the function.")
    elif status == -4:
        raise Exception("FFCVX IPP Error: Not enough memory for the operation.")
    elif status == -2:
        raise Exception("FFCVX IPP Error: Unknown/unspecified error.")
    elif status == 1:
        raise Exception("FFCVX IPP Error: No operation has been executed.")
    elif status == 2:
        raise ZeroDivisionError("FFCVX IPP Error: Zero value(s) for the divisor in the Div function.")
    elif status == 43:
        raise OSError("FFCVX IPP Error: Cannot load required library, waterfall is used.")
    elif status == 44:
        raise NotImplementedError("FFCVX IPP Error: Operation is not supported for the configuration.")
    else:
        raise Exception("FFCVX IPP Error: Unknown IPP status code.")

#---------------------------------------------------------------------------------------

# Extract and define the interface of imdeocde
ctypes_imdecode = lib.imdecode
ctypes_imdecode.argtypes = [
    c_void_p, c_uint64, c_uint32, c_uint32, c_void_p, c_uint32, c_uint32,
    c_uint32, c_uint32, c_uint32, c_uint32, c_bool, c_bool
]

def imdecode(source: np.ndarray, dst: np.ndarray,
             source_height: int, source_width: int,
             crop_height=None, crop_width=None,
             offset_x=0, offset_y=0, scale_factor_num=1, scale_factor_denom=1,
             enable_crop=False, do_flip=False):
    return ctypes_imdecode(source.ctypes.data, source.size,
                           source_height, source_width, dst.ctypes.data,
                           crop_height, crop_width, offset_x, offset_y, scale_factor_num, scale_factor_denom,
                           enable_crop, do_flip)

#---------------------------------------------------------------------------------------

ctypes_memcopy = lib.my_memcpy
ctypes_memcopy.argtypes = [c_void_p, c_void_p, c_uint64]

def memcpy(source: np.ndarray, dest: np.ndarray):
    return ctypes_memcopy(source.ctypes.data, dest.ctypes.data, source.size*source.itemsize)


ctypes_ipp_resize = lib.ipp_resize
ctypes_ipp_resize.argtypes = [c_void_p, c_void_p, c_uint64]