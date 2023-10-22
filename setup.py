# python3 -m venv .venv
# source .venv/bin/activate
# python setup.py install
from distutils.core import setup, Extension


def main():
    setup(
        name="screenshot",
        version="0.0.1",
        description="Python interface for taking a screenshot image",
        author="Bruno Cabral",
        author_email="cabral.brc@gmail.com",
        ext_modules=[
            Extension(
                name="screenshot",
                sources=["screenshotmodule.cpp"],
                include_dirs=["/usr/include/python3.11"],
                libraries=["X11"],
            )
        ],
    )


if __name__ == "__main__":
    main()
