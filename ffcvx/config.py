import os
import platform
from pathlib import Path
from packaging import version

PY_VERSION = version.parse(platform.python_version())

if PY_VERSION < version.parse('3.8'):
    import importlib_metadata
else:
    import importlib.metadata as importlib_metadata

NUMPY_VERSION = version.parse(importlib_metadata.version('numpy'))
NUMBA_VERSION = version.parse(importlib_metadata.version('numba'))
FFCVX_VERSION = version.parse(importlib_metadata.version('ffcvx'))

# Cache location
FFCVX_CACHE_BASE = Path(os.path.expanduser(os.getenv("FFCVX_CACHE_BASE", "~/.cache/ffcvx")))
FFCVX_NUMBA_CACHE = Path(os.getenv("FFCVX_NUMBA_CACHE", FFCVX_CACHE_BASE/'numba'))
FFCVX_NUMBA_CACHE = FFCVX_NUMBA_CACHE/f'{PY_VERSION.major}.{PY_VERSION.minor}'
FFCVX_DATA_CACHE = Path(os.getenv("FFCVX_DATA_CACHER", FFCVX_CACHE_BASE/'data'))

# Use Numba cache
FFCVX_USE_NUMBA_CACHE = bool(os.getenv("FFCVX_USE_NUMBA_CACHE", False))
FFCVX_USE_NUMBA_OVERIDE = False

def prep_numba_cache(force_cache:bool = False):
    FFCVX_USE_NUMBA_OVERIDE = force_cache
    if FFCVX_USE_NUMBA_CACHE or FFCVX_USE_NUMBA_OVERIDE:
        FFCVX_NUMBA_CACHE.mkdir(parents=True, exist_ok=True)
        versions_path = FFCVX_NUMBA_CACHE/'versions'
        if versions_path.exists():
            cache_versions = versions_path.read_text()
        else:
            cache_versions = ''

        # Clear cache if FFCVX, NumPy, and/or Numba versions don't match
        current_versions = f'{FFCVX_VERSION} {NUMPY_VERSION} {NUMBA_VERSION}'
        if current_versions != cache_versions:
            for child in FFCVX_NUMBA_CACHE.glob('*'):
                if child.is_file():
                    child.unlink()

            versions_path.write_text(current_versions)

        os.environ['NUMBA_CACHE_DIR'] = str(FFCVX_NUMBA_CACHE)
