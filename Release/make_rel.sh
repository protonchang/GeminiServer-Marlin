new file mode 100755
@@ -0,0 +1,50 @@
#!/bin/bash

echo "## ## ## ##"
echo " FIRMWARE RELEASE - Create folder and copy release files"
echo "## ## ## ##"
echo ""
echo "Hi, "$USER""
echo "Please enter the release version to copy to the Release folder!"
echo "i.e.: 2.0.6004 --> "
read version

if [ ! -z $version ]; then
  cpy_path=$PWD/$version-REL

  BUILD_NAME_vg3r_skr=4MAX-vg3r-SKR
  BUILD_NAME_7of9_skr=4MAX-7of9-SKR
  BUILD_NAME_vg3r=4MAX-vg3r
  BUILD_NAME_7of9=4MAX-7of9
  BUILD_NAME_DefD=4MAX-Default
  BUILD_NAME_DefE=4MAX-Default-EN

  FIRMWARE_vg3r_skr=../.pio/build/$BUILD_NAME_vg3r_skr/firmware.bin
  FIRMWARE_7of9_skr=../.pio/build/$BUILD_NAME_7of9_skr/firmware.bin
  FIRMWARE_vg3r=../.pio/build/$BUILD_NAME_vg3r/firmware.hex
  FIRMWARE_7of9=../.pio/build/$BUILD_NAME_7of9/firmware.hex
  FIRMWARE_default=../.pio/build/$BUILD_NAME_DefD/firmware.hex
  FIRMWARE_default_en=../.pio/build/$BUILD_NAME_DefE/firmware.hex

  TARGET_vg3r_skr=$cpy_path/$BUILD_NAME_vg3r_skr-$version-REL.bin
  TARGET_7of9_skr=$cpy_path/$BUILD_NAME_7of9_skr-$version-REL.bin
  TARGET_vg3r=$cpy_path/$BUILD_NAME_vg3r-$version-REL.hex
  TARGET_7of9=$cpy_path/$BUILD_NAME_7of9-$version-REL.hex
  TARGET_default=$cpy_path/$BUILD_NAME_DefD-$version-REL.hex
  TARGET_default_en=$cpy_path/$BUILD_NAME_DefE-$version-REL.hex
  

if [ ! -d "$version-REL" ]; then mkdir $version-REL; else echo "The folder $version-REL already exist. No need to create!"; fi

echo "Starting copy...";
if [ -f $FIRMWARE_vg3r_skr ];   then cp $FIRMWARE_vg3r_skr   $TARGET_vg3r_skr;   echo "Copy $TARGET_vg3r_skr";   else echo "ERROR - File $FIRMWARE_vg3r_skr does not exist. Pleaser check your BUILD folder or ensure you build all release files!"; fi
if [ -f $FIRMWARE_7of9_skr ];   then cp $FIRMWARE_7of9_skr   $TARGET_7of9_skr;   echo "Copy $TARGET_7of9_skr";   else echo "ERROR - File $FIRMWARE_7of9_skr does not exist. Pleaser check your BUILD folder or ensure you build all release files!"; fi
if [ -f $FIRMWARE_vg3r ];       then cp $FIRMWARE_vg3r       $TARGET_vg3r;       echo "Copy $TARGET_vg3r";       else echo "ERROR - File $FIRMWARE_vg3r does not exist. Pleaser check your BUILD folder or ensure you build all release files!"; fi
if [ -f $FIRMWARE_7of9 ];       then cp $FIRMWARE_7of9       $TARGET_7of9;       echo "Copy $TARGET_7of9";       else echo "ERROR - File $FIRMWARE_7of9 does not exist. Pleaser check your BUILD folder or ensure you build all release files!"; fi
if [ -f $FIRMWARE_default ];    then cp $FIRMWARE_default    $TARGET_default;    echo "Copy $TARGET_default";    else echo "ERROR - File $FIRMWARE_default does not exist. Pleaser check your BUILD folder or ensure you build all release files!"; fi
if [ -f $FIRMWARE_default_en ]; then cp $FIRMWARE_default_en $TARGET_default_en; echo "Copy $TARGET_default_en"; else echo "ERROR - File $FIRMWARE_default_en does not exist. Pleaser check your BUILD folder or ensure you build all release files!"; fi

echo "Done!"
else 
 echo "Canceled - You must enter a valid version number!"
fi
No newline at end of file
