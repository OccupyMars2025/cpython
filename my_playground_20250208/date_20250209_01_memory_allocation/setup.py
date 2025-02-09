from setuptools import setup, Extension

module = Extension(
    'custom_allocator',
    sources=['custom_allocator.c']
)

setup(
    name='custom_allocator',
    version='1.0',
    description='Custom memory allocator for Python',
    ext_modules=[module]
)
