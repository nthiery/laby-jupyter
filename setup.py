import os
from setuptools import setup
import glob

setup(
    name='laby',
    version='0.0.1',
    description='Laby-Jupyter: Learn programming, playing with ants and spider webs ;-) In Jupyter :-)',
    url='https://github.com/nthiery/laby-jupyter/',
    author='Nicolas M. Thiéry',
    author_email='nthiery@users.sf.net',
    license='GPLv2+',
    classifiers=[
        'Development Status :: 3 - Alpha',
        #'Intended Audience :: Science/Research'
        #'Topic :: Software Development :: Build Tools',
        #'Topic :: Scientific/Engineering :: Mathematics',
        'License :: OSI Approved :: GNU General Public License (GPL)',
        #'Programming Language :: Python :: 2',
        #'Programming Language :: Python :: 3',
    ],
    packages=[],
    data_files=[
        # like `jupyter nbextension install --sys-prefix`
        ("share/laby/levels",               glob.glob("share/laby/levels/*.laby")),
        ("share/laby/tiles",                glob.glob("share/laby/tiles/*.svg")),
        ("include/laby",                    glob.glob("include/laby/*.hpp")),
    ],
)
