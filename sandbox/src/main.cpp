#include <iostream>
#include <inMemoryInterface/InMemoryInterface.h>
#include <testSupport/ObservableCore.h>
#include <nvmCore/RegisterTypes.h>

int main(int argc, char** argv) {
    nvm::Interface::Ptr iface(new nvm::InMemoryInterface(1024));
    nvm::Options::Ptr options(new nvm::Options());
    nvm::ObservableCore core;
    core.initialize(iface, options);
    core.reset();

    /*
    Set up for something like:

    int j = 0;
    for(int i = 0; i < 10; i++) {
        j += 2;
    }
    */

    nvm::address_t address = 0;
    iface->write(address++, nvm::Instruction::SetLiteral);                //
    iface->write<int8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00); //SET i80 0 //j
    iface->write(address++, 0);                                           //

    iface->write(address++, nvm::Instruction::SetLiteral);                //
    iface->write<int8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x01); //SET i81 0 //i
    iface->write(address++, 0);                                           //

    iface->write(address++, nvm::Instruction::SetLiteral);                //
    iface->write<int8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x02); //SET i82 10 //constant for 10
    iface->write(address++, 10);                                          //

    iface->write(address++, nvm::Instruction::SetLiteral);                //
    iface->write<int8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x03); //SET i83 2 //constant for 2
    iface->write(address++, 2);                                           //

    iface->write(address++, nvm::Instruction::SetLiteral);                //
    iface->write<int8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x04); //SET i84 1 //constant for 1 (this is why we need an increment!)
    iface->write(address++, 1);                                           //

    auto loopStart = address; //save loop label address

    iface->write(address++, nvm::Instruction::Add);                        //
    iface->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x00); //ADD i80 i80 i83 //j += 2
    iface->write<uint8_t>(address++, 0x03);                                //

    iface->write(address++, nvm::Instruction::Add);                        //
    iface->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x01); //ADD i81 i81 i84 // i++
    iface->write<uint8_t>(address++, (0x01 << 4) | 0x04);                  //

    iface->write(address++, nvm::Instruction::Subtract);                   //
    iface->write<uint8_t>(address++, (nvm::RegisterType::i8 << 4) | 0x05); //SUB i85 i81 i82 // test i < 10
    iface->write<uint8_t>(address++, (0x01 << 4) | 0x02);                  //

    iface->write(address++, nvm::Instruction::Jump);  //
    iface->write(address++, 0x40);                    //JMP N loopStart //loop if less than 10
    iface->write<nvm::address_t>(address, loopStart); //
    address += 2;

    while (core.getInstructionPointer() < address) {
        auto error = core.process();
        if(error) {
            std::cout << "Error!" << std::endl;
            return -1;
        }
    }

    std::cout << "done!" << std::endl;
    std::cout << "i80: " << (int)core.getI8Register(0) << std::endl;

    return 0;
}
