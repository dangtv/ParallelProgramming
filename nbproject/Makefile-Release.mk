#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Nhan2MatranMPI.o \
	${OBJECTDIR}/PhuongTrinhNhiet1D_C.o \
	${OBJECTDIR}/PhuongTrinhNhiet1D_C_openmpi.o \
	${OBJECTDIR}/PhuongTrinhNhiet2D.o \
	${OBJECTDIR}/PhuongTrinhNhiet2D_openmpi.o \
	${OBJECTDIR}/bai_tap_mot.o \
	${OBJECTDIR}/example_mpi.o \
	${OBJECTDIR}/example_temperature.o \
	${OBJECTDIR}/my_matrix_multiplication.o \
	${OBJECTDIR}/nhan2matran_MPI_Bcast_demo.o \
	${OBJECTDIR}/nhan2matran_MPI_Gather.o \
	${OBJECTDIR}/nhan2matran_MPI_Scatter_demo.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laptrinhsongsong

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laptrinhsongsong: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laptrinhsongsong ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Nhan2MatranMPI.o: Nhan2MatranMPI.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Nhan2MatranMPI.o Nhan2MatranMPI.c

${OBJECTDIR}/PhuongTrinhNhiet1D_C.o: PhuongTrinhNhiet1D_C.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PhuongTrinhNhiet1D_C.o PhuongTrinhNhiet1D_C.c

${OBJECTDIR}/PhuongTrinhNhiet1D_C_openmpi.o: PhuongTrinhNhiet1D_C_openmpi.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PhuongTrinhNhiet1D_C_openmpi.o PhuongTrinhNhiet1D_C_openmpi.c

${OBJECTDIR}/PhuongTrinhNhiet2D.o: PhuongTrinhNhiet2D.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PhuongTrinhNhiet2D.o PhuongTrinhNhiet2D.c

${OBJECTDIR}/PhuongTrinhNhiet2D_openmpi.o: PhuongTrinhNhiet2D_openmpi.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PhuongTrinhNhiet2D_openmpi.o PhuongTrinhNhiet2D_openmpi.c

${OBJECTDIR}/bai_tap_mot.o: bai_tap_mot.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bai_tap_mot.o bai_tap_mot.c

${OBJECTDIR}/example_mpi.o: example_mpi.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/example_mpi.o example_mpi.c

${OBJECTDIR}/example_temperature.o: example_temperature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/example_temperature.o example_temperature.cpp

${OBJECTDIR}/my_matrix_multiplication.o: my_matrix_multiplication.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/my_matrix_multiplication.o my_matrix_multiplication.c

${OBJECTDIR}/nhan2matran_MPI_Bcast_demo.o: nhan2matran_MPI_Bcast_demo.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nhan2matran_MPI_Bcast_demo.o nhan2matran_MPI_Bcast_demo.c

${OBJECTDIR}/nhan2matran_MPI_Gather.o: nhan2matran_MPI_Gather.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nhan2matran_MPI_Gather.o nhan2matran_MPI_Gather.c

${OBJECTDIR}/nhan2matran_MPI_Scatter_demo.o: nhan2matran_MPI_Scatter_demo.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nhan2matran_MPI_Scatter_demo.o nhan2matran_MPI_Scatter_demo.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laptrinhsongsong

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
