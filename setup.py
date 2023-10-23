# python3 -m venv .venv
# source .venv/bin/activate
# pip install -e .
from setuptools import Extension, setup


def main():
    setup(
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
