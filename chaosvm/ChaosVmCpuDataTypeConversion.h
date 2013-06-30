#if !defined(__CHAOSVM_CPU_DATA_TYPE_CONVERSION_H__)
#define __CHAOSVM_CPU_DATA_TYPE_CONVERSION_H__

__INLINE__ __byte __INTERNAL_FUNC__ INT8_TO_UINT8(__char Int8Value);
__INLINE__ __char __INTERNAL_FUNC__ UINT8_TO_INT8(__byte uInt8Value);
__INLINE__ __word __INTERNAL_FUNC__ INT16_TO_UINT16(__sword Int16Value);
__INLINE__ __sword __INTERNAL_FUNC__ UINT16_TO_INT16(__word uInt16Value);
__INLINE__ __dword __INTERNAL_FUNC__ INT32_TO_UINT32(__sdword Int32Value);
__INLINE__ __sdword __INTERNAL_FUNC__ UINT32_TO_INT32(__dword uInt32Value);
__INLINE__ __qword __INTERNAL_FUNC__ INT64_TO_UINT64(__sqword Int64Value);
__INLINE__ __sqword __INTERNAL_FUNC__ UINT64_TO_INT64(__qword uInt64Value);
__INLINE__ __sword __INTERNAL_FUNC__ INT8_TO_INT16(__char Int8Value);
__INLINE__ __sdword __INTERNAL_FUNC__ INT8_TO_INT32(__char Int8Value);
__INLINE__ __sqword __INTERNAL_FUNC__ INT8_TO_INT64(__char Int8Value);
__INLINE__ __char __INTERNAL_FUNC__ INT16_TO_INT8(__sword Int16Value);
__INLINE__ __sdword __INTERNAL_FUNC__ INT16_TO_INT32(__sword Int16Value);
__INLINE__ __sqword __INTERNAL_FUNC__ INT16_TO_INT64(__sword Int16Value);
__INLINE__ __char __INTERNAL_FUNC__ INT32_TO_INT8(__sdword Int32Value);
__INLINE__ __sword __INTERNAL_FUNC__ INT32_TO_INT16(__sdword Int32Value);
__INLINE__ __sqword __INTERNAL_FUNC__ INT32_TO_INT64(__sdword Int32Value);
__INLINE__ __char __INTERNAL_FUNC__ INT64_TO_INT8(__sqword Int64Value);
__INLINE__ __sword __INTERNAL_FUNC__ INT64_TO_INT16(__sqword Int64Value);
__INLINE__ __sdword __INTERNAL_FUNC__ INT64_TO_INT32(__sqword Int64Value);
__INLINE__ __word __INTERNAL_FUNC__ UINT8_TO_UINT16(__byte uInt8Value);
__INLINE__ __dword __INTERNAL_FUNC__ UINT8_TO_UINT32(__byte uInt8Value);
__INLINE__ __qword __INTERNAL_FUNC__ UINT8_TO_UINT64(__byte uInt8Value);
__INLINE__ __byte __INTERNAL_FUNC__ UINT16_TO_UINT8(__word uInt16Value);
__INLINE__ __dword __INTERNAL_FUNC__ UINT16_TO_UINT32(__word uInt16Value);
__INLINE__ __qword __INTERNAL_FUNC__ UINT16_TO_UINT64(__word uInt16Value);
__INLINE__ __byte __INTERNAL_FUNC__ UINT32_TO_UINT8(__dword uInt32Value);
__INLINE__ __word __INTERNAL_FUNC__ UINT32_TO_UINT16(__dword uInt32Value);
__INLINE__ __qword __INTERNAL_FUNC__ UINT32_TO_UINT64(__dword uInt32Value);
__INLINE__ __byte __INTERNAL_FUNC__ UINT64_TO_UINT8(__qword uInt64Value);
__INLINE__ __word __INTERNAL_FUNC__ UINT64_TO_UINT16(__qword uInt64Value);
__INLINE__ __dword __INTERNAL_FUNC__ UINT64_TO_UINT32(__qword uInt64Value);

#endif

