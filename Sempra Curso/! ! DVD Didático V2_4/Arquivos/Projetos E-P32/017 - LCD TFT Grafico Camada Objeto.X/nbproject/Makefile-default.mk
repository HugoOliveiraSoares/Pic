#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Graphics/Button.o ${OBJECTDIR}/Graphics/Chart.o ${OBJECTDIR}/Graphics/CheckBox.o ${OBJECTDIR}/Graphics/DigitalMeter.o ${OBJECTDIR}/Graphics/DisplayDriver.o ${OBJECTDIR}/Graphics/EditBox.o ${OBJECTDIR}/Graphics/Fonts.o ${OBJECTDIR}/Graphics/GOL.o ${OBJECTDIR}/Graphics/GOLFontDefault.o ${OBJECTDIR}/Graphics/Grid.o ${OBJECTDIR}/Graphics/GroupBox.o ${OBJECTDIR}/Graphics/ListBox.o ${OBJECTDIR}/Graphics/Meter.o ${OBJECTDIR}/Graphics/Palette.o ${OBJECTDIR}/Graphics/Picture.o ${OBJECTDIR}/Graphics/Primitive.o ${OBJECTDIR}/Graphics/ProgressBar.o ${OBJECTDIR}/Graphics/RadioButton.o ${OBJECTDIR}/Graphics/RoundDial.o ${OBJECTDIR}/Graphics/Slider.o ${OBJECTDIR}/Graphics/StaticText.o ${OBJECTDIR}/Graphics/Template.o ${OBJECTDIR}/Graphics/TextEntry.o ${OBJECTDIR}/Graphics/TouchScroll.o ${OBJECTDIR}/Graphics/Window.o ${OBJECTDIR}/Graphics/CustomControlDemo.o ${OBJECTDIR}/main.o ${OBJECTDIR}/TouchScreen.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Graphics/Button.o.d ${OBJECTDIR}/Graphics/Chart.o.d ${OBJECTDIR}/Graphics/CheckBox.o.d ${OBJECTDIR}/Graphics/DigitalMeter.o.d ${OBJECTDIR}/Graphics/DisplayDriver.o.d ${OBJECTDIR}/Graphics/EditBox.o.d ${OBJECTDIR}/Graphics/Fonts.o.d ${OBJECTDIR}/Graphics/GOL.o.d ${OBJECTDIR}/Graphics/GOLFontDefault.o.d ${OBJECTDIR}/Graphics/Grid.o.d ${OBJECTDIR}/Graphics/GroupBox.o.d ${OBJECTDIR}/Graphics/ListBox.o.d ${OBJECTDIR}/Graphics/Meter.o.d ${OBJECTDIR}/Graphics/Palette.o.d ${OBJECTDIR}/Graphics/Picture.o.d ${OBJECTDIR}/Graphics/Primitive.o.d ${OBJECTDIR}/Graphics/ProgressBar.o.d ${OBJECTDIR}/Graphics/RadioButton.o.d ${OBJECTDIR}/Graphics/RoundDial.o.d ${OBJECTDIR}/Graphics/Slider.o.d ${OBJECTDIR}/Graphics/StaticText.o.d ${OBJECTDIR}/Graphics/Template.o.d ${OBJECTDIR}/Graphics/TextEntry.o.d ${OBJECTDIR}/Graphics/TouchScroll.o.d ${OBJECTDIR}/Graphics/Window.o.d ${OBJECTDIR}/Graphics/CustomControlDemo.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/TouchScreen.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Graphics/Button.o ${OBJECTDIR}/Graphics/Chart.o ${OBJECTDIR}/Graphics/CheckBox.o ${OBJECTDIR}/Graphics/DigitalMeter.o ${OBJECTDIR}/Graphics/DisplayDriver.o ${OBJECTDIR}/Graphics/EditBox.o ${OBJECTDIR}/Graphics/Fonts.o ${OBJECTDIR}/Graphics/GOL.o ${OBJECTDIR}/Graphics/GOLFontDefault.o ${OBJECTDIR}/Graphics/Grid.o ${OBJECTDIR}/Graphics/GroupBox.o ${OBJECTDIR}/Graphics/ListBox.o ${OBJECTDIR}/Graphics/Meter.o ${OBJECTDIR}/Graphics/Palette.o ${OBJECTDIR}/Graphics/Picture.o ${OBJECTDIR}/Graphics/Primitive.o ${OBJECTDIR}/Graphics/ProgressBar.o ${OBJECTDIR}/Graphics/RadioButton.o ${OBJECTDIR}/Graphics/RoundDial.o ${OBJECTDIR}/Graphics/Slider.o ${OBJECTDIR}/Graphics/StaticText.o ${OBJECTDIR}/Graphics/Template.o ${OBJECTDIR}/Graphics/TextEntry.o ${OBJECTDIR}/Graphics/TouchScroll.o ${OBJECTDIR}/Graphics/Window.o ${OBJECTDIR}/Graphics/CustomControlDemo.o ${OBJECTDIR}/main.o ${OBJECTDIR}/TouchScreen.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX775F512L
MP_LINKER_FILE_OPTION=,--script="app_hid_boot_PIC32MX775F512L.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Graphics/Button.o: Graphics/Button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Button.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Button.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Button.o.d" -o ${OBJECTDIR}/Graphics/Button.o Graphics/Button.c  
	
${OBJECTDIR}/Graphics/Chart.o: Graphics/Chart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Chart.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Chart.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Chart.o.d" -o ${OBJECTDIR}/Graphics/Chart.o Graphics/Chart.c  
	
${OBJECTDIR}/Graphics/CheckBox.o: Graphics/CheckBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/CheckBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/CheckBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/CheckBox.o.d" -o ${OBJECTDIR}/Graphics/CheckBox.o Graphics/CheckBox.c  
	
${OBJECTDIR}/Graphics/DigitalMeter.o: Graphics/DigitalMeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/DigitalMeter.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/DigitalMeter.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/DigitalMeter.o.d" -o ${OBJECTDIR}/Graphics/DigitalMeter.o Graphics/DigitalMeter.c  
	
${OBJECTDIR}/Graphics/DisplayDriver.o: Graphics/DisplayDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/DisplayDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/DisplayDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/DisplayDriver.o.d" -o ${OBJECTDIR}/Graphics/DisplayDriver.o Graphics/DisplayDriver.c  
	
${OBJECTDIR}/Graphics/EditBox.o: Graphics/EditBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/EditBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/EditBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/EditBox.o.d" -o ${OBJECTDIR}/Graphics/EditBox.o Graphics/EditBox.c  
	
${OBJECTDIR}/Graphics/Fonts.o: Graphics/Fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Fonts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Fonts.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Fonts.o.d" -o ${OBJECTDIR}/Graphics/Fonts.o Graphics/Fonts.c  
	
${OBJECTDIR}/Graphics/GOL.o: Graphics/GOL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/GOL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/GOL.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/GOL.o.d" -o ${OBJECTDIR}/Graphics/GOL.o Graphics/GOL.c  
	
${OBJECTDIR}/Graphics/GOLFontDefault.o: Graphics/GOLFontDefault.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/GOLFontDefault.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/GOLFontDefault.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/GOLFontDefault.o.d" -o ${OBJECTDIR}/Graphics/GOLFontDefault.o Graphics/GOLFontDefault.c  
	
${OBJECTDIR}/Graphics/Grid.o: Graphics/Grid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Grid.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Grid.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Grid.o.d" -o ${OBJECTDIR}/Graphics/Grid.o Graphics/Grid.c  
	
${OBJECTDIR}/Graphics/GroupBox.o: Graphics/GroupBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/GroupBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/GroupBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/GroupBox.o.d" -o ${OBJECTDIR}/Graphics/GroupBox.o Graphics/GroupBox.c  
	
${OBJECTDIR}/Graphics/ListBox.o: Graphics/ListBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/ListBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/ListBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/ListBox.o.d" -o ${OBJECTDIR}/Graphics/ListBox.o Graphics/ListBox.c  
	
${OBJECTDIR}/Graphics/Meter.o: Graphics/Meter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Meter.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Meter.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Meter.o.d" -o ${OBJECTDIR}/Graphics/Meter.o Graphics/Meter.c  
	
${OBJECTDIR}/Graphics/Palette.o: Graphics/Palette.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Palette.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Palette.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Palette.o.d" -o ${OBJECTDIR}/Graphics/Palette.o Graphics/Palette.c  
	
${OBJECTDIR}/Graphics/Picture.o: Graphics/Picture.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Picture.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Picture.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Picture.o.d" -o ${OBJECTDIR}/Graphics/Picture.o Graphics/Picture.c  
	
${OBJECTDIR}/Graphics/Primitive.o: Graphics/Primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Primitive.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Primitive.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Primitive.o.d" -o ${OBJECTDIR}/Graphics/Primitive.o Graphics/Primitive.c  
	
${OBJECTDIR}/Graphics/ProgressBar.o: Graphics/ProgressBar.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/ProgressBar.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/ProgressBar.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/ProgressBar.o.d" -o ${OBJECTDIR}/Graphics/ProgressBar.o Graphics/ProgressBar.c  
	
${OBJECTDIR}/Graphics/RadioButton.o: Graphics/RadioButton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/RadioButton.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/RadioButton.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/RadioButton.o.d" -o ${OBJECTDIR}/Graphics/RadioButton.o Graphics/RadioButton.c  
	
${OBJECTDIR}/Graphics/RoundDial.o: Graphics/RoundDial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/RoundDial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/RoundDial.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/RoundDial.o.d" -o ${OBJECTDIR}/Graphics/RoundDial.o Graphics/RoundDial.c  
	
${OBJECTDIR}/Graphics/Slider.o: Graphics/Slider.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Slider.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Slider.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Slider.o.d" -o ${OBJECTDIR}/Graphics/Slider.o Graphics/Slider.c  
	
${OBJECTDIR}/Graphics/StaticText.o: Graphics/StaticText.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/StaticText.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/StaticText.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/StaticText.o.d" -o ${OBJECTDIR}/Graphics/StaticText.o Graphics/StaticText.c  
	
${OBJECTDIR}/Graphics/Template.o: Graphics/Template.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Template.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Template.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Template.o.d" -o ${OBJECTDIR}/Graphics/Template.o Graphics/Template.c  
	
${OBJECTDIR}/Graphics/TextEntry.o: Graphics/TextEntry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/TextEntry.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/TextEntry.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/TextEntry.o.d" -o ${OBJECTDIR}/Graphics/TextEntry.o Graphics/TextEntry.c  
	
${OBJECTDIR}/Graphics/TouchScroll.o: Graphics/TouchScroll.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/TouchScroll.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/TouchScroll.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/TouchScroll.o.d" -o ${OBJECTDIR}/Graphics/TouchScroll.o Graphics/TouchScroll.c  
	
${OBJECTDIR}/Graphics/Window.o: Graphics/Window.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Window.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Window.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Window.o.d" -o ${OBJECTDIR}/Graphics/Window.o Graphics/Window.c  
	
${OBJECTDIR}/Graphics/CustomControlDemo.o: Graphics/CustomControlDemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/CustomControlDemo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/CustomControlDemo.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/CustomControlDemo.o.d" -o ${OBJECTDIR}/Graphics/CustomControlDemo.o Graphics/CustomControlDemo.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/TouchScreen.o: TouchScreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TouchScreen.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TouchScreen.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TouchScreen.o.d" -o ${OBJECTDIR}/TouchScreen.o TouchScreen.c  
	
else
${OBJECTDIR}/Graphics/Button.o: Graphics/Button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Button.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Button.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Button.o.d" -o ${OBJECTDIR}/Graphics/Button.o Graphics/Button.c  
	
${OBJECTDIR}/Graphics/Chart.o: Graphics/Chart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Chart.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Chart.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Chart.o.d" -o ${OBJECTDIR}/Graphics/Chart.o Graphics/Chart.c  
	
${OBJECTDIR}/Graphics/CheckBox.o: Graphics/CheckBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/CheckBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/CheckBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/CheckBox.o.d" -o ${OBJECTDIR}/Graphics/CheckBox.o Graphics/CheckBox.c  
	
${OBJECTDIR}/Graphics/DigitalMeter.o: Graphics/DigitalMeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/DigitalMeter.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/DigitalMeter.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/DigitalMeter.o.d" -o ${OBJECTDIR}/Graphics/DigitalMeter.o Graphics/DigitalMeter.c  
	
${OBJECTDIR}/Graphics/DisplayDriver.o: Graphics/DisplayDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/DisplayDriver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/DisplayDriver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/DisplayDriver.o.d" -o ${OBJECTDIR}/Graphics/DisplayDriver.o Graphics/DisplayDriver.c  
	
${OBJECTDIR}/Graphics/EditBox.o: Graphics/EditBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/EditBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/EditBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/EditBox.o.d" -o ${OBJECTDIR}/Graphics/EditBox.o Graphics/EditBox.c  
	
${OBJECTDIR}/Graphics/Fonts.o: Graphics/Fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Fonts.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Fonts.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Fonts.o.d" -o ${OBJECTDIR}/Graphics/Fonts.o Graphics/Fonts.c  
	
${OBJECTDIR}/Graphics/GOL.o: Graphics/GOL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/GOL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/GOL.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/GOL.o.d" -o ${OBJECTDIR}/Graphics/GOL.o Graphics/GOL.c  
	
${OBJECTDIR}/Graphics/GOLFontDefault.o: Graphics/GOLFontDefault.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/GOLFontDefault.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/GOLFontDefault.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/GOLFontDefault.o.d" -o ${OBJECTDIR}/Graphics/GOLFontDefault.o Graphics/GOLFontDefault.c  
	
${OBJECTDIR}/Graphics/Grid.o: Graphics/Grid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Grid.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Grid.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Grid.o.d" -o ${OBJECTDIR}/Graphics/Grid.o Graphics/Grid.c  
	
${OBJECTDIR}/Graphics/GroupBox.o: Graphics/GroupBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/GroupBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/GroupBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/GroupBox.o.d" -o ${OBJECTDIR}/Graphics/GroupBox.o Graphics/GroupBox.c  
	
${OBJECTDIR}/Graphics/ListBox.o: Graphics/ListBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/ListBox.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/ListBox.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/ListBox.o.d" -o ${OBJECTDIR}/Graphics/ListBox.o Graphics/ListBox.c  
	
${OBJECTDIR}/Graphics/Meter.o: Graphics/Meter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Meter.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Meter.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Meter.o.d" -o ${OBJECTDIR}/Graphics/Meter.o Graphics/Meter.c  
	
${OBJECTDIR}/Graphics/Palette.o: Graphics/Palette.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Palette.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Palette.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Palette.o.d" -o ${OBJECTDIR}/Graphics/Palette.o Graphics/Palette.c  
	
${OBJECTDIR}/Graphics/Picture.o: Graphics/Picture.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Picture.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Picture.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Picture.o.d" -o ${OBJECTDIR}/Graphics/Picture.o Graphics/Picture.c  
	
${OBJECTDIR}/Graphics/Primitive.o: Graphics/Primitive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Primitive.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Primitive.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Primitive.o.d" -o ${OBJECTDIR}/Graphics/Primitive.o Graphics/Primitive.c  
	
${OBJECTDIR}/Graphics/ProgressBar.o: Graphics/ProgressBar.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/ProgressBar.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/ProgressBar.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/ProgressBar.o.d" -o ${OBJECTDIR}/Graphics/ProgressBar.o Graphics/ProgressBar.c  
	
${OBJECTDIR}/Graphics/RadioButton.o: Graphics/RadioButton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/RadioButton.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/RadioButton.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/RadioButton.o.d" -o ${OBJECTDIR}/Graphics/RadioButton.o Graphics/RadioButton.c  
	
${OBJECTDIR}/Graphics/RoundDial.o: Graphics/RoundDial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/RoundDial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/RoundDial.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/RoundDial.o.d" -o ${OBJECTDIR}/Graphics/RoundDial.o Graphics/RoundDial.c  
	
${OBJECTDIR}/Graphics/Slider.o: Graphics/Slider.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Slider.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Slider.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Slider.o.d" -o ${OBJECTDIR}/Graphics/Slider.o Graphics/Slider.c  
	
${OBJECTDIR}/Graphics/StaticText.o: Graphics/StaticText.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/StaticText.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/StaticText.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/StaticText.o.d" -o ${OBJECTDIR}/Graphics/StaticText.o Graphics/StaticText.c  
	
${OBJECTDIR}/Graphics/Template.o: Graphics/Template.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Template.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Template.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Template.o.d" -o ${OBJECTDIR}/Graphics/Template.o Graphics/Template.c  
	
${OBJECTDIR}/Graphics/TextEntry.o: Graphics/TextEntry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/TextEntry.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/TextEntry.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/TextEntry.o.d" -o ${OBJECTDIR}/Graphics/TextEntry.o Graphics/TextEntry.c  
	
${OBJECTDIR}/Graphics/TouchScroll.o: Graphics/TouchScroll.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/TouchScroll.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/TouchScroll.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/TouchScroll.o.d" -o ${OBJECTDIR}/Graphics/TouchScroll.o Graphics/TouchScroll.c  
	
${OBJECTDIR}/Graphics/Window.o: Graphics/Window.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/Window.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/Window.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/Window.o.d" -o ${OBJECTDIR}/Graphics/Window.o Graphics/Window.c  
	
${OBJECTDIR}/Graphics/CustomControlDemo.o: Graphics/CustomControlDemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Graphics 
	@${RM} ${OBJECTDIR}/Graphics/CustomControlDemo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Graphics/CustomControlDemo.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Graphics/CustomControlDemo.o.d" -o ${OBJECTDIR}/Graphics/CustomControlDemo.o Graphics/CustomControlDemo.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/TouchScreen.o: TouchScreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/TouchScreen.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TouchScreen.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TouchScreen.o.d" -o ${OBJECTDIR}/TouchScreen.o TouchScreen.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=1024 
else
dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/017_-_LCD_TFT_Grafico_Camada_Objeto.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
