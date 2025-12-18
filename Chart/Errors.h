#ifndef ERRORS_H
#define ERRORS_H

#include "Types.h"

#define MAKE_ERROR(code) \
    ((RESULT) (((ULONG)1<<31) | ((ULONG)(code))))

#define RESULT_MASK_CODE(code)  \
    (((RESULT)0xFFFF) & (code))

#define SUCCEDED(Result) ((RESULT)(Result) == 0)
#define FAILED(Result) ((RESULT)(Result) < 0)


// Успешное завершение
const RESULT S_OK = 0;
const RESULT S_TRUE = S_OK;

// Успешное завершение с кодом false
const RESULT S_FALSE = 1;


QString ErrorToString(RESULT code);

//******************Ошибки Global************************
// Обращение не к проинициализированному объекту
const RESULT E_UNINITIALIZED = MAKE_ERROR(1000);

// Метод не реализован
const RESULT E_NOTIMPL = MAKE_ERROR(1001);

// Ошибка в параметрах метода
const RESULT E_INVALIDARG = MAKE_ERROR(1002);

// Ошибка создания дескриптора шины
const RESULT E_BUS_HANDLE = MAKE_ERROR(1003);




#endif // ERRORS_H
