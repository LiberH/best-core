/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#include "instructionBase.h"
#include "arch.h"
#include <sstream>

using namespace std;

/** static information extracted from an instruction:
 *  * PC
 *  * mnemonic
 *  * size (in bytes)
 *  * instruction class
 *  * branch target.
 */

staticInfo *
e200z4_instruction::getStaticInfo (arch *_arch)
{
  staticInfo *i = new staticInfo ();
  
  i -> pc = this -> getInstructionPointer ();
  i -> mnemo = string (this -> mnemo ());
  i -> funct = string (this -> funct ());
  
  this -> execute (_arch);
  i -> write_regs; this -> lockDDCWriteRegs (i -> write_regs);
  i -> read_regs; this -> getDDCReadRegs (i -> read_regs);
  
  i -> is_branch = this -> isBranch ();
  i -> is_unknown = this -> isBranchStaticallyUnknown ();
  i -> do_link = this -> hasID_SP_Check ();
  i -> is_uncond = this -> isBranchUnconditional ();

  i -> test = -1;
  if (i -> is_branch  &&
      this -> hasID_bo() &&
      this -> hasID_bi())
    {
      int BO = this -> getBO();
      int BI = this -> getBI();
      int cr = BI / 4;
      int tt = BI - ((cr * 4) -1);
      bool cond = (((BO >> 3) & 0x01) == 1);
      
      if (cond)
	i -> test = tt;
      else
	i -> test = tt +4;
    }
  if (i -> is_branch  &&
     this -> hasID_z ())
    i -> test = 9;
  if (i -> is_branch  &&
     this -> hasID_nz ())
    i -> test = 10;
  if (i -> is_branch &&
      i -> is_uncond)
    i -> test = 0;

  i -> crfD = -1;
  if (this -> hasID_crfd())
    i -> crfD = this -> getcrfD();
  if (this -> hasID_bi())
    {
      int BI = this -> getBI();
      int cr = BI / 4;
      i -> crfD = cr;
    }
  
  _arch -> setProgramCounter (i -> pc + this -> size ());
  this -> detectBranch (_arch);
  i -> target = _arch -> programCounter ();
  
  i -> do_memory = false;
  #ifdef __P2AC_MEM__
  if (this -> m_memReg       != 0
  ||  this -> m_memOffset    != 0
  ||  this -> m_memRegOffset != 0)
    i -> do_memory = true;
  #endif
  
  return i;
}

