#include "EmuApplication.hpp"

int main(int argc, char *argv[])
{
    EmuApplication emu;
    emu.qtapp = std::make_unique<QApplication>(argc, argv);

    QGuiApplication::setDesktopFileName("snes9x-gtk");

    emu.config = std::make_unique<EmuConfig>();
    emu.config->setDefaults();
    emu.config->loadFile(EmuConfig::findConfigFile());

    emu.input_manager = std::make_unique<SDLInputManager>();
    emu.window = std::make_unique<EmuMainWindow>(&emu);
    emu.window->show();

    emu.updateBindings();
    emu.startIdleLoop();
    emu.qtapp->exec();

    emu.config->saveFile(EmuConfig::findConfigFile());

    return 0;
}