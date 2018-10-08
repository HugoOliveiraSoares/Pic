#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
SHELL=cmd.exe
# Adding MPLAB X bin directory to path
PATH:=C:/Microchip/MPLABX/mplab_ide/mplab_ide/modules/../../bin/:$(PATH)
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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED="${OBJECTDIR}/MDD File System/FSIO.o" "${OBJECTDIR}/MDD File System/SD-SPI.o" ${OBJECTDIR}/Delays.o "${OBJECTDIR}/SD Card.o"
POSSIBLE_DEPFILES="${OBJECTDIR}/MDD File System/FSIO.o.d" "${OBJECTDIR}/MDD File System/SD-SPI.o.d" ${OBJECTDIR}/Delays.o.d "${OBJECTDIR}/SD Card.o.d"

# Object Files
OBJECTFILES=${OBJECTDIR}/MDD\ File\ System/FSIO.o ${OBJECTDIR}/MDD\ File\ System/SD-SPI.o ${OBJECTDIR}/Delays.o ${OBJECTDIR}/SD\ Card.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH="C:\Program Files (x86)\Java\jre6/bin/"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC="C:\Microchip\mplabc32\v2.02\bin\pic32-gcc.exe"
# MP_BC is not defined
MP_AS="C:\Microchip\mplabc32\v2.02\bin\pic32-as.exe"
MP_LD="C:\Microchip\mplabc32\v2.02\bin\pic32-ld.exe"
MP_AR="C:\Microchip\mplabc32\v2.02\bin\pic32-ar.exe"
DEP_GEN=${MP_JAVA_PATH}java -jar "C:/Microchip/MPLABX/mplab_ide/mplab_ide/modules/../../bin/extractobjectdependencies.jar" 
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps
MP_CC_DIR="C:\Microchip\mplabc32\v2.02\bin"
# MP_BC_DIR is not defined
MP_AS_DIR="C:\Microchip\mplabc32\v2.02\bin"
MP_LD_DIR="C:\Microchip\mplabc32\v2.02\bin"
MP_AR_DIR="C:\Microchip\mplabc32\v2.02\bin"
# MP_BC_DIR is not defined

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/MDD\ File\ System/FSIO.o: MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MDD\ File\ System 
	@${RM} ${OBJECTDIR}/MDD\ File\ System/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MDD File System/FSIO.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MDD File System/FSIO.o.d" -o "${OBJECTDIR}/MDD File System/FSIO.o" "MDD File System/FSIO.c"  
	
${OBJECTDIR}/MDD\ File\ System/SD-SPI.o: MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MDD\ File\ System 
	@${RM} ${OBJECTDIR}/MDD\ File\ System/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MDD File System/SD-SPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MDD File System/SD-SPI.o.d" -o "${OBJECTDIR}/MDD File System/SD-SPI.o" "MDD File System/SD-SPI.c"  
	
${OBJECTDIR}/Delays.o: Delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Delays.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Delays.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Delays.o.d" -o ${OBJECTDIR}/Delays.o Delays.c  
	
${OBJECTDIR}/SD\ Card.o: SD\ Card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/SD\ Card.o.d 
	@${FIXDEPS} "${OBJECTDIR}/SD Card.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD Card.o.d" -o "${OBJECTDIR}/SD Card.o" "SD Card.c"  
	
else
${OBJECTDIR}/MDD\ File\ System/FSIO.o: MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MDD\ File\ System 
	@${RM} ${OBJECTDIR}/MDD\ File\ System/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MDD File System/FSIO.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MDD File System/FSIO.o.d" -o "${OBJECTDIR}/MDD File System/FSIO.o" "MDD File System/FSIO.c"  
	
${OBJECTDIR}/MDD\ File\ System/SD-SPI.o: MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/MDD\ File\ System 
	@${RM} ${OBJECTDIR}/MDD\ File\ System/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/MDD File System/SD-SPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MDD File System/SD-SPI.o.d" -o "${OBJECTDIR}/MDD File System/SD-SPI.o" "MDD File System/SD-SPI.c"  
	
${OBJECTDIR}/Delays.o: Delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Delays.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Delays.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Delays.o.d" -o ${OBJECTDIR}/Delays.o Delays.c  
	
${OBJECTDIR}/SD\ Card.o: SD\ Card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/SD\ Card.o.d 
	@${FIXDEPS} "${OBJECTDIR}/SD Card.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/SD Card.o.d" -o "${OBJECTDIR}/SD Card.o" "SD Card.c"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1 
else
dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/012_-_SDCARD_FAT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
