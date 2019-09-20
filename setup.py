import os
from setuptools import setup
import glob

setup(
    name='laby',

    data_files=[
        # like `jupyter nbextension install --sys-prefix`
        ("share/jupyter/nbextensions/laby", glob.glob("data/tiles/*.svg")),
        ("share/laby",                      glob.glob("data/levels/*.laby")),
        ("include/laby",                    glob.glob("laby/*.hpp")),
    ],
)
