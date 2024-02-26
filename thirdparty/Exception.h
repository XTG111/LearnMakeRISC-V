#pragma once
#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <cstdint>
#include <iostream>

class Exception {
public:
    enum class Type {
        InstructionAddrMisaligned,
        InstructionAccessFault,
        IllegalInstruction,
        Breakpoint,
        LoadAccessMisaligned,
        LoadAccessFault,
        StoreAMOAddrMisaligned,
        StoreAMOAccessFault,
        EnvironmentCallFromUMode,
        EnvironmentCallFromSMode,
        EnvironmentCallFromMMode,
        InstructionPageFault,
        LoadPageFault,
        StoreAMOPageFault
    };

private:
    Type type;
    uint64_t value;

public:
    Exception(Type type, uint64_t value);

    friend std::ostream& operator<<(std::ostream& os, const Exception& ex);

    uint64_t getValue() const;

    uint64_t getCode() const;

    bool isFatal() const;
};

#endif //_EXCEPTION_H_
