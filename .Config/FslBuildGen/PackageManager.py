#!/usr/bin/env python3

#****************************************************************************************************************************************************
# Copyright (c) 2014 Freescale Semiconductor, Inc.
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
#    * Neither the name of the Freescale Semiconductor, Inc. nor the names of
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

from typing import Dict
from typing import List
from FslBuildGen.Config import Config
from FslBuildGen.DataTypes import PackageType
from FslBuildGen.Exceptions import DependencyNotFoundException
from FslBuildGen.Exceptions import InternalErrorException
from FslBuildGen.Exceptions import InvalidDependencyException
from FslBuildGen.Exceptions import UsageErrorException
from FslBuildGen.Packages.Package import Package
from FslBuildGen.Packages.Package import PackageDependency
from FslBuildGen.Xml.XmlGenFile import XmlGenFile


def _AllocatePackage(config: Config, genFile: XmlGenFile) -> Package:
    return Package(config, genFile)


class PackageManager(object):
    def __init__(self, config: Config, platformName: str, genFiles: List[XmlGenFile]) -> None:
        super(PackageManager, self).__init__()
        self.__PackageFactoryFunction = _AllocatePackage
        uniqueDict = {}  # type: Dict[str, Package]
        for genFile in genFiles:
            if not genFile.Name in uniqueDict:
                uniqueDict[genFile.Name] = self.__PackageFactoryFunction(config, genFile)
            else:
                raise InternalErrorException("Package has been defined multiple times, this ought to have been caught earlier")

        self.OriginalPackageDict = uniqueDict
        self.Packages = list(uniqueDict.values())  # type: List[Package]

        # Resolve dependency package names -> actual package objects
        for package in self.Packages:
            self.__ResolvePackageDependencies(platformName, package)


    def CreatePackage(self, config: Config, platformName: str, genFile: XmlGenFile, insertAtFront: bool = False) -> Package:
        if genFile.Name in self.OriginalPackageDict:
            raise UsageErrorException("Package '{0}' already exist".format(genFile.Name))
        package = self.__PackageFactoryFunction(config, genFile)
        self.__ResolvePackageDependencies(platformName, package)
        if not insertAtFront:
            self.Packages.append(package)
        else:
            self.Packages.insert(0, package)
        self.OriginalPackageDict[package.Name] = package
        return package


    def __ResolvePackageDependencies(self, platformName: str, package: Package) -> None:
        for dep in package.GetDirectDependencies(platformName):
            if not dep.Name in self.OriginalPackageDict:
                raise DependencyNotFoundException(package.Name, dep.Name)
            elif package.Type != PackageType.TopLevel and not self.OriginalPackageDict[dep.Name].AllowDependencyOnThis:
                raise InvalidDependencyException(package.Name, dep.Name)
            else:
                resolvedDep = PackageDependency(self.OriginalPackageDict[dep.Name], dep.Access)
                package.ResolvedDirectDependencies.append(resolvedDep)
