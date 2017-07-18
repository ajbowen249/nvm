#ifndef __REGISTERTYPES_H__
#define __REGISTERTYPES_H__

namespace nvm {
	enum RegisterCategory {
		GeneralPurpose = 0x0,
		System = 0x8
	};

	enum RegisterType {
		i8 = 0x0,
		ui8 = 0x1,
		i16 = 0x2,
		ui16 = 0x3,
		i32 = 0x4,
		ui32 = 0x5,
		f32 = 0x6,
		f64 = 0x7
	};
}

#endif //__REGISTERTYPES_H__
