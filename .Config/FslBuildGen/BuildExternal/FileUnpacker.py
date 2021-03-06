#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#****************************************************************************************************************************************************
# Copyright 2017 NXP
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    * Redistributions of source code must retain the above copyright notice,
#      this list of conditions and the following disclaimer.
#
#    * Redistributions in binary form must reproduce the above copyright notice,
#      this list of conditions and the following disclaimer in the documentation
#      and/or other materials provided with the distribution.
#
#    * Neither the name of the NXP. nor the names of
#      its contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#****************************************************************************************************************************************************

import tarfile
import zipfile

class FileUnpack(object):
    @staticmethod
    def UnpackZipFile(srcPath: str, dstPath: str) -> None:
        with zipfile.ZipFile(srcPath, 'r') as archive:
            archive.extractall(dstPath)


    @staticmethod
    def UnpackTarFile(srcPath: str, dstPath: str) -> None:
        with tarfile.open(srcPath, "r:") as archive:
            archive.extractall(dstPath)


    @staticmethod
    def UnpackTarGZFile(srcPath: str, dstPath: str) -> None:
        with tarfile.open(srcPath, "r:gz") as archive:
            archive.extractall(dstPath)


    @staticmethod
    def UnpackTarBz2File(srcPath: str, dstPath: str) -> None:
        with tarfile.open(srcPath, "r:bz2") as archive:
            archive.extractall(dstPath)


    @staticmethod
    def UnpackFile(filename: str, dstPath: str) -> None:
        fileNameId = filename.lower()
        if fileNameId.endswith(".zip"):
            FileUnpack.UnpackZipFile(filename, dstPath)
        elif fileNameId.endswith(".tar"):
            FileUnpack.UnpackTarFile(filename, dstPath)
        elif fileNameId.endswith(".tar.gz") or fileNameId.endswith(".tgz"):
            FileUnpack.UnpackTarGZFile(filename, dstPath)
        elif fileNameId.endswith(".tar.bz2"):
            FileUnpack.UnpackTarBz2File(filename, dstPath)
        else:
            raise Exception("Unsupported archive format '{0}'".format(filename))
