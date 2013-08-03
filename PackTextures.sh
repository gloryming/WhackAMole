#!/bin/sh

#  PackTextures.sh
#  WhackAMole
#
#  Created by 郭 一鸣 on 13-7-30.
#
TP="/usr/local/bin/TexturePacker"

if [ "${ACTION}" = "clean" ]
then
echo "cleaning..."

rm resources/background*
rm resources/foreground*
rm resources/sprites*

else
echo "building..."

${TP} --smart-update \
--format cocos2d \
--data Resources/hd/background.plist \
--sheet Resources/hd/background.pvr.ccz \
--dither-fs \
--opt RGB565 \
Art/background/*.png

${TP} --smart-update \
--format cocos2d \
--data Resources/sd/background.plist \
--sheet Resources/sd/background.pvr.ccz \
--dither-fs \
--scale 0.5 \
--opt RGB565 \
Art/background/*.png

${TP} --smart-update \
--format cocos2d \
--data Resources/hd/foreground.plist \
--sheet Resources/hd/foreground.pvr.ccz \
--dither-fs-alpha \
--opt RGBA4444 \
Art/foreground/*.png

${TP} --smart-update \
--format cocos2d \
--data Resources/sd/foreground.plist \
--sheet Resources/sd/foreground.pvr.ccz \
--dither-fs-alpha \
--scale 0.5 \
--opt RGBA4444 \
Art/foreground/*.png

${TP} --smart-update \
--format cocos2d \
--data Resources/hd/sprites.plist \
--sheet Resources/hd/sprites.pvr.ccz \
--dither-fs-alpha \
--opt RGBA4444 \
Art/sprites/*.png

${TP} --smart-update \
--format cocos2d \
--data Resources/sd/sprites.plist \
--sheet Resources/sd/sprites.pvr.ccz \
--dither-fs-alpha \
--scale 0.5 \
--opt RGBA4444 \
Art/sprites/*.png

fi
exit 0