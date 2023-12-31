#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "port.h"
#include "type.h"
#include "gdt.h"

class InterruptMan
{
protected:
    struct GateDescriptor
    {
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerAddressHighBits;
    } __attribute__((packed));

    static GateDescriptor interruptDescriptorTable[256];

    static void SetInterruptDescriptorTableEntry(
        uint8_t interruptNum,
        uint16_t gdt_codeSegmentorOffset,
        void (*handler)(),
        uint8_t DescriptorPrivilegeLevel,
        uint8_t DescriptorType
    );

    Port8BitSlow picMasterCommand;
    Port8BitSlow picMasterData;
    Port8BitSlow picSlaveCommand;
    Port8BitSlow picSlaveData;

public:
    InterruptMan(GlobalDescriptorTable* gdt);
    ~InterruptMan();

    void Activate();

    static uint32_t handleInterrupt(uint8_t interruptNum, uint32_t esp);
    static void IgnoreInterruptRequest();
    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
};

#endif
