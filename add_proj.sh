#!/bin/sh

templateName=cpp_template
templateDir=../cpp-template/src/$templateName

newProj=$1
if [[ -n $newProj ]] ; then
    sedRegex="s/$templateName/$newProj/g"
    newProjDir=src/$newProj
    mkdir $newProjDir
    for file in $templateDir/* ; do
        filename=$(basename $file)
        destFileName=$(echo $filename | sed $sedRegex)
        sed $sedRegex $file > $newProjDir/$destFileName
    done
else
    echo Enter a non-empty project name.
fi
