#!/usr/bin/env python
from setuptools import setup, Extension



# chasher = Extension('chasher',
#                      define_macros = [('MAJOR_VERSION', '0'),
#                                       ('MINOR_VERSION', '1')],
#                     include_dirs = ['/usr/local/include'],
#                     library_dirs = ['/usr/local/lib'],
#                     extra_compile_args = ['-I/usr/lib/x86_64-linux-gnu/glib-2.0/include', '-I/usr/include/glib-2.0'],
#                     sources = ['hasher.cpp', 'chasher.cpp'])


setup(name='pyhash',
      version = '0.1',
      description = 'Library to calculate multiple a MD5 hash.',
      author = 'Angelo Frangione',
      author_email = 'angelo.frangione@gmail.com',
      license = 'GPL-v2.0',
      py_modules=['pyhash'],
      install_requires = ['eventlet']
      # ext_modules = [chasher]
      )