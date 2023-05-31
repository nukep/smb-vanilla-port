# Ghidra stuff

The SMB port uses Ghidra to decompile NES roms into C code. This project would not be possible without it.

While Ghidra can do a lot of work for us, NES games are unfortunately very non-trivial by Ghidra's standards. Getting a decompilation requires a lot of game-specific scripting and modifying the 6502 SLEIGH spec (SLEIGH is Ghidra's processor definition language to implement what a processor's instructions do).

## Setting up the Ghidra project

This works with a copy of the Super Mario Bros (NTSC) ROM.
SHA1 hash: ea343f4e445a9050d4b4fbac2c77d0693b1d0922

1. Copy the "6502smb" directory from "ghidra-processors" into Ghidra's "Ghidra/Processors" directory.
2. Create a project with File -> Import File. Select the ROM as the file. Set the language to "6502" with "smb" variant. In Options, choose any block name ("CODE" will work). Set the base address to 0x8000, file offset to 0x10, length to 0x8000. Uncheck both the "processor defined labels" options.
3. Open the project. If it asks to auto-analyze, choose "No".
4. In the Script Manager (Window -> Script Manager), find the "Manage Script Directories" tool-button and add the "ghidra-scripts" path.

## Run the scripts

There's a convenience script you can run: "smb_analyze.py".

This will run the required scripts in order.

NOTE to devs: smb-flow might raise varnode errors if the SLEIGH spec for the 6502 processor has been reloaded while Ghidra has been running. Restart Ghidra in this case.
