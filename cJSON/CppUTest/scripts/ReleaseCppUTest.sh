#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
#/bin/sh -x
#source in release generator script

if [ ! -d "scripts" ]; then
  echo "You have to run this script from the CPPUTEST_HOME directory!";
  exit
fi

GENERATED_FILES=""
release_dir=Releases
scripts_dir=scripts
version=v2.4a
zip_root=CppUTest-${version}
zip_file=${zip_root}.zip

exitIfFileExists() {
  if [ -e $1 ]
    then 
      echo "${1} already exists, exiting."
      exit
  fi
}

generateMakeScript() {
    filename=$1
    dateTime=$2
    version=$3
    target=$4
    exitIfFileExists $filename.sh
    echo "#Generated file - ${filename}.sh"  >$filename.sh
    echo "echo \"Running ${filename} for CppUTest ${version} created on ${dateTime}\"" >>$filename.sh
    echo "export CPPUTEST_HOME=\$(pwd)" >>$filename.sh
    echo "echo \"export CPPUTEST_HOME=\$(pwd)/\"" >>$filename.sh
    echo "make $target" >>$filename.sh

    chmod +x $filename.sh
    GENERATED_FILES+=" $filename.sh"
}

generateVersionFile() {
    version=$1
    dateTime=$2
    versionFile=version.txt
    echo "CppUTest ${version} created on ${dateTime}" > $versionFile
    GENERATED_FILES+=$versionFile
}

zipIt() {
    mkdir -p ${release_dir}
    zip -r ${release_dir}/${zip_file} \
           $GENERATED_FILES \
           .\
           -x@${scripts_dir}/zipExclude.txt
}

cleanUp() {
    rm -f $GENERATED_FILES
}

generateCppUTestRelease() {
    dateTime=$(date +%F-%H-%M)
    generateVersionFile $version $dateTime
    generateMakeScript makeAll $dateTime $version everythingInstall
    generateMakeScript cleanAll $dateTime  $version cleanEverythingInstall
    zipIt $version
    cleanUp
}

openAndMakeRelease()
{
    cd ${release_dir}
    rm -rf ${zip_root}
    unzip ${zip_file} -d ${zip_root}
    cd ${zip_root}
    ./makeAll.sh
    cd ../..
}


#Main
generateCppUTestRelease
openAndMakeRelease
