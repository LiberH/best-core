/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#ifndef __e200z4_PERIPHERALS_H__
#define __e200z4_PERIPHERALS_H__

#ifndef GADL_NO_ACTION

#include "types.h"
#include "action.h"

class arch;
class SERIAL0write : public writeAction {
	arch *m_arch;
public :
	SERIAL0write(arch *a) : writeAction(), m_arch(a) {};
	virtual ~SERIAL0write() {};
	virtual bool trigger(storage *, u8 , spyInfo *);
};

#endif //GADL_NO_ACTION

#endif