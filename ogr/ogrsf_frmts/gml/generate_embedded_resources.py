#!/usr/bin/env python
# SPDX-License-Identifier: MIT
# Copyright (C) 2024 Even Rouault

import glob
import os

embedded_resources_gen1 = open(
    os.path.join(os.path.dirname(__file__), "embedded_resources_gen1.c"), "wt"
)
embedded_resources_gen2 = open(
    os.path.join(os.path.dirname(__file__), "embedded_resources_gen2.c"), "wt"
)

embedded_resources_gen1.write(
    "// File generated by generate_embedded_resources.py. DO NOT EDIT\n"
)
embedded_resources_gen2.write(
    "// File generated by generate_embedded_resources.py. DO NOT EDIT\n"
)

files = list(glob.glob(os.path.join(os.path.dirname(__file__), "data/*.gfs")))
files += list(glob.glob(os.path.join(os.path.dirname(__file__), "data/*.xml")))

for f in sorted(files):
    f = os.path.basename(f)
    c = f.replace(".", "_")
    embedded_resources_gen1.write(
        """
static const char %s [] = {
    #embed "data/%s"
            , 0
};
"""
        % (c, f)
    )
    embedded_resources_gen2.write("""{ "%s", %s },\n""" % (f, c))

embedded_resources_gen1.close()
embedded_resources_gen2.close()
